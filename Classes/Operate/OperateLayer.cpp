#include "OperateLayer.h"

USING_NS_CC;
using namespace std;

OperateLayer::OperateLayer()
{
	global->operateLayer = this;
}

OperateLayer::~OperateLayer()
{
}

bool OperateLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF( !Layer::init() );
		//方向虚拟摇杆
		auto m_pjoystick = Joystick::create();
		m_pjoystick->setJoystick(Vec2(50, 50));
		this->addChild(m_pjoystick);

		//攻击虚拟按键
		auto visibleSize = Director::getInstance()->getVisibleSize();
		//创造attackItem图标
		auto attackItem = MenuItemImage::create("attackbuttonNormal.png", "attackbuttonSelected.png", CC_CALLBACK_1(OperateLayer::attackButton, this));

		//图标大小
		attackItem->setScale(1.5);
		//attackItem->setContentSize(Size(50,50));

		//图标放在
		attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width / 2 - 50, attackItem->getContentSize().height / 2 + 20);

		auto menu = Menu::create(attackItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 100);


		ret = true;
	}while(0);

	return ret;
}

void OperateLayer::attackButton(Ref *pSender)
{
	global->hero->onAttack(1);
}

