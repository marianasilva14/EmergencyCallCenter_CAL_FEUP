/*
 * NoInfo.cpp
 *
 *  Created on: 29/03/2017
 *      Author: Sissi
 */
#include "NoInfo.h"


NoInfo::NoInfo(long long idNo, double longitude_radians, double latitude_radians){
	this->idNo = idNo;
	this->longitude_radians = longitude_radians;
	this->latitude_radians = latitude_radians;
}

long long NoInfo::getIdNo(){
return idNo;
}

double NoInfo::getLongitude_radians(){
	return longitude_radians;
}

double NoInfo::getLatitude_radians(){
return latitude_radians;
}


