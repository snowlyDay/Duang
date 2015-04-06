
#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "cocos2d.h"

USING_NS_CC;
class GameScene : public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void updateCustom(float dt);
	void update(float dt);
private:
	Sprite* leftHeng;
	Sprite* rightHeng;
	Vec2 leftPos;
	Vec2 rightPos;
	float speed;
	bool isRight;
	bool isJumping;


	MotionStreak *streak;
	Sprite *player;
	void jumpCall();
	bool onTouchBegan(Touch *it, Event *eve);
	void onTouchMove(Touch *it, Event *eve);
	void onTouchEnd(Touch *it, Event *eve);
};

#endif