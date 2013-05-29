/* 
 * File:   StatToken.h
 * Author: rmartins
 *
 * Created on April 30, 2013, 12:07 AM
 */

#ifndef STATTOKEN_H
#define	STATTOKEN_H

#include <euryale/serialization/Serializable.h>

class StatToken : public Serializable {
public:
    StatToken();

    StatToken(int i, long duration) {
        m_duration = duration;
        m_i = i;
    }
    StatToken(const StatToken& orig);
    virtual ~StatToken();

    void serialize(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_longlong(m_duration);
        outputStream.write_longlong(m_i);
    }

    void deserialize(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_longlong(m_duration);
        inputStream.read_longlong(m_i);
    }

protected:
    LongLong m_duration;
    LongLong m_i;
};

#endif	/* STATTOKEN_H */
