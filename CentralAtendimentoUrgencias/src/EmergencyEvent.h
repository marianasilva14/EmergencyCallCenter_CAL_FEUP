/*
 * EmergencyEvent.h
 *
 *  Created on: 01/04/2017
 *      Author: Sissi
 */

#ifndef EMERGENCYEVENT_H_
#define EMERGENCYEVENT_H_

class Emergency{
public:
	typedef enum {
		HIGH,
		MEDIUM,
		LOW
	}emergency;
};

class EmergencyEvent {
private:
	Emergency::emergency emergency_type;
	//Transport::transport transport_type;
public:
	EmergencyEvent();
//	EmergencyEvent(Emergency::emergency e, Transport::transport t);
	virtual ~EmergencyEvent();

};












#endif /* EMERGENCYEVENT_H_ */
