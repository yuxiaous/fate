LOCAL_PATH := $(call my-dir)


#===== third os start =========================================================

include $(CLEAR_VARS)
LOCAL_MODULE := megjb
LOCAL_SRC_FILES := ../sdk/AndGame.Sdk_v20121/SDK/libs/armeabi/libmegjb.so
include $(PREBUILT_SHARED_LIBRARY)

#===== third os end =========================================================


include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := \
../../Classes/protobuf-lite/google/protobuf/io/coded_stream.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/common.cc \
../../Classes/protobuf-lite/google/protobuf/extension_set.cc \
../../Classes/protobuf-lite/google/protobuf/generated_message_util.cc \
../../Classes/protobuf-lite/google/protobuf/message_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/once.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/atomicops_internals_x86_gcc.cc \
../../Classes/protobuf-lite/google/protobuf/repeated_field.cc \
../../Classes/protobuf-lite/google/protobuf/wire_format_lite.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream.cc \
../../Classes/protobuf-lite/google/protobuf/io/zero_copy_stream_impl_lite.cc \
../../Classes/protobuf-lite/google/protobuf/stubs/stringprintf.cc \
../../Classes/runtime/ConnectWaitLayer.cpp \
../../Classes/runtime/ConsoleCommand.cpp \
../../Classes/runtime/FileServer.cpp \
../../Classes/runtime/Landscape_png.cpp \
../../Classes/runtime/PlayDisable_png.cpp \
../../Classes/runtime/PlayEnable_png.cpp \
../../Classes/runtime/Portrait_png.cpp \
../../Classes/runtime/Protos.pb.cc \
../../Classes/runtime/Runtime.cpp \
../../Classes/runtime/Shine_png.cpp \
../../Classes/VisibleRect.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/ConfigParser.cpp \
hellojavascript/Runtime_android.cpp \
hellojavascript/main.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Classes/protobuf-lite \
$(LOCAL_PATH)/../../Classes/runtime \
$(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../../../Classes \
$(LOCAL_PATH)/../../../../Classes/jsb \
$(LOCAL_PATH)/../../../../Classes/sdk
 
 
LOCAL_STATIC_LIBRARIES := cocos_jsb_static
LOCAL_STATIC_LIBRARIES += game_jsb_static
LOCAL_STATIC_LIBRARIES += game_sdk_static


LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module,bindings)
$(call import-module,jsb)
$(call import-module,sdk)
