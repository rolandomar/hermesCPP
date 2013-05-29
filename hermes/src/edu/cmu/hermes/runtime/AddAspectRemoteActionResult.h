/* 
 * File:   AddAspectRemoteActionResult.h
 * Author: rmartins
 *
 * Created on May 2, 2013, 7:06 PM
 */

#ifndef ADDASPECTREMOTEACTIONRESULT_H
#define	ADDASPECTREMOTEACTIONRESULT_H

#include <hermes/runtime/RemoteActionResult.h>
class AddAspectRemoteActionResult: public RemoteActionResult {
public:
    static const int SERIAL_ID = 6000011;
    AddAspectRemoteActionResult(): m_result(false){
    }
    AddAspectRemoteActionResult(bool result) {
        m_result = result;        
    }
    
    virtual ~AddAspectRemoteActionResult();
    
    int getSerialID() {
        return SERIAL_ID;
    }
protected:
    bool m_result;
    
    void serializeActionResult(OutputStream& outputStream) throw (SerializationException&){
        outputStream.write_boolean(m_result);
    }
    void deserializableActionResult(InputStream& inputStream) throw (SerializationException&){
        inputStream.read_boolean(m_result);
    }

};

#endif	/* ADDASPECTREMOTEACTIONRESULT_H */

//public class AddAspectRemoteActionResult extends RemoteActionResult {
//
//    public static int SERIAL_ID = 6000011;
//
//    boolean m_result = false;
//
//    public AddAspectRemoteActionResult() {
//    }
//
//    public AddAspectRemoteActionResult(boolean result) {
//        m_result = result;        
//    }
//    
//    @Override
//    public int getSerialID() {
//        return SERIAL_ID;
//    }
//
//    public boolean getResult(){
//        return m_result;
//    }
//        
//
//    @Override
//    protected void serializeActionResult(ByteBuffer buf) throws Exception {
//        HermesSerializableHelper.serializeBoolean(buf, m_result);       
//    }
//
//    @Override
//    protected void deserializableActionResult(ByteBuffer buf) throws Exception {
//        m_result = HermesSerializableHelper.deserializeBoolean(buf);
//    }
//}
