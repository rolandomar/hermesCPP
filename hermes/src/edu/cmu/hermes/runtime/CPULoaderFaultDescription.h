/* 
 * File:   CPULoaderFaultDescription.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 1:21 PM
 */

#ifndef CPULOADERFAULTDESCRIPTION_H
#define	CPULOADERFAULTDESCRIPTION_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>
#include <hermes/runtime/FaultDescription.h>

class CPULoaderFaultDescription: public FaultDescription{
public:
    static const int SERIAL_ID = 123123981;
    int m_noThreads;
    int m_duration;
    int m_load;

    CPULoaderFaultDescription(){}
    
    CPULoaderFaultDescription(int noThreads, int duration,
            int load) {
        m_noThreads = 0;
        m_duration = 0;
        m_load = load;
    }
    CPULoaderFaultDescription(const CPULoaderFaultDescription& orig){
        m_noThreads = orig.m_noThreads;
        m_duration = orig.m_duration;
        m_load = orig.m_load;
    }
    virtual ~CPULoaderFaultDescription();

    int getSerialID() {
        return SERIAL_ID;
    }

    int getNoThreads() {
        return m_noThreads;
    }

    int getDuration() {
        return m_duration;
    }

    int getLoad() {
        return m_load;
    }
protected:
    

    void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(m_noThreads);
        outputStream.write_long(m_duration);
        outputStream.write_long(m_load);
    }

    void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_long(m_noThreads);
        inputStream.read_long(m_duration);
        inputStream.read_long(m_load);
    }

    void toString(String& str) {
        //        str = "CPULoaderFaultDescription: noThreads=" + m_noThreads + " " +
        //                "duration=" + m_duration + " " +
        //                "load=" + m_load;        
    }
};

#endif	/* CPULOADERFAULTDESCRIPTION_H */
