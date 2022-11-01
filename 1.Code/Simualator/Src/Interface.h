#ifndef _PDR_INTERFACE_H
#define _PDR_INTERFACE_H
#include "PDRBase.h"

/**---------------------------------------------------------------------
* Function    : PDRLocationMainLoop
* Description : PDR定位主循环
* Date        : 2022/11/1 logzhan
*---------------------------------------------------------------------**/
int PDRLocationMainLoop(IMU_t* imu, Nmea_t* nmea, LctFs_t* LocFusion);


/**----------------------------------------------------------------------
* Function    : GetPDRVersion
* Description : 获取pdr版本号
* Date        : 2022/10/15 logzhan
*---------------------------------------------------------------------**/
const char* GetPDRVersion(void);

#endif // _PDR_INTERFACE_H
