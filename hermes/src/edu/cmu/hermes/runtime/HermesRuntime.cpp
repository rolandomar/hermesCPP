/* 
 * File:   HermesRuntime.cpp
 * Author: rmartins
 * 
 * Created on April 24, 2013, 11:44 AM
 */

#include "HermesRuntime.h"
#include <hermes/runtime/DefaultRemoteActionHandler.h>

//HermesRuntimePtr HermesRuntime::hermesRuntime(new HermesRuntime());
HermesRuntime* HermesRuntime::hermesRuntime(new HermesRuntime());

HermesRuntime::~HermesRuntime() {
}

HermesRuntime::HermesRuntime() {
    getRandomUUID(m_id);
    isActive = true;
    m_remoteActionHandler = new DefaultRemoteActionHandler(this);
}

HermesRuntime::HermesRuntime(String& id) {
    m_id = id;
    isActive = true;
    m_remoteActionHandler = new DefaultRemoteActionHandler(this);
}

//HermesRuntimePtr& HermesRuntime::getInstance() {

HermesRuntime* HermesRuntime::getInstance() {
    return hermesRuntime;
}