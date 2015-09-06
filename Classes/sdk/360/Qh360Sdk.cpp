#include "Qh360Sdk.h"


static Qh360Sdk *instance = nullptr;

Qh360Sdk::Qh360Sdk()
{
    instance = this;
}

Qh360Sdk *Qh360Sdk::getInstance()
{
    return instance;
}

void Qh360Sdk::init()
{

}

void Qh360Sdk::update(float dt)
{

}

void Qh360Sdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{

}

void Qh360Sdk::charge(const std::string &order, const std::string &identifier)
{

}