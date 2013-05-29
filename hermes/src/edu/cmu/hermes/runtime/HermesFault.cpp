/* 
 * File:   HermesFault.cpp
 * Author: rmartins
 * 
 * Created on April 28, 2013, 7:23 PM
 */

#include "HermesFault.h"
#include <hermes/runtime/FaultCustomTriggerChecker.h>
#include <hermes/runtime/HermesRuntime.h>
#include <hermes/runtime/HermesRuntimeException.h>
#include <hermes/runtime/CrashFault.h>

const String HermesFault::GLOBAL_FAULT_SIGNATURE("global");

HermesFault::~HermesFault() {
}

HermesFault::HermesFault() :
m_runtime(HermesRuntime::getInstance()), m_customChecker(0) {
    m_faultID = 0;
    m_synchronizedFault = false;
    m_triggerType = TRIGGER_DISABLED;
}

HermesFault::HermesFault(Byte triggerType) :
m_runtime(HermesRuntime::getInstance()), m_customChecker(0) {

    m_faultID = 0;
    m_synchronizedFault = false;
    m_triggerType = triggerType;
}

HermesFault::HermesFault(HermesRuntime* runtime, String& id, Byte triggerType) :
m_runtime(HermesRuntime::getInstance()), m_customChecker(0) {
    m_faultID = id;
    m_synchronizedFault = false;
    m_triggerType = triggerType;
}

HermesFault::HermesFault(HermesRuntime* runtime, String& id, bool synchronizedFault, Byte triggerType) :
m_runtime(HermesRuntime::getInstance()), m_customChecker(0) {
    m_faultID = id;
    m_synchronizedFault = synchronizedFault;
    m_triggerType = triggerType;
}

bool HermesFault::getSynchronizedFaul() {
    return m_synchronizedFault;
}

Byte HermesFault::getTriggerType() {
    return m_triggerType;
}

void HermesFault::setSynchronizedFault(bool synch) {
    m_synchronizedFault = synch;
}

String HermesFault::getFaultID() {
    return m_faultID;
}

void HermesFault::setFaultID(String& aspectID) {
    m_faultID = aspectID;
}

void HermesFault::serialize(OutputStream& outputStream) throw (SerializationException&) {
    outputStream.write_long(getSerialID());
    outputStream.write_string(m_faultID);
    outputStream.write_boolean(m_synchronizedFault);
    outputStream.write_octet(m_triggerType);

    m_ctx.serialize(outputStream);
    serializableImpl(outputStream);
}

void HermesFault::deserialize(InputStream& inputStream) throw (SerializationException&) {
    int serial;
    inputStream.read_long(serial);
    if (serial != getSerialID()) {
        throw SerializationException(SerializationException::BAD_STREAM);
    }
    inputStream.read_string(m_faultID);
    inputStream.read_boolean(m_synchronizedFault);
    inputStream.read_octet(m_triggerType);
    m_ctx.deserialize(inputStream);
    deserializableImpl(inputStream);
}

void HermesFault::deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {
    if (serial != getSerialID()) {
        throw SerializationException(SerializationException::BAD_STREAM);
    }
    inputStream.read_string(m_faultID);
    inputStream.read_boolean(m_synchronizedFault);
    inputStream.read_octet(m_triggerType);
    m_ctx.deserialize(inputStream);
    deserializableImpl(inputStream);
}

void HermesFault::execute() throw (HermesRuntimeException&) {
    if (trigger()) {
        preExecute();
        if (getSerialID() == CrashFault::SERIAL_ID) {
            //will crash so we send the postExecute before...
            postExecute();
        }
        executeImpl();
        //will never reach in crashes
        postExecute();
    }
}

void HermesFault::setFaultContext(FaultContext& ctx) throw (HermesRuntimeException&) {
    m_ctx = ctx;
}

FaultContext HermesFault::getFaultContext() {
    return m_ctx;
}

void HermesFault::postExecutionNotification() {
    //Notification notification = new FaultNotification(m_faultID);
    //m_runtime.notification(notification, NOTIFICATION_TIMEOUT);
}

void HermesFault::setRuntime(HermesRuntime* runtime) {
    m_runtime = runtime;
}

bool HermesFault::trigger() {
    switch (m_triggerType) {
        case TRIGGER_ALWAYS:
            return true;
        case TRIGGER_ONCE:
            return true;
        case TRIGGER_CUSTOM:
            return customTriggerChecker();
        case TRIGGER_DISABLED:
        default:
            return false;
    }
}

bool HermesFault::isEnabled() {
    //return m_enable;
    switch (m_triggerType) {
        case TRIGGER_ALWAYS:
        case TRIGGER_ONCE:
            return true;
        case TRIGGER_CUSTOM:
            return customTriggerChecker();
        case TRIGGER_DISABLED:
        default:
            return false;
    }
}

void HermesFault::disable() {
    m_triggerType = TRIGGER_DISABLED;
}

void HermesFault::toString(String str) {
    //str = "HermesFault:" + m_faultID + " sync=" + m_synchronizedFault;
}

bool HermesFault::customTriggerChecker() {
    //double check if this fault was disabled
    if (m_triggerType == TRIGGER_DISABLED) {
        return false;
    }
    if (m_customChecker == 0) {
        return true;
    } else {
        return m_customChecker->customTriggerChecker(this);
    }
}

bool HermesFault::checkForInjectingFault(long timeout) throw (HermesRuntimeException&) {
    CheckFaultInjectionAction* action =
            new CheckFaultInjectionAction(m_runtime->getRuntimeID(), m_faultID, m_ctx);
    CheckFaultInjectionActionResult* result =
            (CheckFaultInjectionActionResult*) m_runtime->action(action, timeout);
    printf("CheckFaultInjectionActionResult(%d)\n",result->getCheck());
    return result->getCheck();
}

void HermesFault::serializableImpl(OutputStream& outputStream) throw (SerializationException&) {

}

void HermesFault::deserializableImpl(InputStream& inputStream) throw (SerializationException&) {

}

void HermesFault::postExecute() throw (HermesRuntimeException&) {
    postExecutionNotification();
}

void HermesFault::preExecute() throw (HermesRuntimeException&) {
    if (checkForInjectingFault(NOTIFICATION_TIMEOUT)==0) {
        //Logger.getLogger(HermesFault.class.getName()).log(Level.INFO,
        //      "HermesFault: preExecute(): FaultID not synchronized");
        throw HermesRuntimeException("Synchronization failed");
    }
    if (m_triggerType == TRIGGER_ONCE) {
        disable();
    }
    //if (HermesConfig.DEBUG) {
    //    Logger.getLogger(HermesFault.class.getName()).log(Level.INFO,
    //            "HermesFault: preExecute(): FaultID synchronized, can be executed!");
    //}
}