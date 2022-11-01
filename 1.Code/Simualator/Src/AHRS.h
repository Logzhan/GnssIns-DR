#ifndef  _PDR_AHRS_H_
#define  _PDR_AHRS_H_

#include "PDRBase.h"

#define AHRS_SAMPLE_FREQ                        100                   // ARHS算法的传感器采样频率   
#define AHRS_KP                                 0.500

/**----------------------------------------------------------------------
* Function    : AHRS_Init
* Description : AHRS初始化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void AHRS_Init();

/**----------------------------------------------------------------------
* Function    : MahonyUpdateAHRS
* Description : Mahony姿态更新算法
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void MahonyUpdateAHRS(float gx, float gy, float gz, float ax, float ay, float az,
                      float mx, float my, float mz);

/**----------------------------------------------------------------------
* Function    : UpdateAHRS
* Description : AHRS融合解算
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
int UpdateAHRS(IMU_t* IMU);

#endif