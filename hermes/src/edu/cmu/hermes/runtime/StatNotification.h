/* 
 * File:   StatNotification.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 12:16 AM
 */

#ifndef STATNOTIFICATION_H
#define	STATNOTIFICATION_H
#include <hermes/runtime/Notification.h>

#include "StatToken.h"

class StatNotification : public Notification {
public:
    static const int STATNOTIFICATION_SERIALID = 822386210;

    StatNotification();

    StatNotification(String& srcID, StatToken& st) :
    Notification(srcID),m_st(st) {
    }

    StatNotification(const StatNotification& orig);
    virtual ~StatNotification();

    int getSerialID() {
        return STATNOTIFICATION_SERIALID;
    }
protected:
    StatToken m_st;
    
    virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&) {
        m_st.serialize(outputStream);
    }
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&) {
        m_st.deserialize(inputStream);
    }

};

#endif	/* STATNOTIFICATION_H */

