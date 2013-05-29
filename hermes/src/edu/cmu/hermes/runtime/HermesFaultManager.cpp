/* 
 * File:   HermesFaultManager.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 10:05 AM
 */

#include "HermesFaultManager.h"
#include <hermes/runtime/HermesFault.h>

HermesFaultManager::HermesFaultManager() {
}

HermesFaultManager::HermesFaultManager(const HermesFaultManager& orig) {
}

HermesFaultManager::~HermesFaultManager() {
}

void HermesFaultManager::addFault(HermesFaultPtr& aspect) {
    m_aspectMap.bind(aspect->getFaultID(), aspect);
}

void HermesFaultManager::getFault(const String& faultId, HermesFaultPtr& fault) {
    m_aspectMap.find(faultId, fault);
}