/* 
 * File:   FaultDescriptionFactory.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 2:01 PM
 */

#include "FaultDescriptionFactory.h"

FaultDescriptionFactory* FaultDescriptionFactory::m_staticInstance = new FaultDescriptionFactory();

FaultDescriptionFactory::FaultDescriptionFactory() {
}

FaultDescriptionFactory::FaultDescriptionFactory(const FaultDescriptionFactory& orig) {
}

FaultDescriptionFactory::~FaultDescriptionFactory() {
}

