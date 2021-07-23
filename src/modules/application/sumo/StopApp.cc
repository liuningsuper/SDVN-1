#include "StopApp.h"

using namespace std;

Define_Module(StopApp);

void StopApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        EV << "Initializing StopApp" << std::endl;

        beenInAccident = false;
        sentMessage = false;
        lastDroveAt = simTime();



    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
    }
}

void StopApp::finish()
{
    DemoBaseApplLayer::finish();

}

void StopApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void StopApp::onWSM(BaseFrame1609_4* wsm)
{
    SafetyAlertMessage* alert = check_and_cast<SafetyAlertMessage*>(wsm);

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(alert->getDemoData(), 9999);
    if (!sentMessage) {
        sentMessage = true;
        // repeat the received traffic update once in 2 seconds plus some random delay
        alert->setSenderAddress(myId);
        alert->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), alert->dup());
    }
}

void StopApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void StopApp::handleSelfMsg(cMessage* msg)
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

void StopApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    if (mobility->getSpeed() < 1) {
            if (simTime() - lastDroveAt >= 10 && beenInAccident == false) {

                if(traciVehicle->getVType()=="warning"){
                    findHost()->getDisplayString().setTagArg("i", 1, "red");
                    beenInAccident = sentMessage = true;
                    SafetyAlertMessage* wsm = new SafetyAlertMessage();
                    populateWSM(wsm);
                    wsm->setDemoData(mobility->getRoadId().c_str());
                    sendDown(wsm);
                }
            }
        }
        else {
            lastDroveAt = simTime();
        }

}
