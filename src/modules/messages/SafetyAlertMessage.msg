cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}}

class BaseFrame1609_4;
class noncobject Coord;
class LAddress::L2Type extends void;

packet SafetyAlertMessage extends BaseFrame1609_4 {
    string demoData;
    LAddress::L2Type senderAddress = -1;
    int serial = 0;
    simtime_t messageOriginTime; 
}