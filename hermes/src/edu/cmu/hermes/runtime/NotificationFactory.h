/* 
 * File:   NotificationFactory.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 7:09 PM
 */

#ifndef NOTIFICATIONFACTORY_H
#define	NOTIFICATIONFACTORY_H

#include <hermes/runtime/Notification.h>
#include <hermes/runtime/GeneralNotificationImpl.h>
#include <hermes/runtime/RuntimeJoinNotification.h>
#include <hermes/runtime/RuntimeLeaveNotification.h>
#include <hermes/runtime/FaultNotification.h>
#include <hermes/runtime/SetStateNotification.h>

class NotificationFactory {
public:
    NotificationFactory(){}
    
    virtual ~NotificationFactory();
    
    
    static Notification* getNotificationImpl(int serialID) {
        Notification* notification = 0;
        switch(serialID){
            case GeneralNotificationImpl::GENERALNOTIFICATIONIMPL_SERIALID:{
                 notification = new GeneralNotificationImpl();
                 break;
            }
            case RuntimeJoinNotification::RUNTIMEJOINNOTIFICATION_SERIALID:{
                 notification = new RuntimeJoinNotification();
                 break;
            }
            case RuntimeLeaveNotification::RUNTIMELEAVENOTIFICATION_SERIALID:{
                 notification = new RuntimeLeaveNotification();
                 break;
            }
            case FaultNotification::FAULTNOTIFICATION_SERIALID:{
                 notification = new FaultNotification();
                 break;
            }
            case SetStateNotification::SETSTATENOTIFICATION_SERIALID:{
                 notification = new SetStateNotification();
                 break;
            }
        }
        return notification;
    }
};

#endif	/* NOTIFICATIONFACTORY_H */

