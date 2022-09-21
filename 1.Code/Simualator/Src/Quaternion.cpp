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
void QuaternConj(float _q[], float q[]) {
	_q[0] =  q[0];
	_q[1] = -q[1];
	_q[2] = -q[2];
	_q[3] = -q[3];
}

/**---------------------------------------------------------------------
* Function    : QuaternProd
* Description : 四元数乘法
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternProd(float ab[], float a[], float b[]) {
	ab[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
	ab[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
	ab[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
	ab[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
}