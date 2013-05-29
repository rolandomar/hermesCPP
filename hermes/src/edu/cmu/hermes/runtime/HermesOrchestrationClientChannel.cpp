/* 
 * File:   OrchestrationNodeClient.cpp
 * Author: rmartins
 * 
 * Created on April 29, 2013, 3:45 PM
 */

#include <hermes/runtime/NotificationRequestPacket.h>
#include <hermes/runtime/NotificationReplyPacket.h>
#include <hermes/runtime/ActionRequestPacket.h>
#include <hermes/runtime/ActionReplyPacket.h>
#include <hermes/runtime/RemoteActionRequestPacket.h>
#include <hermes/runtime/RemoteActionReplyPacket.h>
#include <hermes/runtime/InitPacket.h>
#include <hermes/runtime/InitReplyPacket.h>

#include <hermes/runtime/HermesOrchestrationClientChannel.h>


#include <hermes/runtime/HermesOrchestrationClient.h>

HermesOrchestrationClientChannel::~HermesOrchestrationClientChannel() {
}

HermesOrchestrationClientChannel::HermesOrchestrationClientChannel(
        HermesOrchestrationClient* client,
        String& id,
        bool asyncRead, bool asyncWrite,
        ExecutionModelPtr* ec,
        NetReservation* reserve,
        NetQoS* qos,
        CloseListener<ACE_SOCK_Stream, ACE_MT_SYNCH>* closeListener) :
m_client(client),
PacketChannel<HermesAbstractPacket, HermesAbstractPacketHeader, //P3DiscoveryPacketFactory,
ACE_SOCK_Stream, ACE_MT_SYNCH>(new OrchestratorPacketFactory(), asyncRead, asyncWrite,
ec, reserve, qos, closeListener), m_id(id) {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("RPCServiceClient: RPCServiceClient::~RPCServiceClient(2) %@\n"), this));
    //m_requests = new ChannelRequestEngine<RPCServiceClientHandler, SthenoStreamPacket*>();    
}

int HermesOrchestrationClientChannel::handlePacket(HermesAbstractPacket* packet) {
    printf("received packet %d\n", packet->getPacketHeader()->getType());
    switch (packet->getPacketHeader()->getType()) {
        case InitReplyPacket::INITPACKETREPLY_OPCODE:
        {
            InitReplyPacket* initReplyPacket =
                    static_cast<InitReplyPacket*> (packet);
            break;
        }

        case RemoteActionRequestPacket::SERIAL_ID:
        {
            printf("RemoteActionRequestPacket\n");
            RemoteActionRequestPacket* request = (RemoteActionRequestPacket*) packet;
            RemoteActionResult* r = m_client->onRemoteAction(request->getRemoteAction());
            RemoteActionReplyPacket* reply = new RemoteActionReplyPacket(request->getRequestNo(), r);
            printf("RemoteActionRequestPacket - send reply\n");  
            sendPacket(reply);
            break;
        }
        case InitPacket::INITPACKET_OPCODE:
        {
            //check reply
            break;
        }
        case NotificationReplyPacket::NOTIFICATIONREPLY_OPCODE:
        {
            NotificationReplyPacket* notificationReplyPacket =
                    static_cast<NotificationReplyPacket*> (packet);
            //printf("requestno %d",notificationReplyPacket->getRequestNo());
            if (m_requests.setReply(notificationReplyPacket->getRequestNo(), packet) == -1) {
                delete notificationReplyPacket;
                printf("failed to set reply!\n");
            }
            break;
        }
        case ActionReplyPacket::ACTIONREPLY_OPCODE:
        {
            ActionReplyPacket* actionReply =
                    static_cast<ActionReplyPacket*> (packet);
            printf("SETTING ACTION REPLY\n");
            if (m_requests.setReply(actionReply->getRequestNo(), packet) == -1) {
                delete actionReply;
                printf("\nfailed to set reply!\n");
            }else{
                printf("SETTING ACTION REPLY\n");
            }
            
            break;
        }
    }
    return 0;
}