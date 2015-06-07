//
//  JsonStorage.cpp
//  HappyHero
//
//  Created by linyongxing on 14-6-10.
//
//

#include "JsonStorage.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
USING_NS_CC;
using namespace rapidjson;


static std::map<std::string , JsonStorage*> g_json_storages;

JsonStorage * JsonStorage::GetInstance( std::string fileName )
{
    std::map<std::string , JsonStorage*>::iterator find = g_json_storages.find(fileName);
    if(find != g_json_storages.end()) {
        return find->second;
    }
    
    JsonStorage *js = new JsonStorage();
    js->_fileName = fileName;
    js->parse();
    
    g_json_storages.insert(std::make_pair(fileName, js));
    
	return js;
}

void JsonStorage::parse()
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + _fileName;
    
    std::string fileContent = FileUtils::getInstance()->getStringFromFile(filePath.c_str());
    if(!fileContent.empty()) {
        _json.Parse<0>(fileContent.c_str());
    }
    
    if(!_json.IsObject()) {
        _json.Parse<0>("{}");
    }
    
    if(_json.HasParseError()){
        CCLOG("Json Parse Error: %s",_json.GetParseError());
    }
}

void JsonStorage::flush()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + _fileName;

//	if(!YLJFilePlatform::IsDirExist(FileUtils::getInstance()->getWritablePath().c_str())) {
//		YLJFilePlatform::DirCreate(FileUtils::getInstance()->getWritablePath().c_str());
//	}
    
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    _json.Accept(writer);
    
    FILE *fp = fopen(filePath.c_str(), "wt+");
    if(fp){
        fwrite(buffer.GetString(), buffer.Size(), 1, fp);
        fclose(fp);
    }
}

bool JsonStorage::getBoolForKey( const std::string &key, bool defaultValue /*= false*/ )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        bool ret = val.GetBool();
        return ret;
    }
    return defaultValue;
}


int JsonStorage::getIntegerForKey( const std::string &key, int defaultValue /*= 0*/ )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        int ret = val.GetInt();
        return ret;
    }
    return defaultValue;
}

double JsonStorage::getDoubleForKey( const std::string &key, float defaultValue/*=0.0f*/ )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        double ret = val.GetDouble();
        return ret;
    }
    return defaultValue;
}


std::string JsonStorage::getStringForKey( const std::string &key, const std::string & defaultValue /*= ""*/ )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        std::string ret = val.GetString();
        return ret;
    }
    return defaultValue;
}

void JsonStorage::setBoolForKey( const std::string &key, bool value )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        val.SetBool(value);
    }
    else {
        rapidjson::Value jname(key.c_str(), _json.GetAllocator());
        rapidjson::Value jvalue(value);
        _json.AddMember(jname, jvalue, _json.GetAllocator());
    }
}


void JsonStorage::setIntegerForKey( const std::string &key, int value )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        val.SetInt(value);
    }
    else {
        rapidjson::Value jname(key.c_str(), _json.GetAllocator());
        rapidjson::Value jvalue(value);
        _json.AddMember(jname, jvalue, _json.GetAllocator());
    }
}

void JsonStorage::setDoubleForKey( const std::string &key, double value )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        val.SetDouble(value);
    }
    else {
        rapidjson::Value jname(key.c_str(), _json.GetAllocator());
        rapidjson::Value jvalue(value);
        _json.AddMember(jname, jvalue, _json.GetAllocator());
    }
}

void JsonStorage::setStringForKey( const std::string &key, const std::string & value )
{
    if(_json.HasMember(key.c_str())) {
        rapidjson::Value& val = _json[key.c_str()];
        val.SetString(value.c_str(), _json.GetAllocator());
    }
    else {
        rapidjson::Value jname(key.c_str(), _json.GetAllocator());
        rapidjson::Value jvalue(value.c_str(), _json.GetAllocator());
        _json.AddMember(jname, jvalue, _json.GetAllocator());
    }
}

