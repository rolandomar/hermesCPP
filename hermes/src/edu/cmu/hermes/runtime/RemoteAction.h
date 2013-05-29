/* 
 * File:   RemoteAction.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:36 PM
 */

#ifndef REMOTEACTION_H
#define	REMOTEACTION_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>
#include <hermes/runtime/HermesRuntimeException.h>

class RemoteAction : public Serializable{
public:
    RemoteAction();
    RemoteAction(const RemoteAction& orig);
    virtual ~RemoteAction();

    virtual int getSerialID() = 0;

    void serialize(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(getSerialID());
        serializeAction(outputStream);
    }

    void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw HermesRuntimeException("RemoteAction.deserializable: wrong serial");
        }
        deserializableAction(inputStream);
    }
    
    void deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {                
        if (serial != getSerialID()) {
            throw HermesRuntimeException("RemoteAction.deserializable: wrong serial");
        }
        deserializableAction(inputStream);
    }
protected:
    virtual void serializeAction(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableAction(InputStream& inputStream) throw (SerializationException&) = 0;

};

#endif	/* REMOTEACTION_H */
