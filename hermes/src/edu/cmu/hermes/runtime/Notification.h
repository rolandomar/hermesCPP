/* 
 * File:   Notification.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 10:42 AM
 */

#ifndef NOTIFICATION_H
#define	NOTIFICATION_H

#include <euryale/Types.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>

class Notification {
public:
    Notification();

    Notification(String& srcID) {
        m_srcID = srcID;
    }
    Notification(const Notification& orig);
    virtual ~Notification();

    virtual int getSerialID() = 0;

    String& getSourceID() {
        return m_srcID;
    }

    virtual void serialize(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(getSerialID());
        outputStream.write_string(m_srcID);
        serializeNotification(outputStream);
    }

    virtual void deserialize(InputStream& inputStream) throw (SerializationException&) {
        int serial;
        inputStream.read_long(serial);
        if (serial != getSerialID()) {
            throw SerializationException(SerializationException::BAD_STREAM);
        }
        inputStream.read_string(m_srcID);
        deserializableNotification(inputStream);
    }
    //for factory
    virtual void deserialize(int serial,InputStream& inputStream) throw (SerializationException&) {        
        inputStream.read_string(m_srcID);
        deserializableNotification(inputStream);
    }


protected:
    String m_srcID;

    virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&) = 0;
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&) = 0;


};

#endif	/* NOTIFICATION_H */

