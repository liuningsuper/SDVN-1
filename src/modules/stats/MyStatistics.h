#ifndef STATISCS_H
#define STATISCS_H

#include<omnetpp.h>

using namespace omnetpp;
using namespace std;

/**
 * https://doc.omnetpp.org/omnetpp/manual/sec:simple-modules:declaring-statistics
 */

class MyStatistics : public cSimpleModule  {

    public:

        void updateReceivedAlerts();
        void updateDuplicatedMessages();
        void updateRebroadcast();
        void updateRoi(int);
        void recordDelay(simtime_t);

        void initialize(int stage) override;
        //void finish() override;

    protected:

        uint receivedAlerts;
        uint duplicatedMessages;
        uint rebroadcast;

        simsignal_t receivedAlertsSignal;
        simsignal_t roiSignal;
        simsignal_t delaySignal;
        simsignal_t duplicatedMessagesSignal; // Indicate the number of duplicate messages received by a vehicle
        simsignal_t rebroadcastSignal; // Indicate the number of rebroadcast by a vehicle

};

class StatisticsModule {

    public:

        StatisticsModule() {}

        static MyStatistics* getIfExists(){
            return dynamic_cast<MyStatistics*>(cSimulation::getActiveSimulation()->getModuleByPath("stats"));
        }

};

#endif
