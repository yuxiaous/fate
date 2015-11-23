var AnnouncementLayer = ui.GuiWindowBase.extend({
    _guiFile : "ui/announcement_layer.json",

    ctor : function () {
        this._super();
    },

    onEnter : function () {
        this._super();
        this._ui = {
            lbl_content: this.seekWidgetByName("lbl_content")
        };

        this._ui.lbl_content.setString("" +
            "中文名称：命运长夜（单机版）\n" +
            "应用类型：动作冒险\n" +
            "版本号：1.2\n" +
            "版权所有：上海红豆泥网络科技有限公司\n" +
            "开发商：上海红豆泥网络科技有限公司\n" +
            "公司名称：上海红豆泥网络科技有限公司\n" +
            "发行商：天津莱玩网络科技有限公司\n" +
            "客服电话：010-51145017\n" +
            "玩家QQ群：293400487\n" +
            (util.getChannelId() == GameChannel.Telecom ? "免责声明：本游戏的版权归上海红豆泥网络科技有限公司所有，游戏中的图片、文字等内容均为游戏版权所有者的个人态度和立场，炫彩公司对此不承担任何法律责任。\n" : "") +
            "");
    },

    onExit : function () {
        this._ui = null;
        this._super();
    },

    _on_btn_close : function () {
        this.close();
    }
});