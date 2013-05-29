/* 
 * File:   FaultContext.h
 * Author: rmartins
 *
 * Created on April 28, 2013, 7:52 PM
 */

#ifndef FAULTCONTEXT_H
#define	FAULTCONTEXT_H

#include <ace/Hash_Map_Manager.h>
#include <ace/Time_Value.h>
#include <ace/ACE.h>
#include <ace/SString.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Containers_T.h>
#include <euryale/Types.h>
#include <euryale/common/Integer.h>
#include <euryale/serialization/Serializable.h>
#include <euryale/serialization/SerializationException.h>

class FaultContext : public Serializable {
public:
    typedef ACE_Hash_Map_Manager<String, String, ACE_SYNCH_RW_MUTEX> FaultContextMap;
    FaultContext();
    FaultContext(const FaultContext& orig);
    virtual ~FaultContext();

    FaultContext(FaultContextMap& ctx) {
        FaultContextMap::ITERATOR iter = ctx.begin();
        while (iter != ctx.end()) {
            m_ctx.bind((*iter).key(), (*iter).item());
            iter++;
        }
    }

    Long getLongValue(String key) {
        String item;
        if (m_ctx.find(key, item) == -1) {
            return -1;
        }
        return Integer::stringToNumber<Long>(item);
    }

    int putLongValue(String key, Long value) {
        String str = Integer::numberToString<Long>(value);
        return m_ctx.bind(key, str);
    }

    Int getIntValue(String key) {
        String item;
        if (m_ctx.find(key, item) == -1) {
            return -1;
        }
        return Integer::stringToNumber<Int>(item);
    }

    int putIntValue(String key, Int value) {
        String str = Integer::numberToString<Int>(value);
        return m_ctx.bind(key, str);
    }

    String getString(String key) {
        String str = "";
        m_ctx.find(key, str);
        return str;
    }

    void putStringValue(String key, String value) {
        m_ctx.bind(key, value);
    }

    Boolean hasKey(String key) {
        return (m_ctx.find(key) != -1);
    }

    Long getRun() {
        if (hasKey("RUN")) {
            return getLongValue("RUN");
        }
        return -1;
    }

    virtual void serialize(OutputStream& outputStream) throw (SerializationException&) {
        LongLong size = m_ctx.current_size();
        if (size == 0) {
            outputStream.write_longlong(0);
            return;
        } else {
            outputStream.write_longlong(size);
            FaultContextMap::ITERATOR iter = m_ctx.begin();
            while (iter != m_ctx.end()) {
                outputStream.write_string((*iter).key());
                outputStream.write_string((*iter).item());
                iter++;
            }
        }
    }

    virtual void deserialize(InputStream& inputStream) throw (SerializationException&) {
        //long == int...
        LongLong size;
        inputStream.read_longlong(size);
        m_ctx.unbind_all();
        if (size == 0) {
            return;
        }
        String key, item;
        printf("HermesFaultContext:deserialize:\n");
        for (int i = 0; i < size; i++) {            
            inputStream.read_string(key);
            inputStream.read_string(item);
            printf("key(%s) value(%s)\n",key.c_str(),item.c_str());
            m_ctx.bind(key, item);
        }
    }

    void operator=(const FaultContext& orig) {
        FaultContextMap::CONST_ITERATOR iter = orig.m_ctx.begin();
        while (iter != orig.m_ctx.end()) {
            m_ctx.bind((*iter).key(), (*iter).item());
            iter++;
        }
    }


protected:

    FaultContextMap m_ctx;

};

#endif	/* FAULTCONTEXT_H */

