/* 
 * File:   DefaultRemoteActionHandler.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 12:52 PM
 */

#include "DefaultRemoteActionHandler.h"

#include <hermes/runtime/HermesRuntime.h>

DefaultRemoteActionHandler::~DefaultRemoteActionHandler() {
}

RemoteActionResult* DefaultRemoteActionHandler::remoteAction(RemoteAction* remoteAction) {
    //printf("DefaultRemoteActionHandler: onRemoteAction() id="+remoteAction.getSerialID());
    switch (remoteAction->getSerialID()) {
        case GetStateRemoteAction::SERIAL_ID:
        {
            //TODO!
            //GetStateActionResult result = new GetStateActionResult(1001);
            //System.out.println("DefaultRemoteActionHandler: onRemoteAction(): getstate");
            //return result;
            return 0;
        }
        case AddAspectRemoteAction::SERIAL_ID:
        {
            //System.out.println("DefaultRemoteActionHandler: AddAspectRemoteAction()");
            printf("AddAspectRemoteAction");
            AddAspectRemoteAction* addAspectAction = (AddAspectRemoteAction*) remoteAction;
            addAspectAction->getFault()->setRuntime(m_runtime);
            //System.out.println("DefaultRemoteActionHandler: AddAspectRemoteAction() faultid="+
            //        addAspectAction.getFault().getFaultID());
            m_runtime->getFaultManager().addFault(addAspectAction->getFault());
            AddAspectRemoteActionResult* result = new AddAspectRemoteActionResult(true);
            return result;
            //return 0;
        }
    }
    //System.out.println("DefaultRemoteActionHandler: onRemoteAction(): null");
    return 0;
}