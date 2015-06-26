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

void DeveloperSdk::buy(const std::string &param)
{
    if(_buyCallback) {
        
        // get param
        rapidjson::Document jsonParam;
        jsonParam.Parse<0>(param.c_str());
        
        const char *param_order_key = "order";
        std::string param_order_value;
        if(jsonParam.HasMember(param_order_key)) {
            rapidjson::Value& val = jsonParam[param_order_key];
            param_order_value = val.GetString();
        }
        
        const char *param_id_key = "platform_good_id";
        std::string param_id_value;
        if(jsonParam.HasMember(param_id_key)) {
            rapidjson::Value& val = jsonParam[param_id_key];
            param_id_value = val.GetString();
        }
        
        // set result
        rapidjson::Document jsonResult;
        jsonResult.Parse<0>("{}");
        
        const char *result_result_key = "result";
        int result_result_value = 0;
        rapidjson::Value j_result_result_key(result_result_key, jsonResult.GetAllocator());
        rapidjson::Value j_resutl_result_value(result_result_value);
        jsonResult.AddMember(j_result_result_key, j_resutl_result_value, jsonResult.GetAllocator());
        
        const char *result_order_key = "order";
        std::string result_order_value = param_order_value;
        rapidjson::Value j_result_order_key(result_order_key, jsonResult.GetAllocator());
        rapidjson::Value j_resutl_order_value(result_order_value.c_str(), jsonResult.GetAllocator());
        jsonResult.AddMember(j_result_order_key, j_resutl_order_value, jsonResult.GetAllocator());
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsonResult.Accept(writer);
        
        onBuyCallback(buffer.GetString());
    }
}