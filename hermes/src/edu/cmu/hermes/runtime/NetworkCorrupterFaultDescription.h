/* 
 * File:   NetworkCorrupterFaultDescription.h
 * Author: rmartins
 *
 * Created on May 3, 2013, 1:12 PM
 */

#ifndef NETWORKCORRUPTERFAULTDESCRIPTION_H
#define	NETWORKCORRUPTERFAULTDESCRIPTION_H
#include <hermes/runtime/FaultDescription.h>
class NetworkCorrupterFaultDescription: public FaultDescription {
public:
    static const int SERIAL_ID = 123123984;
    NetworkCorrupterFaultDescription(){}
    NetworkCorrupterFaultDescription(
            int corruptPer) {
        m_corruptPer = corruptPer;
    }

    virtual ~NetworkCorrupterFaultDescription();
    
    int getCorruptionPercentage() {
        return m_corruptPer;
    }
    
    int getSerialID() {
        return SERIAL_ID;
    }
protected:
    int m_corruptPer;
    
    virtual void serializableFaultDescriptionImpl(OutputStream& outputStream) throw (SerializationException&) {
        outputStream.write_long(m_corruptPer);
        
    }
    virtual void deserializableFaultDescriptionImpl(InputStream& inputStream) throw (SerializationException&) {
        inputStream.read_long(m_corruptPer);
    }

};

#endif	/* NETWORKCORRUPTERFAULTDESCRIPTION_H */

