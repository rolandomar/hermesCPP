/* 
 * File:   RemoteActionResultFactory.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 4:38 PM
 */

#ifndef REMOTEACTIONRESULTFACTORY_H
#define	REMOTEACTIONRESULTFACTORY_H

#include <hermes/runtime/RemoteActionResult.h>

class RemoteActionResultFactory {
public:    
    virtual ~RemoteActionResultFactory();

    static RemoteActionResult* getRemoteActionResultImpl(int serialID) {
        RemoteActionResult* remoteActionResult = 0;
        //switch(serialID){
            
            
        //}
        return remoteActionResult;
    }

};

#endif	/* REMOTEACTIONRESULTFACTORY_H */

