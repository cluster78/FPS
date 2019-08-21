#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	virtual void Render() override;		//3_랜더 추가

	RenderTile	m_Data;					//3_랜더 데이터 변수 추가
};

