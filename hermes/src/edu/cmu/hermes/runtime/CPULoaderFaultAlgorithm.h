/* 
 * File:   CPULoaderFaultAlgorithm.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 1:19 PM
 */

#ifndef CPULOADERFAULTALGORITHM_H
#define	CPULOADERFAULTALGORITHM_H

#include <hermes/runtime/HermesFault.h>
#include <hermes/runtime/FaultDescription.h>
#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>

#include "FaultDescriptionFactory.h"
#include "CPULoaderFaultDescription.h"

#include <euryale/qos/cpu_qos/CPUQoS.h>
#include <euryale/qos/cpu_qos/CPUReservation.h>
#include <euryale/threading/Task.h>
#include <ace/Recursive_Thread_Mutex.h>

#include <ace/Time_Value.h>
#include <euryale/threading/Task.h>

class CPULoaderFaultAlgorithmLoader : public Task {
public:
    static int const MAXBURNPERIOD = 999999; //50000
    //static int const MAXBURNPERIOD  = 10;//50000
    CPULoaderFaultAlgorithmLoader();
    virtual ~CPULoaderFaultAlgorithmLoader();

    int open(int load,
            int threads = ACE_OS::num_processors(),
            ACE_Time_Value* timeout = 0,
            CPUReservation* reserve = 0,
            CPUQoS* qos = 0, bool verbose = false);

    virtual int svc_i(void* arg);

    void close(bool waitForFinish);

protected:
    ACE_Time_Value* m_timeout;
    bool m_open;
    bool m_closed;
    int m_load;
    int m_threads;
    bool m_verbose;

    virtual int close(u_long flags = 0) {
        return 0;
    }
    bool isActive();
    ACE_Time_Value* calculatePeriod(int load, int threads);
    ACE_Time_Value* calculatePeriodWithVariableTimeUnit(int load, int timeUnit);

};

class CPULoaderFaultAlgorithm : public HermesFault {
public:
    static const int SERIAL_ID = 0x800000;
    CPULoaderFaultAlgorithm();

    CPULoaderFaultAlgorithm(HermesRuntime* runtime, String& faultID,
            CPULoaderFaultDescription* description, Byte triggerType) :
    HermesFault(runtime, faultID, triggerType), m_faultDescription(description) {
    }
    CPULoaderFaultAlgorithm(const CPULoaderFaultAlgorithm& orig);
    virtual ~CPULoaderFaultAlgorithm();

    CPULoaderFaultDescription* getFaultDescription() {
        return m_faultDescription;
    }

    int getSerialID() {
        return SERIAL_ID;
    }

    virtual void serializableImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(getSerialID());
        m_faultDescription->serialize(outputStream);
    }

    virtual void deserializableImpl(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw SerializationException(SerializationException::BAD_STREAM);
        }
        m_faultDescription =
                (CPULoaderFaultDescription*) FaultDescriptionFactory::
                getInstance()->getFaultDescriptionImpl(CPULoaderFaultDescription::SERIAL_ID);
        m_faultDescription->deserialize(inputStream);
    }
    
    virtual void deserializableImpl(int serial,InputStream& inputStream) throw (SerializationException&) {
        if (serial != getSerialID()) {
            throw SerializationException(SerializationException::BAD_STREAM);
        }
        m_faultDescription =
                (CPULoaderFaultDescription*) FaultDescriptionFactory::
                getInstance()->getFaultDescriptionImpl(CPULoaderFaultDescription::SERIAL_ID);
        m_faultDescription->deserialize(inputStream);
    }

    virtual void executeImpl() throw (HermesRuntimeException&) {
        CPULoaderFaultAlgorithmLoader loader;
        loader.open(m_faultDescription->getLoad(),
                m_faultDescription->getNoThreads());
        loader.wait();
    }

    //    @Override

    void toString(String& str) {
        //str = "CPULoaderFaultAlgorithm:" + this.getFaultID() + " sync=" + this.getSynchronizedFaul() + " ";
                //+m_faultDescription.toString();
    }
    //

protected:
    CPULoaderFaultDescription* m_faultDescription;

    //protected static Random randomGenerator = null;
    //
    //    static {
    //        randomGenerator = new Random(System.currentTimeMillis());
    //        //randomGenerator.
    //
    //    }
};

#endif	/* CPULOADERFAULTALGORITHM_H */

