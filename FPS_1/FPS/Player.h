#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;

	virtual Rect GetRendertRect() const override;
	void SetStat(struct CharacterData* a_pStat);

private:
	void Move(float a_fDeltaTime);				//6_�̵��Լ� �߰�
	void BombCheck();							//6_��źüũ�Լ� �߰�

protected:
	virtual bool _Update(float a_fDelta);		//6_������Ʈ �Լ� �߰�.
	//virtual void Render() override;		//3_���� �߰�    6_���� �ٽ� ����

	RenderTile	m_Data;					//3_���� ������ ���� �߰�
	struct CharacterData* m_refStat;

public:
	int m_nPutBombCount = 0;
};

