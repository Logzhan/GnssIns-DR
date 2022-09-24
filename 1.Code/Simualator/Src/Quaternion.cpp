#include "math.h"
#include "Quaternion.h"

const float FLT_THRES = 0.000001f;                    // 浮点数最小阈值

/**---------------------------------------------------------------------
* Function    : QuaternionNorm
* Description : 四元数归一化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternionNorm(float* q0, float* q1, float* q2, float* q3) {

	float norm = sqrtf(((*q0) * (*q0) + (*q1) * (*q1) +
		(*q2) * (*q2) + (*q3) * (*q3)));
	if (norm > FLT_THRES) {
		norm = 1 / norm;
		(*q0) *= norm;  (*q1) *= norm;
		(*q2) *= norm;  (*q3) *= norm;
	}
}

/**---------------------------------------------------------------------
* Function    : QuaternConj
* Description : 四元数求共轭四元数
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternConj(float qc[], float q[]) {
	qc[0] =  q[0];
	qc[1] = -q[1];
	qc[2] = -q[2];
	qc[3] = -q[3];
}

/**---------------------------------------------------------------------
* Function    : QuaternProd
* Description : 四元数乘法
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternProd(float qab[], float qa[], float qb[]) {
	qab[0] = qa[0] * qb[0] - qa[1] * qb[1] - qa[2] * qb[2] - qa[3] * qb[3];
	qab[1] = qa[0] * qb[1] + qa[1] * qb[0] + qa[2] * qb[3] - qa[3] * qb[2];
	qab[2] = qa[0] * qb[2] - qa[1] * qb[3] + qa[2] * qb[0] + qa[3] * qb[1];
	qab[3] = qa[0] * qb[3] + qa[1] * qb[2] - qa[2] * qb[1] + qa[3] * qb[0];
}