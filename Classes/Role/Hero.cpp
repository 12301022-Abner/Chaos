#include "Hero.h"
#include "Other\Resources.h"
Hero::Hero()
{
	global->hero = this;
}

Hero::~Hero()
{
	
}

bool Hero::init()
{
	bool ret = false;
	do
	{

		// idle��һ��ͼ 
		this->initWithSpriteFrameName(si_4IDLE0001);
		//վ��ʱ���Ŷ���
		Animation *idleAnim = this->createNomalAnimation("4IDLE%04d.png", 24, 5);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		//����
		Animation *walkAnim = this->createNomalAnimation("4RUN%04d.png", 18, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		//��ͨ����A���ֳ��к����У��ڼ���ӹ����ж�.�Լ�����ͨ������fps���Ƴ����ٶ�֮���
		Animation *attackAnima1 = this->createAttackAnimation("4ATTACK%05d.png",1,5,10);
		Animation *attackAnima2 = this->createAttackAnimation("4ATTACK%05d.png", 5, 9, 15);
		this->setNomalAttackA(Sequence::create(
			Animate::create(attackAnima1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnima2),
			Role::createIdleCallbackFunc(),
			NULL));


		//�չ�B
		Animation *attackAnimb1 = this->createAttackAnimation("4ATTACK1%04d.png", 1, 5, 10);
		Animation *attackAnimb2 = this->createAttackAnimation("4ATTACK1%04d.png", 5, 11, 15);
		this->setNomalAttackB(Sequence::create(
			Animate::create(attackAnimb1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		//�չ�C
		Animation *attackAnimc1 = this->createAttackAnimation("4ATTACK2%04d.png", 1, 4, 10);
		Animation *attackAnimc2 = this->createAttackAnimation("4ATTACK2%04d.png", 4, 7, 15);
		this->setNomalAttackC(Sequence::create(
			Animate::create(attackAnimc1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		//�չ�D
		Animation *attackAnimd1 = this->createAttackAnimation("4ATTACK3%04d.png", 1, 6, 10);
		Animation *attackAnimd2 = this->createAttackAnimation("4ATTACK3%04d.png", 6, 13, 15);
		this->setNomalAttackD(Sequence::create(
			Animate::create(attackAnima1),
			Animate::create(attackAnima2),
			Animate::create(attackAnimb1),
			Animate::create(attackAnimb2),
			Animate::create(attackAnimc1),
			Animate::create(attackAnimc2),
			Animate::create(attackAnimd1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimd2),
			Role::createIdleCallbackFunc(),
			NULL));

		//��������
		/*
		this->setComboAttack(Sequence::create(
			Animate::create(attackAnima1),
			Animate::create(attackAnima2),
			Animate::create(attackAnimb1),
			Animate::create(attackAnimb2),
			Animate::create(attackAnimc1),
			Animate::create(attackAnimc2),
			Animate::create(attackAnimd1),
			Animate::create(attackAnimd2),
			Role::createIdleCallbackFunc(),
			NULL));
		*/
		ret = true;
	} while (0);
	return ret;
}

void Hero::onMove(Vec2  direction, float distance)
{
	//���ó���
	if (direction.x < 0)
		setRoleDirection(true);
	else if (direction.x > 0)
		setRoleDirection(false);
	// ���Ǻܺõİ취
	if (0 == direction.y)
		this->setFlippedX(direction.x < 0 ? true : false);
	this->runWalkAction();
	Vec2 velocity = direction * (distance < 33 ? 1 : 3);
	
	this->setVelocity(velocity);
}

void Hero::onStop()//վ��
{
	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}

void Hero::onAttack(int number)//ִ�й���
{
	//this->setAnchorPoint(Point(0.0f, 0.0f));
	switch (number)
	{
	case ACTION_STATE_NOMAL_ATTACK_D:
	{

		this->setFlippedX(getRoleDirection());
		this->runNomalAttackD();
		break;
	}
	default:
	{
		//CCLOG("%d",getRoleDirection());
		this->setFlippedX(getRoleDirection());
		this->runNomalAttackA();
		break;
	}
		
	}
		
}

void Hero::updateSelf()//ˢ���Լ�
{
	if (this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 currentP = this->getPosition();				//��ǰ����
		Vec2 expectP = currentP + this->getVelocity();	//��������
		Vec2 actualP = expectP;							//ʵ������
		float mapWidth = global->tileMap->getContentSize().width;   //���ŵ�ͼ���
		//float mapHeight = global->tileMap->getContentSize().height; //���ŵ�ͼ�ĸ߶�
		float herofat = this->getBodyBox().actual.size.width / 2;     //��ɫ������,���ܹ�����bodyboxΪ׼
		//�����ܳ�ǰ��ͼ
		if ( false == (global->tileAllowMove(expectP)))
		{
			actualP = currentP;
		}
		//�����ܳ���ͼ����
		if (expectP.x < herofat || expectP.x >= mapWidth - herofat)
		{
			actualP.x = currentP.x;
		}

		this->setPosition(actualP);
		this->setLocalZOrder(Director::getInstance()->getVisibleSize().height - this->getPositionY());
	}
}
