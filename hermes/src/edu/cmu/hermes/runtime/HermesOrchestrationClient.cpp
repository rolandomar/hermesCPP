/* 
 * File:   HermesOrchestrationClient.cpp
 * Author: rmartins
 * 
 * Created on April 30, 2013, 5:57 PM
 */

#include "HermesOrchestrationClient.h"
#include <hermes/runtime/HermesRuntime.h>
#include <hermes/runtime/RemoteAction.h>
#include <hermes/runtime/RemoteActionResult.h>

HermesOrchestrationClient::HermesOrchestrationClient(HermesRuntime* runtime, String& id) : 
m_runtime(runtime), m_id(id), m_channel(0) {
    printf("runtime(%p) this(%p)\n",runtime,this);
}

HermesOrchestrationClient::~HermesOrchestrationClient() {
}

RemoteActionResult* HermesOrchestrationClient::onRemoteAction(RemoteAction* remoteAction) {
    printf("runtime(%p) this(%p)\n",m_runtime,this);
    return m_runtime->onRemoteAction(remoteAction);
}
