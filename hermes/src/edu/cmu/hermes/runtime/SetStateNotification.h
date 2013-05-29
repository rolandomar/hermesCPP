/* 
 * File:   SetStateNotification.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:40 PM
 */

#ifndef SETSTATENOTIFICATION_H
#define	SETSTATENOTIFICATION_H

#include <hermes/runtime/Notification.h>

class SetStateNotification : public Notification {
public:
    static const int SETSTATENOTIFICATION_SERIALID = 20000001;
    SetStateNotification();

    SetStateNotification(String srcID, String stateID, String signature, int mutationNo) :
    Notification(srcID) {
        m_stateID = stateID;
        m_signature = signature;
        m_mutationNo = mutationNo;
    }
    SetStateNotification(const SetStateNotification& orig);
    virtual ~SetStateNotification();

    String& getStateID() {
        return m_stateID;
    }

    int getMutationNo() {
        return m_mutationNo;
    }

    int getSerialID() {
        return SETSTATENOTIFICATION_SERIALID;
    }

    
    
protected:
    String m_stateID;
    int m_mutationNo;
    String m_signature;
    
    virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&){
        outputStream.write_string(m_stateID);
        outputStream.write_string(m_signature);
        outputStream.write_long(m_mutationNo);        
    }
    
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&){
        inputStream.read_string(m_stateID);
        inputStream.read_string(m_signature);
        inputStream.read_long(m_mutationNo);
    }
};

#endif	/* SETSTATENOTIFICATION_H */
//
//    
//
//    @Override
//    protected void serializeNotification(ByteBuffer buf) {
//        HermesSerializableHelper.serializeString(buf, m_stateID);
//        HermesSerializableHelper.serializeString(buf, m_signature);
//        buf.putInt(m_mutationNo);
//    }
//
//    @Override
//    protected void deserializableNotification(ByteBuffer buf) throws Exception {
//        m_stateID = HermesSerializableHelper.deserializeString(buf);
//        m_signature = HermesSerializableHelper.deserializeString(buf);
//        m_mutationNo = buf.getInt();
//    }
//
//    @Override
//    public final int getSerialID() {
//        return SETSTATENOTIFICATION_SERIALID;
//    }
//    
//     @Override
//    public String toString(){
//        return "SetStateNotification ("+m_srcID+","+m_stateID+","+m_signature+","+m_mutationNo+")";
//    }
//}
