#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;
	virtual void Render() override;							//3_랜더 함수 추가
	virtual void Interaction(class Hero* a_refHero) override;

	eItem m_eType = eItem::None;
	RenderTile m_Item[(int)eItem::Max];						//3_아이템 랜더데이터변수 추가
};

