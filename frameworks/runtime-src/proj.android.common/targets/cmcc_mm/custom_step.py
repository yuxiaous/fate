import shutil
import os

def merge_dir(from_dir, to_dir):
    for parent, dirnames, filenames in os.walk(from_dir):
        for dirname in  dirnames: 
            dest_dir = os.path.join(to_dir, parent, dirname)
            if not os.path.exists(dest_dir):
                os.makedirs(dest_dir)

        for filename in filenames:
            if filename == ".DS_Store":
                continue
            shutil.copy(os.path.join(parent, filename), os.path.join(to_dir, parent, filename))





def handle_event(event, args):
    print "event: "+event
    print args

    if event == "pre-ndk-build":
        shutil.copy2("jni/Application.mk", "../../jni/Application.mk")
        pass

    if event == "post-ndk-build":
        lib_path = "../../../../../Classes/sdk/mmbilling/android/armeabi"
        shutil.copy(os.path.join(lib_path, "libcasdkjni.so"), "../../libs/armeabi/libcasdkjni.so")
        shutil.copy(os.path.join(lib_path, "libcmcc_haze.so"), "../../libs/armeabi/libcmcc_haze.so")
        shutil.copy(os.path.join(lib_path, "libcmcc_rusteze.so"), "../../libs/armeabi/libcmcc_rusteze.so")
        shutil.copy(os.path.join(lib_path, "libidentifyapp.so"), "../../libs/armeabi/libidentifyapp.so")
        pass

    if event == "post-copy-assets":
        merge_dir("res", "../..")
        pass

    if event == "pre-ant-build":
        shutil.copy("AndroidManifest.xml", "../../AndroidManifest.xml")
        shutil.copy("build.xml", "../../build.xml")
        merge_dir("src", "../..")
        pass


    pass

