/* 
 * File:   HermesAbstractPacket.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 3:51 PM
 */

#include "HermesAbstractPacket.h"

HermesAbstractPacketHeader::HermesAbstractPacketHeader() :
m_magic(MAGIC),
m_messageType(0),
m_requestID(0), m_messageSize(0) {
}

HermesAbstractPacketHeader::HermesAbstractPacketHeader(Int messageType,
        Int requestID, UInt messageSize) :
m_magic(MAGIC),
m_messageType(messageType),
m_requestID(requestID),
m_messageSize(messageSize) {
    //m_messageSize(0) {

}

HermesAbstractPacketHeader::HermesAbstractPacketHeader(Int magic,
        Int messageType, Int requestID,
        UInt messageSize) :
m_magic(magic),
m_messageType(messageType), m_requestID(requestID),
m_messageSize(messageSize) {
}

HermesAbstractPacketHeader::~HermesAbstractPacketHeader() {
}

HermesAbstractPacketHeader::HermesAbstractPacketHeader(InputStream& is) THROW(SerializationException&) {
    deserialize(is);
}

void HermesAbstractPacketHeader::serialize(OutputStream& outputStream)
throw (SerializationException&) {
    outputStream.write_long(m_magic); 
    outputStream.write_long(VERSION); 
    outputStream.write_long(m_messageType);
    outputStream.write_long(m_requestID);
    outputStream.write_long(m_messageSize);
}

void HermesAbstractPacketHeader::deserialize(InputStream& inputStream)
throw (SerializationException&) {
    int version;    
    inputStream.read_long(m_magic);
    inputStream.read_long(version);
    inputStream.read_long(m_messageType);
    inputStream.read_long(m_requestID);
    inputStream.read_long(m_messageSize);
    printf("packet(%d,%d,%d,%d,%d)\n",m_magic,version,m_messageType,m_requestID,
            m_messageSize);
}

UInt HermesAbstractPacketHeader::getBodySize() {
    return m_messageSize;
}

void HermesAbstractPacketHeader::setBodySize(UInt size) {
    m_messageSize = size;
}

UInt HermesAbstractPacketHeader::getSize() {
    //return 18;
    //return 16;
    return 20;
}

UInt HermesAbstractPacketHeader::getSerializationSize(Alignment* aligment) {
    //return 18;
    //return 16;
    return 20;
}

Int HermesAbstractPacketHeader::getType() {
    return m_messageType;
}

Int HermesAbstractPacketHeader::getPacketID() {
    return m_requestID;
}

Int HermesAbstractPacketHeader::getMessageSize() {
    return m_messageSize;
}

void HermesAbstractPacketHeader::setMessageSize(UInt messageSize) {
    m_messageSize = messageSize;
}

void HermesAbstractPacketHeader::setRequestID(Int requestID) {
    m_requestID = requestID;
}

HermesAbstractPacket::HermesAbstractPacket(Int messageType,
        Int requestID,
        UInt messageSize) {
    HermesAbstractPacketHeader* header = new HermesAbstractPacketHeader(messageType,
            requestID, messageSize);
    Packet<HermesAbstractPacketHeader>::m_packetHeader = header;
}

HermesAbstractPacket::HermesAbstractPacket(HermesAbstractPacketHeader* packetHeader) :
Packet<HermesAbstractPacketHeader>(packetHeader) {
}

HermesAbstractPacket::HermesAbstractPacket() : Packet<HermesAbstractPacketHeader>() {
}

HermesAbstractPacket::~HermesAbstractPacket() {
}

void HermesAbstractPacket::serialize(OutputStream& outputStream) throw (SerializationException&) {    
    UInt bodySize = getBodySerializationSize();
    getPacketHeader()->setMessageSize(bodySize);
    serializeHeader(outputStream);
    serializeBody(outputStream);
}