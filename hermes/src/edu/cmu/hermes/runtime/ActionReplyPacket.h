/* 
 * File:   ActionReplyPacket.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 3:52 PM
 */

#ifndef ACTIONREPLYPACKET_H
#define	ACTIONREPLYPACKET_H

#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/ActionResult.h>
#include <hermes/runtime/ActionResultFactory.h>

class ActionReplyPacket : public HermesAbstractPacket {
public:
    static const int ACTIONREPLY_OPCODE = 0x002001;

    ActionReplyPacket() {
    }

    ActionReplyPacket(HermesAbstractPacketHeader* header) :
    HermesAbstractPacket(header) {
    }

    ActionReplyPacket(int requestID, ActionResult* actionResult) :
    HermesAbstractPacket(ACTIONREPLY_OPCODE, requestID), m_result(actionResult) {
    }

    ActionResult* dettachActionResult() {
        ActionResult* result = m_result;
        m_result = 0;
        return result;
    }

    virtual ~ActionReplyPacket();

    int getRequestNo() {
        return m_requestNo;
    }
protected:
    ActionResult* m_result;
    int m_requestNo;

    virtual void
    serializeBody(OutputStream& outputStream) THROW(SerializationException&) {
        outputStream.write_long(m_requestNo);
        m_result->serialize(outputStream);
    }

    virtual void
    deserializeBody(InputStream& inputStream) THROW(SerializationException&) {
        inputStream.read_long(m_requestNo);
        int serialID;
        inputStream.read_long(serialID);
        m_result = ActionResultFactory::getActionResultImpl(serialID);
        m_result->deserialize(serialID, inputStream);
    }

};

#endif	/* ACTIONREPLYPACKET_H */

//public class ActionReplyPacket extends TwoWayRequest {
//    
//    public static final int ACTIONREPLY_OPCODE = 0x002001;
//    
//    private ActionResult m_result;
//
//    public ActionReplyPacket() {
//        
//    }
//    
//    public ActionReplyPacket(HermesAbstractPacketHeader header) {
//        super(header);
//    }
//    
//    public ActionReplyPacket(int requestNo,ActionResult result) {
//        super(requestNo);
//        m_header.setOpcode(ACTIONREPLY_OPCODE);
//        m_result = result;        
//    }
//    
//    
//    public ActionResult getActionResult(){
//        return m_result;
//    }
//
//    @Override
//    protected void serializeTwoWayRequestBody(ByteBuffer buf) throws Exception {
//        m_result.serializable(buf);
//    }
//
//    @Override
//    protected void deserializeTwoWayRequestBody(ByteBuffer buf) throws Exception {
//        int serialID = buf.getInt(buf.position());
//        m_result = ActionFactory.getInstance().getActionResultImpl(serialID);
//        m_result.deserializable(buf);
//    }
//}