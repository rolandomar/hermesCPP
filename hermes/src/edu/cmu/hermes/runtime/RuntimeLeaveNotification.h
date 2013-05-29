/* 
 * File:   RuntimeLeaveNotification.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 10:52 AM
 */

#ifndef RUNTIMELEAVENOTIFICATION_H
#define	RUNTIMELEAVENOTIFICATION_H

#include <hermes/runtime/Notification.h>

class RuntimeLeaveNotification: public Notification {
public:
    static const int RUNTIMELEAVENOTIFICATION_SERIALID = 142386210;
    RuntimeLeaveNotification();
    RuntimeLeaveNotification(String srcID):
    Notification(srcID){
        
    }
    RuntimeLeaveNotification(const RuntimeLeaveNotification& orig);
    virtual ~RuntimeLeaveNotification();
    
   
    virtual int getSerialID() {
        return RUNTIMELEAVENOTIFICATION_SERIALID;
    }
protected:
     virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&){
         
     }
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&){
        
    }


};

#endif	/* RUNTIMELEAVENOTIFICATION_H */
