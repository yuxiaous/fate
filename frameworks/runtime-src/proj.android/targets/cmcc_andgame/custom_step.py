import shutil
import os

def merge_dir(from_dir, to_dir):
    for parent, dirnames, filenames in os.walk(from_dir):
        for dirname in  dirnames: 
            src_dir = os.path.join(parent, dirname)
            tmp_dir = src_dir[len(from_dir)+1:]
            dest_dir = os.path.join(to_dir, tmp_dir)

            # print "dir src  : " + src_dir
            # print "dir dest : " + dest_dir
            if not os.path.exists(dest_dir):
                os.makedirs(dest_dir)

        for filename in filenames:
            if filename == ".DS_Store":
                continue

            srd_file = os.path.join(parent, filename)
            tmp_file = srd_file[len(from_dir)+1:]
            dest_file = os.path.join(to_dir, tmp_file)

            # print "file src  : " + srd_file
            # print "file dest : " + dest_file
            shutil.copy(srd_file, dest_file)

def handle_event(event, args):
    if event == "post-ndk-build":
        path = "../../../../../Classes/sdk/AndGame/android/libs/armeabi"
        shutil.copy(os.path.join(path, "libmegjb.so"), "../../libs/armeabi")
        pass

    if event == "post-copy-assets":
        print "sdfsdfsdfsadfsdaf"
        path = "../../../../../Classes/sdk/AndGame/android/assets"
        merge_dir(path, "../../assets")
        pass
    pass

