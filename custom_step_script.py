import shutil
import sys 
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
            shutil.copy2(srd_file, dest_file)
    pass



def handle_event(event, tp, args):
    print "event: " + event
    print "platform: " + tp
    print args
    
    # args: {
    #     'ndk-build-mode': 'debug', 
    #     'project-path': '/Users/yuxiao/Documents/workspace/fate/client', 
    #     'build-mode': 'debug', 
    #     'platform-project-path': '/Users/yuxiao/Documents/workspace/fate/client/frameworks/runtime-src/proj.android', 
    #     'output-dir': '/Users/yuxiao/Documents/workspace/fate/client/runtime/android'
    # }

    project_path = args['platform-project-path']


    if tp == "android":
        os.chdir(project_path)

        # backup 
        if event == "pre-build":
            # remove temp files and folders
            if os.path.isfile("build.xml"):
                os.remove("build.xml")
            if os.path.isfile("AndroidManifest.xml"):
                os.remove("AndroidManifest.xml")
            if os.path.isdir("jni"):
                shutil.rmtree("jni")
            if os.path.isdir("res"):
                shutil.rmtree("res")
            if os.path.isdir("src"):
                shutil.rmtree("src")

            # copy inherit files
            inherit_path = os.path.join(project_path, "targets", "inherit")
            if os.path.isdir(inherit_path):
                shutil.copy2(os.path.join(inherit_path, "build.xml"), ".")
                shutil.copy2(os.path.join(inherit_path, "AndroidManifest.xml"), ".")
                shutil.copytree(os.path.join(inherit_path, "jni"), "jni", True)
                shutil.copytree(os.path.join(inherit_path, "res"), "res", True)
                shutil.copytree(os.path.join(inherit_path, "src"), "src", True)

            # copy target files
            target_path = os.path.join(project_path, "target")
            if os.path.isdir(target_path):
                shutil.copy2(os.path.join(target_path, "build.xml"), ".")
                shutil.copy2(os.path.join(target_path, "AndroidManifest.xml"), ".")
                merge_dir("target/jni", "jni")
                merge_dir("target/res", "res")
                merge_dir("target/src", "src")
                pass

            pass

        if event == "pre-ndk-build":
            pass

        if event == "post-ndk-build":
            target_path = os.path.join(project_path, "target")
            if os.path.isdir(target_path):
                merge_dir("target/libs", "libs")
            pass

        if event == "pre-copy-assets":
            pass

        if event == "post-copy-assets":
            target_path = os.path.join(project_path, "target")
            if os.path.isdir(target_path):
                merge_dir("target/assets", "assets")
            pass

        if event == "pre-ant-build":
            pass

        if event == "post-ant-build":
            pass

        if event == "post-build":
            pass

        pass

