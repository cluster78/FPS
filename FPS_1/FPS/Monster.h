
#include "Object.h"

class Monster : public Object
{
public:
	Monster(int x, int y);
	virtual ~Monster();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;
	virtual bool Interaction(class Player* a_refHero) override;

	//virtual void Render() override;			//6_���� ����

	RenderTile	m_Data;
};
