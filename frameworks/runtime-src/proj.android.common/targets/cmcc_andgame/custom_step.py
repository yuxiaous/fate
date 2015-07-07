import shutil
import os

def handle_event(event, args):

    if event == "post-ndk-build":
        lib_path = "../../../../../Classes/sdk/AndGame/android/libs/armeabi"
        shutil.copy(os.path.join(lib_path, "libmegjb.so"), "../../libs/armeabi")
        pass

    pass

