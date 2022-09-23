#ifndef _PDR_PEDOMETER_H_
#define _PDR_PEDOMETER_H_

#include "PDRBase.h"

void Pedometer_Init(void);

void PedometerUpdate(IMU_t* imu, uint64_t* step);

#endif