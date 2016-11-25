#include "LevelSelection.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"



USING_NS_CC;

using namespace cocostudio::timeline;



Scene* LevelSelection::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelSelection::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
void changeScene(int i = 0)
{
    UserDefault::getInstance()->setIntegerForKey("lvl", i);
    Scene* escena = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.4f, escena));
}
// on "init" you need to initialize your instance
bool LevelSelection::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("res/LevelSelection.csb");
    addChild(rootNode);
    Node* sv = rootNode->getChildByName("sv");
    
    ui::Button* btn1 = (ui::Button*)sv->getChildByName("btn1");
    btn1->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            changeScene(0);
        }
    });
    ui::Button* btn2 = (ui::Button*)sv->getChildByName("btn2");
    btn2->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            changeScene(1);
        }
    });
    ui::Button* btn3 = (ui::Button*)sv->getChildByName("btn3");
    btn3->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            changeScene(2);
        }
    });
    ui::Button* btn4 = (ui::Button*)sv->getChildByName("btn4");
    btn4->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            changeScene(3);
        }
    });
    ui::Button* btn5 = (ui::Button*)sv->getChildByName("btn5");
    btn5->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            changeScene(4);
        }
    });
    return true;
}

