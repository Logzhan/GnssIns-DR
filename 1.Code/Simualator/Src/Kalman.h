#ifndef _PDR_KALMAN_H_
#define _PDR_KALMAN_H_

#include "PDRBase.h"

/**----------------------------------------------------------------------
* Function    : EKF_Init
* Description : ��ʼ���������˲������
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void EKF_Init(void);

/**----------------------------------------------------------------------
* Function    : EKFCalQRMatrix
* Description : ����GPS�ź����������������˲���������q�����ǹ�����������
*               ��Ҫ���ߵ�Ԥ��λ�þ�����ء�r����ΪGNSS�۲���������GPS�����
*               ��Ϣ�����йء�
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void EKFCalQRMatrix();

/**----------------------------------------------------------------------
* Function    : EKFStateUpdate
* Description : ��չ�������˲�����״̬���·���
* Date        : 2020/7/22 logzhan
*---------------------------------------------------------------------**/
void EKFStateUpdate(EKFPara_t* kf);

/**----------------------------------------------------------------------
* Function    : EKFUpdateInsState
* Description : ��չ�������˲�������INS״̬
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
void EKFUpdateInsState(void);

#endif