LOCAL_PATH := $(call my-dir)






#prebuild KTPlay library
#KTPLAY_LIBRARIES_PATH := ../../../../Classes/sdk/ktplay/Platform/Android/KTPlaySDK/KTPlay/libs/armeabi
KTPLAY_LIBRARIES_PATH := ktplay/Platform/Android/KTPlaySDK/KTPlay/libs/armeabi

include $(CLEAR_VARS)
LOCAL_MODULE := KTPlay
LOCAL_SRC_FILES := $(KTPLAY_LIBRARIES_PATH)/libKTPlay.so
LOCAL_MODULE_FILENAME := libKTPlay
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KTAccountmanager
LOCAL_SRC_FILES := $(KTPLAY_LIBRARIES_PATH)/libKTAccountmanager.so
LOCAL_MODULE_FILENAME := libKTAccountmanager
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KTFriendship
LOCAL_SRC_FILES := $(KTPLAY_LIBRARIES_PATH)/libKTFriendship.so
LOCAL_MODULE_FILENAME := libKTFriendship
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KTLeaderboard
LOCAL_SRC_FILES := $(KTPLAY_LIBRARIES_PATH)/libKTLeaderboard.so
LOCAL_MODULE_FILENAME := libKTLeaderboard
include $(PREBUILT_SHARED_LIBRARY)





include $(CLEAR_VARS)

LOCAL_MODULE := game_sdk_static

LOCAL_MODULE_FILENAME := libgamesdk

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := SdkManager.cpp \
                   Sdk.cpp \
                   TalkingDataGameAnalytics/TalkingDataGameAnalyticsSdk.cpp \
                   DeveloperSdk.cpp \
                   AndGame/AndGameSdk.cpp \
                   mmbilling/MMSdk.cpp \
                   ktplay/KtplaySdk.cpp \
                   unipay/UniPaySdk.cpp \
                   egame/EgameSdk.cpp


LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT


LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/2d \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/base \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/ui \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/audio/include \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/storage \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/extensions \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/external \
                    $(LOCAL_PATH) \
                    $(LOCAL_PATH)/..

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/..

LOCAL_STATIC_LIBRARIES := cocos2dx-talkingdata


LOCAL_SHARED_LIBRARIES := KTPlay \
                          KTAccountmanager \
                          KTFriendship \
                          KTLeaderboard

include $(BUILD_STATIC_LIBRARY)

$(call import-module,sdk/TalkingDataGameAnalytics/android)

