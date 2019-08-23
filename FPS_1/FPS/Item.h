#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;
	//virtual void Render() override;							//3_랜더 함수 추가		6_랜더함수 삭제
	virtual bool Interaction(class Player* a_refHero) override;

	virtual void _PreUpdate(float a_fDelta) override;
	virtual bool _Update(float a_fDelta) override;

	eItem m_eType = eItem::None;
	class Ani* m_pAni = nullptr;
	//RenderTile m_Item[(int)eItem::Max];						//3_아이템 랜더데이터변수 추가	//6_아이템 변수 삭제
};

