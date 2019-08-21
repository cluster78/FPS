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

	ClearObject();	//2_스테이지 넘어갈때 오브젝트 삭제용인듯.

	m_refMap =  MapData::Get(m_nNowStage);	//2_현재 스테이지에 맞춰서 맵데이터 가져옴.
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);	//2_제작되거나 변경된 맵 이 없다면 에러.

	int nWidth = m_refMap->x;	//2_넓이 추가
	int nHeight = m_refMap->y;	//2_높이 추가
	const std::string& sRef = m_refMap->mapOriginData;	//2_원본맵데이터 저장.?
	m_pMap = m_refMap->pMap;		//2_현재 맵을 제작 or 변경된 맵으로 덮어씀.

	//2_맵 제작 추가
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
				m_pPlayer->SetMap(m_pMap);		//2_자기 위치 자기가 셋팅?
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

			pObj->SetMap(m_pMap);		//2_오브젝트 맵에 셋팅.
		}
	}
}

void GameManager::ClearObject()		//2_ 오브젝트 날림.
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
	//for (auto obj : m_vcObj)			//2_오브젝트에 렌더가 없어져서 삭제.
	//{
	//	obj->Render();
	//}

	//m_pPlayer->Render();


	SetCursor(0, 0);				// 2_0,0부터 차례대로 맵 랜더.
	m_refMap->Render();
}

void GameManager::RemoveObject(class Object* a_pObj)		//2_오브젝트 삭제 추가.
{
	auto itor = std::find_if(std::begin(m_vcObj), std::end(m_vcObj), [a_pObj](Object* p) { return p == a_pObj; });
	assert(itor != m_vcObj.end());
	m_vcObj.erase(itor);
}

void GameManager::DropItem(Object* a_pObj)
{

}

void GameManager::ObtainItem(eItem a_eItem)			//2_아이템 획득 관련함수 추가.
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
void GameManager::GetBombData(Bomb* a_refBomb) const		//2_폭탄 데이터 가져옴.
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}
