/* 
 * File:   HermesFaultManager.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 10:05 AM
 */

#ifndef HERMESFAULTMANAGER_H
#define	HERMESFAULTMANAGER_H

#include <hermes/runtime/HermesRuntimeException.h>
#include <euryale/common/Object.h>
#include <ace/Hash_Map_Manager.h>
#include <ace/Time_Value.h>
#include <ace/ACE.h>
#include <ace/SString.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Containers_T.h>

class HermesFault;
typedef ACE_Strong_Bound_Ptr<HermesFault, ACE_SYNCH_MUTEX> HermesFaultPtr;
//typedef ACE_Strong_Bound_Ptr<HermesFault, ACE_SYNCH_MUTEX> HermesFaultPtr;
class HermesFaultManager {
public:
    HermesFaultManager();
    HermesFaultManager(const HermesFaultManager& orig);
    virtual ~HermesFaultManager();
    
    void addFault(HermesFaultPtr& aspect);
    void getFault(const String& faultId,HermesFaultPtr& fault);
    
protected:
    typedef ACE_Hash_Map_Manager<String, HermesFaultPtr, ACE_SYNCH_RW_MUTEX> HermesFaultManagerMap;
    HermesFaultManagerMap m_aspectMap;    
};


#endif	/* HERMESFAULTMANAGER_H */

