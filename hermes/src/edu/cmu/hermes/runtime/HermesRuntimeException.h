/* 
 * File:   HermesRuntimeException.h
 * Author: rmartins
 *
 * Created on April 28, 2013, 11:37 AM
 */

#ifndef HERMESRUNTIMEEXCEPTION_H
#define	HERMESRUNTIMEEXCEPTION_H

#include <euryale/common/exception/Exception.h>
#include <euryale/common/Integer.h>

class HermesRuntimeException : public Exception {
public:    
    static const char* GENERAL_ERROR;
        
    HermesRuntimeException(const char* exception);
    HermesRuntimeException(const HermesRuntimeException&);
    virtual ~HermesRuntimeException();

    virtual void raise(void) {
        throw *this;
    }

    virtual const String& message() {
        return m_messageString;
    }

    virtual const char* objectID() const {
        return "c1814bb30fad0657573b1687d34b5129";
    }

    virtual const String& toString() {
        return message();
    }
    

private:
    String m_messageString;
};

#endif	/* HERMESRUNTIMEEXCEPTION_H */

