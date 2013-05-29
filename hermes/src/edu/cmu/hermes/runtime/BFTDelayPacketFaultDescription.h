/* 
 * File:   BFTDelayPacketFaultDescription.h
 * Author: rmartins
 *
 * Created on May 6, 2013, 3:21 PM
 */

#ifndef BFTDELAYPACKETFAULTDESCRIPTION_H
#define	BFTDELAYPACKETFAULTDESCRIPTION_H
#include <hermes/runtime/FaultDescription.h>

class BFTDelayPacketFaultDescription : public FaultDescription {
public:
    static const int SERIAL_ID = 52511083;

    static const int ALL = 1;
    static const int MOD_SEQ = 2;

    BFTDelayPacketFaultDescription() : m_usDelay(0), m_type(0) {
    }

    BFTDelayPacketFaultDescription(int type, LongLong usDelay) : m_usDelay(usDelay), m_type(type) {
    }

    virtual ~BFTDelayPacketFaultDescription();

    int getSerialID() {
        return SERIAL_ID;
    }

    LongLong getDelay() {
        return m_usDelay;
    }

    int getType() {
        return m_type;
    }

protected:
    LongLong m_usDelay; //delay in microseconds
    int m_type; //delay in microseconds

    virtual void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_longlong(m_usDelay);
        outputStream.write_long(m_type);
    }

    virtual void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_longlong(m_usDelay);
        inputStream.read_long(m_type);
    }
};

#endif	/* BFTDELAYPACKETFAULTDESCRIPTION_H */

