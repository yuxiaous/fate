//
//  Sdk.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include "Sdk.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"


Sdk::Sdk()
{
//    SdkManager::addSdk(this);
}

Sdk::~Sdk()
{
//    SdkManager::removeSdk(this);
}



void SdkChargeProtocol::onChargeCallback(int result, const std::string &order) {
    if(_chargeCallback) {
        rapidjson::Document json;
        json.Parse<0>("{}");
        
        // result: [int] 0:success 1:fail
        rapidjson::Value result_key("result", json.GetAllocator());
        rapidjson::Value result_value(result);
        json.AddMember(result_key, result_value, json.GetAllocator());
        
        // order: [string]
        rapidjson::Value order_key("order", json.GetAllocator());
        rapidjson::Value order_value(order.c_str(), json.GetAllocator());
        json.AddMember(order_key, order_value, json.GetAllocator());
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json.Accept(writer);
        
        _chargeCallback((char*)buffer.GetString());
    }
    
    SdkManager::onChargeResult(result, order);
}