import shutil
import os

def handle_event(event, args):

    if event == "post-ndk-build":
        lib_path = "../../../../../Classes/sdk/mmbilling/android/armeabi"
        shutil.copy(os.path.join(lib_path, "libcasdkjni.so"), "../../libs/armeabi/libcasdkjni.so")
        shutil.copy(os.path.join(lib_path, "libcmcc_haze.so"), "../../libs/armeabi/libcmcc_haze.so")
        shutil.copy(os.path.join(lib_path, "libcmcc_rusteze.so"), "../../libs/armeabi/libcmcc_rusteze.so")
        shutil.copy(os.path.join(lib_path, "libidentifyapp.so"), "../../libs/armeabi/libidentifyapp.so")
        pass


    pass

