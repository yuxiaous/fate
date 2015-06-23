//
//  Sdk.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include "Sdk.h"


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void *Sdk::_appController = nullptr;
void *Sdk::_viewController = nullptr;
void *Sdk::_window = nullptr;
#endif


Sdk::Sdk()
{
//    SdkManager::addSdk(this);
}

Sdk::~Sdk()
{
//    SdkManager::removeSdk(this);
}

