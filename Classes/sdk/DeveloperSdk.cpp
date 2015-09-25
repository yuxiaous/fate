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

DeveloperSdk::DeveloperSdk()
{
    instance = this;
}

DeveloperSdk *DeveloperSdk::getInstance()
{
    return instance;
}

void DeveloperSdk::charge(const std::string &order, const std::string &key)
{
    std::string identifier = getChargeIdentifier(key);
    
    onChargeCallback(0, order);
}

