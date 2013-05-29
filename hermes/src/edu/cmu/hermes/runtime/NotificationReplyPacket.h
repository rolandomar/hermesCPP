/* 
 * File:   NotificationReplyPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 10:18 AM
 */

#ifndef NOTIFICATIONREPLYPACKET_H
#define	NOTIFICATIONREPLYPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/Notification.h>

class NotificationReplyPacket : public HermesAbstractPacket{
public:
    static const int NOTIFICATIONREPLY_OPCODE = 0x001111;    
    static const int RETCODE_OK = 0;
    static const int RETCODE_NOK = -1;
    
    NotificationReplyPacket();
    NotificationReplyPacket(HermesAbstractPacketHeader* header):
    HermesAbstractPacket(header){    
    }
    
    NotificationReplyPacket(int requestNo,int retcode):
    HermesAbstractPacket(NOTIFICATIONREPLY_OPCODE,0),m_requestNo(requestNo){        
        m_retcode = retcode;
    }
    
    virtual ~NotificationReplyPacket();
    
    int getRequestNo(){
        return m_requestNo;
    }
    int getRetCode(){
        return m_retcode;
    }

protected:
    int m_retcode;
    int m_requestNo;
    
   virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {        
       outputStream.write_long(m_requestNo);
        outputStream.write_long(m_retcode);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        inputStream.read_long(m_retcode);
        
    }

};

#endif	/* NOTIFICATIONREPLYPACKET_H */
