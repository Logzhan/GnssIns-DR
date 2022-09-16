/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : PDR_KmlSupport.cpp
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.15
* Comments           : PDR Google地图KML格式输出
********************************************************************************/
#include "PDR_KmlSupport.h"
#include <vector>

using namespace PDR;

/**----------------------------------------------------------------------
* Function    : KmlWrite
* Description : 将pdr算法输出的gps和pdr轨迹写为kml形式
*               path    : kml文件的输出文件路径
*               name    : kml文件主体名称
*               postfix ：在主体名称后面添加的后缀，用于区分类型或者版本
* Date        : 2020/11/1 logzhan
*---------------------------------------------------------------------**/
void KmlWrite(string path, string name, string postfix, vector<KmlTracks_t>& gps, 
			  vector<KmlTracks_t>& pdr)
{
	string pdrColor = "ff0000ff";
	string gpsColor = "ff00ffff";

	if (path == "") {
		return;
	}

	string kmlPath = path + name + postfix + ".kml";
	string kmlName = name + postfix;
	FILE* fid = NULL;

	fopen_s(&fid,kmlPath.c_str(), "w");

	if (fid == NULL) {
		return;
	}

	fprintf(fid, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(fid, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	fprintf(fid, "\t<Document>\n");
	fprintf(fid, "\t\t<name>%s</name>\n", kmlName.c_str());

	fprintf(fid, "\t\t<Folder id=\"ID1\">\n");
	fprintf(fid, "\t\t<name>GPS Fixs</name>\n");

	// 写gps结果
	for (int i = 0; i < gps.size(); i++) {
		fprintf(fid, "\t\t<Placemark>\n");
		fprintf(fid, "\t\t\t<Style>\n");
		fprintf(fid, "\t\t\t\t<IconStyle>\n");
		fprintf(fid, "\t\t\t\t\t<Icon>\n");
		fprintf(fid, "\t\t\t\t\t\t<href>%s</href>\n",
			"http://maps.google.com/mapfiles/kml/shapes/arrow.png");
		fprintf(fid, "\t\t\t\t\t</Icon>\n");
		fprintf(fid, "\t\t\t\t\t<scale>%.2f</scale>\n", 0.4);

		// 描述轨迹方向信息
		fprintf(fid, "\t\t\t\t\t<heading>%.7f</heading>\n", gps[i].heading);
		fprintf(fid, "\t\t\t\t\t<color>%s</color>\n", gpsColor.c_str());
		fprintf(fid, "\t\t\t\t</IconStyle>\n");
		fprintf(fid, "\t\t\t</Style>\n");

		// 写入时间信息
		//double h, m, s;
		//pdr_utc2hms(gps[i].utcTime, &h, &m, &s);
		//fprintf(fid, "\t\t\t<TimeStamp>\n");
		//fprintf(fid, "\t\t\t\t<when>2021-01-22T%s:%s:%s</when>\n", time2str(h).c_str(),
		//	time2str(m).c_str(), time2str(s).c_str());
		//fprintf(fid, "\t\t\t</TimeStamp>\n");

		// 写入描述信息
		fprintf(fid, "\t\t\t<description>\n");
		fprintf(fid, "\t\t\t\t<![CDATA[\n");
		fprintf(fid, "\t\t\t\t<dl>\n");
		fprintf(fid, "\t\t\t\t<dd>East : 0.0 (m/s)</dd>\n");
		fprintf(fid, "\t\t\t\t<dd>HDOP : %.2f (m/s)</dd>\n",
			gps[i].hdop);
		fprintf(fid, "\t\t\t\t<dd>accuracy : %.2f (m)</dd>\n",
			gps[i].accuracy);
		fprintf(fid, "\t\t\t\t<dd>speed : %.2f (m/s)</dd>\n",
			gps[i].vel);
		fprintf(fid, "\t\t\t\t<dd>Heading : %.2f (degrees) </dd>\n",
			gps[i].heading);
		fprintf(fid, "\t\t\t\t</dl><hr>]]>\n");
		fprintf(fid, "\t\t\t</description>\n");
		// 写入坐标信息
		fprintf(fid, "\t\t\t<Point>\n");
		fprintf(fid, "\t\t\t\t<coordinates>%.10f,%.10f</coordinates>\n",
			gps[i].lon,
			gps[i].lat);
		fprintf(fid, "\t\t\t</Point>\n");
		fprintf(fid, "\t\t</Placemark>\n");
	}
	fprintf(fid, "\t\t</Folder>\n");

	fprintf(fid, "\t\t<Folder id=\"ID2\">\n");
	fprintf(fid, "\t\t<name>PDR Fixs</name>\n");
	// 写pdr结果
	for (int i = 0; i < pdr.size(); i++) {
		fprintf(fid, "\t\t<Placemark>\n");
		fprintf(fid, "\t\t\t<Style>\n");
		fprintf(fid, "\t\t\t\t<IconStyle>\n");
		fprintf(fid, "\t\t\t\t\t<Icon>\n");
		fprintf(fid, "\t\t\t\t\t\t<href>%s</href>\n",
			"http://maps.google.com/mapfiles/kml/shapes/arrow.png");
		fprintf(fid, "\t\t\t\t\t</Icon>\n");
		fprintf(fid, "\t\t\t\t\t<scale>%.2f</scale>\n", 0.4);
		fprintf(fid, "\t\t\t\t\t<heading>%.7f</heading>\n",
			pdr[i].heading);

		fprintf(fid, "\t\t\t\t\t<color>%s</color>\n", pdrColor.c_str());
		fprintf(fid, "\t\t\t\t</IconStyle>\n");
		fprintf(fid, "\t\t\t</Style>\n");

		// 写入时间信息
		//double h, m, s;
		//pdr_utc2hms(resTracks.pdrTrack[i].time, &h, &m, &s);
		//fprintf(fid, "\t\t\t<TimeStamp>\n");
		//fprintf(fid, "\t\t\t\t<when>2021-01-22T%s:%s:%s</when>\n", time2str(h).c_str(),
		//	time2str(m).c_str(), time2str(s).c_str());
		//fprintf(fid, "\t\t\t</TimeStamp>\n");

		// description
		fprintf(fid, "\t\t\t<description>\n");
		fprintf(fid, "\t\t\t\t<![CDATA[\n");
		fprintf(fid, "\t\t\t\t<dl>\n");
		fprintf(fid, "\t\t\t\t<dd>East : 0.0 (m/s)</dd>\n");
		fprintf(fid, "\t\t\t\t<dd>HDOP : %.2f (m/s)</dd>\n",
			pdr[i].hdop);

		//fprintf(fid, "\t\t\t\t<dd>MOTION TYPE : %s (m/s)</dd>\n",
		//	motionType2Str(resTracks.pdrTrack[i].motionType));

		fprintf(fid, "\t\t\t\t<dd>accuracy : %.2f (m/s)</dd>\n",
			pdr[i].accuracy);
		fprintf(fid, "\t\t\t\t<dd>Heading : %.2f (degrees) </dd>\n",
			pdr[i].heading);
		fprintf(fid, "\t\t\t\t</dl><hr>]]>\n");
		fprintf(fid, "\t\t\t</description>\n");

		fprintf(fid, "\t\t\t<Point>\n");
		fprintf(fid, "\t\t\t\t<coordinates>%.10f,%.10f</coordinates>\n",
			pdr[i].lon,
			pdr[i].lat);
		fprintf(fid, "\t\t\t</Point>\n");
		fprintf(fid, "\t\t</Placemark>\n");
	}
	fprintf(fid, "\t\t</Folder>\n");

	fprintf(fid, "\t</Document>\n");
	fprintf(fid, "</kml>\n");

	fclose(fid);
}
