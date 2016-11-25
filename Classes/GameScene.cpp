#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LevelSelection.h"



USING_NS_CC;

using namespace cocostudio::timeline;

Sprite* indexer;
RobotR robot;
int countForAnim = 0;
bool editing = true;
bool finished = false;
Node* rootNodeUNMANAGED;
ui::Layout* panelTools;
ui::Layout* panelWork;
Vector<ui::Button*> botones;
void winGame()
{
    Sprite* star = (Sprite*)rootNodeUNMANAGED->getChildByName("star");
    DelayTime* time = DelayTime::create(0.4f);
    ScaleBy* big = ScaleBy::create(0.4f, 3.f);
    ScaleBy* small = ScaleBy::create(0.4f, 0.f);
    Sequence* sec = Sequence::create(time,big,small, NULL);
    star->runAction(sec);
    panelWork->unschedule("anims");
    finished = true;
    //Change scene
    panelWork->scheduleOnce([=](float dt)
    {
        
        rootNodeUNMANAGED->getParent()->stopAllActions();
        botones.clear();
        editing = true;
        countForAnim = 0;
        Scene* escena = LevelSelection::createScene();
        Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, escena));
    }, 1.f, "chan");
}
void updateButtons()
{
    
	for (int i = 0; i < botones.size(); i++)
	{
		if (botones.at(i)->getTag() == (int)ButtonTypes::Delete)
		{
			botones.at(i)->runAction(RemoveSelf::create(true));
			botones.erase(i);
			i--;
		}
		else
		{
			int btnPosX = 90 * (i % 4) + 50;
			int btnPosY = -90 * (i / 4) + 350;
			//botones.at(i)->setPosition(Vec2(btnPosX, btnPosY));
			//RELOCATION TEST
			MoveTo* move = MoveTo::create(0.125f, Vec2(btnPosX, btnPosY));
            botones.at(i)->stopAllActions();
			botones.at(i)->runAction(move);
		}
	}
}
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    finished = false;
    botones.clear();
    editing = true;
    countForAnim = 0;
    
    auto rootNode = CSLoader::createNode("res/MainScene.csb");
    rootNodeUNMANAGED = rootNode;

    addChild(rootNode);
    
    int lev = UserDefault::getInstance()->getIntegerForKey("lvl");
    
	map = MapR(rootNode, levels[lev]);
	robot = RobotR(rootNode,levels[lev]);
	
	rootNode->getChildByName("bg")->setGlobalZOrder(-100000);
	

    //Home button
    ui::Button* home = (ui::Button*)rootNode->getChildByName("home");
    home->setGlobalZOrder(5.f);
    home->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            Scene* escena = LevelSelection::createScene();
            Director::getInstance()->replaceScene(TransitionFadeBL::create(0.2f, escena));
        }
    });
	//Button config
	panelTools = (ui::Layout*)rootNode->getChildByName("panelTools");
	panelWork = (ui::Layout*)rootNode->getChildByName("panelWork");
	//INDEXER
	indexer = (Sprite*)rootNode->getChildByName("panelWork")->getChildByName("indexer");
	rootNode->getChildByName("panelWork")->setGlobalZOrder(-2.f);
	indexer->setGlobalZOrder(-1.f);
	indexer->setPosition(50, 350);
	//BUTTTONS

	ui::Button* rightBtn = (ui::Button*)panelTools->getChildByName("rightBtn");
	ui::Button* leftBtn = (ui::Button*)panelTools->getChildByName("leftBtn");
	ui::Button* upBtn = (ui::Button*)panelTools->getChildByName("upBtn");
	ui::Button* jmpLBtn = (ui::Button*)panelTools->getChildByName("jmpLBtn");
	ui::Button* jmpRBtn = (ui::Button*)panelTools->getChildByName("jmpRBtn");
    ui::Button* jmpLDBtn = (ui::Button*)panelTools->getChildByName("jmpLDBtn");
    ui::Button* jmpRDBtn = (ui::Button*)panelTools->getChildByName("jmpRDBtn");
    ui::Button* reloadBtn = (ui::Button*)rootNode->getChildByName("panelWork")->getChildByName("reloadBtn");
	ui::Button* playBtn = (ui::Button*)rootNode->getChildByName("panelWork")->getChildByName("playBtn");
	playBtn->setGlobalZOrder(2);

	//RIGHT BUTTON
	rightBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)  
	{
		if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
		{
			ui::Button* btnA = ui::Button::create("res/Sprites/right.png", "res/Sprites/right.png");
			btnA->setTag(ButtonTypes::RightB);
			botones.pushBack(btnA);
			panelWork->addChild(btnA);
			btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED && editing)
				{
					((Node*)sender)->setTag((int)ButtonTypes::Delete);
					updateButtons();
				}
			});
			updateButtons();
		}
	});
	//LEFT BUTTON
	leftBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing )
		{
			ui::Button* btnA = ui::Button::create("res/Sprites/left.png", "res/Sprites/left.png");
			btnA->setTag(ButtonTypes::LeftB);
			botones.pushBack(btnA);
			panelWork->addChild(btnA);
			btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED && editing)
				{
					((Node*)sender)->setTag((int)ButtonTypes::Delete);
					updateButtons();
				}
			});
			updateButtons();
		}
	});
	//UP BUTTON
	upBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
		{
			ui::Button* btnA = ui::Button::create("res/Sprites/up.png", "res/Sprites/up.png");
			btnA->setTag(ButtonTypes::UpB);
			botones.pushBack(btnA);
			panelWork->addChild(btnA);
			btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED && editing)
				{
					((Node*)sender)->setTag((int)ButtonTypes::Delete);
					updateButtons();
				}
			});
			updateButtons();
		}
	});
	//JMPL BUTTON
	jmpLBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
		{
			ui::Button* btnA = ui::Button::create("res/Sprites/jmpLeft.png", "res/Sprites/jmpLeft.png");
			btnA->setTag(ButtonTypes::JumpLeftB);
			botones.pushBack(btnA);
			panelWork->addChild(btnA);
			btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED && editing)
				{
					((Node*)sender)->setTag((int)ButtonTypes::Delete);
					updateButtons();
				}
			});
			updateButtons();
		}
	});
	//JMPR BUTTON
	jmpRBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
		{
			ui::Button* btnA = ui::Button::create("res/Sprites/jmpRight.png",
                                                  "res/Sprites/jmpRight.png");
			btnA->setTag(ButtonTypes::JumpRightB);
			botones.pushBack(btnA);
			panelWork->addChild(btnA);
			btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED && editing)
				{
					((Node*)sender)->setTag((int)ButtonTypes::Delete);
					updateButtons();
				}
			});
			updateButtons();
		}
	});
    //JMPL BUTTON DOUBLE
    jmpLDBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
        {
            ui::Button* btnA = ui::Button::create("res/Sprites/jmpLeftDouble.png",
                                                  "res/Sprites/jmpLeftDouble.png");
            btnA->setTag(ButtonTypes::JumpDoubleLeftB);
            botones.pushBack(btnA);
            panelWork->addChild(btnA);
            btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
            {
                if (type == ui::Widget::TouchEventType::ENDED && editing)
                {
                    ((Node*)sender)->setTag((int)ButtonTypes::Delete);
                        updateButtons();
                }
            });
            updateButtons();
        }
    });
    //JMPR BUTTON DOUBLE
    jmpRDBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED && botones.size() < 16 && editing)
        {
            ui::Button* btnA = ui::Button::create("res/Sprites/jmpRightDouble.png",
                                                  "res/Sprites/jmpRightDouble.png");
            btnA->setTag(ButtonTypes::JumpDoubleRightB);
            botones.pushBack(btnA);
            panelWork->addChild(btnA);
            btnA->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
            {
                if (type == ui::Widget::TouchEventType::ENDED && editing)
                {
                    ((Node*)sender)->setTag((int)ButtonTypes::Delete);
                    updateButtons();
                }
            });
            updateButtons();
       }
   });
    //PLAY BUTTON
    playBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (editing)
			{
				editing = false;
				countForAnim = 0;
                
				panelWork->schedule([=](float dt)
				{
                    if(!finished)
                    {
                        switch ((ButtonTypes)botones.at(countForAnim)->getTag())
                        {
                        case ButtonTypes::RightB:
                            robot.Move(Directions::Right);
                            break;
                        case ButtonTypes::LeftB:
                            robot.Move(Directions::Left);
                            break;
                        case ButtonTypes::UpB:
                            robot.Jump(Directions::Up);
                                if(robot.isForWin(true))
                                    winGame();
                            break;
                        case ButtonTypes::JumpRightB:
                            robot.Jump(Directions::Right);
                            break;
                        case ButtonTypes::JumpLeftB:
                            robot.Jump(Directions::Left);
                            break;
                        case ButtonTypes::JumpDoubleRightB:
                                robot.Jump(Directions::DoubleRight);
                            break;
                        case ButtonTypes::JumpDoubleLeftB:
                                robot.Jump(Directions::DoubleLeft);
                            break;
                        }
                        //Moving indexer
                        int indexerPosX = 90 * (countForAnim % 4) + 50;
                        int indexerPosY = -90 * (countForAnim / 4) + 350;
                        MoveTo* move = MoveTo::create(0.25f, Vec2(indexerPosX, indexerPosY));
                        EaseSineInOut* ease = EaseSineInOut::create(move);
                        indexer->runAction(ease);
                        indexer->setOpacity(255);
                        
                        if(robot.isForWin())
                            winGame();
                        countForAnim++;
                    }
				}, 1.5f, botones.size()-1.0, 0.f, "anims");
			}
		}
	});
    //RELOAD BUTTON
    reloadBtn->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            rootNodeUNMANAGED->getParent()->stopAllActions();
            botones.clear();
            editing = true;
            countForAnim = 0;
            Scene* scene = GameScene::createScene();
            TransitionFade* trans = TransitionFade::create(0.2f, scene);
            Director::getInstance()->replaceScene(trans);
        }
    });
    return true;
}

