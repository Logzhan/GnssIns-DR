#include <string.h>
#include "Kalman.h"
#include "Matrix.h"

// 扩展卡尔曼向量缓存
static double EkfVecBuf[5][N] = { {0.0} };
// 扩展卡尔曼矩阵缓存
static double EkfMatBuf[7][N][N] = { { {0.0} } };

/**----------------------------------------------------------------------
* Function    : EKF_Init
* Description : 初始化卡尔曼滤波器相关
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void EKF_Init(void) {
	memset(EkfMatBuf, 0, sizeof(double) * 7 * N * N);
	memset(EkfVecBuf, 0, sizeof(double) * 5 * N);
}


/**----------------------------------------------------------------------
* Function    : EKFCalQRMatrix
* Description : 根据GPS信号特征调整卡尔曼滤波噪声矩阵，q矩阵是过程噪声矩阵，
*               需要跟惯导预测位置精度相关。r矩阵为GNSS观测噪声，跟GPS输出的
*               信息精度有关。
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void EKFCalQRMatrix() {
	memset(EkfMatBuf, 0, sizeof(double) * 7 * N * N);
	memset(EkfVecBuf, 0, sizeof(double) * 5 * N);
}

/**----------------------------------------------------------------------
* Function    : EKFStateUpdate
* Description : 扩展卡尔曼滤波器的状态更新方程
* Date        : 2020/7/22 logzhan
*---------------------------------------------------------------------**/
void EKFStateUpdate(EKFPara_t* kf) {
	double lambda = 0;

	// NxN矩阵定义
	double(*H)[N]     = (double(*)[N]) & (EkfMatBuf[0][0][0]);
	double(*I)[N]     = (double(*)[N]) & (EkfMatBuf[1][0][0]);
	double(*pvec1)[N] = (double(*)[N]) & (EkfMatBuf[2][0][0]);
	double(*Ht)[N]    = (double(*)[N]) & (EkfMatBuf[3][0][0]);
	double(*pvec3)[N] = (double(*)[N]) & (EkfMatBuf[4][0][0]);
	double(*pvec4)[N] = (double(*)[N]) & (EkfMatBuf[5][0][0]);
	double(*pv3)[N]   = (double(*)[N]) & (EkfMatBuf[6][0][0]);

	memset(EkfMatBuf, 0, sizeof(double) * 7 * N * N);
	memset(EkfVecBuf, 0, sizeof(double) * 5 * N);

	// Nx1向量定义
	double* z      = &(EkfVecBuf[0][0]);
	double(*pvec5) = &(EkfVecBuf[1][0]);
	double(*pvec6) = &(EkfVecBuf[2][0]);
	double(*pv1)   = &(EkfVecBuf[3][0]);
	double(*pv2)   = &(EkfVecBuf[4][0]);

	// 创建单位矩阵
	for (char i = 0; i < 4; i++) {
		H[i][i] = 1;
		I[i][i] = 1;
	}

	//z[0] = pgnss->xNed;                                          // 北向位置
	//z[1] = pgnss->yNed;                                          // 东向位置   
	//z[2] = 0.5;                                                  // 步长默认0.5
	//z[3] = pgnss->yaw * PI / 180;

		// 计算 K = K = PHt / (R + H*P*H^T)
	MatrixTrans(H, Ht);                                            // 计算Ht
	MatrixMultiply(H, kf->pPk, pvec1);                             // 计算HP
	MatrixMultiply(pvec1, Ht, pvec3);                              // pvec3 = H*P*H^T
	MatrixAdd(pvec3, kf->R, pvec4);                                // pvec4 = R + H*P*H^T
	MatrixInverse(pvec4, pvec1);                                   // 计算 1 / (R + H*P*H^T)

	for (char i = 0; i < N; i++) {
		for (char j = 0; j < N; j++) {
			pv3[i][j] = pvec3[i][j];
		}
	}

	MatrixMultiply(kf->pPk, Ht, pvec3);                            // 计算PHt
	MatrixMultiply(pvec3, pvec1, kf->Kk);                          // 计算增益K = PHt / (R + H*P*H^T)


	VecMatMultiply(kf->pXk, H, pvec5);                             // pvec5 = Hx'
	VectorSub(z, pvec5, pvec6);                                    // pvec6 = Z - Hx'
	//modAngle(&pvec6[3], -PI, PI);
	for (char i = 0; i < N; i++) {
		pv1[i] = pvec6[i];
	}

	VecMatMultiply(pvec6, kf->Kk, pvec5); // pvec5 = K*( z - Hx')
	// Get the optimally updated state estimation
	VectorAdd(kf->pXk, pvec5, kf->Xk);

	// pvec1 = K*H
	MatrixMultiply(kf->Kk, H, pvec1);
	// pvec2 = (I - K*H)
	MatrixSub(I, pvec1, Ht);
	// pvec3 = (I - K*H)*P
	MatrixMultiply(Ht, kf->pPk, pvec3);
	// pvec4 = (I- K*H)^T
	MatrixTrans(Ht, pvec4);
	// pvec1 = (I - K*H)*P*(I- K*H)^T
	MatrixMultiply(pvec3, pvec4, pvec1);

	// pvec2 = K*R
	MatrixMultiply(kf->Kk, kf->R, Ht);
	// pvec3 = K^T
	MatrixTrans(kf->Kk, pvec3);
	// pvec4 = K*R*K^T
	MatrixMultiply(Ht, pvec3, pvec4);
	// Get the updated estimate covariance: P' = (I - K*H)*P*(I- K*H)^T + K*R*K^T
	MatrixAdd(pvec1, pvec4, kf->Pk);

	// pv2 = (z - Hx')*( H*P*H^T )
	VecMatMultiply(pv1, pv3, pv2);
}

/**----------------------------------------------------------------------
* Function    : EKFUpdateInsState
* Description : 扩展卡尔曼滤波器更新INS状态
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
void EKFUpdateInsState() {
	
}