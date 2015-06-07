LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := levelhelper_static

LOCAL_MODULE_FILENAME := liblevelhelper

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := LevelHelper2-API/LHAnimation.cpp \
                   LevelHelper2-API/LHAnimationProperty.cpp \
                   LevelHelper2-API/LHAsset.cpp \
                   LevelHelper2-API/LHBackUINode.cpp \
                   LevelHelper2-API/LHBezier.cpp \
                   LevelHelper2-API/LHBodyShape.cpp \
                   LevelHelper2-API/LHBone.cpp \
                   LevelHelper2-API/LHBoneFrame.cpp \
                   LevelHelper2-API/LHBoneNodes.cpp \
                   LevelHelper2-API/LHBox2dCollisionHandling.cpp \
                   LevelHelper2-API/LHBox2dDebugDrawNode.cpp \
                   LevelHelper2-API/LHCamera.cpp \
                   LevelHelper2-API/LHCameraActivateProperty.cpp \
                   LevelHelper2-API/LHChildrenOpacitiesProperty.cpp \
                   LevelHelper2-API/LHChildrenPositionsProperty.cpp \
                   LevelHelper2-API/LHChildrenRotationsProperty.cpp \
                   LevelHelper2-API/LHChildrenScalesProperty.cpp \
                   LevelHelper2-API/LHContactInfo.cpp \
                   LevelHelper2-API/LHDevice.cpp \
                   LevelHelper2-API/LHDictionary.cpp \
                   LevelHelper2-API/LHDistanceJointNode.cpp \
                   LevelHelper2-API/LHDrawNode.cpp \
                   LevelHelper2-API/LHFrame.cpp \
                   LevelHelper2-API/LHGameWorldNode.cpp \
                   LevelHelper2-API/LHGearJointNode.cpp \
                   LevelHelper2-API/LHGravityArea.cpp \
                   LevelHelper2-API/LHJointsProtocol.cpp \
                   LevelHelper2-API/LHNode.cpp \
                   LevelHelper2-API/LHNodeAnimationProtocol.cpp \
                   LevelHelper2-API/LHNodeProtocol.cpp \
                   LevelHelper2-API/LHOpacityFrame.cpp \
                   LevelHelper2-API/LHOpacityProperty.cpp \
                   LevelHelper2-API/LHParallax.cpp \
                   LevelHelper2-API/LHParallaxLayer.cpp \
                   LevelHelper2-API/LHPhysicsProtocol.cpp \
                   LevelHelper2-API/LHPositionFrame.cpp \
                   LevelHelper2-API/LHPositionProperty.cpp \
                   LevelHelper2-API/LHPrismaticJointNode.cpp \
                   LevelHelper2-API/LHPulleyJointNode.cpp \
                   LevelHelper2-API/LHRevoluteJointNode.cpp \
                   LevelHelper2-API/LHRootBoneProperty.cpp \
                   LevelHelper2-API/LHRopeJointNode.cpp \
                   LevelHelper2-API/LHRotationFrame.cpp \
                   LevelHelper2-API/LHRotationProperty.cpp \
                   LevelHelper2-API/LHScaleFrame.cpp \
                   LevelHelper2-API/LHScaleProperty.cpp \
                   LevelHelper2-API/LHScene.cpp \
                   LevelHelper2-API/LHShape.cpp \
                   LevelHelper2-API/LHSprite.cpp \
                   LevelHelper2-API/LHSpriteFrame.cpp \
                   LevelHelper2-API/LHSpriteFrameProperty.cpp \
                   LevelHelper2-API/LHUINode.cpp \
                   LevelHelper2-API/LHUserProperties.cpp \
                   LevelHelper2-API/LHUtils.cpp \
                   LevelHelper2-API/LHWater.cpp \
                   LevelHelper2-API/LHWeldJointNode.cpp \
                   LevelHelper2-API/LHWheelJointNode.cpp \
                   LevelHelper2-API/NodeTransform.cpp


LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/2d \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/base \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/ui \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/audio/include \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/cocos/storage \
                    $(LOCAL_PATH)/../../frameworks/js-bindings/cocos2d-x/extensions


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/manual \
                           $(LOCAL_PATH)/../../frameworks/js-bindings/bindings/auto

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += spidermonkey_static
LOCAL_STATIC_LIBRARIES += cocos_localstorage_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,storage/local-storage)
