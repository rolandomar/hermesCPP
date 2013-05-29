/* 
 * File:   GeneralNotificationImpl.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 11:32 PM
 */

#ifndef GENERALNOTIFICATIONIMPL_H
#define	GENERALNOTIFICATIONIMPL_H

#include <hermes/runtime/Notification.h>
class GeneralNotificationImpl: public Notification {
public:
    static const int GENERALNOTIFICATIONIMPL_SERIALID = 142386283;
    GeneralNotificationImpl();
    GeneralNotificationImpl(String& srcID):
    Notification(srcID){
        
    }
    
    virtual ~GeneralNotificationImpl();
protected:
    virtual void serializeNotification(OutputStream& outputStream) throw (SerializationException&) {
        
    }
    virtual void deserializableNotification(InputStream& inputStream) throw (SerializationException&) {
        
    }
    
    int getSerialID() {
        return GENERALNOTIFICATIONIMPL_SERIALID;
    }
};

#endif	/* GENERALNOTIFICATIONIMPL_H */
//
//public class GeneralNotificationImpl extends Notification{
//    
//    public GeneralNotificationImpl(){
//        
//    }
//    
//    public GeneralNotificationImpl(String srcID){
//        super(srcID);
//        
//    }
//    
//    public final static int GENERALNOTIFICATIONIMPL_SERIALID = 142386283;
//    @Override
//    protected void serializeNotification(ByteBuffer buf) {        
//    }
//
//    @Override
//    protected void deserializableNotification(ByteBuffer buf) throws Exception {        
//    }
//
//    @Override
//    public final int getSerialID() {
//        return GENERALNOTIFICATIONIMPL_SERIALID;
//    }
//    
//}