#pragma once
#include "Object.h"

class Door : public Object
{
public:
	enum class eDoorState
	{
		Close,
		Open,
	};

	Door(int x, int y);
	virtual ~Door();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	virtual void Init() override;		//2_init() 추가
	virtual void Interaction(class Hero* a_refHero) override;	//2_Interaction() 추가

	eDoorState m_eState = eDoorState::Close;
};