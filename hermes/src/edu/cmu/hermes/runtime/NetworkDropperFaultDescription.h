/* 
 * File:   NetworkDropperFaultDescription.h
 * Author: rmartins
 *
 * Created on May 3, 2013, 2:21 PM
 */

#ifndef NETWORKDROPPERFAULTDESCRIPTION_H
#define	NETWORKDROPPERFAULTDESCRIPTION_H

#include <hermes/runtime/FaultDescription.h>

class NetworkDropperFaultDescription : public FaultDescription {
public:
    static const int SERIAL_ID = 387326666;
    int m_duration;

    NetworkDropperFaultDescription() : m_dropPer(0) {
    }

    NetworkDropperFaultDescription(int dropPer) : m_dropPer(dropPer) {
    }

    virtual ~NetworkDropperFaultDescription();

    int getSerialID() {
        return SERIAL_ID;
    }

    int getDuration() {
        return m_dropPer;
    }
protected:
    int m_dropPer;

    virtual void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(m_dropPer);
    }

    virtual void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_long(m_dropPer);
    }
};

#endif	/* NETWORKDROPPERFAULTDESCRIPTION_H */

