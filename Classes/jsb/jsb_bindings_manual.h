//
//  jsb_bindings_manual.h
//  crows
//
//  Created by yuxiao on 15/1/8.
//
//

#ifndef __crows__jsb_bindings_manual__
#define __crows__jsb_bindings_manual__

#include "ScriptingCore.h"

void register_all_jsb_levelhelper_manual(JSContext *cx, JS::HandleObject global);
void register_all_jsb_bindings_manual(JSContext *cx, JS::HandleObject global);

#endif /* defined(__crows__jsb_bindings_manual__) */
