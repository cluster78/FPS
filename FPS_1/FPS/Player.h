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
	void ResetBomb(Object* a_refBomb);
	virtual bool Exposived() override;

private:
	void Move(float a_fDeltaTime);				//6_�̵��Լ� �߰�
	void BombCheck();							//6_��źüũ�Լ� �߰�

protected:
	virtual void _PreUpdate(float a_fDelta) override;
	virtual bool _Update(float a_fDelta) override;		//6_������Ʈ �Լ� �߰�.
	//virtual void Render() override;		//3_���� �߰�    6_���� �ٽ� ����

	RenderTile	m_Data;					//3_���� ������ ���� �߰�
	struct CharacterData* m_refStat;

public:
	int m_nPutBombCount = 0;
	Object* m_refBomb = nullptr;
};

