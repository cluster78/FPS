#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;
	//virtual void Render() override;							//3_���� �Լ� �߰�		6_�����Լ� ����
	virtual bool Interaction(class Player* a_refHero) override;

	virtual void _PreUpdate(float a_fDelta) override;
	virtual bool _Update(float a_fDelta) override;

	eItem m_eType = eItem::None;
	class Ani* m_pAni = nullptr;
	//RenderTile m_Item[(int)eItem::Max];						//3_������ ���������ͺ��� �߰�	//6_������ ���� ����
};

