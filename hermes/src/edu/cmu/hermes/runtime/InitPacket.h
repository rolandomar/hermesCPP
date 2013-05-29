/* 
 * File:   InitPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 10:50 AM
 */

#ifndef INITPACKET_H
#define	INITPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>

class InitPacket : public HermesAbstractPacket {
public:
    static const int INITPACKET_OPCODE = 0x000005;
    InitPacket(){}
    InitPacket(int requestID, String& ID) :
    HermesAbstractPacket(INITPACKET_OPCODE, 0), m_ID(ID),m_requestNo(requestID) {
    }
    InitPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }
    virtual ~InitPacket();

    
protected:
    String m_ID;
    int m_requestNo;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {
        outputStream.write_long(m_requestNo);
        outputStream.write_string(m_ID);
        
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        //int serialID;
        inputStream.read_long(m_requestNo);
        inputStream.read_string(m_ID);
        
    }
};
#endif	/* INITPACKET_H */

