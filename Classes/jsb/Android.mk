LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_jsb_static

LOCAL_MODULE_FILENAME := libgamejsb

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := jsb_bindings_auto.cpp \
                   jsb_bindings_manual.cpp \
                   jsb_levelhelper_auto.cpp \
                   jsb_dragonbones_auto.cpp
                   

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/manual \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/auto \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/2d \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/base \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/ui \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/audio/include \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/storage \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/extensions \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../SneakyInput \
                    $(LOCAL_PATH)/../LevelHelper2/LevelHelper2-API \
                    $(LOCAL_PATH)/../dragonbones \
                    $(LOCAL_PATH)/../dragonbones/renderer/cocos2d-x-3.x


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/manual \
                           $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/auto

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += spidermonkey_static
LOCAL_STATIC_LIBRARIES += cocos_localstorage_static
LOCAL_STATIC_LIBRARIES += levelhelper_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,storage/local-storage)
$(call import-module,LevelHelper2)
