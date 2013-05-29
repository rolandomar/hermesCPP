/* 
 * File:   NotificationRequestPacket.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 6:48 PM
 */

#ifndef NOTIFICATIONREQUESTPACKET_H
#define	NOTIFICATIONREQUESTPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/Notification.h>
#include <hermes/runtime/NotificationFactory.h>

class NotificationRequestPacket : public HermesAbstractPacket {
public:
    static const int NOTIFICATIONREQUESTY_OPCODE = 0x001110;
    NotificationRequestPacket(){}
    NotificationRequestPacket(int requestID, Notification* notification) :
    HermesAbstractPacket(NOTIFICATIONREQUESTY_OPCODE, 0), m_requestNo(requestID),m_notification(notification) {
    }
    NotificationRequestPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }
    virtual ~NotificationRequestPacket();

    int getRequestNo(){
        return m_requestNo;
    }
    
protected:
    Notification* m_notification;
    int m_requestNo;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {        
        printf("NotificationRequestPacket %d\n",m_requestNo);
        outputStream.write_long(m_requestNo);
        m_notification->serialize(outputStream);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        int serialID;
        inputStream.read_long(serialID);
        m_notification = NotificationFactory::getNotificationImpl(serialID);
        m_notification->deserialize(serialID, inputStream);
    }
};

#endif	/* NOTIFICATIONREQUESTPACKET_H */
