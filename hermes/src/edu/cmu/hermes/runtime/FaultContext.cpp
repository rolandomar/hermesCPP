/* 
 * File:   FaultContext.cpp
 * Author: rmartins
 * 
 * Created on April 28, 2013, 7:52 PM
 */

#include "FaultContext.h"

FaultContext::FaultContext() {
}

FaultContext::FaultContext(const FaultContext& orig) {
    FaultContextMap::CONST_ITERATOR iter = orig.m_ctx.begin();
    while (iter != orig.m_ctx.end()) {
        m_ctx.bind((*iter).key(), (*iter).item());
        iter++;
    }
}

FaultContext::~FaultContext() {
}

