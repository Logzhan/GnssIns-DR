/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : Location.cpp
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.21
* Comments           : PDR导航算法主流程
********************************************************************************/
/* Header File Including -----------------------------------------------------*/
#include "DirectionEstimator.h"
#include "Kalman.h"
#include "AHRS.h"
#include "Pedometer.h"
#include "Detector.h"
#include "Location.h"

/* Global Variable Definition ------------------------------------------------*/
EKFPara_t EkFPara;
PDR_t     PDR;

/**---------------------------------------------------------------------
* Function    : PDRNav_Init
* Description : PDR导航系统初始化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void PDRNav_Init(void) 
{
	Detector_Init();
	AHRS_Init();
	EKF_Init();
	Pedometer_Init();
	DirectionEstimator_Init();
}

/**----------------------------------------------------------------------
* Function    : InsLocation
* Description : PDR惯导位置更新
* Date        : 2022-09-21
*---------------------------------------------------------------------**/
void InsLocationUpdate(IMU_t* ImuData, EKFPara_t* Ekf)
{
	if (UpdateAHRS(ImuData)) {
		
	}
	/* Updating imu info in order to detect user moving type. */
	DetectorUpdateIMU(ImuData);
	/* calculate user step info update. */
	PedometerUpdate(ImuData, &PDR.Steps);
	/* Using multiply sensor info to predict user real moving direction. */
	DirectionPredict(&PDR.Heading);
	/* Extend kalman filter update system state when ins data update. */
	EKFUpdateInsState();
}


/**----------------------------------------------------------------------
* Function    : GnssInsLocFusion
* Description : PDR的GNSS和INS融合定位
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void GnssInsLocationUpdate(void) {

}