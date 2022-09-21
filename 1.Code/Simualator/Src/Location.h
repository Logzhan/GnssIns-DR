#ifndef _PDR_LOCATION_H_
#define _PDR_LOCATION_H_

#include "PDRBase.h"

/**----------------------------------------------------------------------
* Function    : InsLocationPredict
* Description : PDR惯导位置更新
* Date        : 2022-09-21 logzhan
*---------------------------------------------------------------------**/
void InsLocationPredict(void);

/**----------------------------------------------------------------------
* Function    : GnssInsLocFusion
* Description : PDR的GNSS和INS融合定位
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void GnssInsLocFusion(void);

#endif