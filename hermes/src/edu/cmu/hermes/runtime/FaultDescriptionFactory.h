/* 
 * File:   FaultDescriptionFactory.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 2:01 PM
 */

#ifndef FAULTDESCRIPTIONFACTORY_H
#define	FAULTDESCRIPTIONFACTORY_H

#include <hermes/runtime/CPULoaderFaultDescription.h>
#include <hermes/runtime/NetworkCorrupterFaultDescription.h>
#include <hermes/runtime/ThreadDelayFaultDescription.h>
#include <hermes/runtime/NetworkCorrupterFaultDescription.h>
#include <hermes/runtime/BFTDelayPacketFaultDescription.h>


class FaultDescriptionFactory {
public:
    FaultDescriptionFactory();
    FaultDescriptionFactory(const FaultDescriptionFactory& orig);
    virtual ~FaultDescriptionFactory();
    
    static FaultDescriptionFactory* getInstance(){
        return m_staticInstance;
    }
    
    FaultDescription* getFaultDescriptionImpl(int serialID) {
        switch(serialID){
            case CPULoaderFaultDescription::SERIAL_ID:{
                return new CPULoaderFaultDescription();                
            }
            case NetworkCorrupterFaultDescription::SERIAL_ID:{
                return new NetworkCorrupterFaultDescription();                
            }
            case ThreadDelayFaultDescription::SERIAL_ID:{
                return new ThreadDelayFaultDescription();
            }
            case BFTDelayPacketFaultDescription::SERIAL_ID:{
                return new BFTDelayPacketFaultDescription();
            }
            
        }
        return 0;
    }
protected:
    static FaultDescriptionFactory* m_staticInstance;
};

#endif	/* FAULTDESCRIPTIONFACTORY_H */
