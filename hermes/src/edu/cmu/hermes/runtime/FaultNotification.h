/* 
 * File:   FaultNotification.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 12:26 AM
 */

#ifndef FAULTNOTIFICATION_H
#define	FAULTNOTIFICATION_H

#include <hermes/runtime/Notification.h>

class FaultNotification: public Notification {
public:
    static const int FAULTNOTIFICATION_SERIALID = 242386281;
    FaultNotification();
    FaultNotification(String& id):
    m_id(id){
        
    }
    
    FaultNotification(const FaultNotification& orig);
    virtual ~FaultNotification();
    
    int getSerialID() {
        return FAULTNOTIFICATION_SERIALID;
    }
protected:
    String m_id;
    virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&){
        outputStream.write_string(m_id);                
    }
    
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&){
        inputStream.read_string(m_id);
    }
};

#endif	/* FAULTNOTIFICATION_H */
