/* 
 * File:   ActionResultFactory.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 4:09 PM
 */

#ifndef ACTIONRESULTFACTORY_H
#define	ACTIONRESULTFACTORY_H

#include <hermes/runtime/CheckFaultInjectionActionResult.h>

class ActionResultFactory {
public:
    virtual ~ActionResultFactory();

    static ActionResult* getActionResultImpl(int serialID) {
        ActionResult* actionReply = 0;
        switch(serialID){
            case CheckFaultInjectionActionResult::SERIAL_ID:{
                 actionReply = new CheckFaultInjectionActionResult();
                 break;
            }
            
        }
        return actionReply;
    }

};

#endif	/* ACTIONRESULTFACTORY_H */

