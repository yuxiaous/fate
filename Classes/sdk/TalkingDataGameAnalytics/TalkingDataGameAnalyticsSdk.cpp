//
//  TalkingDataGameAnalyticsSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "TalkingDataGameAnalyticsSdk.h"
#include "TalkingData.h"


static TalkingDataGameAnalyticsSdk *instance = nullptr;
TalkingDataGameAnalyticsSdk *TalkingDataGameAnalyticsSdk::getInstance()
{
    if(instance == nullptr) {
        instance = new TalkingDataGameAnalyticsSdk();
    }
    return instance;
}

void TalkingDataGameAnalyticsSdk::init()
{
    TDCCTalkingDataGA::onStart("59EC3DE05BB0234EA444193F4B9E0E4B", "Develop");
}