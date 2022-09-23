#ifndef _PDR_KML_SUPPORT_H
#define _PDR_KML_SUPPORT_H

#include <string>
using namespace std;

namespace PDR {

typedef struct ResultTracks {
	double lat;
	double lon;
	double heading;
	double utcTime;
	double hdop;
	double accuracy;
	double vel;
	double time;
	string motionType;
}KmlTracks_t;


}
#endif // _PDR_KML_SUPPORT_H
