#include "UniPaySdk.h"



static UniPaySdk *instance = nullptr;

UniPaySdk::UniPaySdk()
{
    instance = this;
}

UniPaySdk *UniPaySdk::getInstance()
{
    return instance;
}

void UniPaySdk::init()
{

}

void UniPaySdk::charge(const std::string &order, const std::string &identifier)
{

}