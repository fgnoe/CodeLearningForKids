#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "MapR.h"
#include "RobotR.h"

enum ButtonTypes : int
{
	LeftB = 15,
	RightB,
	UpB,
	DoubleUpB,
	JumpRightB,
	JumpLeftB,
	JumpDoubleRightB,
	JumpDoubleLeftB,
	Delete
};
class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    int levels[2][10][8] =
    {
        {
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 3, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 1, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 2, 0, 0, 0, 1, 0 },
            { 1, 1, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        {
            { 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 1, 0 },
            { 1, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 2, 0, 0, 1 },
            { 0, 0, 1, 1, 1, 0, 1, 1 },
            { 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 1, 1, 1, 0, 1, 0 }
        }
    };
    void backToOriginalFrame(float dt);
	void scheduleTesting(float dt);
	
	MapR map;
};

#endif // __HELLOWORLD_SCENE_H__
