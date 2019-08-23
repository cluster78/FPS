#include "pch.h"
#include "Player.h"

#include "GameManager.h"			//6_���ӸŴ��� ��Ŭ���


Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', 'P', ' ', 'P', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', ' ', ' ', ' ', ' ' } }
{
	m_pNowAni = &m_Data;				//3_�ִϸ��̼ǰ� �߰�.

	rt.x += 1;
	rt.y += 1;
	rt.w = TileSize - 2;
	rt.h = TileSize - 2;
}


Player::~Player()
{
	m_refStat = nullptr;			//6_���ݰ� ����.
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}

Rect Player::GetRendertRect() const		//6_���� ��ǥ�� ����.
{
	return Rect{ rt.x - 1, rt.y - 1, rt.w, rt.h };
}

void Player::SetStat(struct CharacterData* a_pStat)		//6_�÷��̾� ���ݰ� ����
{
	m_refStat = a_pStat;
	m_nPutBombCount = 0;
};

bool Player::_Update(float a_fDelta)
{
	Move(a_fDelta);
	BombCheck();

	return false;
}

void Player::Move(float a_fDeltaTime)		//6_�÷��̾� �̵��Լ�. 
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
}

void Player::BombCheck()							//6_��źüũ �Լ�
{
	if (m_nPutBombCount >= m_refStat->nBombCount) { return; }	//�� ���ݸ�ŭ ��ź�� ������������ ����

	if (IsKeyDown(eKey::SPACE))		//��ź����Ű �����̽�
	{
		COORD c = rt.Center();		// �÷��̾� �̹����� ����ã�Ƽ� ��ǥ �޾ƿ�

		if (GameMng()->AddBomb(c.X, c.Y) == true)		//��ź�߰�.
		{
			++m_nPutBombCount;							//���� ��ź���� ����
		}
	}
}




//void Player::Render()				//3_���� �߰�.	//6_���� ����
//{
//
//}
