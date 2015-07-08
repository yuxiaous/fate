//
//  KtplaySdk.cpp
//  fate
//
//  Created by yuxiao on 15/7/8.
//
//

#include "KtplaySdk.h"
#import "KTPlay.h"



KtplaySdk *KtplaySdk::getInstance()
{
    static KtplaySdk *instance = nullptr;
    if(instance == nullptr) {
        instance = new KtplaySdk();
    }
    return instance;
}

void KtplaySdk::init()
{
    
}