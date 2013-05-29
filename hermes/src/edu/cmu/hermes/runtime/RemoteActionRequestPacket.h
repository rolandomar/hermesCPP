/* 
 * File:   RemoteActionRequestPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 4:17 PM
 */

#ifndef REMOTEACTIONREQUESTPACKET_H
#define	REMOTEACTIONREQUESTPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/RemoteAction.h>


class RemoteActionRequestPacket : public HermesAbstractPacket {
public:
    static const int SERIAL_ID = 0x032000;
    RemoteActionRequestPacket(){}

    RemoteActionRequestPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }

    RemoteActionRequestPacket(int requestID, RemoteAction* ra) :
    HermesAbstractPacket(SERIAL_ID, 0),m_requestNo(requestID) {
        m_remoteAction = ra;
    }
    
    virtual ~RemoteActionRequestPacket();
    
    RemoteAction* getRemoteAction(){
        return m_remoteAction;
    }
    
    int getRequestNo(){
        return m_requestNo;
    }
    
protected:
    RemoteAction* m_remoteAction;
    int m_requestNo;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&);
    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&);
};

#endif	/* REMOTEACTIONREQUESTPACKET_H */
