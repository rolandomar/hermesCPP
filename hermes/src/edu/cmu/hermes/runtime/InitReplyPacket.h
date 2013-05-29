/* 
 * File:   InitReplyPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 3:10 PM
 */

#ifndef INITREPLYPACKET_H
#define	INITREPLYPACKET_H       

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/Notification.h>

class InitReplyPacket : public HermesAbstractPacket {
public:

    static const int INITPACKETREPLY_OPCODE = 0x000006;

    static const int RETCODE_OK = 0;
    static const int RETCODE_NOK = -1;

    InitReplyPacket();

    InitReplyPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }

    InitReplyPacket(int requestNo, int retcode, String retValue) :
    HermesAbstractPacket(INITPACKETREPLY_OPCODE, 0),m_requestNo(requestNo) {
        m_retcode = retcode;
        m_retValue = retValue;
    }
    virtual ~InitReplyPacket();

protected:
    int m_requestNo;
    int m_retcode;
    String m_retValue;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {
        outputStream.write_long(m_requestNo);
        outputStream.write_long(m_retcode);
        outputStream.write_string(m_retValue);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        inputStream.read_long(m_retcode);
        inputStream.read_string(m_retValue);

    }

};

#endif	/* INITREPLYPACKET_H */

