/**
 * Created by yuxiao on 15/4/8.
 */


var ForestScene = SceneBase.extend({
    status: {
        weather: "particles/rain.plist",
        music: "sounds/background1.mp3",

        hero: Saber,

        sections: [
            {
                area: cc.rect(0, 0, 2000, 640),
                street: cc.rect(0, 0, 2000, 220),
                heroPosition: cc.p(300, 110),
                warningLine : 400,

                chat: [
                    {
                        name: "Saber",
                        text: "这是哪里？？",
                        side: DialogPanel.Side.Left,
                        image: "images/chat/saber.png"
                    }
                ],


                monsters: [
                    {
                        class: 203,
                        type : RoleBase.RoleType.Monster,
                        pos: {x:1000, y:0}
                    },
                    {
                        class: 203,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 100}
                    }
                ]
            },

            {
                area: cc.rect(0, 0, 2000, 640),
                street: cc.rect(0, 0, 2000, 220),
                heroPosition: cc.p(300, 110),
                warningLine : 400,

                monsters: [
                    {
                        class: 203,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 0}
                    },
                    {
                        class: 204,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 50}
                    },
                    {
                        class: 203,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 100}
                    }
                ]
            },

            {
                area: cc.rect(2000, 0, 2000, 640),
                street: cc.rect(2000, 0, 2000, 220),
                heroPosition: cc.p(300, 110),
                warningLine : 400,

                chat: [
                    {
                        name: "Archer",
                        text: "哼哼，你来啦！",
                        side: DialogPanel.Side.Right,
                        image: "images/chat/archer.png"
                    },
                    {
                        name: "Saber",
                        text: "原来是你。。。",
                        side: DialogPanel.Side.Left,
                        image: "images/chat/saber.png"
                    },
                    {
                        name: "Archer",
                        text: "打我呀打我呀",
                        side: DialogPanel.Side.Right,
                        image: "images/chat/archer.png"
                    },
                    {
                        name: "Saber",
                        text: "_(:з」∠)_",
                        side: DialogPanel.Side.Left,
                        image: "images/chat/saber.png"
                    }
                ],

                monsters: [
                    {
                        class: 204,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 25}
                    },
                    {
                        class: 205,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 75}
                    },
                    {
                        class: 204,
                        type : RoleBase.RoleType.Monster,
                        pos: {x: 1000, y: 0}
                    },
                    {
                        class: Caster,
                        type : RoleBase.RoleType.Boss,
                        pos: {x: 1500, y: 100}
                    }
                ]
            }
        ]
    },

    ctor: function() {
        this._super("senlin");
        this.setBackgroundMusic(this.status.music);
    },

    onEnter: function() {
        this._super();

        this.play(this.status);
    },

    onExit: function() {
        this._super();
    }
});

