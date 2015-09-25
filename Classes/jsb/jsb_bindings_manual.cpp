//
//  jsb_bindings_manual.cpp
//  crows
//
//  Created by yuxiao on 15/1/8.
//
//

#include "jsb_bindings_manual.h"
#include "jsb_bindings_auto.hpp"
#include "jsb_levelhelper_auto.hpp"
#include "LevelHelper2API.h"
#include "GameUtils.h"

// LevelHelper
static bool js_levelhelper_LHScene_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    LHScene *nobj = new (std::nothrow) LHScene();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "LHScene");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

void register_all_jsb_levelhelper_manual(JSContext *cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_LHScene_prototype), "ctor", js_levelhelper_LHScene_ctor, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

// GameUtils
static bool js_GameUtils_setConfigGetter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        GameUtils::ConfigGetter arg0;
        do {
            if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
            {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
                auto lambda = [=](const char* larg0, const char* larg1) -> const char* {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[2];
                    largv[0] = c_string_to_jsval(cx, larg0);
                    largv[1] = c_string_to_jsval(cx, larg1);
                    JS::RootedValue rval(cx);
                    bool ok = func->invoke(2, &largv[0], &rval);
                    if (!ok && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                    
                    const char *ret;
                    jsval_to_charptr(cx, rval, &ret);
                    return ret;
                };
                arg0 = lambda;
            }
            else
            {
                arg0 = nullptr;
            }
        } while(0);
        
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setChargeCallback : Error processing arguments");
        GameUtils::setConfigGetter(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setChargeCallback : wrong number of arguments");
    return false;
}


void register_all_jsb_bindings_manual(JSContext *cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_GameUtils_prototype), "setConfigGetter", js_GameUtils_setConfigGetter, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}












