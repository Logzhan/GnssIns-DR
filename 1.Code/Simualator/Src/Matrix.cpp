/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : Matrix.c
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.14
* Comments           : PDR矩阵运算库
********************************************************************************/
/* Header File Including -----------------------------------------------------*/
#include "Matrix.h"

/**---------------------------------------------------------------------
* Function    : MatrixTrans
* Description : 矩阵转置
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixTrans(double a[N][N], double r[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			r[i][j] = a[j][i];
		}
	}
}

/**---------------------------------------------------------------------
* Function    : VecMatMultiply
* Description : 向量和矩阵相乘 r = b * a
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VecMatMultiply(double a[N], double b[N][N], double r[N]) {
	int i, j;
	double temp[N] = { 0.0 };
	//for (i = 0; i < N; i++) {
	//	temp[i] = a[i];
	//}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			temp[i] += ((b[i][j] * 100) * (a[j] * 100)) / 10000;
		}
	}
	for (i = 0; i < N; i++) {
		r[i] = temp[i];
	}

}

/**---------------------------------------------------------------------
* Function    : MatrixMultiply
* Description : 矩阵和矩阵相乘 r = a * b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixMultiply(double a[N][N], double b[N][N], double r[N][N]) {
	int i, j, m;
	double temp[N][N] = { { 0.0 } };
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (m = 0; m < N; m++) {
				//temp[i][j] += a[j][m] * b[m][j];
				temp[i][j] += a[i][m] * b[m][j];
			}
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			r[i][j] = temp[i][j];
		}
	}
}

/**---------------------------------------------------------------------
* Function    : MatrixAdd
* Description : 矩阵和矩阵相加 r = a + b, 注意这个函数支持a = a + b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixAdd(double a[N][N], double b[N][N], double r[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			r[i][j] = a[i][j] + b[i][j];
		}
	}
}


/**---------------------------------------------------------------------
* Function    : VectorAdd
* Description : 向量和向量相加 r = a + b, 注意这个函数支持a = a + b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VectorAdd(double a[N], double b[N], double r[N]) {
	int i;
	for (i = 0; i < N; i++) {
		r[i] = a[i] + b[i];
	}
}

/**---------------------------------------------------------------------
* Function    : MatrixSub
* Description : 矩阵和矩阵相减 r = a - b, 注意这个函数支持a = a - b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixSub(double a[N][N], double b[N][N], double r[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			r[i][j] = a[i][j] - b[i][j];
		}
	}
}
/**---------------------------------------------------------------------
* Function    : VectorSub
* Description : 向量和向量相减 r = a - b, 注意这个函数支持a = a - b
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void VectorSub(double a[N], double b[N], double r[N]) {
	int i;
	for (i = 0; i < N; i++) {
		r[i] = a[i] - b[i];
	}
}

/**---------------------------------------------------------------------
* Function    : MatrixInverse
* Description : 求矩阵的逆矩阵
* Date        : 2022/09/14 logzhan
*---------------------------------------------------------------------**/
void MatrixInverse(double(*M)[N], double (*MInv)[N]) {

	double l[N][N] = { { 0.0 } };
	double u[N][N] = { { 0.0 } };
	double LInv[N][N] = { { 0.0 } };
	double UInv[N][N] = { { 0.0 } };
	double Temp[N][N] = { { 0.0 } };

	int i, j, k;
	double s;

	for (i = 0; i < N; i++)l[i][i] = 1;

	for (i = 0; i < N; i++){
		for (j = i; j <N; j++){
			s = 0;
			for (k = 0; k < i; k++){
				s += l[i][k] * u[k][j];
			}
			u[i][j] = M[i][j] - s;
		}
		for (j = i + 1; j < N; j++){
			s = 0;
			for (k = 0; k < i; k++){
				s += l[j][k] * u[k][i];
			}
			l[j][i] = (M[j][i] - s) / u[i][i];
		}
	}
	for (i = 0; i < N; i++)LInv[i][i] = 1;

	for (i = 1; i < N; i++){
		for (j = 0; j < i; j++){
			s = 0;
			for (k = 0; k < i; k++){
				s += l[i][k] * LInv[k][j];
			}
			LInv[i][j] = -s;
		}
	}
	for (i = 0; i < N; i++){
		UInv[i][i] = 1 / u[i][i];
	}
	for (i = 1; i < N; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			s = 0;
			for (k = j + 1; k <= i; k++)
			{
				s += u[j][k] * UInv[k][i];
			}
			UInv[j][i] = -s / u[j][j];
		}
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			for (k = 0; k < N; k++){
				Temp[i][j] += UInv[i][k] * LInv[k][j];
			}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			MInv[i][j] = Temp[i][j];
		}
	}
}