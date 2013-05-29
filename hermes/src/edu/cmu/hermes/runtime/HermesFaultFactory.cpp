/* 
 * File:   HermesFaultFactory.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 1:07 PM
 */

#include "HermesFaultFactory.h"
#include "ThreadDelayFault.h"
#include "BFTDelayPacketFault.h"
#include "BFTForgePayloadFault.h"
#include <hermes/runtime/HermesFault.h>
#include <hermes/runtime/CPULoaderFaultAlgorithm.h>
#include <hermes/runtime/CrashFault.h>
#include <hermes/runtime/BFTDelayPacketFault.h>
#include <hermes/runtime/BFTForgePayloadFault.h>

HermesFaultFactory* HermesFaultFactory::m_staticInstance = new HermesFaultFactory();

HermesFaultFactory::HermesFaultFactory() {
}

HermesFaultFactory::~HermesFaultFactory() {
}

HermesFaultFactory* HermesFaultFactory::getInstance() {
    return m_staticInstance;
}

void HermesFaultFactory::getAspectImpl(int serialID, HermesFaultPtr& f) {
    switch (serialID) {
        case CPULoaderFaultAlgorithm::SERIAL_ID:
        {
            f.reset(new CPULoaderFaultAlgorithm());
            break;
        }
        case CrashFault::SERIAL_ID:
        {
            f.reset(new CrashFault());
            break;
        }
        case ThreadDelayFault::SERIAL_ID:{
            f.reset(new ThreadDelayFault());
            break;
        }
        
        case BFTDelayPacketFault::SERIAL_ID:{
            f.reset(new BFTDelayPacketFault());
            break;
        }
        
        case BFTForgePayloadFault::SERIAL_ID:{
            f.reset(new BFTForgePayloadFault());
        }
        //case NetworkDropperFault::
    }
}


