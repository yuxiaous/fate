#include "jsb_bindings_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "jsb.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
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
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
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
JSClass  *jsb_Shake_class;
JSObject *jsb_Shake_prototype;

bool js_jsb_bindings_auto_Shake_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Shake* cobj = (Shake *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_Shake_initWithDuration : Invalid Native Object");
    if (argc == 3) {
        double arg0;
        double arg1;
        double arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_Shake_initWithDuration : Error processing arguments");
        bool ret = cobj->initWithDuration(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_Shake_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_bindings_auto_Shake_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_Shake_create : Error processing arguments");
        Shake* ret = Shake::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<Shake>(cx, (Shake*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_Shake_create : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_Shake_createWithStrength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        double arg0;
        double arg1;
        double arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_Shake_createWithStrength : Error processing arguments");
        Shake* ret = Shake::createWithStrength(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<Shake>(cx, (Shake*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_Shake_createWithStrength : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_Shake_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    Shake* cobj = new (std::nothrow) Shake();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<Shake> t;
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
    AddNamedObjectRoot(cx, &p->obj, "Shake");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_Shake_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Shake)", obj);
}

void js_register_jsb_bindings_auto_Shake(JSContext *cx, JS::HandleObject global) {
    jsb_Shake_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_Shake_class->name = "Shake";
    jsb_Shake_class->addProperty = JS_PropertyStub;
    jsb_Shake_class->delProperty = JS_DeletePropertyStub;
    jsb_Shake_class->getProperty = JS_PropertyStub;
    jsb_Shake_class->setProperty = JS_StrictPropertyStub;
    jsb_Shake_class->enumerate = JS_EnumerateStub;
    jsb_Shake_class->resolve = JS_ResolveStub;
    jsb_Shake_class->convert = JS_ConvertStub;
    jsb_Shake_class->finalize = js_Shake_finalize;
    jsb_Shake_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithDuration", js_jsb_bindings_auto_Shake_initWithDuration, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_Shake_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithStrength", js_jsb_bindings_auto_Shake_createWithStrength, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_Shake_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_Shake_class,
        js_jsb_bindings_auto_Shake_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Shake", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<Shake> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_Shake_class;
        p->proto = jsb_Shake_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_FallOffShake_class;
JSObject *jsb_FallOffShake_prototype;

bool js_jsb_bindings_auto_FallOffShake_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_FallOffShake_create : Error processing arguments");
        FallOffShake* ret = FallOffShake::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<FallOffShake>(cx, (FallOffShake*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_FallOffShake_create : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_FallOffShake_createWithStrength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        double arg0;
        double arg1;
        double arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_FallOffShake_createWithStrength : Error processing arguments");
        FallOffShake* ret = FallOffShake::createWithStrength(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<FallOffShake>(cx, (FallOffShake*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_FallOffShake_createWithStrength : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_FallOffShake_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    FallOffShake* cobj = new (std::nothrow) FallOffShake();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<FallOffShake> t;
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
    AddNamedObjectRoot(cx, &p->obj, "FallOffShake");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_Shake_prototype;

void js_FallOffShake_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (FallOffShake)", obj);
}

void js_register_jsb_bindings_auto_FallOffShake(JSContext *cx, JS::HandleObject global) {
    jsb_FallOffShake_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_FallOffShake_class->name = "FallOffShake";
    jsb_FallOffShake_class->addProperty = JS_PropertyStub;
    jsb_FallOffShake_class->delProperty = JS_DeletePropertyStub;
    jsb_FallOffShake_class->getProperty = JS_PropertyStub;
    jsb_FallOffShake_class->setProperty = JS_StrictPropertyStub;
    jsb_FallOffShake_class->enumerate = JS_EnumerateStub;
    jsb_FallOffShake_class->resolve = JS_ResolveStub;
    jsb_FallOffShake_class->convert = JS_ConvertStub;
    jsb_FallOffShake_class->finalize = js_FallOffShake_finalize;
    jsb_FallOffShake_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_FallOffShake_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithStrength", js_jsb_bindings_auto_FallOffShake_createWithStrength, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_FallOffShake_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_Shake_prototype),
        jsb_FallOffShake_class,
        js_jsb_bindings_auto_FallOffShake_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "FallOffShake", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<FallOffShake> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_FallOffShake_class;
        p->proto = jsb_FallOffShake_prototype;
        p->parentProto = jsb_Shake_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SneakyButton_class;
JSObject *jsb_SneakyButton_prototype;

bool js_jsb_bindings_auto_SneakyButton_onTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchMoved : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchMoved : Error processing arguments");
        cobj->onTouchMoved(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_onTouchMoved : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_setRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_setRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_setRadius : Error processing arguments");
        cobj->setRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_setRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchEnded : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchEnded : Error processing arguments");
        cobj->onTouchEnded(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_onTouchEnded : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_setIsEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsEnable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsEnable : Error processing arguments");
        cobj->setIsEnable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_setIsEnable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getIsActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getIsActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsActive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getIsActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getIsEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getIsEnable : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsEnable();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getIsEnable : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_setRateLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_setRateLimit : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_setRateLimit : Error processing arguments");
        cobj->setRateLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_setRateLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_onTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchCancelled : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchCancelled : Error processing arguments");
        cobj->onTouchCancelled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_onTouchCancelled : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchBegan : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_onTouchBegan : Error processing arguments");
        bool ret = cobj->onTouchBegan(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_onTouchBegan : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getValue : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getValue();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getRateLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getRateLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRateLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getRateLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getIsToggleable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getIsToggleable : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsToggleable();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getIsToggleable : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_limiter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_limiter : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_limiter : Error processing arguments");
        cobj->limiter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_limiter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_initWithSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_initWithSize : Error processing arguments");
        bool ret = cobj->initWithSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_setIsHoldable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsHoldable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsHoldable : Error processing arguments");
        cobj->setIsHoldable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_setIsHoldable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_setIsToggleable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsToggleable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_setIsToggleable : Error processing arguments");
        cobj->setIsToggleable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_setIsToggleable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getIsHoldable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getIsHoldable : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsHoldable();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getIsHoldable : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_getRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButton* cobj = (SneakyButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButton_getRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_getRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButton_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButton_create : Error processing arguments");
        SneakyButton* ret = SneakyButton::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyButton>(cx, (SneakyButton*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButton_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_SneakyButton_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SneakyButton)", obj);
}

void js_register_jsb_bindings_auto_SneakyButton(JSContext *cx, JS::HandleObject global) {
    jsb_SneakyButton_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SneakyButton_class->name = "SneakyButton";
    jsb_SneakyButton_class->addProperty = JS_PropertyStub;
    jsb_SneakyButton_class->delProperty = JS_DeletePropertyStub;
    jsb_SneakyButton_class->getProperty = JS_PropertyStub;
    jsb_SneakyButton_class->setProperty = JS_StrictPropertyStub;
    jsb_SneakyButton_class->enumerate = JS_EnumerateStub;
    jsb_SneakyButton_class->resolve = JS_ResolveStub;
    jsb_SneakyButton_class->convert = JS_ConvertStub;
    jsb_SneakyButton_class->finalize = js_SneakyButton_finalize;
    jsb_SneakyButton_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("onTouchMoved", js_jsb_bindings_auto_SneakyButton_onTouchMoved, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRadius", js_jsb_bindings_auto_SneakyButton_setRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchEnded", js_jsb_bindings_auto_SneakyButton_onTouchEnded, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsEnable", js_jsb_bindings_auto_SneakyButton_setIsEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsActive", js_jsb_bindings_auto_SneakyButton_getIsActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsEnable", js_jsb_bindings_auto_SneakyButton_getIsEnable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRateLimit", js_jsb_bindings_auto_SneakyButton_setRateLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchCancelled", js_jsb_bindings_auto_SneakyButton_onTouchCancelled, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchBegan", js_jsb_bindings_auto_SneakyButton_onTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getValue", js_jsb_bindings_auto_SneakyButton_getValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRateLimit", js_jsb_bindings_auto_SneakyButton_getRateLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsToggleable", js_jsb_bindings_auto_SneakyButton_getIsToggleable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("limiter", js_jsb_bindings_auto_SneakyButton_limiter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSize", js_jsb_bindings_auto_SneakyButton_initWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsHoldable", js_jsb_bindings_auto_SneakyButton_setIsHoldable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsToggleable", js_jsb_bindings_auto_SneakyButton_setIsToggleable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsHoldable", js_jsb_bindings_auto_SneakyButton_getIsHoldable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRadius", js_jsb_bindings_auto_SneakyButton_getRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_SneakyButton_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SneakyButton_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_SneakyButton_class,
        dummy_constructor<SneakyButton>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SneakyButton", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SneakyButton> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SneakyButton_class;
        p->proto = jsb_SneakyButton_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SneakyButtonSkinnedBase_class;
JSObject *jsb_SneakyButtonSkinnedBase_prototype;

bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getPressSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getPressSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getPressSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getPressSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getButton(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getButton : Invalid Native Object");
    if (argc == 0) {
        SneakyButton* ret = cobj->getButton();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyButton>(cx, (SneakyButton*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getButton : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getActivatedSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getActivatedSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getActivatedSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getActivatedSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton : Invalid Native Object");
    if (argc == 1) {
        SneakyButton* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (SneakyButton*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton : Error processing arguments");
        cobj->setButton(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDefaultSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDefaultSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getDefaultSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDefaultSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite : Error processing arguments");
        cobj->setDefaultSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite : Error processing arguments");
        cobj->setActivatedSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf : Error processing arguments");
        cobj->watchSelf(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite : Error processing arguments");
        cobj->setPressSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize : Error processing arguments");
        cobj->setContentSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite : Error processing arguments");
        cobj->setDisabledSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDisabledSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyButtonSkinnedBase* cobj = (SneakyButtonSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDisabledSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getDisabledSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDisabledSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyButtonSkinnedBase_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        SneakyButtonSkinnedBase* ret = SneakyButtonSkinnedBase::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyButtonSkinnedBase>(cx, (SneakyButtonSkinnedBase*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyButtonSkinnedBase_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_SneakyButtonSkinnedBase_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SneakyButtonSkinnedBase)", obj);
}

void js_register_jsb_bindings_auto_SneakyButtonSkinnedBase(JSContext *cx, JS::HandleObject global) {
    jsb_SneakyButtonSkinnedBase_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SneakyButtonSkinnedBase_class->name = "SneakyButtonSkinnedBase";
    jsb_SneakyButtonSkinnedBase_class->addProperty = JS_PropertyStub;
    jsb_SneakyButtonSkinnedBase_class->delProperty = JS_DeletePropertyStub;
    jsb_SneakyButtonSkinnedBase_class->getProperty = JS_PropertyStub;
    jsb_SneakyButtonSkinnedBase_class->setProperty = JS_StrictPropertyStub;
    jsb_SneakyButtonSkinnedBase_class->enumerate = JS_EnumerateStub;
    jsb_SneakyButtonSkinnedBase_class->resolve = JS_ResolveStub;
    jsb_SneakyButtonSkinnedBase_class->convert = JS_ConvertStub;
    jsb_SneakyButtonSkinnedBase_class->finalize = js_SneakyButtonSkinnedBase_finalize;
    jsb_SneakyButtonSkinnedBase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getPressSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_getPressSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getButton", js_jsb_bindings_auto_SneakyButtonSkinnedBase_getButton, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActivatedSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_getActivatedSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setButton", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setButton, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDefaultSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDefaultSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDefaultSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActivatedSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setActivatedSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_jsb_bindings_auto_SneakyButtonSkinnedBase_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("watchSelf", js_jsb_bindings_auto_SneakyButtonSkinnedBase_watchSelf, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPressSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setPressSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setContentSize", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setContentSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDisabledSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_setDisabledSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisabledSprite", js_jsb_bindings_auto_SneakyButtonSkinnedBase_getDisabledSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_SneakyButtonSkinnedBase_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SneakyButtonSkinnedBase_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_SneakyButtonSkinnedBase_class,
        dummy_constructor<SneakyButtonSkinnedBase>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SneakyButtonSkinnedBase", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SneakyButtonSkinnedBase> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SneakyButtonSkinnedBase_class;
        p->proto = jsb_SneakyButtonSkinnedBase_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SneakyJoystick_class;
JSObject *jsb_SneakyJoystick_prototype;

bool js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections : Error processing arguments");
        cobj->setNumberOfDirections(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_onTouchEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchEnded : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchEnded : Error processing arguments");
        cobj->onTouchEnded(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_onTouchEnded : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getAutoCenter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getAutoCenter : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getAutoCenter();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getAutoCenter : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getThumbRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getThumbRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getThumbRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getThumbRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getIsActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getIsActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsActive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getIsActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setIsDPad(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsDPad : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsDPad : Error processing arguments");
        cobj->setIsDPad(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setIsDPad : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getIsDPad(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getIsDPad : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsDPad();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getIsDPad : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getJoystickRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getJoystickRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getJoystickRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getJoystickRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone : Error processing arguments");
        cobj->setHasDeadzone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius : Error processing arguments");
        cobj->setJoystickRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getTouchArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getTouchArea : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getTouchArea();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getTouchArea : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getDegrees(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getDegrees : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDegrees();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getDegrees : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_initWithSize : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Size arg0;
        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_initWithSize : Error processing arguments");
        bool ret = cobj->initWithSize(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getIsEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getIsEnable : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsEnable();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getIsEnable : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_onTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchMoved : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchMoved : Error processing arguments");
        cobj->onTouchMoved(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_onTouchMoved : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setIsEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsEnable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsEnable : Error processing arguments");
        cobj->setIsEnable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setIsEnable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getNumberOfDirections(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getNumberOfDirections : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getNumberOfDirections();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getNumberOfDirections : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled : Error processing arguments");
        cobj->onTouchCancelled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_onTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchBegan : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Event*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_onTouchBegan : Error processing arguments");
        bool ret = cobj->onTouchBegan(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_onTouchBegan : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setTouchArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setTouchArea : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setTouchArea : Error processing arguments");
        cobj->setTouchArea(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setTouchArea : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getIsConstantVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getIsConstantVelocity : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getIsConstantVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getIsConstantVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getStickPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getStickPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getStickPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getStickPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setDeadRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setDeadRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setDeadRadius : Error processing arguments");
        cobj->setDeadRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setDeadRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity : Error processing arguments");
        cobj->setIsConstantVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getHasDeadzone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getHasDeadzone : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getHasDeadzone();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getHasDeadzone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_getDeadRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_getDeadRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDeadRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_getDeadRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setAutoCenter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setAutoCenter : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setAutoCenter : Error processing arguments");
        cobj->setAutoCenter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setAutoCenter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_setThumbRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystick* cobj = (SneakyJoystick *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setThumbRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_setThumbRadius : Error processing arguments");
        cobj->setThumbRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_setThumbRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystick_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Size arg0;
        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystick_create : Error processing arguments");
        SneakyJoystick* ret = SneakyJoystick::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyJoystick>(cx, (SneakyJoystick*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystick_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_SneakyJoystick_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SneakyJoystick)", obj);
}

void js_register_jsb_bindings_auto_SneakyJoystick(JSContext *cx, JS::HandleObject global) {
    jsb_SneakyJoystick_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SneakyJoystick_class->name = "SneakyJoystick";
    jsb_SneakyJoystick_class->addProperty = JS_PropertyStub;
    jsb_SneakyJoystick_class->delProperty = JS_DeletePropertyStub;
    jsb_SneakyJoystick_class->getProperty = JS_PropertyStub;
    jsb_SneakyJoystick_class->setProperty = JS_StrictPropertyStub;
    jsb_SneakyJoystick_class->enumerate = JS_EnumerateStub;
    jsb_SneakyJoystick_class->resolve = JS_ResolveStub;
    jsb_SneakyJoystick_class->convert = JS_ConvertStub;
    jsb_SneakyJoystick_class->finalize = js_SneakyJoystick_finalize;
    jsb_SneakyJoystick_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setNumberOfDirections", js_jsb_bindings_auto_SneakyJoystick_setNumberOfDirections, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchEnded", js_jsb_bindings_auto_SneakyJoystick_onTouchEnded, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAutoCenter", js_jsb_bindings_auto_SneakyJoystick_getAutoCenter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getThumbRadius", js_jsb_bindings_auto_SneakyJoystick_getThumbRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsActive", js_jsb_bindings_auto_SneakyJoystick_getIsActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsDPad", js_jsb_bindings_auto_SneakyJoystick_setIsDPad, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsDPad", js_jsb_bindings_auto_SneakyJoystick_getIsDPad, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJoystickRadius", js_jsb_bindings_auto_SneakyJoystick_getJoystickRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHasDeadzone", js_jsb_bindings_auto_SneakyJoystick_setHasDeadzone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setJoystickRadius", js_jsb_bindings_auto_SneakyJoystick_setJoystickRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchArea", js_jsb_bindings_auto_SneakyJoystick_getTouchArea, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVelocity", js_jsb_bindings_auto_SneakyJoystick_getVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDegrees", js_jsb_bindings_auto_SneakyJoystick_getDegrees, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSize", js_jsb_bindings_auto_SneakyJoystick_initWithSize, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsEnable", js_jsb_bindings_auto_SneakyJoystick_getIsEnable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchMoved", js_jsb_bindings_auto_SneakyJoystick_onTouchMoved, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsEnable", js_jsb_bindings_auto_SneakyJoystick_setIsEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNumberOfDirections", js_jsb_bindings_auto_SneakyJoystick_getNumberOfDirections, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchCancelled", js_jsb_bindings_auto_SneakyJoystick_onTouchCancelled, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTouchBegan", js_jsb_bindings_auto_SneakyJoystick_onTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchArea", js_jsb_bindings_auto_SneakyJoystick_setTouchArea, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIsConstantVelocity", js_jsb_bindings_auto_SneakyJoystick_getIsConstantVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStickPosition", js_jsb_bindings_auto_SneakyJoystick_getStickPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDeadRadius", js_jsb_bindings_auto_SneakyJoystick_setDeadRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsConstantVelocity", js_jsb_bindings_auto_SneakyJoystick_setIsConstantVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHasDeadzone", js_jsb_bindings_auto_SneakyJoystick_getHasDeadzone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeadRadius", js_jsb_bindings_auto_SneakyJoystick_getDeadRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAutoCenter", js_jsb_bindings_auto_SneakyJoystick_setAutoCenter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setThumbRadius", js_jsb_bindings_auto_SneakyJoystick_setThumbRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_SneakyJoystick_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SneakyJoystick_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_SneakyJoystick_class,
        dummy_constructor<SneakyJoystick>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SneakyJoystick", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SneakyJoystick> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SneakyJoystick_class;
        p->proto = jsb_SneakyJoystick_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SneakyJoystickSkinnedBase_class;
JSObject *jsb_SneakyJoystickSkinnedBase_prototype;

bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick : Invalid Native Object");
    if (argc == 1) {
        SneakyJoystick* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (SneakyJoystick*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick : Error processing arguments");
        cobj->setJoystick(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite : Error processing arguments");
        cobj->setThumbSprite(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Sprite* arg0;
        cocos2d::Sprite* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite : Error processing arguments");
        cobj->setThumbSprite(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultBackgroundSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getDefaultBackgroundSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultThumbSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getDefaultThumbSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getBackgroundSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getBackgroundSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getThumbSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getThumbSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite : Error processing arguments");
        cobj->setBackgroundSprite(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Sprite* arg0;
        cocos2d::Sprite* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite : Error processing arguments");
        cobj->setBackgroundSprite(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getJoystick(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SneakyJoystickSkinnedBase* cobj = (SneakyJoystickSkinnedBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getJoystick : Invalid Native Object");
    if (argc == 0) {
        SneakyJoystick* ret = cobj->getJoystick();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyJoystick>(cx, (SneakyJoystick*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getJoystick : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_SneakyJoystickSkinnedBase_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        SneakyJoystickSkinnedBase* ret = SneakyJoystickSkinnedBase::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<SneakyJoystickSkinnedBase>(cx, (SneakyJoystickSkinnedBase*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SneakyJoystickSkinnedBase_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_SneakyJoystickSkinnedBase_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SneakyJoystickSkinnedBase)", obj);
}

void js_register_jsb_bindings_auto_SneakyJoystickSkinnedBase(JSContext *cx, JS::HandleObject global) {
    jsb_SneakyJoystickSkinnedBase_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SneakyJoystickSkinnedBase_class->name = "SneakyJoystickSkinnedBase";
    jsb_SneakyJoystickSkinnedBase_class->addProperty = JS_PropertyStub;
    jsb_SneakyJoystickSkinnedBase_class->delProperty = JS_DeletePropertyStub;
    jsb_SneakyJoystickSkinnedBase_class->getProperty = JS_PropertyStub;
    jsb_SneakyJoystickSkinnedBase_class->setProperty = JS_StrictPropertyStub;
    jsb_SneakyJoystickSkinnedBase_class->enumerate = JS_EnumerateStub;
    jsb_SneakyJoystickSkinnedBase_class->resolve = JS_ResolveStub;
    jsb_SneakyJoystickSkinnedBase_class->convert = JS_ConvertStub;
    jsb_SneakyJoystickSkinnedBase_class->finalize = js_SneakyJoystickSkinnedBase_finalize;
    jsb_SneakyJoystickSkinnedBase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setJoystick", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setJoystick, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setThumbSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setThumbSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultBackgroundSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultBackgroundSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultThumbSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getDefaultThumbSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getBackgroundSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getThumbSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getThumbSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundSprite", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_setBackgroundSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJoystick", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_getJoystick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_jsb_bindings_auto_SneakyJoystickSkinnedBase_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SneakyJoystickSkinnedBase_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_SneakyJoystickSkinnedBase_class,
        dummy_constructor<SneakyJoystickSkinnedBase>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SneakyJoystickSkinnedBase", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SneakyJoystickSkinnedBase> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SneakyJoystickSkinnedBase_class;
        p->proto = jsb_SneakyJoystickSkinnedBase_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_JsonStorage_class;
JSObject *jsb_JsonStorage_prototype;

bool js_jsb_bindings_auto_JsonStorage_setIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_setIntegerForKey : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_setIntegerForKey : Error processing arguments");
        cobj->setIntegerForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_setIntegerForKey : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_getBoolForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_getBoolForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getBoolForKey : Error processing arguments");
        bool ret = cobj->getBoolForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getBoolForKey : Error processing arguments");
        bool ret = cobj->getBoolForKey(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_getBoolForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_setDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_setDoubleForKey : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_setDoubleForKey : Error processing arguments");
        cobj->setDoubleForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_setDoubleForKey : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_getStringForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_getStringForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getStringForKey : Error processing arguments");
        std::string ret = cobj->getStringForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getStringForKey : Error processing arguments");
        std::string ret = cobj->getStringForKey(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_getStringForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_setStringForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_setStringForKey : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_setStringForKey : Error processing arguments");
        cobj->setStringForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_setStringForKey : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_flush(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_flush : Invalid Native Object");
    if (argc == 0) {
        cobj->flush();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_flush : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_getIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_getIntegerForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getIntegerForKey : Error processing arguments");
        int ret = cobj->getIntegerForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getIntegerForKey : Error processing arguments");
        int ret = cobj->getIntegerForKey(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_getIntegerForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_getDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_getDoubleForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getDoubleForKey : Error processing arguments");
        double ret = cobj->getDoubleForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_getDoubleForKey : Error processing arguments");
        double ret = cobj->getDoubleForKey(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_getDoubleForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_setBoolForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    JsonStorage* cobj = (JsonStorage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_bindings_auto_JsonStorage_setBoolForKey : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_setBoolForKey : Error processing arguments");
        cobj->setBoolForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_setBoolForKey : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_bindings_auto_JsonStorage_GetInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_JsonStorage_GetInstance : Error processing arguments");
        JsonStorage* ret = JsonStorage::GetInstance(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<JsonStorage>(cx, (JsonStorage*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_JsonStorage_GetInstance : wrong number of arguments");
    return false;
}



void js_JsonStorage_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JsonStorage)", obj);
}

void js_register_jsb_bindings_auto_JsonStorage(JSContext *cx, JS::HandleObject global) {
    jsb_JsonStorage_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_JsonStorage_class->name = "JsonStorage";
    jsb_JsonStorage_class->addProperty = JS_PropertyStub;
    jsb_JsonStorage_class->delProperty = JS_DeletePropertyStub;
    jsb_JsonStorage_class->getProperty = JS_PropertyStub;
    jsb_JsonStorage_class->setProperty = JS_StrictPropertyStub;
    jsb_JsonStorage_class->enumerate = JS_EnumerateStub;
    jsb_JsonStorage_class->resolve = JS_ResolveStub;
    jsb_JsonStorage_class->convert = JS_ConvertStub;
    jsb_JsonStorage_class->finalize = js_JsonStorage_finalize;
    jsb_JsonStorage_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setIntegerForKey", js_jsb_bindings_auto_JsonStorage_setIntegerForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoolForKey", js_jsb_bindings_auto_JsonStorage_getBoolForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDoubleForKey", js_jsb_bindings_auto_JsonStorage_setDoubleForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringForKey", js_jsb_bindings_auto_JsonStorage_getStringForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStringForKey", js_jsb_bindings_auto_JsonStorage_setStringForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("flush", js_jsb_bindings_auto_JsonStorage_flush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIntegerForKey", js_jsb_bindings_auto_JsonStorage_getIntegerForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDoubleForKey", js_jsb_bindings_auto_JsonStorage_getDoubleForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBoolForKey", js_jsb_bindings_auto_JsonStorage_setBoolForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("GetInstance", js_jsb_bindings_auto_JsonStorage_GetInstance, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_JsonStorage_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_JsonStorage_class,
        dummy_constructor<JsonStorage>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "JsonStorage", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<JsonStorage> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_JsonStorage_class;
        p->proto = jsb_JsonStorage_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_SdkManager_class;
JSObject *jsb_SdkManager_prototype;

bool js_jsb_bindings_auto_SdkManager_setGender(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setGender : Error processing arguments");
        SdkManager::setGender(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setGender : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_onChargeResult(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_onChargeResult : Error processing arguments");
        SdkManager::onChargeResult(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_onChargeResult : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_onPurchase(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        const char* arg0;
        int arg1;
        double arg2;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_onPurchase : Error processing arguments");
        SdkManager::onPurchase(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_onPurchase : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setAccountName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setAccountName : Error processing arguments");
        SdkManager::setAccountName(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setAccountName : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_sdkCommond(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_sdkCommond : Error processing arguments");
        SdkManager::sdkCommond(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_sdkCommond : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_charge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_charge : Error processing arguments");
        SdkManager::charge(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_charge : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setAccount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setAccount : Error processing arguments");
        SdkManager::setAccount(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setAccount : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setSdkCommondCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::function<void (char *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](char* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = c_string_to_jsval(cx, larg0);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(1, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setSdkCommondCallback : Error processing arguments");
        SdkManager::setSdkCommondCallback(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setSdkCommondCallback : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        SdkManager::init();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_init : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setAccountType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setAccountType : Error processing arguments");
        SdkManager::setAccountType(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setAccountType : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_onUse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_onUse : Error processing arguments");
        SdkManager::onUse(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_onUse : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setGameServer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setGameServer : Error processing arguments");
        SdkManager::setGameServer(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setGameServer : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        SdkManager::login();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_login : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setAge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setAge : Error processing arguments");
        SdkManager::setAge(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setAge : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setChargeCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::function<void (char *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](char* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = c_string_to_jsval(cx, larg0);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(1, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setChargeCallback : Error processing arguments");
        SdkManager::setChargeCallback(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setChargeCallback : wrong number of arguments");
    return false;
}

bool js_jsb_bindings_auto_SdkManager_setLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_bindings_auto_SdkManager_setLevel : Error processing arguments");
        SdkManager::setLevel(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_SdkManager_setLevel : wrong number of arguments");
    return false;
}



void js_SdkManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SdkManager)", obj);
}

void js_register_jsb_bindings_auto_SdkManager(JSContext *cx, JS::HandleObject global) {
    jsb_SdkManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SdkManager_class->name = "SdkManager";
    jsb_SdkManager_class->addProperty = JS_PropertyStub;
    jsb_SdkManager_class->delProperty = JS_DeletePropertyStub;
    jsb_SdkManager_class->getProperty = JS_PropertyStub;
    jsb_SdkManager_class->setProperty = JS_StrictPropertyStub;
    jsb_SdkManager_class->enumerate = JS_EnumerateStub;
    jsb_SdkManager_class->resolve = JS_ResolveStub;
    jsb_SdkManager_class->convert = JS_ConvertStub;
    jsb_SdkManager_class->finalize = js_SdkManager_finalize;
    jsb_SdkManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setGender", js_jsb_bindings_auto_SdkManager_setGender, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onChargeResult", js_jsb_bindings_auto_SdkManager_onChargeResult, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onPurchase", js_jsb_bindings_auto_SdkManager_onPurchase, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAccountName", js_jsb_bindings_auto_SdkManager_setAccountName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sdkCommond", js_jsb_bindings_auto_SdkManager_sdkCommond, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("charge", js_jsb_bindings_auto_SdkManager_charge, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAccount", js_jsb_bindings_auto_SdkManager_setAccount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSdkCommondCallback", js_jsb_bindings_auto_SdkManager_setSdkCommondCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_jsb_bindings_auto_SdkManager_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAccountType", js_jsb_bindings_auto_SdkManager_setAccountType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onUse", js_jsb_bindings_auto_SdkManager_onUse, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGameServer", js_jsb_bindings_auto_SdkManager_setGameServer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_jsb_bindings_auto_SdkManager_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAge", js_jsb_bindings_auto_SdkManager_setAge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setChargeCallback", js_jsb_bindings_auto_SdkManager_setChargeCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLevel", js_jsb_bindings_auto_SdkManager_setLevel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SdkManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_SdkManager_class,
        dummy_constructor<SdkManager>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SdkManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SdkManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SdkManager_class;
        p->proto = jsb_SdkManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_GameUtils_class;
JSObject *jsb_GameUtils_prototype;

bool js_jsb_bindings_auto_GameUtils_getChannelId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = GameUtils::getChannelId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_bindings_auto_GameUtils_getChannelId : wrong number of arguments");
    return false;
}



void js_GameUtils_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GameUtils)", obj);
}

void js_register_jsb_bindings_auto_GameUtils(JSContext *cx, JS::HandleObject global) {
    jsb_GameUtils_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameUtils_class->name = "GameUtils";
    jsb_GameUtils_class->addProperty = JS_PropertyStub;
    jsb_GameUtils_class->delProperty = JS_DeletePropertyStub;
    jsb_GameUtils_class->getProperty = JS_PropertyStub;
    jsb_GameUtils_class->setProperty = JS_StrictPropertyStub;
    jsb_GameUtils_class->enumerate = JS_EnumerateStub;
    jsb_GameUtils_class->resolve = JS_ResolveStub;
    jsb_GameUtils_class->convert = JS_ConvertStub;
    jsb_GameUtils_class->finalize = js_GameUtils_finalize;
    jsb_GameUtils_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getChannelId", js_jsb_bindings_auto_GameUtils_getChannelId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_GameUtils_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_GameUtils_class,
        dummy_constructor<GameUtils>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameUtils", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<GameUtils> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_GameUtils_class;
        p->proto = jsb_GameUtils_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_jsb_bindings_auto(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_jsb_bindings_auto_Shake(cx, ns);
    js_register_jsb_bindings_auto_FallOffShake(cx, ns);
    js_register_jsb_bindings_auto_SneakyButton(cx, ns);
    js_register_jsb_bindings_auto_JsonStorage(cx, ns);
    js_register_jsb_bindings_auto_GameUtils(cx, ns);
    js_register_jsb_bindings_auto_SneakyButtonSkinnedBase(cx, ns);
    js_register_jsb_bindings_auto_SneakyJoystick(cx, ns);
    js_register_jsb_bindings_auto_SdkManager(cx, ns);
    js_register_jsb_bindings_auto_SneakyJoystickSkinnedBase(cx, ns);
}

