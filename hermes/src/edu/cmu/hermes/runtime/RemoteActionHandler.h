/* 
 * File:   RemoteActionHandler.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:49 PM
 */

#ifndef REMOTEACTIONHANDLER_H
#define	REMOTEACTIONHANDLER_H

#include <hermes/runtime/RemoteAction.h>
#include <hermes/runtime/RemoteActionResult.h>

class RemoteActionHandler {
public:
    RemoteActionHandler();
    virtual ~RemoteActionHandler();
    
    virtual RemoteActionResult* remoteAction(RemoteAction* notification) = 0;

};

#endif	/* REMOTEACTIONHANDLER_H */

