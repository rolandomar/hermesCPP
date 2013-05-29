/* 
 * File:   RemoteActionReplyPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 4:26 PM
 */

#ifndef REMOTEACTIONREPLYPACKET_H
#define	REMOTEACTIONREPLYPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/RemoteActionResultFactory.h>
#include <hermes/runtime/RemoteActionResult.h>

class RemoteActionReplyPacket: public HermesAbstractPacket {
public:

    static const int SERIAL_ID = 0x032001;

    RemoteActionReplyPacket();
    virtual ~RemoteActionReplyPacket();
    
    RemoteActionReplyPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }

    RemoteActionReplyPacket(int requestID, RemoteActionResult* rar) :
    HermesAbstractPacket(SERIAL_ID, 0),m_requestNo(requestID) {
        m_result = rar;
    }
    
    int getRequestNo() {
        return m_requestNo;
    }

protected:
    RemoteActionResult* m_result;
    int m_requestNo;
    
    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {
        outputStream.write_long(m_requestNo);
        m_result->serialize(outputStream);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        int serialID;
        inputStream.read_long(serialID);
        m_result = RemoteActionResultFactory::getRemoteActionResultImpl(serialID);
        m_result->deserialize(serialID, inputStream);
    }

};

#endif	/* REMOTEACTIONREPLYPACKET_H */

