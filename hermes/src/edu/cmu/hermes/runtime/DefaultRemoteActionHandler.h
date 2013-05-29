/* 
 * File:   DefaultRemoteActionHandler.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:52 PM
 */

#ifndef DEFAULTREMOTEACTIONHANDLER_H
#define	DEFAULTREMOTEACTIONHANDLER_H

#include <hermes/runtime/RemoteActionHandler.h>
#include <hermes/runtime/GetStateRemoteAction.h>
#include <hermes/runtime/AddAspectRemoteAction.h>
#include <hermes/runtime/AddAspectRemoteActionResult.h>
#include <hermes/runtime/RemoteActionHandler.h>

class Runtime;
class DefaultRemoteActionHandler : public RemoteActionHandler {
public:

    DefaultRemoteActionHandler(HermesRuntime* runtime) :
    m_runtime(runtime) {}    
    virtual ~DefaultRemoteActionHandler();

    RemoteActionResult* remoteAction(RemoteAction* remoteAction);
    
protected:
    HermesRuntime* m_runtime;

};

#endif	/* DEFAULTREMOTEACTIONHANDLER_H */
