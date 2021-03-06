//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/SAFETYALERTMESSAGE.msg.
//

#ifndef SAFETYALERTMESSAGE_M_H
#define SAFETYALERTMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef VEINS_API
#  if defined(VEINS_EXPORT)
#    define VEINS_API  OPP_DLLEXPORT
#  elif defined(VEINS_IMPORT)
#    define VEINS_API  OPP_DLLIMPORT
#  else
#    define VEINS_API
#  endif
#endif


#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"


using namespace veins;

class SafetyAlertMessage : public ::veins::BaseFrame1609_4
{
  protected:
    ::omnetpp::opp_string demoData;
    LAddress::L2Type senderAddress;
    int serial;
    simtime_t messageOriginTime;

  private:
    void copy(const SafetyAlertMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SafetyAlertMessage&);

  public:
    SafetyAlertMessage(const char *name=nullptr, short kind=0);
    SafetyAlertMessage(const SafetyAlertMessage& other);
    virtual ~SafetyAlertMessage();
    SafetyAlertMessage& operator=(const SafetyAlertMessage& other);
    virtual SafetyAlertMessage *dup() const override {return new SafetyAlertMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getDemoData() const;
    virtual void setDemoData(const char * demoData);
    virtual LAddress::L2Type& getSenderAddress();
    virtual const LAddress::L2Type& getSenderAddress() const {return const_cast<SafetyAlertMessage*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const LAddress::L2Type& senderAddress);
    virtual int getSerial() const;
    virtual void setSerial(int serial);
    virtual simtime_t getMessageOriginTime();
    virtual void setMessageOriginTime(simtime_t);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SafetyAlertMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SafetyAlertMessage& obj) {obj.parsimUnpack(b);}


#endif

