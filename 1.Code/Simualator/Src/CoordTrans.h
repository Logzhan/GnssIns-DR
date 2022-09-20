#ifndef _PDR_COORD_SUPPORT_H
#define _PDR_COORD_SUPPORT_H

#include <string>
using namespace std;

namespace PDR {

void WGS842ECEF(double* plla, double* ecef);

void ECEF2WGS84(double* ecef, double* plla);

void ECEF2NED(double* ecef, double* plla, double* ned);

void NED2ECEF(double* plla, double* ned, double* ecef0, double* ecef);

void WGS842NED(double* plla, double* ref_lla, double* ned);

void NED2WGS84(double* ref_plla, double* ned, double* plla);

}
#endif // _PDR_KML_SUPPORT_H