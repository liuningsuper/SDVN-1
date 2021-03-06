#include "FloodingApp.h"

using namespace std;

Define_Module(FloodingApp);

void FloodingApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        EV << "Initializing FloodingApp" << std::endl;

        stats = StatisticsModule::getIfExists();

        ASSERT(stats);

        beenInAccident = false;
        sentMessage = false;
        lastDroveAt = simTime();
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
    }
}

void FloodingApp::finish()
{
    DemoBaseApplLayer::finish();
    alerts.clear();

}

void FloodingApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void FloodingApp::onWSM(BaseFrame1609_4* wsm)
{
    SafetyAlertMessage* alert = check_and_cast<SafetyAlertMessage*>(wsm);

    if(!count(alerts.begin(),alerts.end(),alert->getTreeId())){
        stats->recordDelay(alert->getMessageOriginTime());
        findHost()->getDisplayString().setTagArg("i", 1, "green");
        if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(alert->getDemoData(), 9999);
        alert->setSenderAddress(myId);
        alert->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), alert->dup());
        alerts.push_back(alert->getTreeId());
        stats->updateRebroadcast();
        stats->updateReceivedAlerts();
    }else
        stats->updateDuplicatedMessages();
}

void FloodingApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void FloodingApp::handleSelfMsg(cMessage* msg)
{

    if (SafetyAlertMessage* wsm = dynamic_cast<SafetyAlertMessage*>(msg)) {
           // send this message on the service channel until the counter is 3 or higher.
           // this code only runs when channel switching is enabled
           sendDown(wsm->dup());
           wsm->setSerial(wsm->getSerial() + 1);
           if (wsm->getSerial() >= 3) {
               // stop service advertisements
               stopService();
               delete (wsm);
           }
           else {
               scheduleAt(simTime() + 1, wsm);
           }
       }
       else {
           DemoBaseApplLayer::handleSelfMsg(msg);
       }
}

void FloodingApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    if (mobility->getSpeed() < 1) {
            if (simTime() - lastDroveAt >= 10 && beenInAccident == false) {

                if(traciVehicle->getVType()=="warning" || true){
                    findHost()->getDisplayString().setTagArg("i", 1, "red");
                    beenInAccident = true;
                    //std::list<std::string> vInRoi = traci->getLastStepVehiclesId(traciVehicle->getLaneId());
                    //stats->updateRoi(vInRoi.size()-1);

                    stats->updateRoi(((mobility->getManager())->getManagedHosts().size())-1);

                    SafetyAlertMessage* wsm = new SafetyAlertMessage();
                    populateWSM(wsm);
                    wsm->setDemoData(mobility->getRoadId().c_str());
                    wsm->setMessageOriginTime(simTime());
                    sendDown(wsm);
                    alerts.push_back(wsm->getTreeId());
                }
            }
        }
    else {
        lastDroveAt = simTime();
    }

}
