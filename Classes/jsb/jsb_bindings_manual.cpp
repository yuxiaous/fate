//
//  jsb_bindings_manual.cpp
//  crows
//
//  Created by yuxiao on 15/1/8.
//
//

#include "jsb_bindings_manual.h"
#include "jsb_levelhelper_auto.hpp"
#include "LevelHelper2API.h"
#include "jsb_bindings_auto.hpp"
//#include "RoleBaseNode.h"

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
//    JS_DefineFunction(cx, jsb_LHScene_prototype, "ctor", js_levelhelper_LHScene_ctor, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_LHScene_prototype), "ctor", js_levelhelper_LHScene_ctor, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}


// bindings
//static bool js_RoleBaseNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    jsval *argv = JS_ARGV(cx, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    RoleBaseNode *nobj = new (std::nothrow) RoleBaseNode();
//    if (nobj) {
//        nobj->autorelease();
//    }
//    js_proxy_t* p = jsb_new_proxy(nobj, obj);
//    JS_AddNamedObjectRoot(cx, &p->obj, "RoleBaseNode");
//    bool isFound = false;
//    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
//        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
//    JS_SET_RVAL(cx, vp, JSVAL_VOID);
//    return true;
//}

//static bool js_PhysicalNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    jsval *argv = JS_ARGV(cx, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    PhysicalNode *nobj = new (std::nothrow) PhysicalNode();
//    if (nobj) {
//        nobj->autorelease();
//    }
//    js_proxy_t* p = jsb_new_proxy(nobj, obj);
//    JS_AddNamedObjectRoot(cx, &p->obj, "PhysicalNode");
//    bool isFound = false;
//    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
//        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
//    JS_SET_RVAL(cx, vp, JSVAL_VOID);
//    return true;
//}

void register_all_jsb_bindings_manual(JSContext *cx, JS::HandleObject global)
{
//    JS_DefineFunction(cx, jsb_RoleBaseNode_prototype, "ctor", js_RoleBaseNode_ctor, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, jsb_PhysicalNode_prototype, "ctor", js_PhysicalNode_ctor, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}












