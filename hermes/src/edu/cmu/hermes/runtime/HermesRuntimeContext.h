/* 
 * File:   HermesRuntmeContext.h
 * Author: rmartins
 *
 * Created on April 28, 2013, 11:09 AM
 */

#ifndef HERMESRUNTMECONTEXT_H
#define	HERMESRUNTMECONTEXT_H

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

class HermesRuntimeContext {
public:
    HermesRuntimeContext();
    HermesRuntimeContext(const HermesRuntimeContext& orig);
    virtual ~HermesRuntimeContext();

    void getObject(String& key, ObjectPtr& objPtr) throw (HermesRuntimeException&) {
        if (m_map.find(key, objPtr) == -1) {
            throw HermesRuntimeException("Object not found!");
        }
    }

    void put(String& key, ObjectPtr& value) {
        if (m_map.bind(key, value) == -1) {
            throw HermesRuntimeException("Object already in map");
        }
    }
    
    void put(const char* key, Object* value) {
        String k(key);
        ObjectPtr o(value);
        if (m_map.bind(k, o) == -1) {
            throw HermesRuntimeException("Object already in map");
        }
    }

    void getKeys(ACE_Bounded_Set<String>& keys) {
        ObjectMap::ITERATOR iter = m_map.begin();
        while (iter != m_map.end()) {
            keys.insert((*iter).key());
            iter++;
        }
    }

    bool constainsKey(String& key) {
        return (m_map.find(key)!=-1);
    }

    //bool constainsObject(Object& obj) {
    //    return m_contextMap.containsValue(obj);
    //}

protected:    
    typedef ACE_Hash_Map_Manager<String, ObjectPtr, ACE_SYNCH_RW_MUTEX> ObjectMap;
    ObjectMap m_map;    
};

#endif	/* HERMESRUNTMECONTEXT_H */

