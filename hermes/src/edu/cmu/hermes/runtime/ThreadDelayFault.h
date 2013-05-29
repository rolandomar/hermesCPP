/* 
 * File:   ThreadDelayFault.h
 * Author: rmartins
 *
 * Created on May 3, 2013, 2:06 PM
 */

#ifndef THREADDELAYFAULT_H
#define	THREADDELAYFAULT_H

#include <hermes/runtime/HermesFault.h>
#include <hermes/runtime/FaultDescriptionFactory.h>

class ThreadDelayFault : public HermesFault {
public:
    static int const SERIAL_ID = 0x810000;

    ThreadDelayFault() {
    }

//    ThreadDelayFault(ThreadDelayFaultDescription* faultDescription) : m_faultDescription(faultDescription) {
//    }

    ThreadDelayFault(HermesRuntime* runtime,
            String& faultID,
            ThreadDelayFaultDescription* description, Byte triggerType) :
    HermesFault(runtime, faultID, triggerType) {

        m_faultDescription = description;
    }

    ThreadDelayFault(
            String& faultID,
            ThreadDelayFaultDescription* description, Byte triggerType) :
    HermesFault(0, faultID, triggerType) {
        m_faultDescription = description;
    }

    ThreadDelayFaultDescription* getFaultDescription() {
        return m_faultDescription;
    }

    virtual ~ThreadDelayFault();

    void executeImpl() throw (HermesRuntimeException&) {
        sleep(m_faultDescription->getDuration() / 1000);
    }

    int getSerialID() {
        return SERIAL_ID;
    }
protected:
    ThreadDelayFaultDescription* m_faultDescription;

    void serializableImpl(OutputStream& outputStream) throw (SerializationException&) {
        m_faultDescription->serialize(outputStream);
    }

    void deserializableImpl(InputStream& inputStream) throw (SerializationException&) {
        int serialID;
        inputStream.read_long(serialID);
        m_faultDescription =
                (ThreadDelayFaultDescription*) FaultDescriptionFactory::
                getInstance()->getFaultDescriptionImpl(serialID);
        m_faultDescription->deserialize(serialID, inputStream);
    }

};

#endif	/* THREADDELAYFAULT_H */

// public final static int SERIAL_ID = 0x810000;
//    ThreadDelayFaultDescription m_faultDescription;
//
//    public ThreadDelayFault() {
//    }
//
//    public ThreadDelayFault(HermesRuntime runtime,
//            String faultID,
//            ThreadDelayFaultDescription description, byte triggerType) {
//        super(runtime, faultID, triggerType);
//        m_faultDescription = description;
//    }
//    
//     public ThreadDelayFault(
//            String faultID,
//            ThreadDelayFaultDescription description, byte triggerType) {
//        super(null, faultID, triggerType);
//        m_faultDescription = description;
//    }
//
//    public ThreadDelayFaultDescription getFaultDescription() {
//        return m_faultDescription;
//    }
//    
//    @Override    
//    public int getSerialID() {
//        return SERIAL_ID;
//    }
//
//    @Override
//    protected void serializableImpl(ByteBuffer buf) throws Exception {
//        m_faultDescription.serializable(buf);
//    }
//
//    @Override
//    protected void deserializableImpl(ByteBuffer buf) throws Exception {
//        int serialID = buf.getInt(buf.position());
//        m_faultDescription =
//                (ThreadDelayFaultDescription) FaultDescriptionFactory.
//                getInstance().getFaultDescriptionImpl(serialID);
//        m_faultDescription.deserializable(buf);
//    }
//    
//    @Override
//    public void executeImpl() throws Exception{
//        System.out.println("ThreadDelayFaultAlgorithm before sleep of "+m_faultDescription.getDuration());
//        Thread.sleep(m_faultDescription.getDuration());
//        System.out.println("ThreadDelayFaultAlgorithm after sleep of "+m_faultDescription.getDuration());
//    }   
