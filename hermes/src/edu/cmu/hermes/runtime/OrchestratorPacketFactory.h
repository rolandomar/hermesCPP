/* 
 * File:   OrchestratorPacketFactory.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 6:10 PM
 */

#ifndef ORCHESTRATORPACKETFACTORY_H
#define	ORCHESTRATORPACKETFACTORY_H

#include <euryale/common/io/ByteInputStream.h>
#include <euryale/net/packet/PacketFactory.h>
#include <hermes/runtime/HermesAbstractPacket.h>


#include <hermes/runtime/NotificationRequestPacket.h>
#include <hermes/runtime/NotificationReplyPacket.h>
#include <hermes/runtime/ActionRequestPacket.h>
#include <hermes/runtime/ActionReplyPacket.h>

#include <hermes/runtime/RemoteActionRequestPacket.h>
#include <hermes/runtime/RemoteActionReplyPacket.h>


#include <hermes/runtime/InitPacket.h>
#include <hermes/runtime/InitReplyPacket.h>




class OrchestratorPacketFactory: public PacketFactory<HermesAbstractPacket, HermesAbstractPacketHeader>{
public:
    OrchestratorPacketFactory(){}

    virtual ~OrchestratorPacketFactory();
    
    virtual HermesAbstractPacket* createPacket(HermesAbstractPacketHeader* header,ByteInputStream& bis){
        switch(header->getType()){
            case InitPacket::INITPACKET_OPCODE:{
                InitPacket* packet = new InitPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case InitReplyPacket::INITPACKETREPLY_OPCODE:{
                InitReplyPacket* packet = new InitReplyPacket();
                packet->init(header,bis);
                return packet;
            }
            case NotificationRequestPacket::NOTIFICATIONREQUESTY_OPCODE:{
                NotificationRequestPacket* packet = new NotificationRequestPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case NotificationReplyPacket::NOTIFICATIONREPLY_OPCODE:{
                NotificationReplyPacket* packet = new NotificationReplyPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case ActionRequestPacket::ACTIONREQUESTY_OPCODE:{
                ActionRequestPacket* packet = new ActionRequestPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case ActionReplyPacket::ACTIONREPLY_OPCODE:{
                ActionReplyPacket* packet = new ActionReplyPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case RemoteActionRequestPacket::SERIAL_ID:{
                RemoteActionRequestPacket* packet = new RemoteActionRequestPacket();
                packet->init(header,bis);
                return packet;
            }
            
            case RemoteActionReplyPacket::SERIAL_ID:{
                RemoteActionReplyPacket* packet = new RemoteActionReplyPacket();
                packet->init(header,bis);
                return packet;
            }
        }
        return 0;
    }
private:

};

#endif	/* ORCHESTRATORPACKETFACTORY_H */

