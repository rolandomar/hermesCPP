/* 
 * File:   HermesFault.h
 * Author: rmartins
 *
 * Created on April 28, 2013, 7:23 PM
 */

#ifndef HERMESFAULT_H
#define	HERMESFAULT_H

#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <euryale/Types.h>

#include <hermes/runtime/HermesRuntime.h>
#include <hermes/runtime/HermesRuntimeException.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>


#include <hermes/runtime/CheckFaultInjectionAction.h>
#include <hermes/runtime/CheckFaultInjectionActionResult.h>

#include "FaultContext.h"
class FaultCustomTriggerChecker;

class HermesFault {
public:
    static const Byte TRIGGER_DISABLED = 0x0;
    static const Byte TRIGGER_ALWAYS = 0x1;
    static const Byte TRIGGER_ONCE = 0x2;
    static const Byte TRIGGER_CUSTOM = 0x3;
    static const int NOTIFICATION_TIMEOUT = 10000; //ms
    //Scope of the fault, for now defaults to 'global'
    static const String GLOBAL_FAULT_SIGNATURE;

    //HermesFault();
    //HermesFault(const HermesFault& orig);
    virtual ~HermesFault();

    HermesFault();

    HermesFault(Byte triggerType);

    HermesFault(HermesRuntime* runtime, String& id, Byte triggerType);

    HermesFault(HermesRuntime* runtime, String& id, bool synchronizedFault, Byte triggerType) ;

    bool getSynchronizedFaul();
    Byte getTriggerType();

    void setSynchronizedFault(bool synch);
    String getFaultID();

    void setFaultID(String& aspectID);

    virtual void serialize(OutputStream& outputStream) throw (SerializationException&);

    virtual void deserialize(int serial, InputStream& inputStream) throw (SerializationException&);
    virtual void deserialize(InputStream& inputStream) throw (SerializationException&);

    /**
     *
     * @return
     */
    virtual int getSerialID() = 0;

    virtual void executeImpl() throw (HermesRuntimeException&) = 0;

    void execute() throw (HermesRuntimeException&);

    void setFaultContext(FaultContext& ctx) throw (HermesRuntimeException&);

    FaultContext getFaultContext();

    void postExecutionNotification();

    void setRuntime(HermesRuntime* runtime);

    bool trigger();

    bool isEnabled();

    void disable();

    virtual void toString(String str);


protected:
    Byte m_triggerType;
    String m_faultID;
    HermesRuntime* m_runtime;
    bool m_synchronizedFault;
    FaultCustomTriggerChecker* m_customChecker;
    FaultContext m_ctx;

    bool customTriggerChecker();

    virtual bool checkForInjectingFault(long timeout) throw (HermesRuntimeException&);

    virtual void serializableImpl(OutputStream& outputStream) throw (SerializationException&);
    virtual void deserializableImpl(InputStream& inputStream) throw (SerializationException&);

private:

    void postExecute() throw (HermesRuntimeException&);
    void preExecute() throw (HermesRuntimeException&);
};

typedef ACE_Strong_Bound_Ptr<HermesFault, ACE_SYNCH_MUTEX> HermesFaultPtr;

#endif	/* HERMESFAULT_H */

