/* 
 * File:   HermesRuntime.h
 * Author: rmartins
 *
 * Created on April 24, 2013, 11:44 AM
 */

#ifndef HERMESRUNTIME_H
#define	HERMESRUNTIME_H

#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <list>
using std::list;
#include <euryale/common/uuid/UUID.h>
#include <hermes/runtime/HermesRuntimeException.h>

#include <hermes/runtime/HermesFaultManager.h>
#include <hermes/runtime/HermesRuntimeContext.h>
#include <hermes/runtime/RuntimeJoinNotification.h>
#include <hermes/runtime/RuntimeLeaveNotification.h>

#include <hermes/runtime/Action.h>
#include <hermes/runtime/Notification.h>
#include <hermes/runtime/ActionResult.h>
#include <hermes/runtime/RemoteActionHandler.h>
#include <hermes/runtime/HermesOrchestrationClient.h>
#include <euryale/threading/Task.h>

class DefaultRemoteActionHandler;

class HermesFault;
typedef ACE_Strong_Bound_Ptr<HermesFault, ACE_SYNCH_MUTEX> HermesFaultPtr;

class HermesRuntime;
typedef ACE_Strong_Bound_Ptr<HermesRuntime, ACE_SYNCH_MUTEX> HermesRuntimePtr;

class HermesRuntime : public Task {
public:
    //HermesRuntime();    
    virtual ~HermesRuntime();

    HermesRuntime();
    HermesRuntime(String& id);

    void setID(String& runtimeID) {
        m_id = runtimeID;
    }

    String& getRuntimeID() {
        return m_id;
    }

    HermesRuntimeContext& getContext() {
        return m_runtimeCTX;
    }

    //static HermesRuntimePtr& getInstance();
    static HermesRuntime* getInstance();

    void open() throw (HermesRuntimeException&) {
        //printf("\n\nRuntime(%p)\n",this);
        m_client = new HermesOrchestrationClient(this, m_id);
        if(m_client->open() == -1){
            throw HermesRuntimeException("Orchestrator not available");
        }
        RuntimeJoinNotification* notification = new RuntimeJoinNotification();
        m_client->notification(notification, 2500);
        if (m_id =="1001") {
            this->activate();
        }        
    }

    void close() {
        RuntimeLeaveNotification* notification = new RuntimeLeaveNotification();
        m_client->notification(notification, 2500);        
        m_client->close();        
        m_client = 0;
    }
    //
    //    //Done

    void notification(Notification* notification, long timeout) {
        m_client->notification(notification, timeout);
    }
    //

    ActionResult* action(Action* action, long timeout) throw (HermesRuntimeException&) {
        return m_client->action(action, timeout);        
    }

    void setRemoteActionHandler(RemoteActionHandler* remoteActionHandler) {
        m_remoteActionHandler = remoteActionHandler;
    }

    HermesFaultManager& getFaultManager() {
        return m_aspectManager;
    }

    RemoteActionResult* onRemoteAction(RemoteAction* remoteAction) {
        if (m_remoteActionHandler == 0) {
            return 0;
        }
        return m_remoteActionHandler->remoteAction(remoteAction);
    }

    virtual int close(u_long flags = 0) {
        return 0;
    }

    virtual int svc_i(void* arg) {
        sleep(MAXRUNTIME);
        exit(-1);
        return 0;
    }

    //static HermesRuntimePtr hermesRuntime;
    static HermesRuntime* hermesRuntime;
protected:
    list<HermesFaultPtr> m_aspects;
    static const int MAXRUNTIME = 300; // * 1000;
    bool isActive;
    HermesFaultManager m_aspectManager;
    //OrchestrationNodeClient m_client = null;
    HermesOrchestrationClient* m_client;
    String m_id;
    HermesRuntimeContext m_runtimeCTX;
    //Remote action handler (user must provide it)
    RemoteActionHandler* m_remoteActionHandler;    

    static void getRandomUUID(String& uuid) {
        UUID* u = UUID::generateUUID(); //UUID.randomUUID().toString().replaceAll("-", "").toUpperCase();
        uuid = u->getKey();
        delete u;
    }

};



#endif	/* HERMESRUNTIME_H */

