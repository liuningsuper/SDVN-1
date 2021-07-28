#ifndef STOPAPP_H
#define STOPAPP_H

#include<omnetpp.h>
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "modules/messages/SafetyAlertMessage_m.h"
#include "modules/stats/MyStatistics.h"


using namespace omnetpp;
using namespace veins;
using namespace std;

class FloodingApp : public DemoBaseApplLayer  {

    public:

        void initialize(int stage) override;
        void finish() override;

    protected:

        bool beenInAccident;
        bool sentMessage;
        simtime_t lastDroveAt;
        vector<long> alerts;

        MyStatistics* stats;

        void onBSM(DemoSafetyMessage* bsm) override;
        void onWSM(BaseFrame1609_4* wsm) override;
        void onWSA(DemoServiceAdvertisment* wsa) override;

        void handleSelfMsg(cMessage* msg) override;
        void handlePositionUpdate(cObject* obj) override;

};

#endif
