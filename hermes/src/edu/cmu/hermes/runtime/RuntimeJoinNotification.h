/* 
 * File:   RuntimeJoinNotification.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:13 AM
 */

#ifndef RUNTIMEJOINNOTIFICATION_H
#define	RUNTIMEJOINNOTIFICATION_H


#include <hermes/runtime/Notification.h>

class RuntimeJoinNotification: public Notification {
public:
    
    static const int RUNTIMEJOINNOTIFICATION_SERIALID = 142386284;
    RuntimeJoinNotification();
    RuntimeJoinNotification(String srcID): Notification(srcID){
    }
    RuntimeJoinNotification(const RuntimeJoinNotification& orig);
    virtual ~RuntimeJoinNotification();
    
    virtual int getSerialID() {
        return RUNTIMEJOINNOTIFICATION_SERIALID;
    }
protected:
     virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&){
         
     }
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&){
        
    }
};

#endif	/* RUNTIMEJOINNOTIFICATION_H */
