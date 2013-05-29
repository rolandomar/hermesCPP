/* 
 * File:   ActionFactory.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 3:30 PM
 */

#ifndef ACTIONFACTORY_H
#define	ACTIONFACTORY_H

#include <hermes/runtime/CheckFaultInjectionAction.h>

class ActionFactory {
public:
    ActionFactory(){}
 
    virtual ~ActionFactory();

    static Action* getActionImpl(int serialID) {
        Action* action = 0;
        switch(serialID){
            case CheckFaultInjectionAction::SERIAL_ID:{
                 action = new CheckFaultInjectionAction();
                 break;
            }
            
        }
        return action;
    }


};

#endif	/* ACTIONFACTORY_H */

