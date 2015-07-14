#include "HelloWorldScene.h"
#include "SFGameNativeInterface.h"


USING_NS_CC;
cocos2d::LabelTTF* resultText =  NULL;
cocos2d::LabelTTF* stateText =  NULL;

bool bLogined = false;

//支付回调类
class SFNativeIPayResulBackImp : public SFNativeIPayResulBack
{
	virtual void onCanceled(const char* remain)
	{
		resultText->setString("支付取消");
	}
	virtual void onFailed(const char* remain)
	{
		resultText->setString("支付失败");
	}
	virtual void onSuccess(const char* orderNo)
	{
		CCLog("ss");
		resultText->setString("支付成功");
	}

};

//退出回调类
class SFGameExitCallBackImpl : public SFNativeGameExitCallBack
{
	virtual void onGameExit(bool result)
	{

	//result:false 代表SDK取消退出
	if (!result) {
		return;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}


};

//支付回调
SFNativeIPayResulBackImp payCallback = SFNativeIPayResulBackImp();
//退出回调
SFGameExitCallBackImpl exitCallback = SFGameExitCallBackImpl();

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	resultText = NULL;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	

	auto pay0Label = LabelTTF::create("计费点0", "宋体", 40);
	

	CCMenuItemLabel* pay0labelItem = CCMenuItemLabel::create(pay0Label,
		this, menu_selector(HelloWorld::menuPay0Callback));
	CCMenu* pay0labelMenu = CCMenu::create(pay0labelItem, NULL);
	pay0labelMenu->setPosition(ccp(100, 120));
	addChild(pay0labelMenu, 2);

	auto pay1Label = LabelTTF::create("计费点1", "宋体", 40);

	CCMenuItemLabel* pay1labelItem = CCMenuItemLabel::create(pay1Label,
		this, menu_selector(HelloWorld::menuPay1Callback));
	CCMenu* pay1labelMenu = CCMenu::create(pay1labelItem, NULL);
	pay1labelMenu->setPosition(ccp(100, 170));
	addChild(pay1labelMenu, 2);


	auto musicLabel = LabelTTF::create("音效", "宋体", 40);

	CCMenuItemLabel* musiclabelItem = CCMenuItemLabel::create(musicLabel,
		this, menu_selector(HelloWorld::menuMusicCallback));
	CCMenu* musiclabelMenu = CCMenu::create(musiclabelItem, NULL);
	musiclabelMenu->setPosition(ccp(100, 220));
	addChild(musiclabelMenu, 2);

	auto exitLabel = LabelTTF::create("退出", "宋体", 40);

	CCMenuItemLabel* exitlabelItem = CCMenuItemLabel::create(exitLabel,
		this, menu_selector(HelloWorld::menuExitCallback));
	CCMenu* exitlabelMenu = CCMenu::create(exitlabelItem, NULL);
	exitlabelMenu->setPosition(ccp(100, 270));
	addChild(exitlabelMenu, 2);
    /////////////////////////////
    // 3. add your codes below...
    
	resultText = LabelTTF::create("", "宋体", 30);
	resultText->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - resultText->getContentSize().height - 20));

	// add the label as a child to this layer
	this->addChild(resultText, 1);

	stateText = LabelTTF::create("", "宋体", 30);
	stateText->setColor(Color3B::RED);
	stateText->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - resultText->getContentSize().height - 60));

	// add the label as a child to this layer
	this->addChild(stateText, 1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuPay0Callback(Ref* pSender)
{
	//设置支付回调
	SFGameNativeInterface::setSFIPayResulBack(&payCallback);
	//支付，参数为计费点编号
	SFGameNativeInterface::pay("0");
}

void HelloWorld::menuPay1Callback(Ref* pSender)
{
	//设置支付回调
	SFGameNativeInterface::setSFIPayResulBack(&payCallback);
	//支付，参数为计费点编号
	SFGameNativeInterface::pay("1");
}




void HelloWorld::menuMusicCallback(Ref* pSender)
{
//移动基地SDK，进入游戏时必须使用这个函数进行判断音乐是否开关
	if (SFGameNativeInterface::isMusicEnabled()) {
		stateText->setString("音效为开！");
	} else {
		stateText->setString("音效为关！");
	}

}


void HelloWorld::menuExitCallback(Ref* pSender)
{
	SFGameNativeInterface::setSFGameExitCallBack(&exitCallback);
	SFGameNativeInterface::onExit();
}


Scene* ExitPopu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ExitPopu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool ExitPopu::init() {

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	resultText = NULL;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* background = Sprite::create();
    background->setColor(Color3B::GREEN);
//    background->setContentSize(cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2));
    background->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    addChild(background, 1);

	auto exitLabel = LabelTTF::create("退出", "宋体", 50);

	CCMenuItemLabel* exitlabelItem = CCMenuItemLabel::create(exitLabel,
		this, menu_selector(ExitPopu::menuExitCallback));
	CCMenu* exitlabelMenu = CCMenu::create(exitlabelItem, NULL);
	exitlabelMenu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	addChild(exitlabelMenu, 2);


    return true;
}


void ExitPopu::menuExitCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
