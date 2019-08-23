#include "pch.h"
#include "Player.h"

#include "GameManager.h"			//6_게임매니저 인클루드


Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', 'P', ' ', 'P', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', ' ', ' ', ' ', ' ' } }
{
	m_pNowAni = &m_Data;				//3_애니매이션값 추가.

	rt.x += 1;
	rt.y += 1;
	rt.w = TileSize - 2;
	rt.h = TileSize - 2;
}


Player::~Player()
{
	m_refStat = nullptr;			//6_스텟값 삭제.
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}

Rect Player::GetRendertRect() const		//6_범위 좌표값 셋팅.
{
	return Rect{ rt.x - 1, rt.y - 1, rt.w, rt.h };
}

void Player::SetStat(struct CharacterData* a_pStat)		//6_플레이어 스텟갑 셋팅
{
	m_refStat = a_pStat;
	m_nPutBombCount = 0;
}

void Player::_PreUpdate(float a_fDelta)
{
	RenderClear();
}

bool Player::_Update(float a_fDelta)
{
	Move(a_fDelta);
	BombCheck();

	return false;
}

void Player::Move(float a_fDeltaTime)		//6_플레이어 이동함수. 
{
	float fAdd = a_fDeltaTime * (m_refStat->fMoveSeepd);

	float fX = 0;
	float fY = 0;

	if (IsKeyDown(eKey::A)) { fX -= fAdd; }
	if (IsKeyDown(eKey::D)) { fX += fAdd; }

	if (IsKeyDown(eKey::S)) { fX += fAdd; }
	if (IsKeyDown(eKey::W)) { fX -= fAdd; }

	rt.x += fX;
	rt.y += fY;

	if (GameMng()->MoveCheck(m_refBomb) == false)
	{
		rt.x -= fX;
		rt.y -= fY;
	}

	if (m_refBomb != nullptr)
	{
		if (m_refBomb->IsCross(this) == false)
		{
			m_refBomb = nullptr;
		}

	}
}

void Player::BombCheck()							//6_폭탄체크 함수
{
	if (m_nPutBombCount >= m_refStat->nBombCount) { return; }	//내 스텟만큼 폭탄이 놓여져있으면 리턴

	if (IsKeyDown(eKey::SPACE))		//폭탄놓는키 스페이스
	{
		COORD c = rt.Center();		// 플레이어 이미지의 센터찾아서 좌표 받아옴

		auto* pBomb = GameMng()->AddBomb(c.X, c.Y);

		if (pBomb != nullptr)		//폭탄추가.
		{
			++m_nPutBombCount;							//놔진 폭탄변수 증가
			m_refBomb = pBomb;
		}
	}
}

void Player::ResetBomb(Object* a_refBomb)
{
	if (m_refBomb == a_refBomb)
	{
		m_refBomb = nullptr;
	}

	--m_nPutBombCount;

	if (m_nPutBombCount < 0)
	{
		m_nPutBombCount = 0;
	}
}

bool Player::Exposived()
{
	GameMng()->Die(this);
	return false;
}




//void Player::Render()				//3_랜더 추가.	//6_랜더 삭제
//{
//
//}
