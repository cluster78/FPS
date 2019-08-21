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

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;

	virtual void Init() override;		//2_init() �߰�
	virtual void Interaction(class Hero* a_refHero) override;	//2_Interaction() �߰�

	eDoorState m_eState = eDoorState::Close;
};