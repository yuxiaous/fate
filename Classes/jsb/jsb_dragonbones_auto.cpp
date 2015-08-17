#include "jsb_dragonbones_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "DBCCRenderHeaders.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_dragonBones_DBCCArmatureNode_class;
JSObject *jsb_dragonBones_DBCCArmatureNode_prototype;

bool js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler : Invalid Native Object");
    if (argc == 1) {
        std::function<void (dragonBones::DBCCArmatureNode *, char *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](dragonBones::DBCCArmatureNode* larg0, char* larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            largv[1] = c_string_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler : Error processing arguments");
        cobj->registerMovementEventHandler(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getCCEventDispatcher(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_getCCEventDispatcher : Invalid Native Object");
    if (argc == 0) {
        cocos2d::EventDispatcher* ret = cobj->getCCEventDispatcher();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EventDispatcher>(cx, (cocos2d::EventDispatcher*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_getCCEventDispatcher : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler : Invalid Native Object");
    if (argc == 1) {
        std::function<void (dragonBones::DBCCArmatureNode *, char *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](dragonBones::DBCCArmatureNode* larg0, char* larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            largv[1] = c_string_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler : Error processing arguments");
        cobj->registerFrameEventHandler(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterMovementEventHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterMovementEventHandler : Invalid Native Object");
    if (argc == 0) {
        cobj->unregisterMovementEventHandler();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterMovementEventHandler : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay : Error processing arguments");
        bool ret = cobj->gotoAndPlay(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    dragonBones::DBCCArmatureNode* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_getBoundingBox : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect ret = cobj->getBoundingBox(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = ccrect_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cocos2d::Rect ret = cobj->getBoundingBox();
            jsval jsret = JSVAL_NULL;
            jsret = ccrect_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_getBoundingBox : wrong number of arguments");
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterFrameEventHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterFrameEventHandler : Invalid Native Object");
    if (argc == 0) {
        cobj->unregisterFrameEventHandler();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterFrameEventHandler : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature : Invalid Native Object");
    if (argc == 2) {
        dragonBones::DBCCArmature* arg0;
        dragonBones::WorldClock* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::WorldClock*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature : Error processing arguments");
        bool ret = cobj->initWithDBCCArmature(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_getCCDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_getCCDisplay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getCCDisplay();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_getCCDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    dragonBones::DBCCArmatureNode* cobj = (dragonBones::DBCCArmatureNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime : Error processing arguments");
        cobj->advanceTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_dragonbones_auto_DBCCArmatureNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::DBCCArmature* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_create : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_create : wrong number of arguments");
    return false;
}

bool js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        dragonBones::DBCCArmature* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::createWithWorldClock(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        dragonBones::DBCCArmature* arg0;
        dragonBones::WorldClock* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (dragonBones::DBCCArmature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (dragonBones::WorldClock*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = dragonBones::DBCCArmatureNode::createWithWorldClock(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock : wrong number of arguments");
    return false;
}

bool js_jsb_dragonbones_auto_DBCCArmatureNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    dragonBones::DBCCArmatureNode* cobj = new (std::nothrow) dragonBones::DBCCArmatureNode();
    TypeTest<dragonBones::DBCCArmatureNode> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_dragonBones_DBCCArmatureNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DBCCArmatureNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        dragonBones::DBCCArmatureNode *nobj = static_cast<dragonBones::DBCCArmatureNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_dragonbones_auto_DBCCArmatureNode(JSContext *cx, JS::HandleObject global) {
    jsb_dragonBones_DBCCArmatureNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_dragonBones_DBCCArmatureNode_class->name = "DBCCArmatureNode";
    jsb_dragonBones_DBCCArmatureNode_class->addProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->delProperty = JS_DeletePropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->getProperty = JS_PropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->setProperty = JS_StrictPropertyStub;
    jsb_dragonBones_DBCCArmatureNode_class->enumerate = JS_EnumerateStub;
    jsb_dragonBones_DBCCArmatureNode_class->resolve = JS_ResolveStub;
    jsb_dragonBones_DBCCArmatureNode_class->convert = JS_ConvertStub;
    jsb_dragonBones_DBCCArmatureNode_class->finalize = js_dragonBones_DBCCArmatureNode_finalize;
    jsb_dragonBones_DBCCArmatureNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("registerMovementEventHandler", js_jsb_dragonbones_auto_DBCCArmatureNode_registerMovementEventHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCEventDispatcher", js_jsb_dragonbones_auto_DBCCArmatureNode_getCCEventDispatcher, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("registerFrameEventHandler", js_jsb_dragonbones_auto_DBCCArmatureNode_registerFrameEventHandler, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unregisterMovementEventHandler", js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterMovementEventHandler, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPlay", js_jsb_dragonbones_auto_DBCCArmatureNode_gotoAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoundingBox", js_jsb_dragonbones_auto_DBCCArmatureNode_getBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unregisterFrameEventHandler", js_jsb_dragonbones_auto_DBCCArmatureNode_unregisterFrameEventHandler, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDBCCArmature", js_jsb_dragonbones_auto_DBCCArmatureNode_initWithDBCCArmature, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCDisplay", js_jsb_dragonbones_auto_DBCCArmatureNode_getCCDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("advanceTime", js_jsb_dragonbones_auto_DBCCArmatureNode_advanceTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_dragonbones_auto_DBCCArmatureNode_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithWorldClock", js_jsb_dragonbones_auto_DBCCArmatureNode_createWithWorldClock, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_dragonBones_DBCCArmatureNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_dragonBones_DBCCArmatureNode_class,
        js_jsb_dragonbones_auto_DBCCArmatureNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DBCCArmatureNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<dragonBones::DBCCArmatureNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_dragonBones_DBCCArmatureNode_class;
        p->proto = jsb_dragonBones_DBCCArmatureNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_DragonBonesHelper_class;
JSObject *jsb_DragonBonesHelper_prototype;

bool js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = DragonBonesHelper::buildArmatureNode(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode : Error processing arguments");
        dragonBones::DBCCArmatureNode* ret = DragonBonesHelper::buildArmatureNode(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<dragonBones::DBCCArmatureNode>(cx, (dragonBones::DBCCArmatureNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode : wrong number of arguments");
    return false;
}

bool js_jsb_dragonbones_auto_DragonBonesHelper_advanceWorldClock(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DragonBonesHelper_advanceWorldClock : Error processing arguments");
        DragonBonesHelper::advanceWorldClock(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DragonBonesHelper_advanceWorldClock : wrong number of arguments");
    return false;
}

bool js_jsb_dragonbones_auto_DragonBonesHelper_removeDragonBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DragonBonesHelper_removeDragonBones : Error processing arguments");
        DragonBonesHelper::removeDragonBones(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DragonBonesHelper_removeDragonBones : wrong number of arguments");
    return false;
}

bool js_jsb_dragonbones_auto_DragonBonesHelper_addDragonBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_dragonbones_auto_DragonBonesHelper_addDragonBones : Error processing arguments");
        bool ret = DragonBonesHelper::addDragonBones(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_dragonbones_auto_DragonBonesHelper_addDragonBones : wrong number of arguments");
    return false;
}



void js_DragonBonesHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DragonBonesHelper)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        DragonBonesHelper *nobj = static_cast<DragonBonesHelper *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_dragonbones_auto_DragonBonesHelper(JSContext *cx, JS::HandleObject global) {
    jsb_DragonBonesHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_DragonBonesHelper_class->name = "DragonBonesHelper";
    jsb_DragonBonesHelper_class->addProperty = JS_PropertyStub;
    jsb_DragonBonesHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_DragonBonesHelper_class->getProperty = JS_PropertyStub;
    jsb_DragonBonesHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_DragonBonesHelper_class->enumerate = JS_EnumerateStub;
    jsb_DragonBonesHelper_class->resolve = JS_ResolveStub;
    jsb_DragonBonesHelper_class->convert = JS_ConvertStub;
    jsb_DragonBonesHelper_class->finalize = js_DragonBonesHelper_finalize;
    jsb_DragonBonesHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("buildArmatureNode", js_jsb_dragonbones_auto_DragonBonesHelper_buildArmatureNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("advanceWorldClock", js_jsb_dragonbones_auto_DragonBonesHelper_advanceWorldClock, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeDragonBones", js_jsb_dragonbones_auto_DragonBonesHelper_removeDragonBones, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDragonBones", js_jsb_dragonbones_auto_DragonBonesHelper_addDragonBones, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_DragonBonesHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_DragonBonesHelper_class,
        dummy_constructor<DragonBonesHelper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DragonBonesHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<DragonBonesHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_DragonBonesHelper_class;
        p->proto = jsb_DragonBonesHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_jsb_dragonbones_auto(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "dragonBones", &ns);

    js_register_jsb_dragonbones_auto_DBCCArmatureNode(cx, ns);
    js_register_jsb_dragonbones_auto_DragonBonesHelper(cx, ns);
}

