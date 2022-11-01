/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : Interface.c
* Current Version    : V2.0
* Author             : logzhan
* Date of Issued     : 2022.10.15
* Comments           : PDR导航算法对外部接口
********************************************************************************/
#include "Interface.h"
#include "Location.h"

/* Global Variable Definition ------------------------------------------------*/
const char* PDR_Version = "2.0";
Nmea_t      Nmea;
IMU_t       Imu;
/* Extern Variable Definition ------------------------------------------------*/
extern EKFPara_t  EkfPara;

/**---------------------------------------------------------------------
* Function    : ParseDataAndUpdate
* Description : 解析字符串信息并更新
* Date        : 2022/10/16 logzhan
*---------------------------------------------------------------------**/
int ParseDataAndUpdate(char* line, LctFs_t* LocFusion)
{   
    // 解析Gnss和Imu数据用于PDR导航
	//ParseGnssInsData(line, &Imu, &Nmea);
	// 给定Imu和Nmea结构体，返回融合位置
	return PDRLocationMainLoop(&Imu, &Nmea, LocFusion);
}

/**---------------------------------------------------------------------
* Function    : PDRLocationMainLoop
* Description : PDR定位主循环
* Date        : 2022/11/1 logzhan
*---------------------------------------------------------------------**/
int PDRLocationMainLoop(IMU_t* imu, Nmea_t* nmea, LctFs_t* LocFusion) {
    int type = 0;

    if (imu->gyr.update) {
        // 如果陀螺仪更新则采用惯性传感器计算
        InsLocationUpdate(imu, &EkfPara);
        imu->gyr.update = NO_UPDATE;
    }
    // 如果GPS不更新，返回
    if (!nmea->Update)return TYPE_FIX_NONE;

    // 写GPS相关LOG信息
    //SaveGnssInfo(nmea, LocFusion, NULL);

    // 有GPS则采用GPS融合定位
    //int flag = GnssInsFusionLocation(nmea, &g_kfPara, LocFusion);

    //if (flag != TYPE_FIX_NONE) {
    //    // 如果是开车这种，直接输出GPS，不进行平滑处理
    //    LocFusion->latitude = R2D(LocFusion->latitude);
    //    LocFusion->longitudinal = R2D(LocFusion->longitudinal);

    //    LocFusion->last_lat = LocFusion->latitude;
    //    LocFusion->last_lon = LocFusion->longitudinal;
    //    type = 1;
    //}
    //else if (LocFusion->last_lat != 0.0 && LocFusion->last_lon != 0.0) {
    //    LocFusion->latitude = LocFusion->last_lat;
    //    LocFusion->longitudinal = LocFusion->last_lon;
    //    type = 1;
    //}
    //ClearNmeaFlg(nmea);
    return type;
}

/**----------------------------------------------------------------------
* Function    : GetPDRVersion
* Description : 获取pdr版本号
* Date        : 2022/10/15 logzhan
*---------------------------------------------------------------------**/
const char* GetPDRVersion(void) {
    return PDR_Version;
}