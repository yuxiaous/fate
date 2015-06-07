#include "SneakyButtonSkinnedBase.h"

bool SneakyButtonSkinnedBase::init() //Possible errors here
{
	bool pRet = false;
	if(Node::init()){
		this->defaultSprite = nullptr;
		this->activatedSprite = nullptr;
		this->disabledSprite = nullptr;
		this->pressSprite = nullptr;
        this->button = nullptr;
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        this->schedule(schedule_selector(SneakyButtonSkinnedBase::watchSelf));
		pRet = true;
	}
	return pRet;
}

void SneakyButtonSkinnedBase::watchSelf(float delta) //Be Careful Here
{
    if(button == nullptr) return;
    
    auto safeSetVisible = [](Sprite *sprite, bool value) {
        if(sprite) sprite->setVisible(value);
    };
    
    if (!button->getIsEnable()){
        safeSetVisible(disabledSprite, true);
        safeSetVisible(defaultSprite, false);
        safeSetVisible(pressSprite, false);
        safeSetVisible(activatedSprite, false);
    }
    else {
        safeSetVisible(disabledSprite, false);
        
		if(!button->getIsActive()){
			safeSetVisible(pressSprite, false);
            
            if(button->getValue() == 0){
                safeSetVisible(defaultSprite, true);
				safeSetVisible(activatedSprite, false);
			}
			else {
                safeSetVisible(activatedSprite, true);
                safeSetVisible(defaultSprite, false);
			}
		}
        else {
            safeSetVisible(pressSprite, true);
            safeSetVisible(defaultSprite, false);
            safeSetVisible(activatedSprite, false);
		}
	}
}

void SneakyButtonSkinnedBase::setContentSize(Size s)
{
	Node::setContentSize(s);
    
    if(defaultSprite) {
        defaultSprite->setContentSize(s);
    }
    if(button) {
        button->setRadius(s.width/2);
    }
}

void SneakyButtonSkinnedBase::setDefaultSprite(Sprite *aSprite)
{
	if(defaultSprite){
		defaultSprite->removeFromParent();
	}
	defaultSprite = aSprite; //Check again here
	if(defaultSprite){
        Size size = defaultSprite->getContentSize();
        defaultSprite->setPosition(size.width/2, size.height/2);
        
        setContentSize(size);
		addChild(defaultSprite, 0);
	}
}

void SneakyButtonSkinnedBase::setActivatedSprite(Sprite *aSprite)
{
	if(activatedSprite){
		activatedSprite->removeFromParent();
	}
	activatedSprite = aSprite;
	if(activatedSprite){
        Size size = getContentSize();
        activatedSprite->setPosition(size.width/2, size.height/2);
		addChild(activatedSprite, 1);
		
	}
}

void SneakyButtonSkinnedBase::setDisabledSprite(Sprite *aSprite)
{
	if(disabledSprite){
		disabledSprite->removeFromParent();
	}
	disabledSprite = aSprite;
	if(disabledSprite){
        Size size = getContentSize();
        disabledSprite->setPosition(size.width/2, size.height/2);
		addChild(disabledSprite, 2);
	}
}

void SneakyButtonSkinnedBase::setPressSprite(Sprite *aSprite)
{
	if(pressSprite){
		pressSprite->removeFromParent();
	}
	pressSprite = aSprite;
	if(pressSprite){
        Size size = getContentSize();
        pressSprite->setPosition(size.width/2, size.height/2);
		addChild(pressSprite, 3);
	}
}

void SneakyButtonSkinnedBase::setButton(SneakyButton *aButton)
{
	if(button){
		button->removeFromParent();
	}
	button = aButton;
	if(button){
        Size size = getContentSize();
        button->setPosition(size.width/2, size.height/2);
        
		if(defaultSprite)
            button->setRadius(defaultSprite->boundingBox().size.width/2);
        
        addChild(button, 4);
	}
}
