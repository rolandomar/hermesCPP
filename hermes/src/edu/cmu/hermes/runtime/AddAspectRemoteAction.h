/* 
 * File:   AddAspectRemoteAction.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 1:02 PM
 */

#ifndef ADDASPECTREMOTEACTION_H
#define	ADDASPECTREMOTEACTION_H

#include <hermes/runtime/RemoteAction.h>
#include <hermes/runtime/HermesFault.h>

class AddAspectRemoteAction: public RemoteAction {
public:
    static const int SERIAL_ID = 6000010;
    AddAspectRemoteAction();
    AddAspectRemoteAction(HermesFaultPtr& fault):
    m_fault(fault)
    {        
    }
    AddAspectRemoteAction(const AddAspectRemoteAction& orig);
    virtual ~AddAspectRemoteAction();
    
    virtual int getSerialID(){
        return SERIAL_ID;
    }
    
    HermesFaultPtr& getFault(){
        return  m_fault;
    }
protected:
    HermesFaultPtr m_fault;
    virtual void serializeAction(OutputStream& outputStream) throw (SerializationException&);
    
    virtual void deserializableAction(InputStream& inputStream) throw (SerializationException&);
};

#endif	/* ADDASPECTREMOTEACTION_H */

