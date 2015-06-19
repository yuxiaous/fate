LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_sdk_static

LOCAL_MODULE_FILENAME := libgamesdk

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := SdkManager.cpp \
                   Sdk.cpp \


LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../sdk \
                    $(LOCAL_PATH)/../sdk/android

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../sdk \
                           $(LOCAL_PATH)/../sdk/android

include $(BUILD_STATIC_LIBRARY)

