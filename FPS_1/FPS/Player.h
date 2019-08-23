#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	virtual Rect GetRendertRect() const override;
	void SetStat(struct CharacterData* a_pStat);

private:
	void Move(float a_fDeltaTime);				//6_이동함수 추가
	void BombCheck();							//6_폭탄체크함수 추가

protected:
	virtual bool _Update(float a_fDelta);		//6_업데이트 함수 추가.
	//virtual void Render() override;		//3_랜더 추가    6_랜더 다시 삭제

	RenderTile	m_Data;					//3_랜더 데이터 변수 추가
	struct CharacterData* m_refStat;

public:
	int m_nPutBombCount = 0;
};

