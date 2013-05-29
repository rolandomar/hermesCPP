/* 
 * File:   RemoteActionRequestPacket.cpp
 * Author: rmartins
 * 
 * Created on April 30, 2013, 4:17 PM
 */

#include "RemoteActionRequestPacket.h"
#include <hermes/runtime/RemoteActionFactory.h>

RemoteActionRequestPacket::~RemoteActionRequestPacket() {
}

void
RemoteActionRequestPacket::serializeBody(OutputStream& outputStream) THROW(SerializationException&) {
    outputStream.write_long(m_requestNo);
    m_remoteAction->serialize(outputStream);
}

void
RemoteActionRequestPacket::deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
    inputStream.read_long(m_requestNo);
    int serialID;
    inputStream.read_long(serialID);
    m_remoteAction = RemoteActionFactory::getRemoteActionImpl(serialID);
    m_remoteAction->deserialize(serialID, inputStream);
}