#ifndef  _PDR_QUATERNION_H_
#define  _PDR_QUATERNION_H_

#ifdef __cplusplus
extern "C" {
#endif

/**---------------------------------------------------------------------
* Function    : QuaternionNorm
* Description : 四元数归一化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternionNorm(float* q0, float* q1, float* q2, float* q3);

/**---------------------------------------------------------------------
* Function    : QuaternConj
* Description : 四元数求共轭四元数
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternConj(float qc[], float q[]);

/**---------------------------------------------------------------------
* Function    : QuaternProd
* Description : 四元数乘法
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void QuaternProd(float qab[], float qa[], float qb[]);

#ifdef __cplusplus
}
#endif

#endif