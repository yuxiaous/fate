#include "jsb_levelhelper_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "LevelHelper2API.h"

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
JSClass  *jsb_LHUserPropertyProtocol_class;
JSObject *jsb_LHUserPropertyProtocol_prototype;

bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_getClassName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUserPropertyProtocol* cobj = (LHUserPropertyProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_getClassName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getClassName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_getClassName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUserPropertyProtocol* cobj = (LHUserPropertyProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUserPropertyProtocol* cobj = (LHUserPropertyProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary : Error processing arguments");
        cobj->setPropertiesFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHUserPropertyProtocol_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUserPropertyProtocol* cobj = (LHUserPropertyProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUserPropertyProtocol_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_LHUserPropertyProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHUserPropertyProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHUserPropertyProtocol *nobj = static_cast<LHUserPropertyProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHUserPropertyProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_LHUserPropertyProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHUserPropertyProtocol_class->name = "LHUserPropertyProtocol";
    jsb_LHUserPropertyProtocol_class->addProperty = JS_PropertyStub;
    jsb_LHUserPropertyProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_LHUserPropertyProtocol_class->getProperty = JS_PropertyStub;
    jsb_LHUserPropertyProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_LHUserPropertyProtocol_class->enumerate = JS_EnumerateStub;
    jsb_LHUserPropertyProtocol_class->resolve = JS_ResolveStub;
    jsb_LHUserPropertyProtocol_class->convert = JS_ConvertStub;
    jsb_LHUserPropertyProtocol_class->finalize = js_LHUserPropertyProtocol_finalize;
    jsb_LHUserPropertyProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getClassName", js_jsb_levelhelper_auto_LHUserPropertyProtocol_getClassName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNode", js_jsb_levelhelper_auto_LHUserPropertyProtocol_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPropertiesFromDictionary", js_jsb_levelhelper_auto_LHUserPropertyProtocol_setPropertiesFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_jsb_levelhelper_auto_LHUserPropertyProtocol_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_LHUserPropertyProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHUserPropertyProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHUserPropertyProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHUserPropertyProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHUserPropertyProtocol_class;
        p->proto = jsb_LHUserPropertyProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHNodeProtocol_class;
JSObject *jsb_LHNodeProtocol_prototype;

bool js_jsb_levelhelper_auto_LHNodeProtocol_isRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isRopeJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isRopeJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isRopeJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_setUuid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_setUuid : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_setUuid : Error processing arguments");
        cobj->setUuid(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_setUuid : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary : Error processing arguments");
        cobj->loadTransformationInfoFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isUINode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isUINode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName : Error processing arguments");
        cocos2d::Node* ret = cobj->getChildNodeWithName(arg0);
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isRevoluteJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isRevoluteJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isRevoluteJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getUuid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getUuid : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getUuid();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getUuid : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_setTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_setTags : Invalid Native Object");
    if (argc == 1) {
        LHArray* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_setTags : Error processing arguments");
        cobj->setTags(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_setTags : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isJoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isJoint : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isJoint();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isJoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isLHWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isLHWeldJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLHWeldJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isLHWeldJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isSprite : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isSprite();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isShape(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isShape : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isShape();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isShape : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isParallaxLayer : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isParallaxLayer();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isParallaxLayer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isDistanceJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDistanceJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isDistanceJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isParallax(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isParallax : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isParallax();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isParallax : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary : Error processing arguments");
        cobj->loadUserPropertyWithDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary : Error processing arguments");
        cobj->loadGenericInfoFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isWater(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isWater : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isWater();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isWater : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isBackUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isBackUINode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBackUINode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isBackUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGearJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isGearJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isGearJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isGearJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isPulleyJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPulleyJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isPulleyJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isWheelJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isWheelJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isWheelJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isB2WorldDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isB2WorldDirty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isB2WorldDirty();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isB2WorldDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isCamera : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isCamera();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isCamera : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getTags : Invalid Native Object");
    if (argc == 0) {
        std::vector<std::string> ret = cobj->getTags();
        jsval jsret = JSVAL_NULL;
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getTags : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags : Invalid Native Object");
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags : Error processing arguments");
        cocos2d::__Array* ret = cobj->getChildrenWithTags(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::vector<std::string> arg0;
        bool arg1;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags : Error processing arguments");
        cocos2d::__Array* ret = cobj->getChildrenWithTags(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getUserProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getUserProperty : Invalid Native Object");
    if (argc == 0) {
        LHUserPropertyProtocol* ret = cobj->getUserProperty();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHUserPropertyProtocol>(cx, (LHUserPropertyProtocol*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getUserProperty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isGameWorldNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isGameWorldNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isGameWorldNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_containsTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_containsTag : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_containsTag : Error processing arguments");
        bool ret = cobj->containsTag(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_containsTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isAsset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isAsset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAsset();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isAsset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isPrismaticJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPrismaticJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isPrismaticJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_markAsB2WorldDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_markAsB2WorldDirty : Invalid Native Object");
    if (argc == 0) {
        cobj->markAsB2WorldDirty();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_markAsB2WorldDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isScene(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isScene : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScene();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isScene : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isGravityArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isGravityArea : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isGravityArea();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isGravityArea : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID : Error processing arguments");
        cocos2d::Node* ret = cobj->getChildNodeWithUUID(arg0);
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_isBezier(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_isBezier : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBezier();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_isBezier : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeProtocol* cobj = (LHNodeProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary : Error processing arguments");
        cobj->loadChildrenFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeProtocol_positionForNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Node* arg0;
        cocos2d::Point arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_positionForNode : Error processing arguments");
        cocos2d::Point ret = LHNodeProtocol::positionForNode(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_positionForNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHNodeProtocol_createLHNodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_createLHNodeWithDictionary : Error processing arguments");
        cocos2d::Node* ret = LHNodeProtocol::createLHNodeWithDictionary(arg0, arg1);
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
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_createLHNodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        LHNodeProtocol* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHNodeProtocol*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNode : Error processing arguments");
        cocos2d::Node* ret = LHNodeProtocol::LHGetNode(arg0);
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
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNodeProtocol(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNodeProtocol : Error processing arguments");
        LHNodeProtocol* ret = LHNodeProtocol::LHGetNodeProtocol(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHNodeProtocol>(cx, (LHNodeProtocol*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNodeProtocol : wrong number of arguments");
    return false;
}



void js_LHNodeProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHNodeProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHNodeProtocol *nobj = static_cast<LHNodeProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHNodeProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_LHNodeProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHNodeProtocol_class->name = "LHNodeProtocol";
    jsb_LHNodeProtocol_class->addProperty = JS_PropertyStub;
    jsb_LHNodeProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_LHNodeProtocol_class->getProperty = JS_PropertyStub;
    jsb_LHNodeProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_LHNodeProtocol_class->enumerate = JS_EnumerateStub;
    jsb_LHNodeProtocol_class->resolve = JS_ResolveStub;
    jsb_LHNodeProtocol_class->convert = JS_ConvertStub;
    jsb_LHNodeProtocol_class->finalize = js_LHNodeProtocol_finalize;
    jsb_LHNodeProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isRopeJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isRopeJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUuid", js_jsb_levelhelper_auto_LHNodeProtocol_setUuid, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTransformationInfoFromDictionary", js_jsb_levelhelper_auto_LHNodeProtocol_loadTransformationInfoFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isUINode", js_jsb_levelhelper_auto_LHNodeProtocol_isUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildNodeWithName", js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isRevoluteJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isRevoluteJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUuid", js_jsb_levelhelper_auto_LHNodeProtocol_getUuid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTags", js_jsb_levelhelper_auto_LHNodeProtocol_setTags, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isJoint", js_jsb_levelhelper_auto_LHNodeProtocol_isJoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHWeldJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isLHWeldJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isSprite", js_jsb_levelhelper_auto_LHNodeProtocol_isSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isShape", js_jsb_levelhelper_auto_LHNodeProtocol_isShape, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isParallaxLayer", js_jsb_levelhelper_auto_LHNodeProtocol_isParallaxLayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDistanceJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isDistanceJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isNode", js_jsb_levelhelper_auto_LHNodeProtocol_isNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isParallax", js_jsb_levelhelper_auto_LHNodeProtocol_isParallax, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHNodeProtocol_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadUserPropertyWithDictionary", js_jsb_levelhelper_auto_LHNodeProtocol_loadUserPropertyWithDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadGenericInfoFromDictionary", js_jsb_levelhelper_auto_LHNodeProtocol_loadGenericInfoFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isWater", js_jsb_levelhelper_auto_LHNodeProtocol_isWater, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBackUINode", js_jsb_levelhelper_auto_LHNodeProtocol_isBackUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isGearJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isGearJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPulleyJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isPulleyJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isWheelJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isWheelJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isB2WorldDirty", js_jsb_levelhelper_auto_LHNodeProtocol_isB2WorldDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isCamera", js_jsb_levelhelper_auto_LHNodeProtocol_isCamera, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTags", js_jsb_levelhelper_auto_LHNodeProtocol_getTags, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildrenWithTags", js_jsb_levelhelper_auto_LHNodeProtocol_getChildrenWithTags, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserProperty", js_jsb_levelhelper_auto_LHNodeProtocol_getUserProperty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isGameWorldNode", js_jsb_levelhelper_auto_LHNodeProtocol_isGameWorldNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("containsTag", js_jsb_levelhelper_auto_LHNodeProtocol_containsTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAsset", js_jsb_levelhelper_auto_LHNodeProtocol_isAsset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPrismaticJointNode", js_jsb_levelhelper_auto_LHNodeProtocol_isPrismaticJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("markAsB2WorldDirty", js_jsb_levelhelper_auto_LHNodeProtocol_markAsB2WorldDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScene", js_jsb_levelhelper_auto_LHNodeProtocol_isScene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isGravityArea", js_jsb_levelhelper_auto_LHNodeProtocol_isGravityArea, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildNodeWithUUID", js_jsb_levelhelper_auto_LHNodeProtocol_getChildNodeWithUUID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBezier", js_jsb_levelhelper_auto_LHNodeProtocol_isBezier, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadChildrenFromDictionary", js_jsb_levelhelper_auto_LHNodeProtocol_loadChildrenFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("positionForNode", js_jsb_levelhelper_auto_LHNodeProtocol_positionForNode, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createLHNodeWithDictionary", js_jsb_levelhelper_auto_LHNodeProtocol_createLHNodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LHGetNode", js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("LHGetNodeProtocol", js_jsb_levelhelper_auto_LHNodeProtocol_LHGetNodeProtocol, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHNodeProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHNodeProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHNodeProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHNodeProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHNodeProtocol_class;
        p->proto = jsb_LHNodeProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHScene_class;
JSObject *jsb_LHScene_prototype;

bool js_jsb_levelhelper_auto_LHScene_setGlobalGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_setGlobalGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_setGlobalGravity : Error processing arguments");
        cobj->setGlobalGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_setGlobalGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getGlobalGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getGlobalGravity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getGlobalGravity();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getGlobalGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_setGameWorldRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_setGameWorldRect : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_setGameWorldRect : Error processing arguments");
        cobj->setGameWorldRect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_setGameWorldRect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getChildNodeWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getChildNodeWithName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_getChildNodeWithName : Error processing arguments");
        cocos2d::Node* ret = cobj->getChildNodeWithName(arg0);
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getChildNodeWithName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getGameWorldRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getGameWorldRect : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getGameWorldRect();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getGameWorldRect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_initWithContentOfFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_initWithContentOfFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_initWithContentOfFile : Error processing arguments");
        bool ret = cobj->initWithContentOfFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_initWithContentOfFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getGameWorldNode : Invalid Native Object");
    if (argc == 0) {
        LHGameWorldNode* ret = cobj->getGameWorldNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHGameWorldNode>(cx, (LHGameWorldNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getGameWorldNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID : Error processing arguments");
        cocos2d::__Array* ret = cobj->tracedFixturesWithUUID(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getDesignResolutionSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getDesignResolutionSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getDesignResolutionSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getDesignResolutionSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getDesignOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getDesignOffset : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getDesignOffset();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getDesignOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_assetInfoForFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_assetInfoForFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_assetInfoForFile : Error processing arguments");
        cocos2d::__Dictionary* ret = cobj->assetInfoForFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Dictionary>(cx, (cocos2d::__Dictionary*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_assetInfoForFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getUINode : Invalid Native Object");
    if (argc == 0) {
        LHUINode* ret = cobj->getUINode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHUINode>(cx, (LHUINode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getCurrentDeviceSuffix(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getCurrentDeviceSuffix : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCurrentDeviceSuffix();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getCurrentDeviceSuffix : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_isScene(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_isScene : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScene();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_isScene : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_getBackUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHScene* cobj = (LHScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHScene_getBackUINode : Invalid Native Object");
    if (argc == 0) {
        LHBackUINode* ret = cobj->getBackUINode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHBackUINode>(cx, (LHBackUINode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_getBackUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHScene_createWithContentOfFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_createWithContentOfFile : Error processing arguments");
        LHScene* ret = LHScene::createWithContentOfFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHScene>(cx, (LHScene*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_createWithContentOfFile : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHScene_isLHScene(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHScene_isLHScene : Error processing arguments");
        bool ret = LHScene::isLHScene(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHScene_isLHScene : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHScene_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHScene* cobj = new (std::nothrow) LHScene();
    TypeTest<LHScene> t;
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


extern JSObject *jsb_cocos2d_Scene_prototype;

void js_LHScene_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHScene)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHScene *nobj = static_cast<LHScene *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHScene(JSContext *cx, JS::HandleObject global) {
    jsb_LHScene_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHScene_class->name = "LHScene";
    jsb_LHScene_class->addProperty = JS_PropertyStub;
    jsb_LHScene_class->delProperty = JS_DeletePropertyStub;
    jsb_LHScene_class->getProperty = JS_PropertyStub;
    jsb_LHScene_class->setProperty = JS_StrictPropertyStub;
    jsb_LHScene_class->enumerate = JS_EnumerateStub;
    jsb_LHScene_class->resolve = JS_ResolveStub;
    jsb_LHScene_class->convert = JS_ConvertStub;
    jsb_LHScene_class->finalize = js_LHScene_finalize;
    jsb_LHScene_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setGlobalGravity", js_jsb_levelhelper_auto_LHScene_setGlobalGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGlobalGravity", js_jsb_levelhelper_auto_LHScene_getGlobalGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGameWorldRect", js_jsb_levelhelper_auto_LHScene_setGameWorldRect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildNodeWithName", js_jsb_levelhelper_auto_LHScene_getChildNodeWithName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGameWorldRect", js_jsb_levelhelper_auto_LHScene_getGameWorldRect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithContentOfFile", js_jsb_levelhelper_auto_LHScene_initWithContentOfFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGameWorldNode", js_jsb_levelhelper_auto_LHScene_getGameWorldNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("tracedFixturesWithUUID", js_jsb_levelhelper_auto_LHScene_tracedFixturesWithUUID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDesignResolutionSize", js_jsb_levelhelper_auto_LHScene_getDesignResolutionSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDesignOffset", js_jsb_levelhelper_auto_LHScene_getDesignOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("assetInfoForFile", js_jsb_levelhelper_auto_LHScene_assetInfoForFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUINode", js_jsb_levelhelper_auto_LHScene_getUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentDeviceSuffix", js_jsb_levelhelper_auto_LHScene_getCurrentDeviceSuffix, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScene", js_jsb_levelhelper_auto_LHScene_isScene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackUINode", js_jsb_levelhelper_auto_LHScene_getBackUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithContentOfFile", js_jsb_levelhelper_auto_LHScene_createWithContentOfFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHScene", js_jsb_levelhelper_auto_LHScene_isLHScene, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHScene_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Scene_prototype),
        jsb_LHScene_class,
        js_jsb_levelhelper_auto_LHScene_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHScene", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHScene> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHScene_class;
        p->proto = jsb_LHScene_prototype;
        p->parentProto = jsb_cocos2d_Scene_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHUINode_class;
JSObject *jsb_LHUINode_prototype;

bool js_jsb_levelhelper_auto_LHUINode_isUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUINode* cobj = (LHUINode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUINode_isUINode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isUINode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUINode_isUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHUINode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHUINode* cobj = (LHUINode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHUINode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHUINode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUINode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHUINode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHUINode_nodeWithDictionary : Error processing arguments");
        LHUINode* ret = LHUINode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHUINode>(cx, (LHUINode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUINode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHUINode_isLHUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHUINode_isLHUINode : Error processing arguments");
        bool ret = LHUINode::isLHUINode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHUINode_isLHUINode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHUINode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHUINode* cobj = new (std::nothrow) LHUINode();
    TypeTest<LHUINode> t;
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

void js_LHUINode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHUINode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHUINode *nobj = static_cast<LHUINode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHUINode(JSContext *cx, JS::HandleObject global) {
    jsb_LHUINode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHUINode_class->name = "LHUINode";
    jsb_LHUINode_class->addProperty = JS_PropertyStub;
    jsb_LHUINode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHUINode_class->getProperty = JS_PropertyStub;
    jsb_LHUINode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHUINode_class->enumerate = JS_EnumerateStub;
    jsb_LHUINode_class->resolve = JS_ResolveStub;
    jsb_LHUINode_class->convert = JS_ConvertStub;
    jsb_LHUINode_class->finalize = js_LHUINode_finalize;
    jsb_LHUINode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isUINode", js_jsb_levelhelper_auto_LHUINode_isUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHUINode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHUINode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHUINode", js_jsb_levelhelper_auto_LHUINode_isLHUINode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHUINode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHUINode_class,
        js_jsb_levelhelper_auto_LHUINode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHUINode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHUINode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHUINode_class;
        p->proto = jsb_LHUINode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHBackUINode_class;
JSObject *jsb_LHBackUINode_prototype;

bool js_jsb_levelhelper_auto_LHBackUINode_isBackUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHBackUINode* cobj = (LHBackUINode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHBackUINode_isBackUINode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBackUINode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHBackUINode_isBackUINode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHBackUINode* cobj = (LHBackUINode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHBackUINode_isLHBackUINode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHBackUINode_isLHBackUINode : Error processing arguments");
        bool ret = LHBackUINode::isLHBackUINode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHBackUINode_isLHBackUINode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHBackUINode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHBackUINode_nodeWithDictionary : Error processing arguments");
        LHBackUINode* ret = LHBackUINode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHBackUINode>(cx, (LHBackUINode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHBackUINode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHBackUINode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHBackUINode* cobj = new (std::nothrow) LHBackUINode();
    TypeTest<LHBackUINode> t;
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

void js_LHBackUINode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHBackUINode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHBackUINode *nobj = static_cast<LHBackUINode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHBackUINode(JSContext *cx, JS::HandleObject global) {
    jsb_LHBackUINode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHBackUINode_class->name = "LHBackUINode";
    jsb_LHBackUINode_class->addProperty = JS_PropertyStub;
    jsb_LHBackUINode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHBackUINode_class->getProperty = JS_PropertyStub;
    jsb_LHBackUINode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHBackUINode_class->enumerate = JS_EnumerateStub;
    jsb_LHBackUINode_class->resolve = JS_ResolveStub;
    jsb_LHBackUINode_class->convert = JS_ConvertStub;
    jsb_LHBackUINode_class->finalize = js_LHBackUINode_finalize;
    jsb_LHBackUINode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isBackUINode", js_jsb_levelhelper_auto_LHBackUINode_isBackUINode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHBackUINode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("isLHBackUINode", js_jsb_levelhelper_auto_LHBackUINode_isLHBackUINode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHBackUINode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHBackUINode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHBackUINode_class,
        js_jsb_levelhelper_auto_LHBackUINode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHBackUINode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHBackUINode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHBackUINode_class;
        p->proto = jsb_LHBackUINode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHGameWorldNode_class;
JSObject *jsb_LHGameWorldNode_prototype;

bool js_jsb_levelhelper_auto_LHGameWorldNode_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_isGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_isGameWorldNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isGameWorldNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_isGameWorldNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_update(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_update : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_update : Error processing arguments");
        cobj->update(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_update : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_setScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setScale : Error processing arguments");
        cobj->setScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_setScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_getGravity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getGravity();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGameWorldNode* cobj = (LHGameWorldNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_setPosition : Error processing arguments");
        cobj->setPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHGameWorldNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_nodeWithDictionary : Error processing arguments");
        LHGameWorldNode* ret = LHGameWorldNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHGameWorldNode>(cx, (LHGameWorldNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHGameWorldNode_isLHGameWorldNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGameWorldNode_isLHGameWorldNode : Error processing arguments");
        bool ret = LHGameWorldNode::isLHGameWorldNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGameWorldNode_isLHGameWorldNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHGameWorldNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHGameWorldNode* cobj = new (std::nothrow) LHGameWorldNode();
    TypeTest<LHGameWorldNode> t;
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

void js_LHGameWorldNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHGameWorldNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHGameWorldNode *nobj = static_cast<LHGameWorldNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHGameWorldNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHGameWorldNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHGameWorldNode_class->name = "LHGameWorldNode";
    jsb_LHGameWorldNode_class->addProperty = JS_PropertyStub;
    jsb_LHGameWorldNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHGameWorldNode_class->getProperty = JS_PropertyStub;
    jsb_LHGameWorldNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHGameWorldNode_class->enumerate = JS_EnumerateStub;
    jsb_LHGameWorldNode_class->resolve = JS_ResolveStub;
    jsb_LHGameWorldNode_class->convert = JS_ConvertStub;
    jsb_LHGameWorldNode_class->finalize = js_LHGameWorldNode_finalize;
    jsb_LHGameWorldNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setGravity", js_jsb_levelhelper_auto_LHGameWorldNode_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isGameWorldNode", js_jsb_levelhelper_auto_LHGameWorldNode_isGameWorldNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHGameWorldNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("update", js_jsb_levelhelper_auto_LHGameWorldNode_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale", js_jsb_levelhelper_auto_LHGameWorldNode_setScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHGameWorldNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGravity", js_jsb_levelhelper_auto_LHGameWorldNode_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosition", js_jsb_levelhelper_auto_LHGameWorldNode_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHGameWorldNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHGameWorldNode", js_jsb_levelhelper_auto_LHGameWorldNode_isLHGameWorldNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHGameWorldNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHGameWorldNode_class,
        js_jsb_levelhelper_auto_LHGameWorldNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHGameWorldNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHGameWorldNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHGameWorldNode_class;
        p->proto = jsb_LHGameWorldNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHPhysicsProtocol_class;
JSObject *jsb_LHPhysicsProtocol_prototype;

bool js_jsb_levelhelper_auto_LHPhysicsProtocol_removeBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_removeBody : Invalid Native Object");
    if (argc == 0) {
        cobj->removeBody();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_removeBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_visitPhysicsProtocol(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_visitPhysicsProtocol : Invalid Native Object");
    if (argc == 0) {
        cobj->visitPhysicsProtocol();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_visitPhysicsProtocol : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsScale : Invalid Native Object");
    if (argc == 0) {
        cobj->updatePhysicsScale();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        LHScene* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (LHScene*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary : Error processing arguments");
        cobj->loadPhysicsFromDictionary(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsTransform : Invalid Native Object");
    if (argc == 0) {
        cobj->updatePhysicsTransform();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_shouldRemoveBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPhysicsProtocol* cobj = (LHPhysicsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_shouldRemoveBody : Invalid Native Object");
    if (argc == 0) {
        cobj->shouldRemoveBody();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_shouldRemoveBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPhysicsProtocol_LHGetNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        LHPhysicsProtocol* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHPhysicsProtocol*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPhysicsProtocol_LHGetNode : Error processing arguments");
        cocos2d::Node* ret = LHPhysicsProtocol::LHGetNode(arg0);
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
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPhysicsProtocol_LHGetNode : wrong number of arguments");
    return false;
}



void js_LHPhysicsProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHPhysicsProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHPhysicsProtocol *nobj = static_cast<LHPhysicsProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHPhysicsProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_LHPhysicsProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHPhysicsProtocol_class->name = "LHPhysicsProtocol";
    jsb_LHPhysicsProtocol_class->addProperty = JS_PropertyStub;
    jsb_LHPhysicsProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_LHPhysicsProtocol_class->getProperty = JS_PropertyStub;
    jsb_LHPhysicsProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_LHPhysicsProtocol_class->enumerate = JS_EnumerateStub;
    jsb_LHPhysicsProtocol_class->resolve = JS_ResolveStub;
    jsb_LHPhysicsProtocol_class->convert = JS_ConvertStub;
    jsb_LHPhysicsProtocol_class->finalize = js_LHPhysicsProtocol_finalize;
    jsb_LHPhysicsProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeBody", js_jsb_levelhelper_auto_LHPhysicsProtocol_removeBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visitPhysicsProtocol", js_jsb_levelhelper_auto_LHPhysicsProtocol_visitPhysicsProtocol, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updatePhysicsScale", js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadPhysicsFromDictionary", js_jsb_levelhelper_auto_LHPhysicsProtocol_loadPhysicsFromDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updatePhysicsTransform", js_jsb_levelhelper_auto_LHPhysicsProtocol_updatePhysicsTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("shouldRemoveBody", js_jsb_levelhelper_auto_LHPhysicsProtocol_shouldRemoveBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("LHGetNode", js_jsb_levelhelper_auto_LHPhysicsProtocol_LHGetNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHPhysicsProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHPhysicsProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHPhysicsProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHPhysicsProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHPhysicsProtocol_class;
        p->proto = jsb_LHPhysicsProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHNodeAnimationProtocol_class;
JSObject *jsb_LHNodeAnimationProtocol_prototype;

bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary : Error processing arguments");
        cobj->createAnimationsFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getActiveAnimation : Invalid Native Object");
    if (argc == 0) {
        LHAnimation* ret = cobj->getActiveAnimation();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHAnimation>(cx, (LHAnimation*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getActiveAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName : Error processing arguments");
        LHAnimation* ret = cobj->getAnimationWithName(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHAnimation>(cx, (LHAnimation*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimations(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimations : Invalid Native Object");
    if (argc == 0) {
        cocos2d::__Array* ret = cobj->getAnimations();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::__Array>(cx, (cocos2d::__Array*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimations : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation : Invalid Native Object");
    if (argc == 1) {
        LHAnimation* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHAnimation*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation : Error processing arguments");
        cobj->setActiveAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHNodeAnimationProtocol_visitActiveAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHNodeAnimationProtocol* cobj = (LHNodeAnimationProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_visitActiveAnimation : Invalid Native Object");
    if (argc == 0) {
        cobj->visitActiveAnimation();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHNodeAnimationProtocol_visitActiveAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_LHNodeAnimationProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHNodeAnimationProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHNodeAnimationProtocol *nobj = static_cast<LHNodeAnimationProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHNodeAnimationProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_LHNodeAnimationProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHNodeAnimationProtocol_class->name = "LHNodeAnimationProtocol";
    jsb_LHNodeAnimationProtocol_class->addProperty = JS_PropertyStub;
    jsb_LHNodeAnimationProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_LHNodeAnimationProtocol_class->getProperty = JS_PropertyStub;
    jsb_LHNodeAnimationProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_LHNodeAnimationProtocol_class->enumerate = JS_EnumerateStub;
    jsb_LHNodeAnimationProtocol_class->resolve = JS_ResolveStub;
    jsb_LHNodeAnimationProtocol_class->convert = JS_ConvertStub;
    jsb_LHNodeAnimationProtocol_class->finalize = js_LHNodeAnimationProtocol_finalize;
    jsb_LHNodeAnimationProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("createAnimationsFromDictionary", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_createAnimationsFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActiveAnimation", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getActiveAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationWithName", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimationWithName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimations", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_getAnimations, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActiveAnimation", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_setActiveAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visitActiveAnimation", js_jsb_levelhelper_auto_LHNodeAnimationProtocol_visitActiveAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_LHNodeAnimationProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHNodeAnimationProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHNodeAnimationProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHNodeAnimationProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHNodeAnimationProtocol_class;
        p->proto = jsb_LHNodeAnimationProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHSprite_class;
JSObject *jsb_LHSprite_prototype;

bool js_jsb_levelhelper_auto_LHSprite_initWithSpriteName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHSprite* cobj = (LHSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithSpriteName : Invalid Native Object");
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::Node* arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        do {
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithSpriteName : Error processing arguments");
        bool ret = cobj->initWithSpriteName(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_initWithSpriteName : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_jsb_levelhelper_auto_LHSprite_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHSprite* cobj = (LHSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHSprite_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHSprite_isSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHSprite* cobj = (LHSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHSprite_isSprite : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isSprite();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_isSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHSprite_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHSprite* cobj = (LHSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHSprite_initWithFilename(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHSprite* cobj = (LHSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithFilename : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        cocos2d::Node* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_initWithFilename : Error processing arguments");
        bool ret = cobj->initWithFilename(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_initWithFilename : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        cocos2d::Node* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_createWithFile : Error processing arguments");
        LHSprite* ret = LHSprite::createWithFile(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHSprite>(cx, (LHSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_createWithFile : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHSprite_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_nodeWithDictionary : Error processing arguments");
        LHSprite* ret = LHSprite::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHSprite>(cx, (LHSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHSprite_isLHSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_isLHSprite : Error processing arguments");
        bool ret = LHSprite::isLHSprite(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_isLHSprite : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHSprite_createWithSpriteName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::Node* arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        do {
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHSprite_createWithSpriteName : Error processing arguments");
        LHSprite* ret = LHSprite::createWithSpriteName(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHSprite>(cx, (LHSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHSprite_createWithSpriteName : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHSprite* cobj = new (std::nothrow) LHSprite();
    TypeTest<LHSprite> t;
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


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_LHSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHSprite)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHSprite *nobj = static_cast<LHSprite *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHSprite(JSContext *cx, JS::HandleObject global) {
    jsb_LHSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHSprite_class->name = "LHSprite";
    jsb_LHSprite_class->addProperty = JS_PropertyStub;
    jsb_LHSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_LHSprite_class->getProperty = JS_PropertyStub;
    jsb_LHSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_LHSprite_class->enumerate = JS_EnumerateStub;
    jsb_LHSprite_class->resolve = JS_ResolveStub;
    jsb_LHSprite_class->convert = JS_ConvertStub;
    jsb_LHSprite_class->finalize = js_LHSprite_finalize;
    jsb_LHSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithSpriteName", js_jsb_levelhelper_auto_LHSprite_initWithSpriteName, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHSprite_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isSprite", js_jsb_levelhelper_auto_LHSprite_isSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHSprite_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFilename", js_jsb_levelhelper_auto_LHSprite_initWithFilename, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_jsb_levelhelper_auto_LHSprite_createWithFile, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHSprite_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHSprite", js_jsb_levelhelper_auto_LHSprite_isLHSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteName", js_jsb_levelhelper_auto_LHSprite_createWithSpriteName, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_LHSprite_class,
        js_jsb_levelhelper_auto_LHSprite_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHSprite_class;
        p->proto = jsb_LHSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHCamera_class;
JSObject *jsb_LHCamera_prototype;

bool js_jsb_levelhelper_auto_LHCamera_resetLookAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_resetLookAt : Invalid Native Object");
    if (argc == 0) {
        cobj->resetLookAt();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_resetLookAt : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setSmoothMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setSmoothMovement : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setSmoothMovement : Error processing arguments");
        cobj->setSmoothMovement(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setSmoothMovement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld : Error processing arguments");
        cobj->setRestrictedToGameWorld(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Point arg0;
        double arg1;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds : Error processing arguments");
        cobj->lookAtPositionInSeconds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom : Error processing arguments");
        cobj->setUsePinchOrScrollWheelToZoom(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds : Error processing arguments");
        cobj->zoomToValueInSeconds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setPosition : Error processing arguments");
        cobj->setPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_usePinchOrScrollWheelToZoom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_usePinchOrScrollWheelToZoom : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->usePinchOrScrollWheelToZoom();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_usePinchOrScrollWheelToZoom : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds : Error processing arguments");
        cobj->resetLookAtInSeconds(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_followedNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_followedNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->followedNode();
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_followedNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setActive : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setActive : Error processing arguments");
        cobj->setActive(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setActive : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getImportantAreaUnit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getImportantAreaUnit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getImportantAreaUnit();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getImportantAreaUnit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setZoomValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setZoomValue : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setZoomValue : Error processing arguments");
        cobj->setZoomValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setZoomValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Node* arg0;
        double arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds : Error processing arguments");
        cobj->lookAtNodeInSeconds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getZoomValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getZoomValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getZoomValue();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getZoomValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setLockY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setLockY : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setLockY : Error processing arguments");
        cobj->setLockY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setLockY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setLockX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setLockX : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setLockX : Error processing arguments");
        cobj->setLockX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setLockX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getSmoothMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getSmoothMovement : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getSmoothMovement();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getSmoothMovement : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getOffsetUnit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getOffsetUnit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getOffsetUnit();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getOffsetUnit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_isLookingAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_isLookingAt : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLookingAt();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_isLookingAt : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_followNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_followNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_followNode : Error processing arguments");
        cobj->followNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_followNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_isActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_isActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isActive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_isActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_isCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_isCamera : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isCamera();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_isCamera : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_restrictedToGameWorld(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_restrictedToGameWorld : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->restrictedToGameWorld();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_restrictedToGameWorld : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setOffsetUnit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setOffsetUnit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setOffsetUnit : Error processing arguments");
        cobj->setOffsetUnit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setOffsetUnit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit : Error processing arguments");
        cobj->setImportantAreaUnit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getLockY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getLockY : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getLockY();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getLockY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_getLockX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_getLockX : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getLockX();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_getLockX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHCamera* cobj = (LHCamera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds : Error processing arguments");
        cobj->zoomByValueInSeconds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHCamera_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_nodeWithDictionary : Error processing arguments");
        LHCamera* ret = LHCamera::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHCamera>(cx, (LHCamera*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHCamera_isLHCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHCamera_isLHCamera : Error processing arguments");
        bool ret = LHCamera::isLHCamera(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHCamera_isLHCamera : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHCamera_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHCamera* cobj = new (std::nothrow) LHCamera();
    TypeTest<LHCamera> t;
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

void js_LHCamera_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHCamera)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHCamera *nobj = static_cast<LHCamera *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHCamera(JSContext *cx, JS::HandleObject global) {
    jsb_LHCamera_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHCamera_class->name = "LHCamera";
    jsb_LHCamera_class->addProperty = JS_PropertyStub;
    jsb_LHCamera_class->delProperty = JS_DeletePropertyStub;
    jsb_LHCamera_class->getProperty = JS_PropertyStub;
    jsb_LHCamera_class->setProperty = JS_StrictPropertyStub;
    jsb_LHCamera_class->enumerate = JS_EnumerateStub;
    jsb_LHCamera_class->resolve = JS_ResolveStub;
    jsb_LHCamera_class->convert = JS_ConvertStub;
    jsb_LHCamera_class->finalize = js_LHCamera_finalize;
    jsb_LHCamera_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("resetLookAt", js_jsb_levelhelper_auto_LHCamera_resetLookAt, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSmoothMovement", js_jsb_levelhelper_auto_LHCamera_setSmoothMovement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHCamera_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestrictedToGameWorld", js_jsb_levelhelper_auto_LHCamera_setRestrictedToGameWorld, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lookAtPositionInSeconds", js_jsb_levelhelper_auto_LHCamera_lookAtPositionInSeconds, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUsePinchOrScrollWheelToZoom", js_jsb_levelhelper_auto_LHCamera_setUsePinchOrScrollWheelToZoom, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("zoomToValueInSeconds", js_jsb_levelhelper_auto_LHCamera_zoomToValueInSeconds, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosition", js_jsb_levelhelper_auto_LHCamera_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("usePinchOrScrollWheelToZoom", js_jsb_levelhelper_auto_LHCamera_usePinchOrScrollWheelToZoom, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resetLookAtInSeconds", js_jsb_levelhelper_auto_LHCamera_resetLookAtInSeconds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("followedNode", js_jsb_levelhelper_auto_LHCamera_followedNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActive", js_jsb_levelhelper_auto_LHCamera_setActive, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getImportantAreaUnit", js_jsb_levelhelper_auto_LHCamera_getImportantAreaUnit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomValue", js_jsb_levelhelper_auto_LHCamera_setZoomValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lookAtNodeInSeconds", js_jsb_levelhelper_auto_LHCamera_lookAtNodeInSeconds, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomValue", js_jsb_levelhelper_auto_LHCamera_getZoomValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHCamera_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLockY", js_jsb_levelhelper_auto_LHCamera_setLockY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLockX", js_jsb_levelhelper_auto_LHCamera_setLockX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSmoothMovement", js_jsb_levelhelper_auto_LHCamera_getSmoothMovement, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOffsetUnit", js_jsb_levelhelper_auto_LHCamera_getOffsetUnit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLookingAt", js_jsb_levelhelper_auto_LHCamera_isLookingAt, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("followNode", js_jsb_levelhelper_auto_LHCamera_followNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isActive", js_jsb_levelhelper_auto_LHCamera_isActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isCamera", js_jsb_levelhelper_auto_LHCamera_isCamera, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("restrictedToGameWorld", js_jsb_levelhelper_auto_LHCamera_restrictedToGameWorld, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOffsetUnit", js_jsb_levelhelper_auto_LHCamera_setOffsetUnit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setImportantAreaUnit", js_jsb_levelhelper_auto_LHCamera_setImportantAreaUnit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLockY", js_jsb_levelhelper_auto_LHCamera_getLockY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLockX", js_jsb_levelhelper_auto_LHCamera_getLockX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("zoomByValueInSeconds", js_jsb_levelhelper_auto_LHCamera_zoomByValueInSeconds, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHCamera_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHCamera", js_jsb_levelhelper_auto_LHCamera_isLHCamera, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHCamera_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHCamera_class,
        js_jsb_levelhelper_auto_LHCamera_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHCamera", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHCamera> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHCamera_class;
        p->proto = jsb_LHCamera_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHAsset_class;
JSObject *jsb_LHAsset_prototype;

bool js_jsb_levelhelper_auto_LHAsset_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAsset* cobj = (LHAsset *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAsset_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHAsset_initWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAsset* cobj = (LHAsset *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAsset_initWithName : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        cocos2d::Node* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_initWithName : Error processing arguments");
        bool ret = cobj->initWithName(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_initWithName : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHAsset_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAsset* cobj = (LHAsset *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAsset_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHAsset_isAsset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAsset* cobj = (LHAsset *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAsset_isAsset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAsset();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_isAsset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAsset_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_nodeWithDictionary : Error processing arguments");
        LHAsset* ret = LHAsset::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHAsset>(cx, (LHAsset*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHAsset_createWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        cocos2d::Node* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_createWithName : Error processing arguments");
        LHAsset* ret = LHAsset::createWithName(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHAsset>(cx, (LHAsset*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_createWithName : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHAsset_isLHAsset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAsset_isLHAsset : Error processing arguments");
        bool ret = LHAsset::isLHAsset(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAsset_isLHAsset : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHAsset_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHAsset* cobj = new (std::nothrow) LHAsset();
    TypeTest<LHAsset> t;
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

void js_LHAsset_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHAsset)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHAsset *nobj = static_cast<LHAsset *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHAsset(JSContext *cx, JS::HandleObject global) {
    jsb_LHAsset_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHAsset_class->name = "LHAsset";
    jsb_LHAsset_class->addProperty = JS_PropertyStub;
    jsb_LHAsset_class->delProperty = JS_DeletePropertyStub;
    jsb_LHAsset_class->getProperty = JS_PropertyStub;
    jsb_LHAsset_class->setProperty = JS_StrictPropertyStub;
    jsb_LHAsset_class->enumerate = JS_EnumerateStub;
    jsb_LHAsset_class->resolve = JS_ResolveStub;
    jsb_LHAsset_class->convert = JS_ConvertStub;
    jsb_LHAsset_class->finalize = js_LHAsset_finalize;
    jsb_LHAsset_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("visit", js_jsb_levelhelper_auto_LHAsset_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithName", js_jsb_levelhelper_auto_LHAsset_initWithName, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHAsset_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAsset", js_jsb_levelhelper_auto_LHAsset_isAsset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHAsset_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithName", js_jsb_levelhelper_auto_LHAsset_createWithName, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHAsset", js_jsb_levelhelper_auto_LHAsset_isLHAsset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHAsset_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHAsset_class,
        js_jsb_levelhelper_auto_LHAsset_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHAsset", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHAsset> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHAsset_class;
        p->proto = jsb_LHAsset_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHParallax_class;
JSObject *jsb_LHParallax_prototype;

bool js_jsb_levelhelper_auto_LHParallax_followedNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallax* cobj = (LHParallax *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallax_followedNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->followedNode();
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_followedNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallax_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallax* cobj = (LHParallax *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallax_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallax_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallax_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallax* cobj = (LHParallax *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallax_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallax_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallax_followNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallax* cobj = (LHParallax *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallax_followNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallax_followNode : Error processing arguments");
        cobj->followNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_followNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallax_isParallax(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallax* cobj = (LHParallax *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallax_isParallax : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isParallax();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_isParallax : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallax_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallax_nodeWithDictionary : Error processing arguments");
        LHParallax* ret = LHParallax::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHParallax>(cx, (LHParallax*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHParallax_isLHParallax(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallax_isLHParallax : Error processing arguments");
        bool ret = LHParallax::isLHParallax(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallax_isLHParallax : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHParallax_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHParallax* cobj = new (std::nothrow) LHParallax();
    TypeTest<LHParallax> t;
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

void js_LHParallax_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHParallax)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHParallax *nobj = static_cast<LHParallax *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHParallax(JSContext *cx, JS::HandleObject global) {
    jsb_LHParallax_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHParallax_class->name = "LHParallax";
    jsb_LHParallax_class->addProperty = JS_PropertyStub;
    jsb_LHParallax_class->delProperty = JS_DeletePropertyStub;
    jsb_LHParallax_class->getProperty = JS_PropertyStub;
    jsb_LHParallax_class->setProperty = JS_StrictPropertyStub;
    jsb_LHParallax_class->enumerate = JS_EnumerateStub;
    jsb_LHParallax_class->resolve = JS_ResolveStub;
    jsb_LHParallax_class->convert = JS_ConvertStub;
    jsb_LHParallax_class->finalize = js_LHParallax_finalize;
    jsb_LHParallax_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("followedNode", js_jsb_levelhelper_auto_LHParallax_followedNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHParallax_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHParallax_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("followNode", js_jsb_levelhelper_auto_LHParallax_followNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isParallax", js_jsb_levelhelper_auto_LHParallax_isParallax, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHParallax_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHParallax", js_jsb_levelhelper_auto_LHParallax_isLHParallax, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHParallax_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHParallax_class,
        js_jsb_levelhelper_auto_LHParallax_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHParallax", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHParallax> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHParallax_class;
        p->proto = jsb_LHParallax_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHParallaxLayer_class;
JSObject *jsb_LHParallaxLayer_prototype;

bool js_jsb_levelhelper_auto_LHParallaxLayer_getInitialPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallaxLayer* cobj = (LHParallaxLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_getInitialPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getInitialPosition();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_getInitialPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallaxLayer_getRatioX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallaxLayer* cobj = (LHParallaxLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_getRatioX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRatioX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_getRatioX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallaxLayer_getRatioY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallaxLayer* cobj = (LHParallaxLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_getRatioY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRatioY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_getRatioY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallaxLayer* cobj = (LHParallaxLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallaxLayer_isParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHParallaxLayer* cobj = (LHParallaxLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_isParallaxLayer : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isParallaxLayer();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_isParallaxLayer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHParallaxLayer_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_nodeWithDictionary : Error processing arguments");
        LHParallaxLayer* ret = LHParallaxLayer::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHParallaxLayer>(cx, (LHParallaxLayer*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHParallaxLayer_isLHParallaxLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHParallaxLayer_isLHParallaxLayer : Error processing arguments");
        bool ret = LHParallaxLayer::isLHParallaxLayer(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHParallaxLayer_isLHParallaxLayer : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHParallaxLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHParallaxLayer* cobj = new (std::nothrow) LHParallaxLayer();
    TypeTest<LHParallaxLayer> t;
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

void js_LHParallaxLayer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHParallaxLayer)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHParallaxLayer *nobj = static_cast<LHParallaxLayer *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHParallaxLayer(JSContext *cx, JS::HandleObject global) {
    jsb_LHParallaxLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHParallaxLayer_class->name = "LHParallaxLayer";
    jsb_LHParallaxLayer_class->addProperty = JS_PropertyStub;
    jsb_LHParallaxLayer_class->delProperty = JS_DeletePropertyStub;
    jsb_LHParallaxLayer_class->getProperty = JS_PropertyStub;
    jsb_LHParallaxLayer_class->setProperty = JS_StrictPropertyStub;
    jsb_LHParallaxLayer_class->enumerate = JS_EnumerateStub;
    jsb_LHParallaxLayer_class->resolve = JS_ResolveStub;
    jsb_LHParallaxLayer_class->convert = JS_ConvertStub;
    jsb_LHParallaxLayer_class->finalize = js_LHParallaxLayer_finalize;
    jsb_LHParallaxLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getInitialPosition", js_jsb_levelhelper_auto_LHParallaxLayer_getInitialPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRatioX", js_jsb_levelhelper_auto_LHParallaxLayer_getRatioX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRatioY", js_jsb_levelhelper_auto_LHParallaxLayer_getRatioY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHParallaxLayer_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isParallaxLayer", js_jsb_levelhelper_auto_LHParallaxLayer_isParallaxLayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHParallaxLayer_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHParallaxLayer", js_jsb_levelhelper_auto_LHParallaxLayer_isLHParallaxLayer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHParallaxLayer_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHParallaxLayer_class,
        js_jsb_levelhelper_auto_LHParallaxLayer_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHParallaxLayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHParallaxLayer> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHParallaxLayer_class;
        p->proto = jsb_LHParallaxLayer_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHAnimation_class;
JSObject *jsb_LHAnimation_prototype;

bool js_jsb_levelhelper_auto_LHAnimation_totalTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_totalTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->totalTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_totalTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_node(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_node : Invalid Native Object");
    if (argc == 0) {
        LHNodeAnimationProtocol* ret = cobj->node();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<LHNodeAnimationProtocol>(cx, (LHNodeAnimationProtocol*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_node : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_repetitions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_repetitions : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->repetitions();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_repetitions : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_name(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_name : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->name();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_name : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_currentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_currentTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->currentTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_currentTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_restart(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_restart : Invalid Native Object");
    if (argc == 0) {
        cobj->restart();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_restart : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        LHNodeAnimationProtocol* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (LHNodeAnimationProtocol*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAnimation_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_currentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_currentFrame : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->currentFrame();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_currentFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_setActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setActive : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setActive : Error processing arguments");
        cobj->setActive(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_setActive : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_animating(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_animating : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->animating();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_animating : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_setAnimating(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setAnimating : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setAnimating : Error processing arguments");
        cobj->setAnimating(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_setAnimating : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame : Error processing arguments");
        cobj->setCurrentFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_isActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHAnimation* cobj = (LHAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHAnimation_isActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isActive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_isActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHAnimation_createWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        LHNodeAnimationProtocol* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (LHNodeAnimationProtocol*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHAnimation_createWithDictionary : Error processing arguments");
        LHAnimation* ret = LHAnimation::createWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHAnimation>(cx, (LHAnimation*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHAnimation_createWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHAnimation* cobj = new (std::nothrow) LHAnimation();
    TypeTest<LHAnimation> t;
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



void js_LHAnimation_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHAnimation)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHAnimation *nobj = static_cast<LHAnimation *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHAnimation(JSContext *cx, JS::HandleObject global) {
    jsb_LHAnimation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHAnimation_class->name = "LHAnimation";
    jsb_LHAnimation_class->addProperty = JS_PropertyStub;
    jsb_LHAnimation_class->delProperty = JS_DeletePropertyStub;
    jsb_LHAnimation_class->getProperty = JS_PropertyStub;
    jsb_LHAnimation_class->setProperty = JS_StrictPropertyStub;
    jsb_LHAnimation_class->enumerate = JS_EnumerateStub;
    jsb_LHAnimation_class->resolve = JS_ResolveStub;
    jsb_LHAnimation_class->convert = JS_ConvertStub;
    jsb_LHAnimation_class->finalize = js_LHAnimation_finalize;
    jsb_LHAnimation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("totalTime", js_jsb_levelhelper_auto_LHAnimation_totalTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("node", js_jsb_levelhelper_auto_LHAnimation_node, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("repetitions", js_jsb_levelhelper_auto_LHAnimation_repetitions, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("name", js_jsb_levelhelper_auto_LHAnimation_name, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("currentTime", js_jsb_levelhelper_auto_LHAnimation_currentTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("restart", js_jsb_levelhelper_auto_LHAnimation_restart, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHAnimation_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("currentFrame", js_jsb_levelhelper_auto_LHAnimation_currentFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActive", js_jsb_levelhelper_auto_LHAnimation_setActive, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("animating", js_jsb_levelhelper_auto_LHAnimation_animating, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimating", js_jsb_levelhelper_auto_LHAnimation_setAnimating, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentFrame", js_jsb_levelhelper_auto_LHAnimation_setCurrentFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isActive", js_jsb_levelhelper_auto_LHAnimation_isActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithDictionary", js_jsb_levelhelper_auto_LHAnimation_createWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHAnimation_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHAnimation_class,
        js_jsb_levelhelper_auto_LHAnimation_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHAnimation", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHAnimation> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHAnimation_class;
        p->proto = jsb_LHAnimation_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHGravityArea_class;
JSObject *jsb_LHGravityArea_prototype;

bool js_jsb_levelhelper_auto_LHGravityArea_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_getForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_getForce : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getForce();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_getForce : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_isRadial(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_isRadial : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isRadial();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_isRadial : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_getDirection : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getDirection();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_isGravityArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHGravityArea* cobj = (LHGravityArea *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_isGravityArea : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isGravityArea();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_isGravityArea : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHGravityArea_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_nodeWithDictionary : Error processing arguments");
        LHGravityArea* ret = LHGravityArea::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHGravityArea>(cx, (LHGravityArea*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHGravityArea_isLHGravityArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHGravityArea_isLHGravityArea : Error processing arguments");
        bool ret = LHGravityArea::isLHGravityArea(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHGravityArea_isLHGravityArea : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHGravityArea_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHGravityArea* cobj = new (std::nothrow) LHGravityArea();
    TypeTest<LHGravityArea> t;
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

void js_LHGravityArea_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHGravityArea)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHGravityArea *nobj = static_cast<LHGravityArea *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHGravityArea(JSContext *cx, JS::HandleObject global) {
    jsb_LHGravityArea_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHGravityArea_class->name = "LHGravityArea";
    jsb_LHGravityArea_class->addProperty = JS_PropertyStub;
    jsb_LHGravityArea_class->delProperty = JS_DeletePropertyStub;
    jsb_LHGravityArea_class->getProperty = JS_PropertyStub;
    jsb_LHGravityArea_class->setProperty = JS_StrictPropertyStub;
    jsb_LHGravityArea_class->enumerate = JS_EnumerateStub;
    jsb_LHGravityArea_class->resolve = JS_ResolveStub;
    jsb_LHGravityArea_class->convert = JS_ConvertStub;
    jsb_LHGravityArea_class->finalize = js_LHGravityArea_finalize;
    jsb_LHGravityArea_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("visit", js_jsb_levelhelper_auto_LHGravityArea_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getForce", js_jsb_levelhelper_auto_LHGravityArea_getForce, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isRadial", js_jsb_levelhelper_auto_LHGravityArea_isRadial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDirection", js_jsb_levelhelper_auto_LHGravityArea_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHGravityArea_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isGravityArea", js_jsb_levelhelper_auto_LHGravityArea_isGravityArea, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHGravityArea_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHGravityArea", js_jsb_levelhelper_auto_LHGravityArea_isLHGravityArea, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHGravityArea_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHGravityArea_class,
        js_jsb_levelhelper_auto_LHGravityArea_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHGravityArea", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHGravityArea> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHGravityArea_class;
        p->proto = jsb_LHGravityArea_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHJointsProtocol_class;
JSObject *jsb_LHJointsProtocol_prototype;

bool js_jsb_levelhelper_auto_LHJointsProtocol_getNodeA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getNodeA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNodeA();
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getNodeA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getNodeB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getNodeB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNodeB();
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

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getNodeB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_findConnectedNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_findConnectedNodes : Invalid Native Object");
    if (argc == 0) {
        cobj->findConnectedNodes();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_findConnectedNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_removeJoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_removeJoint : Invalid Native Object");
    if (argc == 0) {
        cobj->removeJoint();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_removeJoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_shouldRemoveJoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_shouldRemoveJoint : Invalid Native Object");
    if (argc == 0) {
        cobj->shouldRemoveJoint();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_shouldRemoveJoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getLocalAnchorA();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getCollideConnected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getCollideConnected : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getCollideConnected();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getCollideConnected : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getLocalAnchorB();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAnchorB();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAnchorA();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHJointsProtocol* cobj = (LHJointsProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary : Invalid Native Object");
    if (argc == 1) {
        LHDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary : Error processing arguments");
        cobj->loadJointInfoFromDictionary(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


void js_LHJointsProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHJointsProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHJointsProtocol *nobj = static_cast<LHJointsProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHJointsProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_LHJointsProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHJointsProtocol_class->name = "LHJointsProtocol";
    jsb_LHJointsProtocol_class->addProperty = JS_PropertyStub;
    jsb_LHJointsProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_LHJointsProtocol_class->getProperty = JS_PropertyStub;
    jsb_LHJointsProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_LHJointsProtocol_class->enumerate = JS_EnumerateStub;
    jsb_LHJointsProtocol_class->resolve = JS_ResolveStub;
    jsb_LHJointsProtocol_class->convert = JS_ConvertStub;
    jsb_LHJointsProtocol_class->finalize = js_LHJointsProtocol_finalize;
    jsb_LHJointsProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getNodeA", js_jsb_levelhelper_auto_LHJointsProtocol_getNodeA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNodeB", js_jsb_levelhelper_auto_LHJointsProtocol_getNodeB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("findConnectedNodes", js_jsb_levelhelper_auto_LHJointsProtocol_findConnectedNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeJoint", js_jsb_levelhelper_auto_LHJointsProtocol_removeJoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("shouldRemoveJoint", js_jsb_levelhelper_auto_LHJointsProtocol_shouldRemoveJoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLocalAnchorA", js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCollideConnected", js_jsb_levelhelper_auto_LHJointsProtocol_getCollideConnected, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLocalAnchorB", js_jsb_levelhelper_auto_LHJointsProtocol_getLocalAnchorB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorB", js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorA", js_jsb_levelhelper_auto_LHJointsProtocol_getAnchorA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadJointInfoFromDictionary", js_jsb_levelhelper_auto_LHJointsProtocol_loadJointInfoFromDictionary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_LHJointsProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_LHJointsProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHJointsProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHJointsProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHJointsProtocol_class;
        p->proto = jsb_LHJointsProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHRopeJointNode_class;
JSObject *jsb_LHRopeJointNode_prototype;

bool js_jsb_levelhelper_auto_LHRopeJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_isRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_isRopeJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isRopeJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_isRopeJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_canBeCut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_canBeCut : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->canBeCut();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_canBeCut : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRopeJointNode* cobj = (LHRopeJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Point arg0;
        cocos2d::Point arg1;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA : Error processing arguments");
        cobj->cutWithLineFromPointA(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHRopeJointNode_isLHRopeJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_isLHRopeJointNode : Error processing arguments");
        bool ret = LHRopeJointNode::isLHRopeJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_isLHRopeJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHRopeJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRopeJointNode_nodeWithDictionary : Error processing arguments");
        LHRopeJointNode* ret = LHRopeJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHRopeJointNode>(cx, (LHRopeJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRopeJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHRopeJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHRopeJointNode* cobj = new (std::nothrow) LHRopeJointNode();
    TypeTest<LHRopeJointNode> t;
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

void js_LHRopeJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHRopeJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHRopeJointNode *nobj = static_cast<LHRopeJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHRopeJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHRopeJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHRopeJointNode_class->name = "LHRopeJointNode";
    jsb_LHRopeJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHRopeJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHRopeJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHRopeJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHRopeJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHRopeJointNode_class->resolve = JS_ResolveStub;
    jsb_LHRopeJointNode_class->convert = JS_ConvertStub;
    jsb_LHRopeJointNode_class->finalize = js_LHRopeJointNode_finalize;
    jsb_LHRopeJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHRopeJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isRopeJointNode", js_jsb_levelhelper_auto_LHRopeJointNode_isRopeJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHRopeJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("canBeCut", js_jsb_levelhelper_auto_LHRopeJointNode_canBeCut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHRopeJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cutWithLineFromPointA", js_jsb_levelhelper_auto_LHRopeJointNode_cutWithLineFromPointA, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("isLHRopeJointNode", js_jsb_levelhelper_auto_LHRopeJointNode_isLHRopeJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHRopeJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHRopeJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHRopeJointNode_class,
        js_jsb_levelhelper_auto_LHRopeJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHRopeJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHRopeJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHRopeJointNode_class;
        p->proto = jsb_LHRopeJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHRevoluteJointNode_class;
JSObject *jsb_LHRevoluteJointNode_prototype;

bool js_jsb_levelhelper_auto_LHRevoluteJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getUpperAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getUpperAngle : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUpperAngle();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getUpperAngle : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getMaxMotorTorque(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getMaxMotorTorque : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxMotorTorque();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getMaxMotorTorque : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableLimit : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableLimit();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getLowerAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getLowerAngle : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLowerAngle();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getLowerAngle : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getMotorSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMotorSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getMotorSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_isRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_isRevoluteJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isRevoluteJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_isRevoluteJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHRevoluteJointNode* cobj = (LHRevoluteJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHRevoluteJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_nodeWithDictionary : Error processing arguments");
        LHRevoluteJointNode* ret = LHRevoluteJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHRevoluteJointNode>(cx, (LHRevoluteJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHRevoluteJointNode_isLHRevoluteJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHRevoluteJointNode_isLHRevoluteJointNode : Error processing arguments");
        bool ret = LHRevoluteJointNode::isLHRevoluteJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHRevoluteJointNode_isLHRevoluteJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHRevoluteJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHRevoluteJointNode* cobj = new (std::nothrow) LHRevoluteJointNode();
    TypeTest<LHRevoluteJointNode> t;
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

void js_LHRevoluteJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHRevoluteJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHRevoluteJointNode *nobj = static_cast<LHRevoluteJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHRevoluteJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHRevoluteJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHRevoluteJointNode_class->name = "LHRevoluteJointNode";
    jsb_LHRevoluteJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHRevoluteJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHRevoluteJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHRevoluteJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHRevoluteJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHRevoluteJointNode_class->resolve = JS_ResolveStub;
    jsb_LHRevoluteJointNode_class->convert = JS_ConvertStub;
    jsb_LHRevoluteJointNode_class->finalize = js_LHRevoluteJointNode_finalize;
    jsb_LHRevoluteJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHRevoluteJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHRevoluteJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUpperAngle", js_jsb_levelhelper_auto_LHRevoluteJointNode_getUpperAngle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxMotorTorque", js_jsb_levelhelper_auto_LHRevoluteJointNode_getMaxMotorTorque, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableLimit", js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLowerAngle", js_jsb_levelhelper_auto_LHRevoluteJointNode_getLowerAngle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHRevoluteJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMotorSpeed", js_jsb_levelhelper_auto_LHRevoluteJointNode_getMotorSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isRevoluteJointNode", js_jsb_levelhelper_auto_LHRevoluteJointNode_isRevoluteJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableMotor", js_jsb_levelhelper_auto_LHRevoluteJointNode_getEnableMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHRevoluteJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHRevoluteJointNode", js_jsb_levelhelper_auto_LHRevoluteJointNode_isLHRevoluteJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHRevoluteJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHRevoluteJointNode_class,
        js_jsb_levelhelper_auto_LHRevoluteJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHRevoluteJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHRevoluteJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHRevoluteJointNode_class;
        p->proto = jsb_LHRevoluteJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHDistanceJointNode_class;
JSObject *jsb_LHDistanceJointNode_prototype;

bool js_jsb_levelhelper_auto_LHDistanceJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_getFrequency : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFrequency();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_getFrequency : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_getDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_getDamping : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDamping();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_getDamping : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_isDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHDistanceJointNode* cobj = (LHDistanceJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_isDistanceJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDistanceJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_isDistanceJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHDistanceJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_nodeWithDictionary : Error processing arguments");
        LHDistanceJointNode* ret = LHDistanceJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHDistanceJointNode>(cx, (LHDistanceJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHDistanceJointNode_isLHDistanceJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHDistanceJointNode_isLHDistanceJointNode : Error processing arguments");
        bool ret = LHDistanceJointNode::isLHDistanceJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHDistanceJointNode_isLHDistanceJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHDistanceJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHDistanceJointNode* cobj = new (std::nothrow) LHDistanceJointNode();
    TypeTest<LHDistanceJointNode> t;
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

void js_LHDistanceJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHDistanceJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHDistanceJointNode *nobj = static_cast<LHDistanceJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHDistanceJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHDistanceJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHDistanceJointNode_class->name = "LHDistanceJointNode";
    jsb_LHDistanceJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHDistanceJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHDistanceJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHDistanceJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHDistanceJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHDistanceJointNode_class->resolve = JS_ResolveStub;
    jsb_LHDistanceJointNode_class->convert = JS_ConvertStub;
    jsb_LHDistanceJointNode_class->finalize = js_LHDistanceJointNode_finalize;
    jsb_LHDistanceJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFrequency", js_jsb_levelhelper_auto_LHDistanceJointNode_getFrequency, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHDistanceJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDamping", js_jsb_levelhelper_auto_LHDistanceJointNode_getDamping, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHDistanceJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHDistanceJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDistanceJointNode", js_jsb_levelhelper_auto_LHDistanceJointNode_isDistanceJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHDistanceJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHDistanceJointNode", js_jsb_levelhelper_auto_LHDistanceJointNode_isLHDistanceJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHDistanceJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHDistanceJointNode_class,
        js_jsb_levelhelper_auto_LHDistanceJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHDistanceJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHDistanceJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHDistanceJointNode_class;
        p->proto = jsb_LHDistanceJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHWeldJointNode_class;
JSObject *jsb_LHWeldJointNode_prototype;

bool js_jsb_levelhelper_auto_LHWeldJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_getFrequency : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFrequency();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_getFrequency : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_getDampingRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_getDampingRatio : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingRatio();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_getDampingRatio : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_isWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWeldJointNode* cobj = (LHWeldJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_isWeldJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isWeldJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_isWeldJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWeldJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_nodeWithDictionary : Error processing arguments");
        LHWeldJointNode* ret = LHWeldJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHWeldJointNode>(cx, (LHWeldJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHWeldJointNode_isLHWeldJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWeldJointNode_isLHWeldJointNode : Error processing arguments");
        bool ret = LHWeldJointNode::isLHWeldJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWeldJointNode_isLHWeldJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHWeldJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHWeldJointNode* cobj = new (std::nothrow) LHWeldJointNode();
    TypeTest<LHWeldJointNode> t;
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

void js_LHWeldJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHWeldJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHWeldJointNode *nobj = static_cast<LHWeldJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHWeldJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHWeldJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHWeldJointNode_class->name = "LHWeldJointNode";
    jsb_LHWeldJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHWeldJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHWeldJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHWeldJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHWeldJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHWeldJointNode_class->resolve = JS_ResolveStub;
    jsb_LHWeldJointNode_class->convert = JS_ConvertStub;
    jsb_LHWeldJointNode_class->finalize = js_LHWeldJointNode_finalize;
    jsb_LHWeldJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFrequency", js_jsb_levelhelper_auto_LHWeldJointNode_getFrequency, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHWeldJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHWeldJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingRatio", js_jsb_levelhelper_auto_LHWeldJointNode_getDampingRatio, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHWeldJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isWeldJointNode", js_jsb_levelhelper_auto_LHWeldJointNode_isWeldJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHWeldJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHWeldJointNode", js_jsb_levelhelper_auto_LHWeldJointNode_isLHWeldJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHWeldJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHWeldJointNode_class,
        js_jsb_levelhelper_auto_LHWeldJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHWeldJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHWeldJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHWeldJointNode_class;
        p->proto = jsb_LHWeldJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHPrismaticJointNode_class;
JSObject *jsb_LHPrismaticJointNode_prototype;

bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getUpperTranslation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getUpperTranslation : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUpperTranslation();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getUpperTranslation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getAxis(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getAxis : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAxis();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getAxis : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getMaxMotorForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getMaxMotorForce : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxMotorForce();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getMaxMotorForce : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getLowerTranslation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getLowerTranslation : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLowerTranslation();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getLowerTranslation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableLimit : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableLimit();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_isPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_isPrismaticJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPrismaticJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_isPrismaticJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getMotorSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMotorSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getMotorSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPrismaticJointNode* cobj = (LHPrismaticJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPrismaticJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_nodeWithDictionary : Error processing arguments");
        LHPrismaticJointNode* ret = LHPrismaticJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHPrismaticJointNode>(cx, (LHPrismaticJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHPrismaticJointNode_isLHPrismaticJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPrismaticJointNode_isLHPrismaticJointNode : Error processing arguments");
        bool ret = LHPrismaticJointNode::isLHPrismaticJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPrismaticJointNode_isLHPrismaticJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHPrismaticJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHPrismaticJointNode* cobj = new (std::nothrow) LHPrismaticJointNode();
    TypeTest<LHPrismaticJointNode> t;
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

void js_LHPrismaticJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHPrismaticJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHPrismaticJointNode *nobj = static_cast<LHPrismaticJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHPrismaticJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHPrismaticJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHPrismaticJointNode_class->name = "LHPrismaticJointNode";
    jsb_LHPrismaticJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHPrismaticJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHPrismaticJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHPrismaticJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHPrismaticJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHPrismaticJointNode_class->resolve = JS_ResolveStub;
    jsb_LHPrismaticJointNode_class->convert = JS_ConvertStub;
    jsb_LHPrismaticJointNode_class->finalize = js_LHPrismaticJointNode_finalize;
    jsb_LHPrismaticJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getUpperTranslation", js_jsb_levelhelper_auto_LHPrismaticJointNode_getUpperTranslation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHPrismaticJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAxis", js_jsb_levelhelper_auto_LHPrismaticJointNode_getAxis, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHPrismaticJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxMotorForce", js_jsb_levelhelper_auto_LHPrismaticJointNode_getMaxMotorForce, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLowerTranslation", js_jsb_levelhelper_auto_LHPrismaticJointNode_getLowerTranslation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableLimit", js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPrismaticJointNode", js_jsb_levelhelper_auto_LHPrismaticJointNode_isPrismaticJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMotorSpeed", js_jsb_levelhelper_auto_LHPrismaticJointNode_getMotorSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHPrismaticJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableMotor", js_jsb_levelhelper_auto_LHPrismaticJointNode_getEnableMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHPrismaticJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHPrismaticJointNode", js_jsb_levelhelper_auto_LHPrismaticJointNode_isLHPrismaticJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHPrismaticJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHPrismaticJointNode_class,
        js_jsb_levelhelper_auto_LHPrismaticJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHPrismaticJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHPrismaticJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHPrismaticJointNode_class;
        p->proto = jsb_LHPrismaticJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHWheelJointNode_class;
JSObject *jsb_LHWheelJointNode_prototype;

bool js_jsb_levelhelper_auto_LHWheelJointNode_getFrequency(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getFrequency : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFrequency();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getFrequency : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_getAxis(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getAxis : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAxis();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getAxis : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_getMaxMotorTorque(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getMaxMotorTorque : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxMotorTorque();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getMaxMotorTorque : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_getDampingRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getDampingRatio : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingRatio();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getDampingRatio : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_getMotorSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getMotorSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMotorSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getMotorSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_isWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_isWheelJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isWheelJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_isWheelJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_getEnableMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHWheelJointNode* cobj = (LHWheelJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_getEnableMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_getEnableMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHWheelJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_nodeWithDictionary : Error processing arguments");
        LHWheelJointNode* ret = LHWheelJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHWheelJointNode>(cx, (LHWheelJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHWheelJointNode_isLHWheelJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHWheelJointNode_isLHWheelJointNode : Error processing arguments");
        bool ret = LHWheelJointNode::isLHWheelJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHWheelJointNode_isLHWheelJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHWheelJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHWheelJointNode* cobj = new (std::nothrow) LHWheelJointNode();
    TypeTest<LHWheelJointNode> t;
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

void js_LHWheelJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHWheelJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHWheelJointNode *nobj = static_cast<LHWheelJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHWheelJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHWheelJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHWheelJointNode_class->name = "LHWheelJointNode";
    jsb_LHWheelJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHWheelJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHWheelJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHWheelJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHWheelJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHWheelJointNode_class->resolve = JS_ResolveStub;
    jsb_LHWheelJointNode_class->convert = JS_ConvertStub;
    jsb_LHWheelJointNode_class->finalize = js_LHWheelJointNode_finalize;
    jsb_LHWheelJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFrequency", js_jsb_levelhelper_auto_LHWheelJointNode_getFrequency, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHWheelJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAxis", js_jsb_levelhelper_auto_LHWheelJointNode_getAxis, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHWheelJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxMotorTorque", js_jsb_levelhelper_auto_LHWheelJointNode_getMaxMotorTorque, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingRatio", js_jsb_levelhelper_auto_LHWheelJointNode_getDampingRatio, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHWheelJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMotorSpeed", js_jsb_levelhelper_auto_LHWheelJointNode_getMotorSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isWheelJointNode", js_jsb_levelhelper_auto_LHWheelJointNode_isWheelJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableMotor", js_jsb_levelhelper_auto_LHWheelJointNode_getEnableMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHWheelJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHWheelJointNode", js_jsb_levelhelper_auto_LHWheelJointNode_isLHWheelJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHWheelJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHWheelJointNode_class,
        js_jsb_levelhelper_auto_LHWheelJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHWheelJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHWheelJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHWheelJointNode_class;
        p->proto = jsb_LHWheelJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_LHPulleyJointNode_class;
JSObject *jsb_LHPulleyJointNode_prototype;

bool js_jsb_levelhelper_auto_LHPulleyJointNode_lateLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_lateLoading : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->lateLoading();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_lateLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_isPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_isPulleyJointNode : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPulleyJointNode();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_isPulleyJointNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getGroundAnchorA();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_visit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_visit : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        unsigned int arg2;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_visit : Error processing arguments");
        cobj->visit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_visit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary : Invalid Native Object");
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary : Error processing arguments");
        bool ret = cobj->initWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LHPulleyJointNode* cobj = (LHPulleyJointNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getGroundAnchorB();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_jsb_levelhelper_auto_LHPulleyJointNode_nodeWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        LHDictionary* arg0;
        cocos2d::Node* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (LHDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_nodeWithDictionary : Error processing arguments");
        LHPulleyJointNode* ret = LHPulleyJointNode::nodeWithDictionary(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<LHPulleyJointNode>(cx, (LHPulleyJointNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_nodeWithDictionary : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHPulleyJointNode_isLHPulleyJointNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_jsb_levelhelper_auto_LHPulleyJointNode_isLHPulleyJointNode : Error processing arguments");
        bool ret = LHPulleyJointNode::isLHPulleyJointNode(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_jsb_levelhelper_auto_LHPulleyJointNode_isLHPulleyJointNode : wrong number of arguments");
    return false;
}

bool js_jsb_levelhelper_auto_LHPulleyJointNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    LHPulleyJointNode* cobj = new (std::nothrow) LHPulleyJointNode();
    TypeTest<LHPulleyJointNode> t;
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

void js_LHPulleyJointNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LHPulleyJointNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        LHPulleyJointNode *nobj = static_cast<LHPulleyJointNode *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_jsb_levelhelper_auto_LHPulleyJointNode(JSContext *cx, JS::HandleObject global) {
    jsb_LHPulleyJointNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LHPulleyJointNode_class->name = "LHPulleyJointNode";
    jsb_LHPulleyJointNode_class->addProperty = JS_PropertyStub;
    jsb_LHPulleyJointNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LHPulleyJointNode_class->getProperty = JS_PropertyStub;
    jsb_LHPulleyJointNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LHPulleyJointNode_class->enumerate = JS_EnumerateStub;
    jsb_LHPulleyJointNode_class->resolve = JS_ResolveStub;
    jsb_LHPulleyJointNode_class->convert = JS_ConvertStub;
    jsb_LHPulleyJointNode_class->finalize = js_LHPulleyJointNode_finalize;
    jsb_LHPulleyJointNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("lateLoading", js_jsb_levelhelper_auto_LHPulleyJointNode_lateLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPulleyJointNode", js_jsb_levelhelper_auto_LHPulleyJointNode_isPulleyJointNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGroundAnchorA", js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("visit", js_jsb_levelhelper_auto_LHPulleyJointNode_visit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithDictionary", js_jsb_levelhelper_auto_LHPulleyJointNode_initWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGroundAnchorB", js_jsb_levelhelper_auto_LHPulleyJointNode_getGroundAnchorB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("nodeWithDictionary", js_jsb_levelhelper_auto_LHPulleyJointNode_nodeWithDictionary, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLHPulleyJointNode", js_jsb_levelhelper_auto_LHPulleyJointNode_isLHPulleyJointNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_LHPulleyJointNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_LHPulleyJointNode_class,
        js_jsb_levelhelper_auto_LHPulleyJointNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LHPulleyJointNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<LHPulleyJointNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_LHPulleyJointNode_class;
        p->proto = jsb_LHPulleyJointNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_jsb_levelhelper_auto(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "lh", &ns);

    js_register_jsb_levelhelper_auto_LHNodeProtocol(cx, ns);
    js_register_jsb_levelhelper_auto_LHJointsProtocol(cx, ns);
    js_register_jsb_levelhelper_auto_LHPulleyJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHWheelJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHGameWorldNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHNodeAnimationProtocol(cx, ns);
    js_register_jsb_levelhelper_auto_LHPhysicsProtocol(cx, ns);
    js_register_jsb_levelhelper_auto_LHSprite(cx, ns);
    js_register_jsb_levelhelper_auto_LHCamera(cx, ns);
    js_register_jsb_levelhelper_auto_LHAsset(cx, ns);
    js_register_jsb_levelhelper_auto_LHUserPropertyProtocol(cx, ns);
    js_register_jsb_levelhelper_auto_LHParallax(cx, ns);
    js_register_jsb_levelhelper_auto_LHRopeJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHAnimation(cx, ns);
    js_register_jsb_levelhelper_auto_LHUINode(cx, ns);
    js_register_jsb_levelhelper_auto_LHDistanceJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHPrismaticJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHParallaxLayer(cx, ns);
    js_register_jsb_levelhelper_auto_LHRevoluteJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHScene(cx, ns);
    js_register_jsb_levelhelper_auto_LHWeldJointNode(cx, ns);
    js_register_jsb_levelhelper_auto_LHGravityArea(cx, ns);
    js_register_jsb_levelhelper_auto_LHBackUINode(cx, ns);
}

