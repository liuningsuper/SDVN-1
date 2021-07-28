#include "MyStatistics.h"


Define_Module(MyStatistics)

void MyStatistics::initialize(int stage){

    if(stage==0){
        receivedAlertsSignal = registerSignal("receivedAlerts");
        receivedAlerts=0;
        roiSignal = registerSignal("roi");
        delaySignal = registerSignal("delay");
        duplicatedMessagesSignal = registerSignal("duplicatedMessages");
        duplicatedMessages=0;
        rebroadcastSignal = registerSignal("rebroadcast");
        rebroadcast=0;
    }

}

void MyStatistics::updateReceivedAlerts(){

    emit(receivedAlertsSignal,receivedAlerts++);

}




void MyStatistics::updateDuplicatedMessages(){

    emit(duplicatedMessagesSignal,duplicatedMessages++);
}

void MyStatistics::updateRebroadcast(){

    emit(rebroadcastSignal,rebroadcast++);
}


void MyStatistics::updateRoi(int roi){

    emit(roiSignal,roi);

}

void MyStatistics::recordDelay(simtime_t delay){

    emit(delaySignal,simTime()-delay);
}
