/* 
 * File:   ActionRequestPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 3:22 PM
 */

#ifndef ACTIONREQUESTPACKET_H
#define	ACTIONREQUESTPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/Action.h>
#include <hermes/runtime/ActionFactory.h>

class ActionRequestPacket : public HermesAbstractPacket {
public:
    static const int ACTIONREQUESTY_OPCODE = 0x002000;
    ActionRequestPacket(){}
    ActionRequestPacket(int requestNo, Action* action) :
    HermesAbstractPacket(ACTIONREQUESTY_OPCODE, 0), m_action(action),m_requestNo(requestNo) {
    }
    ActionRequestPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }
    virtual ~ActionRequestPacket();
    
    int getRequestNo(){
        return m_requestNo;
    }
    
protected:
    Action* m_action;
    int m_requestNo;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {        
        outputStream.write_long(m_requestNo);
        m_action->serialize(outputStream);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        int serialID;
        inputStream.read_long(serialID);
        m_action = ActionFactory::getActionImpl(serialID);
        m_action->deserialize(serialID, inputStream);
    }
};

#endif	/* ACTIONREQUESTPACKET_H */

//public class ActionRequestPacket extends TwoWayRequest {
//    public static final int ACTIONREQUESTY_OPCODE = 0x002000;
//    private Action m_action;
//
//    
//    public ActionRequestPacket() {
//        
//    }
//    
//    public ActionRequestPacket(HermesAbstractPacketHeader header) {
//        super(header);
//    }
//    
//    public ActionRequestPacket(int requestNo,Action action) {
//        super(requestNo);        
//        m_header.setOpcode(ACTIONREQUESTY_OPCODE);
//        m_action = action;
//    }
//
//    public Action getAction() {
//        return m_action;
//    }
//
//    @Override
//    protected void serializeTwoWayRequestBody(ByteBuffer buf) throws Exception{
//        m_action.serializable(buf);
//    }
//
//    @Override
//    protected void deserializeTwoWayRequestBody(ByteBuffer buf) throws Exception {        
//        
//        int serialID = buf.getInt(buf.position());
//        m_action = ActionFactory.getInstance().getActionImpl(serialID);
//        m_action.deserializable(buf);
//    }
//}