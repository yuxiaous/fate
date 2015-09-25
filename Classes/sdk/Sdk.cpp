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
#include "GameUtils.h"


Sdk::Sdk()
{
    SdkManager::addSdk(this);
}

Sdk::~Sdk()
{
    SdkManager::removeSdk(this);
}


std::function<void(char*)> SdkChargeProtocol::_chargeCallback = nullptr;

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

        if(_chargeCallback) {
            _chargeCallback((char*)buffer.GetString());
        }
    }
}

std::string SdkChargeProtocol::getShopConfig(const std::string &key)
{
    const GameUtils::ConfigGetter getter = GameUtils::getConfigGetter();
    if(getter == nullptr) {
        return std::string();
    }
    
    return getter("shop", key.c_str());
}

std::string SdkChargeProtocol::getChargeIdentifier(const std::string &key)
{
    std::string configstr = getShopConfig(key);
    if(configstr.empty()) {
        return std::string();
    }
    
    rapidjson::Document json;
    json.Parse<0>(configstr.c_str());
    rapidjson::Value jidentifier;
    jidentifier = json["platform_good_id"];
    if(jidentifier.IsString() == false) {
        return std::string();
    }
    
    return jidentifier.GetString();
}

