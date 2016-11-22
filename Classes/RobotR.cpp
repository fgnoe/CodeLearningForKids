#include "RobotR.h"

Sprite* spriteUNMANAGED;

ParticleSystemQuad* particleUNMANAGED;

RobotR::RobotR(Node* rootNode,int mp[10][8])
{
	this->rootNode = rootNode;
	sprite = rootNode->getChildByName<Sprite*>("robot");
	analizeCells(mp);
	particleSystem = ParticleSystemQuad::create("particle.plist");
	particleSystem->setEmissionRate(0);
	particleSystem->setScale(0.3f);
	particleSystem->setPosition(Vec2(0, 30));
	particleSystem->setGlobalZOrder(-1);
	sprite->addChild(particleSystem);
	spriteUNMANAGED = sprite;
	particleUNMANAGED = particleSystem;
	orientation = Directions::Right;
}
void RobotR::RunAnimation()
{
	Vector<SpriteFrame*> animFrames(2);
	char str[100] = { 0 };
	for (int i = 1; i <= 2; i++)
	{
		sprintf(str, "sprites/robot%d.png", i);
		SpriteFrame* frame = SpriteFrame::create(str, Rect(0, 0, 80, 80));
		animFrames.pushBack(frame);
	}
	Animation* runingAnimation = Animation::createWithSpriteFrames(animFrames, 0.15f,1);
	Animate* animationAction = Animate::create(runingAnimation);
	sprite->runAction(RepeatForever::create(animationAction));
}
bool RobotR::Jump(Directions direction)///////////////////////////////////JUMP
{
	switch (direction)
	{
	case Directions::Up:////////////Jump UP
	{
		if (canJumpUp() == Movements::Ok)
		{
			sprite->stopAllActions();
			sprite->setTexture("sprites/robot3.png");
			sprite->runAction(JumpBy::create(1.f, Vec2::ZERO, 80, 1));
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				spriteUNMANAGED->setTexture("sprites/robot1.png");
			}, 1.f, "backToOriginalFrame");
		}
	}
		break;
	case Directions::DoubleUp:////////Jump DOUBLE UP
	{
		if (canJumpDoubleUp() == Movements::Ok)
		{
			sprite->stopAllActions();
			sprite->setTexture("sprites/robot3.png");
			sprite->runAction(JumpBy::create(2.f, Vec2::ZERO, 160, 1));
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				spriteUNMANAGED->setTexture("sprites/robot1.png");
			}, 2.f, "backToOriginalFrame");
		}
	}
		break;
	case Directions::Right:///////////////Jump RIGHT
	{
		if (canJumpRight() == Movements::Ok)
		{
			sprite->stopAllActions();
			if (orientation == Directions::Left)
			{
				sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
				orientation = Directions::Right;
			}
			sprite->setTexture("sprites/robot3.png");
			sprite->runAction(JumpBy::create(0.7f, Vec2(0, 80), 55, 1));
			x++;
			y--;
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				spriteUNMANAGED->setTexture("sprites/robot1.png");
				particleUNMANAGED->setEmissionRate(100);
				EaseSineInOut* sineMove = EaseSineInOut::create(MoveBy::create(1.f, Vec2(80, 0)));
				sprite->runAction(sineMove);
			}, 0.38f, "backToOriginalFrame");
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				particleUNMANAGED->setEmissionRate(0);
			}, 0.7f, "backToNoEmision");
		}
        else if(canJumpRight()  == Movements::Fall)
        {
            if (orientation == Directions::Left)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Right;
            }
            float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(80,-80*(nBlocksFall - y - 1)), 80, 1);
            sprite->runAction(fall);
            y += nBlocksFall - y - 1;
            x++;
            return true;
        }
	}
		break;
	case Directions::Left://///////////Jump Left
	{
		if (canJumpLeft() == Movements::Ok)
		{
			sprite->stopAllActions();
			if (orientation == Directions::Right)
			{
				spriteUNMANAGED->runAction(RotateTo::create(0.3f, Vec3(0, -180, 0)));
				orientation = Directions::Left;
			}

			sprite->setTexture("sprites/robot3.png");
			sprite->runAction(JumpBy::create(0.7f, Vec2(0, 80), 55, 1));
			x--;
			y--;
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				spriteUNMANAGED->setTexture("sprites/robot1.png");
				particleUNMANAGED->setEmissionRate(100);
				EaseSineInOut* sineMove = EaseSineInOut::create(MoveBy::create(1.f, Vec2(-80, 0)));
				sprite->runAction(sineMove);
			}, 0.38f, "backToOriginalFrame");
			spriteUNMANAGED->scheduleOnce([=](float dt)
			{
				particleUNMANAGED->setEmissionRate(0);
			}, 0.7f, "backToNoEmision");
		}
        else if(canJumpLeft()  == Movements::Fall)
        {
            if (orientation == Directions::Right)
            {
                spriteUNMANAGED->runAction(RotateTo::create(0.3f, Vec3(0, -180, 0)));
                orientation = Directions::Left;
            }
            float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(-80,-80*(nBlocksFall - y - 1)), 80, 1);
            sprite->runAction(fall);
            y += nBlocksFall - y - 1;
            x--;
            return true;
        }
	}
		break;////////////////////////Jump double right
    case Directions::DoubleRight:
    {
        switch (canDoubleJumpRight())
        {
        case Movements::Ok:
            sprite->stopAllActions();
            if (orientation == Directions::Left)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Right;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.7f, Vec2(80*3, 0 ), 55, 1));
            x += 3;
                particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.38f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.7f, "backToNoEmision");
            break;
            case Movements::JustOneStep:
            {
                sprite->stopAllActions();
                if (orientation == Directions::Left)
                {
                    sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                    orientation = Directions::Right;
                }
                sprite->setTexture("sprites/robot3.png");
                sprite->runAction(JumpBy::create(0.5f, Vec2(80, 0 ), 55, 1));
                x++;
                particleUNMANAGED->setEmissionRate(100);
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  spriteUNMANAGED->setTexture("sprites/robot1.png");
                                              }, 0.5f, "backToOriginalFrame");
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  particleUNMANAGED->setEmissionRate(0);
                                              }, 0.5f, "backToNoEmision");
            }
                break;
            case Movements::JustTwoSteps:
            {
                sprite->stopAllActions();
                if (orientation == Directions::Left)
                {
                    sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                    orientation = Directions::Right;
                }
                sprite->setTexture("sprites/robot3.png");
                sprite->runAction(JumpBy::create(0.8, Vec2(160, 0 ), 55, 1));
                x += 2;
                particleUNMANAGED->setEmissionRate(100);
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  spriteUNMANAGED->setTexture("sprites/robot1.png");
                                              }, 0.8f, "backToOriginalFrame");
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  particleUNMANAGED->setEmissionRate(0);
                                              }, 0.8f, "backToNoEmision");
                break;
            }
            case Movements::Fall:
            {
                sprite->stopAllActions();
                if (orientation == Directions::Left)
                {
                    sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                    orientation = Directions::Right;
                }
                sprite->setTexture("sprites/robot3.png");
                sprite->runAction(JumpBy::create(0.3f, Vec2(80, 0 ), 55, 1));
                particleUNMANAGED->setEmissionRate(100);
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  spriteUNMANAGED->setTexture("sprites/robot1.png");
                                              }, 0.5f, "backToOriginalFrame");
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  particleUNMANAGED->setEmissionRate(0);
                                              }, 0.3f, "backToNoEmision");
                float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
                JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
                sprite->runAction(Sequence::create(DelayTime::create(0.3f),fall, NULL));
                y += nBlocksFall - y - 1;
                x++;
                return true;
            }
                break;
            case Movements::FallAtBlock2:
            {
                sprite->stopAllActions();
                if (orientation == Directions::Left)
                {
                    sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                    orientation = Directions::Right;
                }
                sprite->setTexture("sprites/robot3.png");
                sprite->runAction(JumpBy::create(0.6f, Vec2(160, 0 ), 55, 1));
                particleUNMANAGED->setEmissionRate(100);
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  spriteUNMANAGED->setTexture("sprites/robot1.png");
                                              }, 0.8f, "backToOriginalFrame");
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  particleUNMANAGED->setEmissionRate(0);
                                              }, 0.3f, "backToNoEmision");
                float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
                JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
                sprite->runAction(Sequence::create(DelayTime::create(0.6f),fall, NULL));
                y += nBlocksFall - y - 1;
                x+=2;
                return true;
            }
                break;
            case Movements::FallAtBlock3:
            {
                sprite->stopAllActions();
                if (orientation == Directions::Left)
                {
                    sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                    orientation = Directions::Right;
                }
                sprite->setTexture("sprites/robot3.png");
                sprite->runAction(JumpBy::create(0.6, Vec2(240, 0 ), 55, 1));
                particleUNMANAGED->setEmissionRate(100);
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  spriteUNMANAGED->setTexture("sprites/robot1.png");
                                              }, 0.7f, "backToOriginalFrame");
                spriteUNMANAGED->scheduleOnce([=](float dt)
                                              {
                                                  particleUNMANAGED->setEmissionRate(0);
                                              }, 0.8f, "backToNoEmision");
                float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
                JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
                sprite->runAction(Sequence::create(DelayTime::create(0.6f),fall, NULL));
                y += nBlocksFall - y - 1;
                x+=3;
                return true;
            }
                break;

        }
        
    }
        break;
    case Directions::DoubleLeft:///////Jump double left
        switch (canDoubleJumpLeft())
    {
        case Movements::Ok:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.7f, Vec2(-80*3, 0 ), 55, 1));
            x -= 3;
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.38f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.7f, "backToNoEmision");
        }
            break;
        case Movements::JustOneStep:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.5f, Vec2(-80, 0 ), 55, 1));
            x --;
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.5f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.5f, "backToNoEmision");
        }
            break;
        case Movements::JustTwoSteps:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.7f, Vec2(-160, 0 ), 55, 1));
            x -= 2;
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.5f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.5f, "backToNoEmision");
            break;
        }
        case Movements::Fall:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.3f, Vec2(-80, 0 ), 55, 1));
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.5f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.3f, "backToNoEmision");
            float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
            sprite->runAction(Sequence::create(DelayTime::create(0.3f),fall, NULL));
            y += nBlocksFall - y - 1;
            x--;
            return true;
        }
            break;
        case Movements::FallAtBlock2:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.5f, Vec2(-160, 0 ), 55, 1));
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.5f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.3f, "backToNoEmision");
            float tiem = ((nBlocksFall - y - 1)/7.0f * 1.4f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
            sprite->runAction(Sequence::create(DelayTime::create(0.5f),fall, NULL));
            y += nBlocksFall - y - 1;
            x-=2;
            return true;
        }
            break;
        case Movements::FallAtBlock3:
        {
            sprite->stopAllActions();
            if (orientation == Directions::Right)
            {
                sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
                orientation = Directions::Left;
            }
            sprite->setTexture("sprites/robot3.png");
            sprite->runAction(JumpBy::create(0.7f, Vec2(-240, 0 ), 55, 1));
            particleUNMANAGED->setEmissionRate(100);
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              spriteUNMANAGED->setTexture("sprites/robot1.png");
                                          }, 0.7f, "backToOriginalFrame");
            spriteUNMANAGED->scheduleOnce([=](float dt)
                                          {
                                              particleUNMANAGED->setEmissionRate(0);
                                          }, 0.7f, "backToNoEmision");
            float tiem = ((nBlocksFall - y - 1)/7.0f * 0.6f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
            sprite->runAction(Sequence::create(DelayTime::create(0.7f),fall, NULL));
            y += nBlocksFall - y - 1;
            x-=3;
            return true;
        }
            break;
    }
        break;
	default:
		break;
	}
	return false;
}
bool RobotR::Move(Directions direction)//////////////////////////////////MOVE
{
	Movements mov;
	switch (direction)
	{
        case Directions::Right://///////////////Move to RIGHT
        {
		sprite->stopAllActions();
		mov = canGoToRight();
		if (orientation == Directions::Left)
		{
			sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
			orientation = Directions::Right;
		}
		if (mov == Movements::Ok)
		{
			RunAnimation();
			sprite->runAction(MoveBy::create(1.3f, Vec2(80, 0)));
			x++;
			return true;
		}
        else if(mov == Movements::Fall)
        {
            RunAnimation();
            MoveBy* desplaz = MoveBy::create(0.7f, Vec2(80,0));
            float tiemp = ((nBlocksFall - y - 1)/3.0f * 0.4f);
            JumpBy* fall = JumpBy::create(tiemp, Vec2(0,-80* (nBlocksFall - y - 1)), 0, 1);
            Sequence* secuencua = Sequence::create(desplaz, fall, NULL);
            sprite->runAction(secuencua);
            y += nBlocksFall - y - 1;
            x++;
            return true;
        }
	}
            break;
        case Directions::Left://////////////////Move to LEFT
        {
		sprite->stopAllActions();
		mov = canGoToLeft();
		if (orientation == Directions::Right)
		{
			sprite->runAction(RotateBy::create(0.3f, Vec3(0, 180, 0)));
			orientation = Directions::Left;
		}
		if (mov == Movements::Ok)
		{
			RunAnimation();
			sprite->runAction(MoveBy::create(1.3f, Vec2(-80, 0)));
			x--;
			return true;
		}
        else if(mov == Movements::Fall)
        {
            RunAnimation();
            MoveBy* desplaz = MoveBy::create(0.7f, Vec2(-80,0));
            float tiem = ((nBlocksFall - y - 1)/3.0f * 0.4f);
            JumpBy* fall = JumpBy::create(tiem, Vec2(0,-80*(nBlocksFall - y - 1)), 0, 1);
            Sequence* secuencua = Sequence::create(desplaz, fall, NULL);
            sprite->runAction(secuencua);
            y += nBlocksFall - y - 1;
            x--;
            return true;
        }
	}
            break;
        default:
            break;
	}
	return false;
}
Movements RobotR::canGoToRight()
{
	if (x == mapSizeX-1)
		return Movements::NoPass;
	if (map[y][x + 1] == 1)
		return Movements::NoPass;
	if (map[y + 1][x + 1] == 1)
		return Movements::Ok;
	for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 1] == 0; nBlocksFall++);
	return Movements::Fall;

}
Movements RobotR::canGoToLeft()
{
	if (x == 0)
		return Movements::NoPass;
	if (map[y][x - 1] == 1)
		return Movements::NoPass;
	if (map[y + 1][x - 1] == 1)
		return Movements::Ok;
	for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x-1] == 0; nBlocksFall++);
	return Movements::Fall;
	
}
Movements RobotR::canJumpUp()
{
	if (map[y - 1][x] == 0)
		return Movements::Ok;
	return Movements::NoPass;
}
Movements RobotR::canJumpDoubleUp()
{
	if (map[y - 1][x] == 0  && map[y - 2][x] == 0)
		return Movements::Ok;
	if (map[y - 1][x] == 0)
		return Movements::Fall;
	return Movements::NoPass;
}
Movements RobotR::canJumpRight()
{
	if (x == mapSizeX - 1)
	{
		if (map[y - 1][x] == 0)
			return Movements::JumpToWall;
		return Movements::NoPass;
	}
	if (map[y - 1][x] == 0 && map[y - 1][x + 1] == 0 && map[y][x + 1] == 1)
		return Movements::Ok;
	if (map[y - 1][x] == 0 && map[y - 1][x + 1] == 1)
		return Movements::JumpToWall;
	if (map[y - 1][x] == 1)
		return Movements::NoPass;
	for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 1] == 0; nBlocksFall++);
	return Movements::Fall;
}
Movements RobotR::canJumpLeft()
{
	if (x == 0)
	{
		if (map[y - 1][x] == 0)
			return Movements::JumpToWall;
		return Movements::NoPass;
	}
	if (map[y - 1][x] == 0 && map[y - 1][x - 1] == 0 && map[y][x - 1] == 1)
		return Movements::Ok;
	if (map[y - 1][x] == 0 && map[y - 1][x - 1] == 1)
		return Movements::JumpToWall;
	if (map[y - 1][x] == 1)
		return Movements::NoPass;
	for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 1] == 0; nBlocksFall++);
	return Movements::Fall;
}
Movements RobotR::canDoubleJumpLeft()
{
    if (x == 0)
    {
        if (map[y - 1][x] == 0)
            return Movements::JumpToWall;
        return Movements::NoPass;
    }
    ///////////LIMIT CORRECTION
    {
        if(x == 1)
        {
            if(map[y][x-1] + map[y-1][x-1] + map[y-1][x] == 0)
            {
                if(map[y+1][x-1] == 0)
                {
                    for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 1] == 0;nBlocksFall++);
                    return Movements::Fall;
                }
                return JustOneStep;
                    
            }
            return Movements::JumpToWall;
        }
        if(x == 2)
        {
             if(map[y][x-1] + map[y-1][x-1] + map[y-1][x] == 0)
             {
                 if(map[y][x-2] + map[y-1][x-2] == 0)
                 {
                     if(map[y+1][x-2] == 1)
                         return JustTwoSteps;
                     for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 2] == 0;nBlocksFall++);
                     return Movements::FallAtBlock2;
                 }
                 if(map[y+1][x-1] == 1)
                     return JustOneStep;
                 for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 1] == 0;nBlocksFall++);
                 return Fall;
                 
             }
            return JumpToWall;
        }
    }
    if (((map[y-1][x] + map[y-1][x-1] + map[y-1][x-2] + map[y-1][x-3]) +
        (map[y][x-1] + map[y][x-2] + map[y][x-3])) == 0)
    {
        if(map[y+1][x-3] == 1)
            return Movements::Ok;
        for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 3] == 0;
             nBlocksFall++);
        return Movements::FallAtBlock3;
    }
    if(map[y-1][x] + map[y-1][x-1] + map[y][x-1] != 0)
        return Movements::JumpToWall;
    if(map[y][x-2] + map[y-1][x-2] != 0)
    {
        if(map[y+1][x-1]==0)
        {
            for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 1] == 0;
                 nBlocksFall++);
            return Movements::Fall;
        }
        return Movements::JustOneStep;
    }
    if(map[y][x-3] + map[y-1][x-3] != 0)
    {
        if(map[y+1][x-2]==0)
        {
            for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 2] == 0;
                 nBlocksFall++);
            return Movements::FallAtBlock2;
        }
        return Movements::JustTwoSteps;
    }
    for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x - 3] == 0;
         nBlocksFall++);
    return Movements::Fall;
}
Movements RobotR::canDoubleJumpRight()
{
    if (x == mapSizeX-1)
    {
        if (map[y - 1][x] == 0)
            return Movements::JumpToWall;
        return Movements::NoPass;
    }
    ///////////LIMIT CORRECTION
    {
        if(x == mapSizeX-2)
        {
            if(map[y][x+1] + map[y-1][x+1] + map[y-1][x] == 0)
            {
                if(map[y+1][x+1] == 0)
                {
                    for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 1] == 0;nBlocksFall++);
                    return Movements::Fall;
                }
                return JustOneStep;
                
            }
            return Movements::JumpToWall;
        }
        if(x == mapSizeX-3)
        {
            if(map[y][x+1] + map[y-1][x+1] + map[y-1][x] == 0)
            {
                if(map[y][x+2] + map[y-1][x+2] == 0)
                {
                    if(map[y+1][x+2] == 1)
                        return JustTwoSteps;
                    for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 2] == 0;nBlocksFall++);
                    return FallAtBlock2;
                }
                if(map[y+1][x+1] == 1)
                    return JustOneStep;
                for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 1] == 0;nBlocksFall++);
                return Fall;
                
            }
            return JumpToWall;
        }
    }
    if (((map[y-1][x] + map[y-1][x+1] + map[y-1][x+2] + map[y-1][x+3]) +
         (map[y][x+1] + map[y][x+2] + map[y][x+3])) == 0)
    {
        if(map[y+1][x+3] == 1)
            return Movements::Ok;
        for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 3] == 0;
             nBlocksFall++);
        return Movements::FallAtBlock3;
    }
    if(map[y-1][x] + map[y-1][x+1] + map[y][x+1] != 0)
        return Movements::JumpToWall;
    if(map[y][x+2] + map[y-1][x+2] != 0)
    {
        if(map[y+1][x+1]==0)
        {
            for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 1] == 0;
                 nBlocksFall++);
            return Movements::Fall;
        }
        return Movements::JustOneStep;
    }
    if(map[y][x+3] + map[y-1][x+3] != 0)
    {
        if(map[y+1][x+2]==0)
        {
            for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 2] == 0;
                 nBlocksFall++);
            return Movements::FallAtBlock2;
        }
        return Movements::JustTwoSteps;
    }
    for (nBlocksFall = y + 1; nBlocksFall < mapSizeY && map[nBlocksFall][x + 3] == 0;
         nBlocksFall++);
    return Movements::Fall;
}
