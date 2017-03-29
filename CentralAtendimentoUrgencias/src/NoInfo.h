/*
 * NoInfo.h
 *
 *  Created on: 29/03/2017
 *      Author: Sissi
 */

#ifndef SRC_NOINFO_H_
#define SRC_NOINFO_H_
#include <string>
#include<sstream>


class NoInfo{
public:
	long long idNo;
	double longitude_radians;
	double latitude_radians;

	NoInfo(long long idNo, double longitude_radians, double latitude_radians);
	long long getIdNo();
	double getLongitude_radians();
	double getLatitude_radians();

	friend bool operator==(NoInfo const & left,NoInfo const & right){
		return left.idNo == right.idNo;
	}

	friend bool operator!=(NoInfo const & left,NoInfo const & right){
		return left.idNo != right.idNo;
	}
};


#endif /* SRC_NOINFO_H_ */
