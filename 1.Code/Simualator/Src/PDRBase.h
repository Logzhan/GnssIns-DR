#ifndef  _PDR_BASE_H_
#define  _PDR_BASE_H_

#define ACCURACY_ERR_MAX                    1000                 // GPS的accuracy最大值,一般用于初始化用
#define N                                   4                    // 矩阵维数
#define MAX_NO_GPS_PREDICT                  10		             // 无GPS信息状态，最大位置推算数量			     


typedef struct {
	double xk[N];             // 系统状态变量  xk[0]: 北向x  xk[1]：东向y  xk[2]：步长  xk[3] ：航向角
	double p_xk[N];           // 最佳预测变量  xk[0]: 北向x  xk[1]：东向y  xk[2]：步长  xk[3] ：航向角
	double zk[N];
	double p_pk[N][N];
	double pk[N][N];
	double phi[N][N];
	double hk[N][N];
	double q[N][N];           // 卡尔曼滤波的Q矩阵(过程噪声)
	double r[N][N];           // 卡尔曼滤波R矩阵(观测噪声)
	double Kk[N][N];
	double lambda;
	double plat;
	double plon;
	double initHeading;
}EKFPara_t;

#endif // ! _PDR_BASE_H
