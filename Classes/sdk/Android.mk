LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_sdk_static

LOCAL_MODULE_FILENAME := libgamesdk

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := SdkManager.cpp \
                   Sdk.cpp \
                   DeveloperSdk.cpp \
                   TalkingDataGameAnalytics/TalkingDataGameAnalyticsSdk.cpp


LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT \
                -DTALKING_DATA_GA \
                -DFATE_DEV

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/2d \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/base \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/ui \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/audio/include \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/storage \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/extensions \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/external \
                    $(LOCAL_PATH)/../sdk

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../sdk

LOCAL_STATIC_LIBRARIES := cocos2dx-talkingdata

include $(BUILD_STATIC_LIBRARY)

$(call import-module,sdk/TalkingDataGameAnalytics/android)

