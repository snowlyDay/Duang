#include "GameScene.h"

Scene *GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}


bool GameScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visiable = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	this->addChild(bg);
	auto left = Sprite::create("left.png");
	left->setAnchorPoint(Vec2(0, 0));
	left->setPosition(Vec2(0, 0));
	this->addChild(left);
	
	auto right = Sprite::create("left.png");
	right->setAnchorPoint(Vec2(1, 0));
	right->setPosition(Vec2(visiable.width, 0));
	this->addChild(right);


	leftPos = Vec2(left->getContentSize().width, visiable.height / 2);
	leftHeng = Sprite::create("heng.png");
	leftHeng->setAnchorPoint(Vec2(0, 0));
	leftHeng->setPosition(leftPos);
	this->addChild(leftHeng);

	rightPos = Vec2(visiable.width - right->getContentSize().width, visiable.height / 2);
	rightHeng = Sprite::create("heng.png");
	rightHeng->setAnchorPoint(Vec2(1, 0));
	rightHeng->setPosition(rightPos);
	this->addChild(rightHeng);
	
	player = Sprite::create("9.png");
	player->setPosition(left->getContentSize().width + player->getContentSize().width / 2, visiable.height / 4);
	this->addChild(player);

	streak = MotionStreak::create(0.8f, 0.5, 10, Color3B::WHITE, "9.png");
	streak->setPosition(player->getPosition());

	this->addChild(streak);


	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnd, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(schedule_selector(GameScene::updateCustom), 0.1f, kRepeatForever, 0);
	scheduleUpdate();

	speed = 15;
	isRight = false;
	isJumping = false;
	return true;
}

void GameScene::update(float dt){

	if (leftPos.y > -100){
		leftPos.y -= speed;
	}

	if (rightPos.y > -100){
		rightPos.y -= speed;
	}
	rightHeng->setPosition(rightPos);
	leftHeng->setPosition(leftPos);
	streak->setPosition(player->getPosition());

}
void GameScene::updateCustom(float dt){
	
	float a = rand_0_1();
	
 if (a<0.2&&leftPos.y<-10)
	{
		leftPos.y = Director::getInstance()->getWinSize().height;
		speed += 1;
 
 }
	
	
	 if (a>0.8&&rightPos.y<-10)
	{
		rightPos.y = Director::getInstance()->getWinSize().height;
	}
	
}

void GameScene::jumpCall(){
	isJumping = false;

}
bool GameScene::onTouchBegan(Touch *th, Event *ev){
    auto pos =	th->getLocation();
	if (isJumping){
		return true; 
	}

	if (pos.x>0&&!isRight){
		auto jum = JumpTo::create(0.2, Vec2(Director::getInstance()->getWinSize().width - 100, player->getPositionY()), 100, 1);
		auto call = CallFunc::create(this, callfunc_selector(GameScene::jumpCall));
		auto seq = Sequence::create(jum, call, NULL);
		player->runAction(seq);
		isRight = true;
		isJumping = true;
	}
	else
	{
		auto jum = JumpTo::create(0.2, Vec2( 100, player->getPositionY()), 100, 1);
		isRight = false;
		auto call = CallFunc::create(this, callfunc_selector(GameScene::jumpCall));
		auto seq = Sequence::create(jum, call, NULL);
		player->runAction(seq);
		isJumping = true;
	}
	
	return true;
}

void GameScene::onTouchMove(Touch *th, Event *ev){


}

void GameScene::onTouchEnd(Touch *th, Event *ev){


}