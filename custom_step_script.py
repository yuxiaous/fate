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



    if tp == "android":
        project_path = args['platform-project-path']
        target_name = args['target-name']

        inherit_path = os.path.join(project_path, "targets", "inherit")
        target_path = os.path.join(project_path, "targets", target_name)

        os.chdir(project_path)

        if not os.path.isdir(target_path):
            print "Target not exist."
            exit(0)
            return

        # backup 
        if event == "pre-build":
            # remove temp files and folders
            if os.path.isfile(os.path.join(project_path, "build.xml")):
                os.remove(os.path.join(project_path, "build.xml"))
            if os.path.isfile(os.path.join(project_path, "AndroidManifest.xml")):
                os.remove(os.path.join(project_path, "AndroidManifest.xml"))
            if os.path.isdir(os.path.join(project_path, "jni")):
                shutil.rmtree(os.path.join(project_path, "jni"))
            if os.path.isdir(os.path.join(project_path, "res")):
                shutil.rmtree(os.path.join(project_path, "res"))
            if os.path.isdir(os.path.join(project_path, "src")):
                shutil.rmtree(os.path.join(project_path, "src"))

            # copy inherit files
            if os.path.isdir(inherit_path):
                if os.path.isfile(os.path.join(inherit_path, "build.xml")):
                    shutil.copy2(os.path.join(inherit_path, "build.xml"), os.path.join(project_path, "build.xml"))
                if os.path.isfile(os.path.join(inherit_path, "AndroidManifest.xml")):
                    shutil.copy2(os.path.join(inherit_path, "AndroidManifest.xml"), os.path.join(project_path, "AndroidManifest.xml"))
                if os.path.isdir(os.path.join(inherit_path, "jni")):
                    shutil.copytree(os.path.join(inherit_path, "jni"), os.path.join(project_path, "jni"), True)
                if os.path.isdir(os.path.join(inherit_path, "res")):
                    shutil.copytree(os.path.join(inherit_path, "res"), os.path.join(project_path, "res"), True)
                if os.path.isdir(os.path.join(inherit_path, "src")):
                    shutil.copytree(os.path.join(inherit_path, "src"), os.path.join(project_path, "src"), True)
                pass

            # copy target files
            if os.path.isdir(target_path):
                if os.path.isfile(os.path.join(target_path, "build.xml")):
                    shutil.copy2(os.path.join(target_path, "build.xml"), os.path.join(project_path, "build.xml"))
                if os.path.isfile(os.path.join(target_path, "AndroidManifest.xml")):
                    shutil.copy2(os.path.join(target_path, "AndroidManifest.xml"), os.path.join(project_path, "AndroidManifest.xml"))
                if os.path.isdir(os.path.join(target_path, "jni")):
                    merge_dir(os.path.join("targets", target_name, "jni"), "jni")
                if os.path.isdir(os.path.join(target_path, "res")):
                    merge_dir(os.path.join("targets", target_name, "res"), "res")
                if os.path.isdir(os.path.join(target_path, "src")):
                    merge_dir(os.path.join("targets", target_name, "src"), "src")
                pass

            pass

        if event == "pre-ndk-build":
            pass

        if event == "post-ndk-build":
            if os.path.isdir(inherit_path):
                merge_dir(os.path.join("targets", "inherit", "libs"), "libs")
            if os.path.isdir(target_path):
                merge_dir(os.path.join("targets", target_name, "libs"), "libs")
            pass

        if event == "pre-copy-assets":
            pass

        if event == "post-copy-assets":
            if os.path.isdir(inherit_path):
                merge_dir(os.path.join("targets", "inherit", "assets"), "assets")
            if os.path.isdir(target_path):
                merge_dir(os.path.join("targets", target_name, "assets"), "assets")
            pass

        if event == "pre-ant-build":
            pass

        if event == "post-ant-build":
            pass

        if event == "post-build":
            pass

        pass

