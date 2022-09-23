#ifndef _PDR_DETECTOR_H_
#define _PDR_DETECTOR_H_

#include "PDRBase.h"

/**---------------------------------------------------------------------
* Function    : pdr_initDetector
* Description : 初始化运动分类器，识别用户处于哪一种运动模式
* Date        : 2020/02/16 logzhan & logzhan
*---------------------------------------------------------------------**/
void Detector_Init(void);

/**---------------------------------------------------------------------
* Function    : DetectorReset
* Description : 重置PDR运动检测器
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
void DetectorReset(void);

/**---------------------------------------------------------------------
* Function    : DetectorUpdateIMU
* Description : 更新运动类型检测器的imu信息，如果到达一定的时间间隔，则会检测
*               用户的运动类型
* Date        : 2022/09/23
*---------------------------------------------------------------------**/
void DetectorUpdateIMU(IMU_t* imu);

/**---------------------------------------------------------------------
* Function    : DetectMotionType
* Description : pdr运动类型检测
* Date        : 2020/7/20
*---------------------------------------------------------------------**/
int DetectMotionType(void);

#endif