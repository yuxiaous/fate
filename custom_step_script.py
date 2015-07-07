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



def handle_event(event, tp, args):
    # args: {
    #     'ndk-build-mode': 'debug', 
    #     'project-path': '/Users/yuxiao/Documents/workspace/fate/client', 
    #     'build-mode': 'debug', 
    #     'platform-project-path': '/Users/yuxiao/Documents/workspace/fate/client/frameworks/runtime-src/proj.android', 
    #     'output-dir': '/Users/yuxiao/Documents/workspace/fate/client/runtime/android'
    # }

    if tp == "android":
        # backup 
        if event == "pre-build":
            os.chdir(args['platform-project-path'])

            # remove
            if os.path.isfile("build.xml.bak"):
                os.remove("build.xml.bak")
            if os.path.isfile("AndroidManifest.xml.bak"):
                os.remove("AndroidManifest.xml.bak")
            if os.path.isfile("jni/Application.mk.bak"):
                os.remove("jni/Application.mk.bak")
            if os.path.isdir("res.bak"):
                shutil.rmtree("res.bak")
            if os.path.isdir("src.bak"):
                shutil.rmtree("src.bak")

            # backup
            shutil.copy("build.xml", "build.xml.bak")
            shutil.copy("AndroidManifest.xml", "AndroidManifest.xml.bak")
            shutil.copy("jni/Application.mk", "jni/Application.mk.bak")
            shutil.copytree("res", "res.bak", True)
            shutil.copytree("src", "src.bak", True)

        # resume
        if event == "post-ant-build":
            os.chdir(args['platform-project-path'])

            # # remove
            os.remove("build.xml")
            os.remove("AndroidManifest.xml")
            os.remove("jni/Application.mk")
            shutil.rmtree("res")
            shutil.rmtree("src")

            # # rename
            os.rename("build.xml.bak", "build.xml")
            os.rename("AndroidManifest.xml.bak", "AndroidManifest.xml")
            os.rename("jni/Application.mk.bak", "jni/Application.mk")
            shutil.move("res.bak", "res")
            shutil.move("src.bak", "src")

        # handle event
        android_handle_event(event, args)

