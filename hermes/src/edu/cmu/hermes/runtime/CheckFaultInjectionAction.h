/* 
 * File:   CheckFaultInjectionAction.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:57 AM
 */

#ifndef CHECKFAULTINJECTIONACTION_H
#define	CHECKFAULTINJECTIONACTION_H

#include <hermes/runtime/Action.h>
#include <hermes/runtime/FaultContext.h>

class CheckFaultInjectionAction : public Action {
public:
    static const int SERIAL_ID = 5000004;
    CheckFaultInjectionAction(){}    
    virtual ~CheckFaultInjectionAction();

    CheckFaultInjectionAction(String& srcID, String& faultID) :
    Action(srcID, ""), m_faultID(faultID) {
    }

    CheckFaultInjectionAction(String& srcID, String& faultID, FaultContext& ctx) :
    Action(srcID, ""), m_faultID(faultID), m_ctx(ctx) {
    }    

    int getSerialID() {
        return SERIAL_ID;
    }

    FaultContext& getFaultContext() {
        return m_ctx;
    }

    String& getFaultID() {
        return m_faultID;
    }

protected:
    String m_faultID;
    FaultContext m_ctx;

    void serializeAction(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_string(m_faultID);        
        m_ctx.serialize(outputStream);
    }

    void deserializableAction(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_string(m_faultID);        
        m_ctx.deserialize(inputStream);        
    }

};

#endif	/* CHECKFAULTINJECTIONACTION_H */
