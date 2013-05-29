/* 
 * File:   OrchestrationNodeClient.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 3:45 PM
 */

#ifndef ORCHESTRATIONNODECLIENT_H
#define	ORCHESTRATIONNODECLIENT_H

#include "ace/Synch_Traits.h"
#include "ace/Null_Condition.h"
#include "ace/Null_Mutex.h"

#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/LSOCK_Stream.h"
#include "ace/LSOCK_Connector.h"
#include "ace/Connector.h"
#include "ace/Svc_Handler.h"
#include "ace/Reactor_Notification_Strategy.h"
#include <ace/Future.h>
#include <ace/Atomic_Op.h>

#include <euryale/net/PacketChannel.h>
#include "ace/Auto_Ptr.h"
#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Dgram_Mcast.h>
#include "ace/Reactor.h"
#include <ace/UNIX_Addr.h>
#include <hermes/runtime/HermesAbstractPacket.h>
#include <hermes/runtime/OrchestratorPacketFactory.h>
#include <euryale/net/ChannelRequestEngine.h>
#include <hermes/runtime/Notification.h>
#include <hermes/runtime/Action.h>
#include <hermes/runtime/ActionResult.h>


class HermesOrchestrationClient;

class HermesOrchestrationClientChannel : public PacketChannel<HermesAbstractPacket, HermesAbstractPacketHeader,
ACE_SOCK_Stream, ACE_MT_SYNCH> {
public:

    HermesOrchestrationClientChannel():m_client(0) {
    }

    HermesOrchestrationClientChannel(
            HermesOrchestrationClient* client,
            String& id,
            bool asyncRead, bool asyncWrite,
            ExecutionModelPtr* ec = 0,
            NetReservation* reserve = 0,
            NetQoS* qos = 0,
            CloseListener<ACE_SOCK_Stream, ACE_MT_SYNCH>* closeListener = 0);

    virtual ~HermesOrchestrationClientChannel();

    int open(void *arg = 0) {
        InitPacket* initPacket = new InitPacket(m_sequenceID++, m_id);
        ACE_Time_Value* timeout = 0;
        int ret = sendPacket((HermesAbstractPacket*&) initPacket, timeout);
        delete initPacket;
        if (ret == -1) {
            printf("RPCServiceClientHandler: open failed on sendpacket\n");
            return -1;
        }
        ret = PacketChannel<HermesAbstractPacket, HermesAbstractPacketHeader, //P3DiscoveryPacketFactory,
                ACE_SOCK_Stream, ACE_MT_SYNCH>::open(arg);
        if (ret == -1) {
            printf("RPCServiceClientHandler: open failed on super\n");
        }
        return ret;
    }

    int close(u_long flags) {
        {
            ACE_GUARD_RETURN(ACE_SYNCH_RECURSIVE_MUTEX, ace_mon, m_lock, -1);
            if (!m_close) {
                m_requests.clearAll();
            }
        }
        return PacketChannel<HermesAbstractPacket, HermesAbstractPacketHeader,
                ACE_SOCK_Stream, ACE_MT_SYNCH>::close(flags);
    }

    virtual int handlePacket(HermesAbstractPacket* packet);

    virtual ChannelRequestEngine<HermesOrchestrationClientChannel, HermesAbstractPacket*>::RequestPtr*
    sendRequest(HermesAbstractPacket* packet, UInt id,
            ACE_Time_Value* timeout = 0) {
        ACE_GUARD_RETURN(ACE_SYNCH_RECURSIVE_MUTEX, ace_mon, SuperType::m_lock, 0);
        if (this->m_close) {
            return 0;
        }
        ACE_Message_Block* mb = serializePacket(packet);
        //UInt id = ((HermesAbstractPacketHeader*) (packet->getPacketHeader()))->getPacketID();
        ChannelRequestEngine<HermesOrchestrationClientChannel, HermesAbstractPacket*>::RequestPtr* request =
                new ChannelRequestEngine<HermesOrchestrationClientChannel, HermesAbstractPacket*>::RequestPtr(
                new ChannelRequest<HermesOrchestrationClientChannel, HermesAbstractPacket*>(this, &m_requests, id, timeout));
        m_requests.bind(request);
        int ret = AbstractStreamChannel<ACE_SOCK_Stream, ACE_MT_SYNCH>::send(mb, timeout);
        ACE_Message_Block::release(mb);
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T)INFO: CellClientHandler:sendRequest() - register ID(%d).\n"), id));
        if (ret == -1) {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t|%T)ERROR: P3DiscoveryClientHandler:sendRequest() - ID(%d)\n"), id));
            delete request;
            return 0;
        }
        return request;
    }

    UUIDPtr& getPID() {
        return m_ptr;
    }

protected:
    HermesOrchestrationClient* m_client;
    UUIDPtr m_ptr;
    String m_id;
    ChannelRequestEngine<HermesOrchestrationClientChannel, HermesAbstractPacket*> m_requests;
};

#endif	/* ORCHESTRATIONNODECLIENT_H */
