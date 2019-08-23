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
	//virtual void Render() override;		//3_Render() �Լ� �߰�
	virtual bool Interaction(class Player* a_refHero) override;	//2_Interaction() �߰�

	eDoorState m_eState = eDoorState::Close;

	RenderTile	m_Close;
	RenderTile	m_Open;
};

