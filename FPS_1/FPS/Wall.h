#pragma once
#include "Object.h"

class Wall : public Object
{
public:
	Wall(int x, int y);
	virtual ~Wall();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	//virtual void Render() override;		//3_랜더 추가	6_랜더 삭제

	RenderTile	m_Data;					//3_랜더 데이터 변수 추가
};

