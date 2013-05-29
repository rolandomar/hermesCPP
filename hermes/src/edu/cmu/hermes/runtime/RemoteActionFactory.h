/* 
 * File:   RemoteActionFactory.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 4:21 PM
 */

#ifndef REMOTEACTIONFACTORY_H
#define	REMOTEACTIONFACTORY_H

#include <hermes/runtime/GetStateRemoteAction.h>
#include <hermes/runtime/AddAspectRemoteAction.h>

class RemoteActionFactory {
public:
 
    virtual ~RemoteActionFactory();
    
    static RemoteAction* getRemoteActionImpl(int serialID) {
        RemoteAction* action = 0;
        switch(serialID){
            case GetStateRemoteAction::SERIAL_ID:{
                 action = new GetStateRemoteAction();
                 break;
            }
            case AddAspectRemoteAction::SERIAL_ID:{
                 action = new AddAspectRemoteAction();
                 break;
            }
            
        }
        return action;
    }
protected:

};

#endif	/* REMOTEACTIONFACTORY_H */

