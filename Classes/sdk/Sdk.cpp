//
//  Sdk.cpp
//  crows
//
//  Created by yuxiao on 15/4/7.
//
//

#include "Sdk.h"


void *Sdk::_appController = nullptr;
void *Sdk::_viewController = nullptr;
void *Sdk::_window = nullptr;

Sdk::Sdk()
{
//    SdkManager::addSdk(this);
}

Sdk::~Sdk()
{
//    SdkManager::removeSdk(this);
}

