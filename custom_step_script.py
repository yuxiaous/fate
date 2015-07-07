import sys 
import os

def handle_event(event, tp, args):
    # args: {
    #     'ndk-build-mode': 'debug', 
    #     'project-path': '/Users/yuxiao/Documents/workspace/fate/client', 
    #     'build-mode': 'debug', 
    #     'platform-project-path': '/Users/yuxiao/Documents/workspace/fate/client/frameworks/runtime-src/proj.android', 
    #     'output-dir': '/Users/yuxiao/Documents/workspace/fate/client/runtime/android'
    # }

    if tp == "android":
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