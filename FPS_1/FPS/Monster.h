
#include "Object.h"

class Monster : public Object
{
public:
	Monster(int x, int y);
	virtual ~Monster();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;
	virtual bool Interaction(class Player* a_refHero) override;

	//virtual void Render() override;			//6_랜더 삭제

	RenderTile	m_Data;
};
