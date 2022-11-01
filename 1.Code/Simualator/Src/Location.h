#ifndef _PDR_LOCATION_H_
#define _PDR_LOCATION_H_

#include "PDRBase.h"

/**---------------------------------------------------------------------
* Function    : PDRNav_Init
* Description : PDR导航系统初始化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void PDRNav_Init(void);

/**----------------------------------------------------------------------
* Function    : InsLocation
* Description : PDR惯导位置更新
* Date        : 2022-09-21 logzhan
*---------------------------------------------------------------------**/
void InsLocationUpdate(IMU_t* ImuData, EKFPara_t* Ekf);

/**----------------------------------------------------------------------
* Function    : GnssInsLocFusion
* Description : PDR的GNSS和INS融合定位
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void GnssInsLocationUpdate(void);

#endif