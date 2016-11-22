#include "TileR.h"


TileR::TileR(Node* rootNode, TileType typ, float x, float y) 
{
	type = typ;
	switch (typ)
	{
	case Ground:
		sprite = Sprite::create("sprites/ground.png");
		break;
	case Star:
		sprite = Sprite::create("sprites/star.png");
		sprite->setRotation(-15.f);
		break;
	default:
		sprite = Sprite::create();
		break;
	}
	if (type == TileType::Star)
	{
		RotateBy* left = RotateBy::create(0.4f, -30.f);
		RotateBy* right = RotateBy::create(0.4f, 30.f);
		EaseSineInOut* easeLeft = EaseSineInOut::create(left);
		EaseSineInOut* easeRight = EaseSineInOut::create(right);
		Sequence* seq = Sequence::create(easeRight, easeLeft, NULL);
		sprite->runAction(RepeatForever::create(seq));
	}
	//sprite->setPosition(Vec2(x, y));
	sprite->setPosition(Vec2(RandomHelper::random_int(0,700), RandomHelper::random_int(0, 1280)));
	rootNode->addChild(sprite);

	MoveTo* move = MoveTo::create(1.f, Vec2(x, y));
	EaseSineInOut* sine = EaseSineInOut::create(move);
	sprite->runAction(sine);
}

TileR::~TileR() {}

