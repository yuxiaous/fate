import sys; 

target_path = "frameworks/runtime-src/proj.android/target"
custom_script = "custom_step"

if not target_path in sys.path:
    sys.path.append(target_path) 

if not custom_script in sys.modules:
    custom_step = __import__(custom_script)


def handle_event(event, tp, args):
    custom_step.handle_event(event, tp, args)
    pass