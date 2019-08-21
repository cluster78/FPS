#include "pch.h"
#include "GameManager.h"

#include "MapData.h"
#include "Object.h"
#include "Player.h"
#include "ObjectFactory.h"

CharacterData::CharacterData()		
{
	fMoveSeepd = GameManager::MoveSpeed;
	fBombTime = GameManager::BombTime;
	nBombPower = GameManager::BombBasePower;
	nBombCount = GameManager::BombBaseCount;
}



GameManager::GameManager() {}
GameManager::~GameManager()
{
	for( auto* pObj : m_vcObj)
	{
		SAFE_DELETE(pObj);
	}
	
	SAFE_DELETE(m_pPlayer);
}

void GameManager::Init()
{
	MapData::Init();
}

void GameManager::Release()		
{
	MapData::Release();
}

void GameManager::GameInit()
{
	m_nNowLife = 3;
	m_nScore = 0;
	m_nNowStage = 0;
}

void GameManager::StageStart()
{
	++m_nNowStage;
	m_fGameTime = RoundTime;

	ClearObject();	//2_�������� �Ѿ�� ������Ʈ �������ε�.

	m_refMap =  MapData::Get(m_nNowStage);	//2_���� ���������� ���缭 �ʵ����� ������.
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);	//2_���۵ǰų� ����� �� �� ���ٸ� ����.

	int nWidth = m_refMap->x;	//2_���� �߰�
	int nHeight = m_refMap->y;	//2_���� �߰�
	const std::string& sRef = m_refMap->mapOriginData;	//2_�����ʵ����� ����.?
	m_pMap = m_refMap->pMap;		//2_���� ���� ���� or ����� ������ ���.

	//2_�� ���� �߰�
	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int nIndex = y * nWidth + x;
			eObjectType eType = (eObjectType)(sRef[nIndex] - '0');

			if (eType == eObjectType::None) { continue; }

			if (eType == eObjectType::Player && m_pPlayer != nullptr)
			{
				m_pPlayer->SetPos(x, y);
				m_pPlayer->SetMap(m_pMap);		//2_�ڱ� ��ġ �ڱⰡ ����?
				continue;
			}

			auto* pObj = ObjectFactory::Make(eType, x, y);
			if (eType == eObjectType::Player)
			{
				m_pPlayer = static_cast<Player*>(pObj);
			}
			else
			{
				m_vcObj.push_back(pObj);
			}

			pObj->SetMap(m_pMap);		//2_������Ʈ �ʿ� ����.
		}
	}
}

void GameManager::ClearObject()		//2_ ������Ʈ ����.
{
	for (auto obj : m_vcObj)
	{
		SAFE_DELETE(obj);
	}
	m_vcObj.clear();
}

void GameManager::Update(float a_fDeltaTime)
{
	for (auto obj : m_vcObj)
	{
		obj->Update(a_fDeltaTime);
	}
		
	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	//for (auto obj : m_vcObj)			//2_������Ʈ�� ������ �������� ����.
	//{
	//	obj->Render();
	//}

	//m_pPlayer->Render();


	SetCursor(0, 0);				// 2_0,0���� ���ʴ�� �� ����.
	m_refMap->Render();
}

void GameManager::RemoveObject(class Object* a_pObj)		//2_������Ʈ ���� �߰�.
{
	auto itor = std::find_if(std::begin(m_vcObj), std::end(m_vcObj), [a_pObj](Object* p) { return p == a_pObj; });
	assert(itor != m_vcObj.end());
	m_vcObj.erase(itor);
}

void GameManager::DropItem(Object* a_pObj)
{

}

void GameManager::ObtainItem(eItem a_eItem)			//2_������ ȹ�� �����Լ� �߰�.
{
	switch (a_eItem)
	{
	case eItem::PowerUp:
		m_stPlayerData.nBombPower += 1;
		break;
	case eItem::BombCount:
		m_stPlayerData.nBombCount += 1;
		break;
	case eItem::SpeedUp:
		m_stPlayerData.fMoveSeepd += 1;
		break;
	default:
		assert(false && "arg error");
		break;
	}
}

#include "Bomb.h"
void GameManager::GetBombData(Bomb* a_refBomb) const		//2_��ź ������ ������.
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}
