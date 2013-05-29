/* 
 * File:   HermesRuntmeContext.cpp
 * Author: rmartins
 * 
 * Created on April 28, 2013, 11:09 AM
 */

#include <hermes/runtime/HermesRuntimeContext.h>

HermesRuntimeContext::HermesRuntimeContext() {
}

HermesRuntimeContext::HermesRuntimeContext(const HermesRuntimeContext& orig) {
    ObjectMap::CONST_ITERATOR iter = orig.m_map.begin();
    while (iter != orig.m_map.end()) {
        m_map.bind((*iter).key(),(*iter).item());
        iter++;
    }
}

HermesRuntimeContext::~HermesRuntimeContext() {
}

