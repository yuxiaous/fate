import shutil
import sys 
import os

def android_handle_event(event, args):
    target_path = os.path.join(args['platform-project-path'], "target")
    if not os.path.exists(target_path):
        print target_path + " not exists."
        return

    global custom
    if not target_path in sys.path:
        sys.path.append(target_path) 
    if not "custom_step" in sys.modules:
        custom = __import__("custom_step")

    os.chdir(target_path)
    custom.handle_event(event, args)


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



def handle_event(event, tp, args):
    # args: {
    #     'ndk-build-mode': 'debug', 
    #     'project-path': '/Users/yuxiao/Documents/workspace/fate/client', 
    #     'build-mode': 'debug', 
    #     'platform-project-path': '/Users/yuxiao/Documents/workspace/fate/client/frameworks/runtime-src/proj.android', 
    #     'output-dir': '/Users/yuxiao/Documents/workspace/fate/client/runtime/android'
    # }

    if tp == "android":
        os.chdir(args['platform-project-path'])

        # backup 
        if event == "pre-build":
            # remove
            if os.path.isfile("build.xml.bak"):
                os.remove("build.xml.bak")
            if os.path.isfile("AndroidManifest.xml.bak"):
                os.remove("AndroidManifest.xml.bak")
            if os.path.isdir("jni.bak"):
                shutil.rmtree("jni.bak")
            if os.path.isdir("res.bak"):
                shutil.rmtree("res.bak")
            if os.path.isdir("src.bak"):
                shutil.rmtree("src.bak")

            # backup
            shutil.copy("build.xml", "build.xml.bak")
            shutil.copy("AndroidManifest.xml", "AndroidManifest.xml.bak")
            shutil.copytree("jni", "jni.bak", True)
            shutil.copytree("res", "res.bak", True)
            shutil.copytree("src", "src.bak", True)

        # resume
        if event == "post-ant-build":
            # # remove
            os.remove("build.xml")
            os.remove("AndroidManifest.xml")
            shutil.rmtree("jni")
            shutil.rmtree("res")
            shutil.rmtree("src")

            # # rename
            os.rename("build.xml.bak", "build.xml")
            os.rename("AndroidManifest.xml.bak", "AndroidManifest.xml")
            shutil.move("jni.bak", "jni")
            shutil.move("res.bak", "res")
            shutil.move("src.bak", "src")

        # handle event
        android_handle_event(event, args)
        pass

