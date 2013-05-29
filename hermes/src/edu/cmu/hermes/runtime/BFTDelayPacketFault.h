/* 
 * File:   BFTDelayPacketFault.h
 * Author: rmartins
 *
 * Created on May 6, 2013, 3:20 PM
 */

#ifndef BFTDELAYPACKETFAULT_H
#define	BFTDELAYPACKETFAULT_H

#include <hermes/runtime/HermesFault.h>
#include <hermes/runtime/FaultDescriptionFactory.h>


class BFTDelayPacketFault: public HermesFault{
public:
    static const int SERIAL_ID = 0x1201000;

    BFTDelayPacketFault() {
    }

    BFTDelayPacketFault(HermesRuntime* runtime, String& faultID,
            BFTDelayPacketFaultDescription* fd, Byte triggerType) :
    HermesFault(runtime, faultID, triggerType), m_fd(fd) {
    }

    BFTDelayPacketFault(String& faultID, BFTDelayPacketFaultDescription* fd,
            Byte triggerType) :
    HermesFault(0, faultID, triggerType), m_fd(fd) {

    }
    
    int getSerialID(){
        return SERIAL_ID;
    }
       
    virtual ~BFTDelayPacketFault();
        
    void executeImpl() throw (HermesRuntimeException&) {
        //Thread.sleep(0, (int) (m_fd.getDelay() * 1000));
        printf("BFTDelayPacketFault:before fault: sleep(%d)\n",m_fd->getDelay());
        sleep(m_fd->getDelay());
        printf("BFTDelayPacketFault:after fault\n");
    }
protected:
    BFTDelayPacketFaultDescription* m_fd;
    
     void serializableImpl(OutputStream& outputStream) throw (SerializationException&) {
        m_fd->serialize(outputStream);
    }

    void deserializableImpl(InputStream& inputStream) throw (SerializationException&) {
        int serialID;
        inputStream.read_long(serialID);
        m_fd =
                (BFTDelayPacketFaultDescription*) FaultDescriptionFactory::
                getInstance()->getFaultDescriptionImpl(serialID);
        m_fd->deserialize(serialID, inputStream);
    }

};

#endif	/* BFTDELAYPACKETFAULT_H */

//    public BFTDelayPacketFault(String faultID, BFTDelayPacketFaultDescription fd,
//            byte triggerType) {
//        super(null, faultID, triggerType);
//        m_fd = fd;
//    }
//
//    @Override
//    public int getSerialID() {
//        return SERIAL_ID;
//    }
//
//    @Override
//    protected void serializableImpl(ByteBuffer buf) throws Exception {
//        m_fd.serializable(buf);
//    }
//
//    @Override
//    protected void deserializableImpl(ByteBuffer buf) throws Exception {
//        int serialID = buf.getInt(buf.position());
//        m_fd =
//                (BFTDelayPacketFaultDescription) FaultDescriptionFactory.
//                getInstance().getFaultDescriptionImpl(serialID);
//        m_fd.deserializable(buf);
//    }
//
//    @Override
//    public void executeImpl() throws Exception {
//        //Thread.sleep(0, (int) (m_fd.getDelay() * 1000));
//        System.out.println("BFTDelayPacketFault:before faullt");
//        Thread.sleep(m_fd.getDelay() * 1000);
//        System.out.println("BFTDelayPacketFault:after faullt");
//    }
//
//    @Override
//    public String toString() {
//        String str = "BFTDelayPacketSequence:" + this.getFaultID()
//                + " sync:" + this.getSynchronizedFaul()
//                + " delay:" + m_fd.getDelay();
//        return str;
//    }
//}