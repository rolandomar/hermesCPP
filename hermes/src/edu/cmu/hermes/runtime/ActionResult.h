/* 
 * File:   ActionResult.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:05 PM
 */

#ifndef ACTIONRESULT_H
#define	ACTIONRESULT_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>
#include <hermes/runtime/HermesRuntimeException.h>

class ActionResult : public Serializable{
public:
    ActionResult();
    ActionResult(const ActionResult& orig);
    virtual ~ActionResult();
    
    virtual int getSerialID() = 0;
    
    void serialize(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(getSerialID());
        serializeActionResult(outputStream);
    }

    void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw HermesRuntimeException("ActionResult.deserializable: wrong serial");
        }
        deserializableActionResult(inputStream);        
    }
    void deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {        
        if (serial != getSerialID()) {
            throw HermesRuntimeException("ActionResult.deserializable: wrong serial");
        }
        deserializableActionResult(inputStream);        
    }
protected:
    virtual void serializeActionResult(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableActionResult(InputStream& inputStream) throw (SerializationException&) = 0;
};

#endif	/* ACTIONRESULT_H */
