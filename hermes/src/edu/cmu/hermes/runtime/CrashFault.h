/* 
 * File:   CrashFault.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:39 AM
 */

#ifndef CRASHFAULT_H
#define	CRASHFAULT_H

#include <hermes/runtime/HermesFault.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>

class CrashFault : public HermesFault {
public:
    static const int SERIAL_ID = 0x800001;
    CrashFault();

    CrashFault(String& faultID, bool synch) :
    HermesFault(HermesFault::TRIGGER_ONCE) {
    }

    CrashFault(HermesRuntime* runtime, String& faultID) :
    HermesFault(runtime, faultID, HermesFault::TRIGGER_ONCE) {

    }

    CrashFault(const CrashFault& orig);
    virtual ~CrashFault();

    int getSerialID() {
        return SERIAL_ID;
    }
    
    
    void executeImpl() throw(HermesRuntimeException&) {
        printf("CrashFaultAlgorithm: crashing node!\n");
        exit(0);
    }   

    virtual void toString(String& str) {
        //str = "CrashFaultAlgorithm:" + this.getFaultID() + " sync=" + this.getSynchronizedFaul();        
    }
protected:

    void serializableImpl(OutputStream& outputStream) throw (SerializationException&) {
    }

    
    void deserializableImpl(InputStream& inputStream) throw (SerializationException&) {
    }
};

#endif	/* CRASHFAULT_H */
