//
//  TalkingDataGameAnalyticsSdk.cpp
//  fate
//
//  Created by yuxiao on 15/6/26.
//
//

#include "TalkingDataGameAnalyticsSdk.h"
#include "GameUtils.h"

#if  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "TalkingDataGameAnalytics/android/TDGAJniHelper.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#endif

USING_NS_CC;


static TalkingDataGameAnalyticsSdk *instance = nullptr;

TalkingDataGameAnalyticsSdk::TalkingDataGameAnalyticsSdk()
: _account(nullptr)
{
    instance = this;
}

TalkingDataGameAnalyticsSdk *TalkingDataGameAnalyticsSdk::getInstance()
{
    return instance;
}

void TalkingDataGameAnalyticsSdk::init()
{
    cocos2d::log("TalkingDataGameAnalyticsSdk::init");

    const char *appid = "59EC3DE05BB0234EA444193F4B9E0E4B";
    const char *channel = "Develop";

#if defined(CHANNEL_APPSTORE)
    channel = "AppStore";
#elif defined(CHANNEL_CMCC_MM)
    channel = "CmccMm";
#elif defined(CHANNEL_CMCC_AND)
    channel = "CmccAnd";
#elif defined(CHANNEL_UNICOM)
    channel = "Unicom";
#elif defined(CHANNEL_TELECOM)
    channel = "Egame";
#elif defined(CHANNEL_MZW)
    channel = "Mzw";
#elif defined(CHANNEL_4399)
    channel = "4399";
#elif defined(CHANNEL_PPS)
    channel = "Pps";
#elif defined(CHANNEL_SOHUWAN)
    channel = "SohuWan";
#elif defined(CHANNEL_YOUKU)
    channel = "Youku";
#elif defined(CHANNEL_BAIDU_91)
    channel = "Baidu91";
#elif defined(CHANNEL_BAIDU_TIEBA)
    channel = "BaiduTieba";
//#elif defined(CHANNEL_360)
//    channel = "360";
//#elif defined(CHANNEL_TENCENT_QQ)
//    channel = "TencentQq";

//=====================================================
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    appid = "D02F09F2D8C67C240618579B2C9BF358";
    channel = "IosDevelop";
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    appid = "D02F09F2D8C67C240618579B2C9BF358";
    channel = "AndroidDevelop";
#else
    appid = "D02F09F2D8C67C240618579B2C9BF358";
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TDCCTalkingDataGA::onStart(appid, channel);
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    TDGAJniHelper::setJavaVM(JniHelper::getJavaVM());

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com.tendcloud.tenddata.TalkingDataGA",
        "init",
        "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        jstring jappid = minfo.env->NewStringUTF(appid);
        jstring jchannel = minfo.env->NewStringUTF(channel);

        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity, jappid, jchannel);

        minfo.env->DeleteLocalRef(jappid);
        minfo.env->DeleteLocalRef(jchannel);
    }
#endif
}

void TalkingDataGameAnalyticsSdk::sdkCommand(const std::string &clazz, const std::string &method, const std::string &param)
{
    if(clazz != "TalkingDataGA"){
        return;
    }
    
    if(method == "setAccount") {
        setAccount(param.c_str());
    }
    else if(method == "setAccountName") {
        setAccountName(param.c_str());
    }
    else if(method == "setAccountType") {
        setAccountType(atoi(param.c_str()));
    }
    else if(method == "setLevel") {
        setLevel(atoi(param.c_str()));
    }
    else if(method == "setGender") {
        setGender(atoi(param.c_str()));
    }
    else if(method == "setAge") {
        setAge(atoi(param.c_str()));
    }
    else if(method == "setGameServer") {
        setGameServer(param.c_str());
    }
    else if(method == "onChargeRequest") {
        std::vector<std::string> ret;
        GameUtils::split(param, ",", ret);
        onChargeRequest(ret[0].c_str(), ret[1].c_str(), atof(ret[2].c_str()), ret[3].c_str(), atof(ret[4].c_str()), ret[5].c_str());
    }
    else if(method == "onChargeSuccess") {
        
        onChargeSuccess(param.c_str());
    }
    else if(method == "onReward") {
        
    }
    else if(method == "onPurchase") {
        std::vector<std::string> ret;
        GameUtils::split(param, ",", ret);
        onPurchase(ret[0].c_str(), atoi(ret[1].c_str()), atof(ret[2].c_str()));
        
    }
    else if(method == "onUse") {
        std::vector<std::string> ret;
        GameUtils::split(param, ",", ret);
        onUse(ret[0].c_str(), atoi(ret[1].c_str()));
    }
    else if(method == "onBegin") {
        onBegin(param.c_str());
    }
    else if(method == "onCompleted") {
        onCompleted(param.c_str());
    }
    else if(method == "onFailed") {
        std::vector<std::string> ret;
        GameUtils::split(param, ",", ret);
        onFailed(ret[0].c_str(), ret[1].c_str());
    }
}

// TDCCAccount
void TalkingDataGameAnalyticsSdk::setAccount(const char* accountId)
{
    if(_account == nullptr) {
        _account = TDCCAccount::setAccount(accountId);
    }
}

void TalkingDataGameAnalyticsSdk::setAccountName(const char* accountName)
{
    if(_account) {
        _account->setAccountName(accountName);
    }
}

void TalkingDataGameAnalyticsSdk::setAccountType(int type)
{
    if(_account) {
        _account->setAccountType((TDCCAccount::TDCCAccountType)type);
    }
}

void TalkingDataGameAnalyticsSdk::setLevel(int level)
{
    if(_account) {
        _account->setLevel(level);
    }
}

void TalkingDataGameAnalyticsSdk::setGender(int gender)
{
    if(_account) {
        _account->setGender((TDCCAccount::TDCCGender)gender);
    }
}

void TalkingDataGameAnalyticsSdk::setAge(int age)
{
    if(_account) {
        _account->setAge(age);
    }
}

void TalkingDataGameAnalyticsSdk::setGameServer(const char* gameServer)
{
    if(_account) {
        _account->setGameServer(gameServer);
    }
}

// TDCCVirtualCurrency
void TalkingDataGameAnalyticsSdk::onChargeRequest(const char* orderId, const char* iapId, double currencyAmount, const char* currencyType, double virtualCurrencyAmount, const char* paymentType)
{
    TDCCVirtualCurrency::onChargeRequest(orderId, iapId, currencyAmount, currencyType, virtualCurrencyAmount, paymentType);
}

void TalkingDataGameAnalyticsSdk::onChargeSuccess(const char* orderId)
{
    TDCCVirtualCurrency::onChargeSuccess(orderId);
}

void TalkingDataGameAnalyticsSdk::onReward(double currencyAmount, const char* reason)
{
    TDCCVirtualCurrency::onReward(currencyAmount, reason);
}

// TDCCItem
void TalkingDataGameAnalyticsSdk::onPurchase(const char* item, int number, double price)
{
    TDCCItem::onPurchase(item, number, price);
}

void TalkingDataGameAnalyticsSdk::onUse(const char* item, int number)
{
    TDCCItem::onUse(item, number);
}

// TDCCMission
void TalkingDataGameAnalyticsSdk::onBegin(const char* missionId)
{
    TDCCMission::onBegin(missionId);
}

void TalkingDataGameAnalyticsSdk::onCompleted(const char* missionId)
{
    TDCCMission::onCompleted(missionId);
}

void TalkingDataGameAnalyticsSdk::onFailed(const char* missionId, const char* failedCause)
{
    TDCCMission::onFailed(missionId, failedCause);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void TalkingDataGameAnalyticsSdk::activityOnPause()
{
    cocos2d::log("TalkingDataGameAnalyticsSdk::activityOnPause");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com.tendcloud.tenddata.TalkingDataGA",
        "onPause",
        "(Landroid/app/Activity;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity);
    }
}
void TalkingDataGameAnalyticsSdk::activityOnResume()
{
    cocos2d::log("TalkingDataGameAnalyticsSdk::activityOnResume");

    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
        "com.tendcloud.tenddata.TalkingDataGA",
        "onResume",
        "(Landroid/app/Activity;)V")) {

        jobject jactivity = (jobject)SdkManager::appActivity;
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jactivity);
    }
}
#endif

