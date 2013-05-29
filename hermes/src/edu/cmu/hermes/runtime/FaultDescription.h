/* 
 * File:   FaultDescription.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 1:29 PM
 */

#ifndef FAULTDESCRIPTION_H
#define	FAULTDESCRIPTION_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>

class FaultDescription: public Serializable {
public:
    FaultDescription();
    FaultDescription(const FaultDescription& orig);
    virtual ~FaultDescription();

    virtual int getSerialID() = 0;

    virtual void serialize(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(getSerialID());
        serializableFaultDescriptionImpl(outputStream);
    }

    virtual void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw SerializationException(SerializationException::BAD_STREAM);
        }
        deserializableFaultDescriptionImpl(inputStream);
    }
    virtual void deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {
        if (serial != getSerialID()) {
            throw SerializationException(SerializationException::BAD_STREAM);
        }
        deserializableFaultDescriptionImpl(inputStream);
    }
protected:
    virtual void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) = 0;

};

#endif	/* FAULTDESCRIPTION_H */

