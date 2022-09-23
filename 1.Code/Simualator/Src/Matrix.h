#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PDR_MATRIX_H_
#define _PDR_MATRIX_H_

#define  N           4

/**---------------------------------------------------------------------
* Function    : MatrixTrans
* Description : 矩阵转置
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixTrans(double a[N][N], double r[N][N]);

/**---------------------------------------------------------------------
* Function    : VecMatMultiply
* Description : 向量和矩阵相乘 r = b * a
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VecMatMultiply(double a[N], double b[N][N], double r[N]);

/**---------------------------------------------------------------------
* Function    : MatrixMultiply
* Description : 矩阵和矩阵相乘 r = a * b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixMultiply(double a[N][N], double b[N][N], double r[N][N]);

/**---------------------------------------------------------------------
* Function    : MatrixAdd
* Description : 矩阵和矩阵相加 r = a + b, 注意这个函数支持a = a + b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixAdd(double a[N][N], double b[N][N], double r[N][N]);

/**---------------------------------------------------------------------
* Function    : VectorAdd
* Description : 向量和向量相加 r = a + b, 注意这个函数支持a = a + b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VectorAdd(double a[N], double b[N], double r[N]);

/**---------------------------------------------------------------------
* Function    : MatrixSub
* Description : 矩阵和矩阵相减 r = a - b, 注意这个函数支持a = a - b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixSub(double a[N][N], double b[N][N], double r[N][N]);

/**---------------------------------------------------------------------
* Function    : VectorSub
* Description : 向量和向量相减 r = a - b, 注意这个函数支持a = a - b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VectorSub(double a[N], double b[N], double r[N]);

/**---------------------------------------------------------------------
* Function    : MatrixInverse
* Description : 求矩阵的逆矩阵
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixInverse(double(*a)[N], double(*a_inv)[N]);

#endif

#ifdef __cplusplus
}
#endif