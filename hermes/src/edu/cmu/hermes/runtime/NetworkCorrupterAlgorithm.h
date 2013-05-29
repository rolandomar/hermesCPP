/* 
 * File:   NetworkCorrupterAlgorithm.h
 * Author: rmartins
 *
 * Created on May 3, 2013, 1:02 PM
 */

#ifndef NETWORKCORRUPTERALGORITHM_H
#define	NETWORKCORRUPTERALGORITHM_H
#include <hermes/runtime/HermesFault.h>
#include <hermes/runtime/HermesFaultFactory.h>
#include <hermes/runtime/FaultDescriptionFactory.h>

class NetworkCorrupterAlgorithm : public HermesFault {
public:
    static const int SERIAL_ID = 0x800003;

    NetworkCorrupterAlgorithm() {
    }

    NetworkCorrupterAlgorithm(NetworkCorrupterFaultDescription* description) {
        m_faultDescription = description;
    }
    virtual ~NetworkCorrupterAlgorithm();
    int getSerialID() {
        return SERIAL_ID;
    }
    
   void executeImpl() throw (HermesRuntimeException&){
        char* packetBytes = m_arg;
        if(packetBytes == 0 || m_len == 0){
            return;
        }
        if(filterPacket()){
            corruptBytes(packetBytes,m_len);
        }
    }    
protected:
    NetworkCorrupterFaultDescription* m_faultDescription;
    char* m_arg;
    int m_len;

    bool filterPacket() {
        return (getRandomPer() <= m_faultDescription->getCorruptionPercentage());
    }

    int getRandomPer() {
        return ACE_OS::rand()%100;        
    }
    void corruptBytes(char* buffer,int len){
        int numberBytesToCorrupt = ACE_OS::rand()%len;
        for(int i=0; i < numberBytesToCorrupt; i++){
            buffer[ACE_OS::rand()%len] = ACE_OS::rand()%255;
        }
    }
    
    virtual void serializableImpl(OutputStream& outputStream) throw (SerializationException&){
        m_faultDescription->serialize(outputStream);
    }
    virtual void deserializableImpl(InputStream& inputStream) throw (SerializationException&){
        int serialID;
        inputStream.read_long(serialID);
        m_faultDescription =
                (NetworkCorrupterFaultDescription*) FaultDescriptionFactory::
                getInstance()->getFaultDescriptionImpl(serialID);
        m_faultDescription->deserialize(serialID,inputStream);
    }
};

#endif	/* NETWORKCORRUPTERALGORITHM_H */
//
//public class NetworkCorrupterAlgorithm extends HermesFault{// extends FaultAlgorithm {    
//
//    public final static int SERIAL_ID = 0x800003;
//    NetworkCorrupterFaultDescription m_faultDescription;
//    byte[] m_arg = null;
//
//    /*public static void runOnce(NetworkCorrupterFaultDescription description,byte[] packetBytes) {
//        NetworkCorrupterAlgorithm alg = new NetworkCorrupterAlgorithm(description);
//        alg.run(packetBytes);
//    }*/
//
//    public NetworkCorrupterAlgorithm(NetworkCorrupterFaultDescription description) {
//        m_faultDescription = description;
//    }
//
//    
//    /*public void run(byte[] packetBytes){
//        if(packetBytes == null || packetBytes.length==0){
//            return;
//        }
//        if(filterPacket()){
//            randomGenerator.nextBytes(packetBytes);
//        }
//    }*/
//    
//    protected boolean filterPacket() {
//        return (getRandomPer() <= m_faultDescription.getCorruptionPercentage());
//    }
//
//    protected int getRandomPer() {
//        return randomGenerator.nextInt() % 100;
//    }
//    protected static Random randomGenerator = null;
//
//    static {
//        randomGenerator = new Random(System.currentTimeMillis());
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
//                (NetworkCorrupterFaultDescription) FaultDescriptionFactory.
//                getInstance().getFaultDescriptionImpl(serialID);
//        m_faultDescription.deserializable(buf);
//    }
//
//    @Override
//    //public void execute(byte[] packetBytes) throws Exception{
//    public void executeImpl() throws Exception{
//        byte[] packetBytes = m_arg;
//        if(packetBytes == null || packetBytes.length==0){
//            return;
//        }
//        if(filterPacket()){
//            randomGenerator.nextBytes(packetBytes);
//        }
//    }    
//}
