#ifndef _GLOBAL_H
#define _GLOBAL_H
#include "cocos2d.h"
USING_NS_CC;

#include "Singleton.h"
#include "Game\GameLayer.h"
#include "Operate\OperateLayer.h"
#include "State\StateLayer.h"

class GameLayer;
class OperateLayer;
class StateLayer;
class Hero;
class Enemy;

//ȫ�ֵ���
class Global:public Singleton<Global>
{
public:
	Global();
	~Global();

	GameLayer *gameLayer;			//��Ϸ��
	OperateLayer *operateLayer;		//������
	StateLayer * stateLayer;		//״̬��
	Hero *hero;						//Ӣ��
	__Array *enemies;				//����
	TMXTiledMap *tileMap;			//��ͼ



	Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = 0);//��pointת���ɵ�ͼGID��point
	bool  tileAllowMove(Vec2 MovePoint);
};
#define global Global::instance()
#endif//Global.h
