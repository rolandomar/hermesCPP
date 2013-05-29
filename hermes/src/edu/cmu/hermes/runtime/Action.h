/* 
 * File:   Action.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:50 AM
 */

#ifndef ACTION_H
#define	ACTION_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>
#include <hermes/runtime/HermesRuntimeException.h>

class Action: public Serializable{
public:
    Action();

    Action(String& srcID, const char* action) {
         m_srcID = srcID;
        m_action = action;
    }
    
    Action(String& srcID, String& action) {
        m_srcID = srcID;
        m_action = action;

    }
    Action(const Action& orig);
    virtual ~Action();
    
    virtual int getSerialID() = 0;

    String& getSourceID() {
        return m_srcID;
    }

    String& getAction() {
        return m_action;
    }
    void serialize(OutputStream& outputStream) throw (SerializationException&) {    
        outputStream.write_long(getSerialID());
        outputStream.write_string(m_srcID);
        outputStream.write_string(m_action);
        serializeAction(outputStream);
    }
    
    void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw HermesRuntimeException("Action.deserializable: wrong serial");
        }
        inputStream.read_string(m_srcID);
        inputStream.read_string(m_action);
        deserializableAction(inputStream);
    }
    
    void deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {        
        if (serial != getSerialID()) {
            throw HermesRuntimeException("Action.deserializable: wrong serial");
        }
        inputStream.read_string(m_srcID);
        inputStream.read_string(m_action);
        deserializableAction(inputStream);
    }
protected:
    String m_srcID;
    String m_action;
    
    virtual void serializeAction(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableAction(InputStream& inputStream) throw (SerializationException&) = 0;

};

#endif	/* ACTION_H */

