/* 
 * File:   CheckFaultInjectionActionResult.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 12:10 PM
 */

#ifndef CHECKFAULTINJECTIONACTIONRESULT_H
#define	CHECKFAULTINJECTIONACTIONRESULT_H

#include <hermes/runtime/ActionResult.h>

class CheckFaultInjectionActionResult: public ActionResult {
public:
    static const int SERIAL_ID = 5000005;
    CheckFaultInjectionActionResult();
    CheckFaultInjectionActionResult(bool status) {
        m_status = status;
    }
    CheckFaultInjectionActionResult(const CheckFaultInjectionActionResult& orig);
    virtual ~CheckFaultInjectionActionResult();
    
    virtual int getSerialID() {
        return SERIAL_ID;
    }
    
    bool getCheck() {
       return m_status;
    }
      
protected:
    bool m_status;
    
    void serializeActionResult(OutputStream& outputStream) throw (SerializationException&){
        outputStream.write_boolean(m_status);        
    }
    
    void deserializableActionResult(InputStream& inputStream) throw (SerializationException&){
        inputStream.read_boolean(m_status);        
    }
    

};

#endif	/* CHECKFAULTINJECTIONACTIONRESULT_H */
