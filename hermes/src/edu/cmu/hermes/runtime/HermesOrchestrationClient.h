/* 
 * File:   HermesOrchestrationClient.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 5:57 PM
 */

#ifndef HERMESORCHESTRATIONCLIENT_H
#define	HERMESORCHESTRATIONCLIENT_H

#include <euryale/threading/tpc/ThreadPerConnection.h>
#include <hermes/runtime/HermesOrchestrationClientChannel.h>
#include <euryale/net/AbstractStreamChannel.h>
class HermesRuntime;
class RemoteActionResult;
class RemoteAction;
class HermesOrchestrationClient:  public CloseListener<ACE_SOCK_Stream, ACE_MT_SYNCH>{
public:
    
    HermesOrchestrationClient(HermesRuntime* runtime,String& id);
    virtual ~HermesOrchestrationClient();

    void notification(Notification* notification, long timeout) {
        NotificationRequestPacket* notificationPacket =
                new NotificationRequestPacket(m_sequenceID++, notification);
        ChannelRequestEngine<HermesOrchestrationClientChannel,
                HermesAbstractPacket*>::RequestPtr* request = 0;
        request = m_channel->sendRequest(notificationPacket, notificationPacket->getRequestNo(),0);
        if (request == 0) {
            delete notificationPacket;
            throw HermesRuntimeException("");
        }
        printf("NOtification waiting for reply\n");
        list<HermesAbstractPacket*>* l = request->get()->waitFuture(0);
        printf("NOtification reply\n");
        if (l == 0 || l->size() == 0) {
            delete request;
            delete notificationPacket;
            throw HermesRuntimeException("");
        }
        NotificationReplyPacket* replyPacket = static_cast<NotificationReplyPacket*> (l->front());
        printf("NOtification ret=%d\n",replyPacket->getRetCode());
        ListHelper<HermesAbstractPacket*>::deleteList(l);
        //delete replyPacket;
        return;
    }

    ActionResult* action(Action* action, long timeout) {
        ActionRequestPacket* notificationPacket =
                new ActionRequestPacket(m_sequenceID++, action);
        ChannelRequestEngine<HermesOrchestrationClientChannel,
                HermesAbstractPacket*>::RequestPtr* request = 0;
        request = m_channel->sendRequest(notificationPacket, notificationPacket->getRequestNo(),0);
        if (request == 0) {
            delete notificationPacket;
            throw HermesRuntimeException("");
        }
        printf("action waiting for reply\n");
        list<HermesAbstractPacket*>* l = request->get()->waitFuture(0);
        printf("action reply\n");
        if (l == 0 || l->size() == 0) {
            delete request;
            delete notificationPacket;
            throw HermesRuntimeException("");
        }
        ActionReplyPacket* replyPacket = static_cast<ActionReplyPacket*> (l->front());       
        ActionResult* ret = replyPacket->dettachActionResult();
        ListHelper<HermesAbstractPacket*>::deleteList(l);
        //delete replyPacket;
        return ret;
    }

   int open() {
        //ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T) HermesOrchestrationClient: HermesOrchestrationClient::open()\n")));
        ACE_GUARD_RETURN(ACE_SYNCH_RECURSIVE_MUTEX, ace_mon, m_lock, -1);
        const char* ip = "127.0.0.1";
        short port = 8989;
                
        //Endpoint endpoint;
        ACE_INET_Addr addr(port,ip);
        //QoSEndpoint qosEndpoint(Endpoint::TCP, 50);
        ACE_Connector<HermesOrchestrationClientChannel, ACE_SOCK_Connector> connector;
        

        ThreadPerConnection *tpc = new ThreadPerConnection();        
        ExecutionModelPtr* tpcPrt = new
                ExecutionModelPtr(tpc);

        
        if (m_channel != 0) {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T) HermesOrchestrationClient: HermesOrchestrationClient::open() closing open client\n")));
            m_channel->close(0);
            delete m_channel;
        }

        m_channel = new HermesOrchestrationClientChannel(this,m_id,
                false, false, tpcPrt, 0, 0, 0);

        tpc->bind(m_channel);
        tpc->open(0, 0);
        //tpc->bind(m_clientHandler);
        connector.reactor(tpc->getResources()->getReactor());
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T) HermesOrchestrationClient: open before connect\n")));
        //if (connector.connect(m_channel, endpoint.getAddr()) == -1) {
        if (connector.connect(m_channel, addr) == -1) {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%T)(%t|%T) ERROR: HermesOrchestrationClient::open() - connect failed!")));
            m_channel->close(0);
            delete m_channel;
            m_channel = 0;
            return -1;
        }
        


        if (m_channel->asynchronous(true, false) != 0) {
            m_channel->close(0);
            delete m_channel;
            m_channel = 0;
            return -1;
        }
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T) HermesOrchestrationClient: after connect\n")));
        /*if (m_rebindStart.msec() != 0) {
            ACE_Time_Value rebindEnd = ACE_OS::gettimeofday() - m_rebindStart;
            m_rebindTotalTime += rebindEnd;
        }*/

        return 0;
    }
   
   void close(){
       m_channel->close(0);
   }

    void onClose(AbstractStreamChannel<ACE_SOCK_Stream, ACE_MT_SYNCH>* channel){
        
    }
    
    RemoteActionResult* onRemoteAction(RemoteAction* remoteAction);

    
protected:
    HermesRuntime* m_runtime;
    String m_id;
    ACE_Atomic_Op<ACE_Thread_Mutex, UInt> m_sequenceID;
    HermesOrchestrationClientChannel* m_channel;
    ACE_SYNCH_RECURSIVE_MUTEX m_lock;

};

#endif	/* HERMESORCHESTRATIONCLIENT_H */


//public class OrchestrationNodeClient {
//
//    protected ReentrantLock m_lock = new ReentrantLock();
//    HermesOrchestrationClientChannel m_channel;
//    HermesRuntime m_runtime;
//    AtomicInteger m_sequencer = new AtomicInteger(1);
//    String m_id;
//
//    public OrchestrationNodeClient(HermesRuntime runtime, String id) {
//        m_runtime = runtime;
//        m_id = id;
//        m_channel = new HermesOrchestrationClientChannel(this, id);
//    }
//
//    public void notification(Notification notification, long timeout) {
//        NotificationRequestPacket notificationPacket =
//                new NotificationRequestPacket(m_sequencer.getAndIncrement(), notification);
//        try {
//            Future<HermesAbstractPacket> future = m_channel.sendRPCPacket(notificationPacket);
//            HermesAbstractPacket replyAbs = future.get(timeout, TimeUnit.MILLISECONDS);
//            NotificationReplyPacket reply = (NotificationReplyPacket) replyAbs;
//            //System.out.println("notification acked");
//            //return reply.getReturnValue();
//
//        } catch (Exception ex) {
//            Logger.getLogger(HermesNodeClientChannel.class.getName()).log(Level.SEVERE, "notification ex=", ex);
//            //return null;
//        }
//    }
//
//    public ActionResult action(Action notification, long timeout) throws Exception {
//        ActionRequestPacket notificationPacket =
//                new ActionRequestPacket(m_sequencer.getAndIncrement(), notification);
//        try {
//            Future<HermesAbstractPacket> future = m_channel.sendRPCPacket(notificationPacket);
//            HermesAbstractPacket replyAbs = future.get(timeout, TimeUnit.MILLISECONDS);
//            ActionReplyPacket reply = (ActionReplyPacket) replyAbs;
//            //System.out.println("action acked");
//            return reply.getActionResult();
//        } catch (Exception ex) {
//            Logger.getLogger(HermesNodeClientChannel.class.getName()).log(Level.SEVERE, "actionKKKKKK", ex);
//            //return null;
//
//            throw ex;
//        }
//
//    }
//
//    public void open() throws Exception {
//        
//        try {
//            m_lock.lock();
//            System.out.println("OrchestrationNodeClient: open()");
//            try {
//                HermesFuture<Boolean> future = m_channel.
//                        open(HermesConfig.getOrchestrationDaemonIP(),
//                        HermesConfig.getOrchestrationDaemonPort());
//                if (!future.get(2500, TimeUnit.MILLISECONDS)) {
//                    throw new Exception("Connection refused");
//                }
//            } catch (IOException | InterruptedException | ExecutionException | TimeoutException ex) {
//                Logger.getLogger(HermesNodeClientChannel.class.getName()).log(Level.SEVERE, "client error", ex);
//                throw ex;
//            }
//            InitPacket packet = new InitPacket(0, m_id);
//            try {
//                m_channel.sendPacket(packet);
//            } catch (Exception ex) {
//                Logger.getLogger(HermesNodeClientChannel.class.getName()).log(Level.SEVERE, "sendPacket", ex);
//                throw ex;
//            }
//        } finally {
//            m_lock.unlock();
//        }
//    }
//
//    public static void main(String[] args) {
//        HermesRuntime r = new HermesRuntime();
//        OrchestrationNodeClient client = new OrchestrationNodeClient(r, "AABBCCDD001122334455");
//        try {
//            client.open();
//        } catch (Exception ex) {
//            Logger.getLogger(OrchestrationNodeClient.class.getName()).log(Level.SEVERE, null, ex);
//        }
//        GeneralNotificationImpl notification = new GeneralNotificationImpl("AABBCCDD00112233445566");
//        client.notification(notification, 2500);
//        while (true) {
//            try {
//                Thread.sleep(10000);
//            } catch (InterruptedException ex) {
//                Logger.getLogger(HermesNodeServerChannel.class.getName()).log(Level.SEVERE, "JJJJ", ex);
//            }
//        }
//    }
//
//    public void close() throws IOException {
//        m_channel.close();
//    }
//
//    public RemoteActionResult onRemoteAction(RemoteAction remoteAction) {
//        return m_runtime.onRemoteAction(remoteAction);
//    }
//
//    public void onServerClientChannelClose(HermesOrchestrationClientChannel aThis) {
//        
//    }
//}