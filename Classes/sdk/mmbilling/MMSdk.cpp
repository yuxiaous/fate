#include "MMSdk.h"


MMSdk *MMSdk::getInstance()
{
    static MMSdk *instance = nullptr;
    if(instance == nullptr) {
        instance = new MMSdk();
    }
    return instance;
}

void MMSdk::init()
{

}

void MMSdk::charge(const std::string &order, const std::string &identifier)
{

}

