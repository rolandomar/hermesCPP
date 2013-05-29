/* 
 * File:   FaultCustomTriggerChecker.h
 * Author: rmartins
 *
 * Created on April 28, 2013, 7:28 PM
 */

#ifndef FAULTCUSTOMTRIGGERCHECKER_H
#define	FAULTCUSTOMTRIGGERCHECKER_H

#include <ace/Bound_Ptr.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Synch.h>
#include <ace/Synch_Traits.h>
#include <euryale/Types.h>
//#include <hermes/runtime/HermesFault.h>
class HermesFault;

class FaultCustomTriggerChecker {
public:
    virtual bool customTriggerChecker(HermesFault* f) = 0;
};

#endif	/* FAULTCUSTOMTRIGGERCHECKER_H */

