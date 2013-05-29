/* 
 * File:   ThreadDelayFaultDescription.h
 * Author: rmartins
 *
 * Created on May 3, 2013, 2:00 PM
 */

#ifndef THREADDELAYFAULTDESCRIPTION_H
#define	THREADDELAYFAULTDESCRIPTION_H

#include <hermes/runtime/FaultDescription.h>

class ThreadDelayFaultDescription : public FaultDescription {
public:
    static const int SERIAL_ID = 133123980;
    int m_duration;

    ThreadDelayFaultDescription() : m_duration(0) {
    }

    ThreadDelayFaultDescription(int duration) : m_duration(duration) {
    }

    virtual ~ThreadDelayFaultDescription();

    int getSerialID() {
        return SERIAL_ID;
    }

    int getDuration() {
        return m_duration;
    }
protected:

    virtual void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(m_duration);
    }

    virtual void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_long(m_duration);
    }
};

#endif	/* THREADDELAYFAULTDESCRIPTION_H */
