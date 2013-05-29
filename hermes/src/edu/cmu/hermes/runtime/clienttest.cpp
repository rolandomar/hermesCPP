/* 
 * File:   clienttest.cpp
 * Author: rmartins
 *
 * Created on April 30, 2013, 7:46 PM
 */

#include <cstdlib>

using namespace std;

#include <hermes/runtime/HermesOrchestrationClient.h>
#include <hermes/runtime/CheckFaultInjectionActionResult.h>

#include "HermesRuntime.h"
#include "HermesFault.h"

/*
 * 
 */
int main(int argc, char** argv) {
    String id("0");
    //HermesOrchestrationClient client(0,id);
    //client.open("localhost",8989);
    //client.open();
    HermesRuntime::getInstance()->setID(id);
    HermesRuntime::getInstance()->open();
    //    Notification* notification = new RuntimeJoinNotification(id);
    //    client.notification(notification,0);
    //    notification = new RuntimeJoinNotification(id);
    //    client.notification(notification,0);
    String faultID("asjh21323");
    
    while (true) {
        //CheckFaultInjectionAction* action = new CheckFaultInjectionAction(id, faultID);
        //ActionResult* result = HermesRuntime::getInstance()->action(action, 0);    
        //printf("check=%d\n",((CheckFaultInjectionActionResult*) result)->getCheck());
        HermesFaultPtr f;
        HermesRuntime::getInstance()->getFaultManager().getFault(faultID,f);
        if(!f.null()){
                printf("Is enabled? %d\n",f->isEnabled());
                try{
                    printf("before fault execution\n");
                    f->execute();
                    printf("before after execution\n");
                }catch(HermesRuntimeException& ex){
                    printf("Exception on fault\n");
                }
        }
        sleep(2);
    }

    return 0;    
}

