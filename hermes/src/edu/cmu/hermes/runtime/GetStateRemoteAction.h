/* 
 * File:   GetStateRemoteAction.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:56 PM
 */

#ifndef GETSTATEREMOTEACTION_H
#define	GETSTATEREMOTEACTION_H

#include <hermes/runtime/RemoteAction.h>

class GetStateRemoteAction: public RemoteAction {
public:
    static const int SERIAL_ID = 6000002;
    GetStateRemoteAction(){}            
    virtual ~GetStateRemoteAction();
    
    int getSerialID(){
        return SERIAL_ID;
    }
protected:
    virtual void serializeAction(OutputStream& outputStream) throw (SerializationException&){
        
    }
    
    virtual void deserializableAction(InputStream& inputStream) throw (SerializationException&){
        
    }

};

#endif	/* GETSTATEREMOTEACTION_H */
