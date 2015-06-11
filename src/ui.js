/**
 * Created by yuxiao on 14-9-29.
 */


var ui = {
    Version: 3.6,
    Z_ORDER_WINDOW: 100,

    pushScene: function(oClass) {
        var scene = oClass instanceof Function ? new oClass() : oClass;

        if(scene) {
            if(cc.director.getRunningScene()) {
                cc.director.pushScene(scene);
            }
            else {
                cc.director.runScene(scene);
            }
        }
        return scene;
    },

    popScene: function(level) {
        if(level === undefined) {
            cc.director.popScene();
        }
        else {
            cc.director.popToSceneStackLevel(level);
        }
    },

    replaceScene: function(oClass) {
        var scene = oClass instanceof Function ? new oClass() : oClass;
        if(scene) {
            cc.director.runScene(scene);
        }
    },

    popWindow: function(oTarget) {
        cc.director.getRunningScene().addChild(oTarget, ui.Z_ORDER_WINDOW);
        return oTarget;
    },

    closeWindow: function(oTarget) {
        oTarget.removeFromParent();
    },

    /*
     * Sprite
     * Node
     * Audio
     * Particle
     * Map
     *
     * Button -> btn
     * CheckBox -> chk
     * Image -> img
     * Text -> lbl, txt
     * BitmapFontLabel -> fnt
     * LoadingBar -> loading
     * Slider -> slider
     * TextFiled -> tf
     *
     * ListView -> list
     * PageView -> page
     * Panel -> lay
     * ScrollView -> scroll
     *
     * ProjectNode
     *
     * */
    preprocessGui: function(oWidget, oCaller) {
        var name = oWidget.getName(),
            fnName;

        // root widget
        if (name == "root") {
            //oWidget._pos_original = oWidget.getPosition();
            //oCaller._root = oWidget;
        }

        // button listener
        else if (name.startsWith("btn_")) {
            fnName = "_on_" + name;

            oWidget.addClickEventListener(function (oTarget) {
                if(oCaller[fnName]) {
                    oCaller[fnName](oTarget);

                    // play sound effect
                    //SoundEffectControl.play(SoundEffectControl.Type.AN_JIAN)
                }
            });
        }

        // text field listener
        else if(name.startsWith("tf_")) {
            fnName = "_on_" + name;

            oWidget.addEventListener(function (oTarget, eType) {
                //var root = oCaller._root;
                //
                //if(eType == ccui.TextField.EVENT_ATTACH_WITH_IME) {
                //    var delta = oCaller._shift || 0;
                //    root.setPositionY(root._pos_original.y + delta);
                //}
                //else if(eType == ccui.TextField.EVENT_DETACH_WITH_IME) {
                //    root.setPosition(root._pos_original);
                //}

                if(oCaller[fnName]) {
                    oCaller[fnName](oTarget, eType);
                }
            }, this);
        }

        // check box
        else if(name.startsWith("chk_")) {
            fnName = "_on_" + name;

            oWidget.addEventListener(function (oTarget, eType) {
                if(oCaller[fnName]) {
                    oCaller[fnName](oTarget, eType);
                }
            }, this);
        }

        // label
        else if(name.startsWith("lbl_") || name.startsWith("txt_")) {
            oWidget._str_original = oWidget.getString();
            oWidget._color_original = oWidget.getColor();
        }

        //// ProjectNode
        //else if(!isRoot && name.startsWith("ProjectNode_")) {
        //    return;
        //}

        // iterate
        var children = oWidget.getChildren();
        for(var i = children.length; i--;) {
            var child = children[i];
            this.preprocessGui(child, oCaller);
        }
    },

    createGuiNode: function(guifile) {
        cc.log("Gui file: " + guifile);
        if(guifile == null) {
            cc.error("Gui file is empty.");
            return null;
        }

        // load layout
        var root = null;
        if(ui.Version >= 3.6) {
            root = ccs.load(guifile, "");
            root.node.setAnchorPoint(0, 0);
        }
        else if(ui.Version >= 3.3) {
            root = ccs.load(guifile, "").node;
        }
        else if(ui.Version >= 3.2) {
            root = ccs.csLoader.createNode(guifile);
        }
        else if(ui.Version >= 1.0) {
            root = ccs.uiReader.widgetFromJsonFile(guifile);
        }
        else {
            cc.error("Current version is not support.");
        }
        if(root == null) {
            cc.error("Root widget create fail.");
            return null;
        }
        return root
    },

    seekGuiNode: function(root, name) {
        var control = null;
        root.enumerateChildren('//' + name, function(node) {
            control = node;
            return true;
        });
        return control;
    }
};

ui.guiExtend = {
    loadGui: function(guifile) {
        if(this.__gui__ == null) {
            var gui = ui.createGuiNode(guifile);
            if(gui) {
                ui.preprocessGui(gui.node, this);

                this.addChild(gui.node);
                this.setContentSize(gui.node.getContentSize());

                gui.node.runAction(gui.action);

                this.__gui__ = gui.node;
                this.__action__ = gui.action;
            }
            else {
                this.__gui__ = null;
                this.__action__ = null;
            }
        }
    },

    unloadGui: function() {
        if(this.__gui__ && this.__action__) {
            this.__gui__.stopAction(this.__action__);
            this.__action__ = null;
        }
        if (this.__gui__) {
            this.__gui__.removeFromParent();
            this.__gui__ = null;
        }
    },

    seekWidgetByName: function(name) {
        if(this.__gui__) {
            return ui.seekGuiNode(this.__gui__, name);
        }
        return null;
    },

    playAnimation: function(name, loop) {
        if(loop == undefined) loop = false;

        if(this.__action__) {
            this.__action__.play(name, loop);
        }
    },

    stopAnimation: function() {
        if(this.__action__) {
            this.__action__.pause();
        }
    }
};

