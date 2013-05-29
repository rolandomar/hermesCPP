/* 
 * File:   AddAspectRemoteAction.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 1:02 PM
 */

#include "AddAspectRemoteAction.h"
#include <hermes/runtime/HermesFaultFactory.h>

AddAspectRemoteAction::AddAspectRemoteAction() {
}

AddAspectRemoteAction::AddAspectRemoteAction(const AddAspectRemoteAction& orig) {
}

AddAspectRemoteAction::~AddAspectRemoteAction() {
}

void AddAspectRemoteAction::serializeAction(OutputStream& outputStream) throw (SerializationException&) {
    m_fault->serialize(outputStream);
}

void AddAspectRemoteAction::deserializableAction(InputStream& inputStream) throw (SerializationException&) {
    int serial;
    inputStream.read_long(serial);
    HermesFaultFactory::
            getInstance()->getAspectImpl(serial,m_fault);
    m_fault->deserialize(serial,inputStream);
}