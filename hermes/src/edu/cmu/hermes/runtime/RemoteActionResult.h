/* 
 * File:   RemoteActionResult.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:42 PM
 */

#ifndef REMOTEACTIONRESULT_H
#define	REMOTEACTIONRESULT_H
#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>
#include <hermes/runtime/HermesRuntimeException.h>
class RemoteActionResult : public Serializable{
public:
    RemoteActionResult();
    RemoteActionResult(const RemoteActionResult& orig);
    virtual ~RemoteActionResult();
    
    virtual int getSerialID() = 0;
    
    void serialize(OutputStream& outputStream) throw (SerializationException&) {
         outputStream.write_long(getSerialID());
         serializeActionResult(outputStream);
    }
        
    void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw HermesRuntimeException("Action.deserializable: wrong serial");
        }
        deserializableActionResult(inputStream);
        
    }
    
    void deserialize( int serial,InputStream& inputStream) throw (SerializationException&) {       
        if (serial != getSerialID()) {
            throw HermesRuntimeException("Action.deserializable: wrong serial");
        }
        deserializableActionResult(inputStream);
        
    }
protected:
    virtual void serializeActionResult(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableActionResult(InputStream& inputStream) throw (SerializationException&) = 0;

};

#endif	/* REMOTEACTIONRESULT_H */
