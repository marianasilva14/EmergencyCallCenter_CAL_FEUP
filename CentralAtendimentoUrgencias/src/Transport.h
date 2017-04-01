/*
 * Transport.h
 *
 *  Created on: 01/04/2017
 *      Author: Sissi
 */

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

class Transport {
public:
	Transport();
	virtual ~Transport();
	typedef enum {
		AMBULANCE,
		CAR,
		MOTORCYCLE
	}transport;
	//static vector<Type> whoareAvailable();
};

#endif /* TRANSPORT_H_ */
