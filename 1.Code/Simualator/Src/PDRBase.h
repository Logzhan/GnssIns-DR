#ifndef  _PDR_BASE_H_
#define  _PDR_BASE_H_

#include <stdint.h>

#define ACCURACY_ERR_MAX                    1000                 // GPS的accuracy最大值,一般用于初始化用
#define N                                   4                    // 矩阵维数
#define MAX_NO_GPS_PREDICT                  10		             // 无GPS信息状态，最大位置推算数量	
#define IMU_SENSOR_AXIS                     3                    // IMU传感器数据轴数量，默认3

// 用户运动识别
#define DETECTOR_TYPE_STATIC                0                    // 用户静止 
#define DETECTOR_TYPE_IRREGULAR             1                    // 无规律运动
#define DETECTOR_TYPE_HANDHELD              2                    // 手持运动
#define DETECTOR_TYPE_SWINGING              3                    // 摆手运动
#define DETECTOR_NO_ERROR                   0

#define PDR_TRUE                            1
#define PDR_FALSE                           0

typedef struct {
	double xk[N];             // 系统状态变量  xk[0]: 北向x  xk[1]：东向y  xk[2]：步长  xk[3] ：航向角
	double p_xk[N];           // 最佳预测变量  xk[0]: 北向x  xk[1]：东向y  xk[2]：步长  xk[3] ：航向角
	double zk[N];
	double p_pk[N][N];
	double pk[N][N];
	double phi[N][N];
	double hk[N][N];
	double q[N][N];           // 卡尔曼滤波的Q矩阵(过程噪声)
	double r[N][N];           // 卡尔曼滤波R矩阵(观测噪声)
	double Kk[N][N];
	double lambda;
	double plat;
	double plon;
	double initHeading;
}EKFPara_t;

typedef struct Sensor {
	unsigned char update;
	int type;
	double time;
	float s[IMU_SENSOR_AXIS];
}Sensor_t;

typedef struct IMU {
	Sensor_t acc;
	Sensor_t gyr;
	Sensor_t mag;
}IMU_t;

// 用户运动类型分类器
typedef struct DETECTOR {
	uint32_t type;                              // 用户运动类别 ： 0:静止运动 1：无规律运动 2：手持运动 3：摆手运动
	uint32_t lastType;
	uint64_t tick;                              // 次数统计，用于调整检测器工作频率
} DETECTOR_t;


typedef struct PDR {
	uint32_t        Status;                     // PDR当前状态
	uint32_t        MotionType;                 // 用户运动类型
	// 速度相关
	double          GnssSpeed;                  // GNSS速度
	double          Heading;                    // 航向
	// 步数相关
	uint64_t        Steps;                      // 当前步数信息
	uint64_t        LastSteps;                  // 上一次的步数
} PDR_t;

#endif // ! _PDR_BASE_H
