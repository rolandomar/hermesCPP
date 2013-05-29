/* 
 * File:   HermesAbstractPacket.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 3:51 PM
 */

#ifndef HERMESABSTRACTPACKET_H
#define	HERMESABSTRACTPACKET_H

#include <euryale/net/packet/Packet.h>
#include <euryale/common/uuid/UUID.h>

class HermesAbstractPacketHeader : public PacketHeader {
public:    
    static const Byte DEFAULT_FLAGS = 0;
    static const int MAGIC = 0x00aacc;
    static const int VERSION = 1;
    static const int HEADER_SIZE = 20;
    static const int DEFAULT_BODY_SIZE = 2048;
    
    

    HermesAbstractPacketHeader();
    HermesAbstractPacketHeader(Int magic,
            Int messageType,
            Int requestID,
            UInt messageSize = 0);

    HermesAbstractPacketHeader(Int messageType,
            Int requestID,
            UInt messageSize = 0);

    virtual ~HermesAbstractPacketHeader();

    HermesAbstractPacketHeader(InputStream& is) THROW(SerializationException&);

    virtual void serialize(OutputStream& outputStream) throw(SerializationException&);
    void deserialize(InputStream& inputStream)throw(SerializationException&);

    UInt getBodySize();
    void setBodySize(UInt size);
    
    static UInt getSize();

    virtual UInt getSerializationSize(Alignment* aligment = 0);

    virtual Int getType();

    virtual Int getPacketID();

    virtual Int getMessageSize();

    virtual void setMessageSize(UInt messageSize);

    virtual void setRequestID(Int requestID);
    
protected:
    Int m_magic;
    Int m_messageType;
    Int m_requestID;
    Int m_messageSize;

};

class HermesAbstractPacket : public Packet<HermesAbstractPacketHeader> {
public:

    HermesAbstractPacket(Int messageType,
            Int requestID,
            UInt messageSize = 0);

    HermesAbstractPacket(HermesAbstractPacketHeader* packetHeader);
    HermesAbstractPacket();
    virtual ~HermesAbstractPacket();

    virtual void serialize(OutputStream& outputStream) throw (SerializationException&);
};

#endif	/* HERMESABSTRACTPACKET_H */

