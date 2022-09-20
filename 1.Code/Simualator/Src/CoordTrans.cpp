/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : CoordTrans.cpp
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.20
* Comments           : PDR 坐标系转换相关函数支持
********************************************************************************/
#include <math.h>
#include "CoordTrans.h"

void WGS842ECEF(double* plla, double* ecef) {
	double f = 1 / 298.257223563;
	double a = 6378136.49;
	double b, e, roc;

	b = a * (1 - f);
	e = sqrt(pow(a, 2) - pow(b, 2)) / a;
	roc = a / sqrt(1 - pow(e * sin(plla[0]), 2));
	ecef[0] = (roc + plla[2]) * cos(plla[0]) * cos(plla[1]);
	ecef[1] = (roc + plla[2]) * cos(plla[0]) * sin(plla[1]);
	ecef[2] = (roc * (1 - e * e) + plla[2]) * sin(plla[0]);

}

void ECEF2WGS84(double* ecef, double* plla) 
{
	double a = 6378137;
	double b = 6356752.314245179;
	double e, ep, p, th, roc;

	e = sqrt(pow(a, 2) - pow(b, 2)) / a;
	b = sqrt(pow(a, 2) * (1 - pow(e, 2)));
	ep = sqrt((pow(a, 2) - pow(b, 2)) / pow(b, 2));
	p = sqrt(ecef[0] * ecef[0] + ecef[1] * ecef[1]);
	th = atan2(a * ecef[2], b * p);

	plla[1] = atan2(ecef[1], ecef[0]);
	plla[0] = atan2((ecef[2] + pow(ep, 2) * b * pow(sin(th), 3)), (p - pow(e, 2) * a * pow(cos(th), 3)));
	roc = a / sqrt(1 - pow(e * sin(plla[0]), 2));
	plla[2] = p / cos(plla[0]) - roc;

}

void ECEF2NED(double* ecef, double* plla, double* ned) 
{
	ned[0] = -sin(plla[0]) * cos(plla[1]) * ecef[0] - sin(plla[0]) * sin(plla[1]) * ecef[1] + cos(plla[0]) * ecef[2];
	ned[1] = -sin(plla[1]) * ecef[0] + cos(plla[1]) * ecef[1];
	ned[2] = -cos(plla[0]) * cos(plla[1]) * ecef[0] - cos(plla[0]) * sin(plla[1]) * ecef[1] - sin(plla[0]) * ecef[2];
}

void NED2ECEF(double* plla, double* ned, double* ecef0, double* ecef) 
{
	ecef[0] = -sin(plla[0]) * cos(plla[1]) * ned[0] - sin(plla[1]) * ned[1] - cos(plla[0]) * cos(plla[1]) * ned[2] + ecef0[0];
	ecef[1] = -sin(plla[0]) * sin(plla[1]) * ned[0] + cos(plla[1]) * ned[1] - cos(plla[0]) * sin(plla[1]) * ned[2] + ecef0[1];
	ecef[2] = cos(plla[0]) * ned[0] - sin(plla[0]) * ned[2] + ecef0[2];;
}

void WGS842NED(double* plla, double* ref_lla, double* ned)
{
	double ecef[3] = { 0 };

	WGS842ECEF(plla, ecef);
	ECEF2NED(ecef, ref_lla, ned);
}

void NED2WGS84(double* ref_plla, double* ned, double* plla)
{
	double ecef[3] = { 0 };
	double ref_ecef[3] = { 0 };
	WGS842ECEF(ref_plla, ref_ecef);

	NED2ECEF(ref_plla, ned, ref_ecef, ecef);
	ECEF2WGS84(ecef, plla);
}