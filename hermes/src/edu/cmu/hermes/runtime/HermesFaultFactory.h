/* 
 * File:   HermesFaultFactory.h
 * Author: rmartins
 *
 * Created on April 29, 2013, 1:07 PM
 */

#ifndef HERMESFAULTFACTORY_H
#define	HERMESFAULTFACTORY_H

#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <euryale/Types.h>

class HermesFault;
typedef ACE_Strong_Bound_Ptr<HermesFault, ACE_SYNCH_MUTEX> HermesFaultPtr;

class HermesFaultFactory {
public:
    HermesFaultFactory();    
    virtual ~HermesFaultFactory();
    
    static HermesFaultFactory* getInstance();
    
    void getAspectImpl(int serialID,HermesFaultPtr& f);
    
protected:
    static HermesFaultFactory* m_staticInstance;
};

#endif	/* HERMESFAULTFACTORY_H */

