//
//  DeveloperSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "DeveloperSdk.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"


static DeveloperSdk *instance = nullptr;
DeveloperSdk *DeveloperSdk::getInstance()
{
    if(instance == nullptr) {
        instance = new DeveloperSdk();
    }
    return instance;
}

void DeveloperSdk::charge(const std::string &order, const std::string &identifier)
{
    onChargeCallback(0, order);
}

