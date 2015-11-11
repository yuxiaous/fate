APP_STL := gnustl_static

# Uncomment this line to compile to armeabi-v7a, your application will run faster but support less devices
#APP_ABI := armeabi-v7a

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif


APP_CPPFLAGS += -DCHANNEL_4399
APP_CPPFLAGS += -DSDK_TALKING_DATA_GA
APP_CPPFLAGS += -DSDK_KTPLAY
APP_CPPFLAGS += -DSDK_MIX
APP_CPPFLAGS += -DMIX_M4399_RECHARGE
APP_CPPFLAGS += -DSDK_UMENG_ONLINE_CONFIG
