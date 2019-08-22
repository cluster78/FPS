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
	/*for( auto* pObj : m_vcObj)
	{
		SAFE_DELETE(pObj);
	}*/

	ClearObject();															//5_ClearObject() 불러오는걸로 변경.
	
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

	ClearObject();															//2_스테이지 넘어갈때 오브젝트 삭제용인듯.

	m_refMap =  MapData::Get(m_nNowStage);									//2_현재 스테이지에 맞춰서 맵데이터 가져옴.
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);				//2_제작되거나 변경된 맵 이 없다면 에러.

	int nWidth = m_refMap->x;												//2_넓이 추가
	int nHeight = m_refMap->y;												//2_높이 추가
	const std::string& sRef = m_refMap->mapOriginData;						//2_원본맵데이터 저장.?
	m_pMap = m_refMap->pMap;												//2_현재 맵을 제작 or 변경된 맵으로 덮어씀.

	//2_맵 제작 추가
	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int nIndex = y * nWidth + x;
			//eObjectType eType = (eObjectType)(sRef[nIndex] - '0');
			eObjectType eType = MapData::DataToObjectType(sRef[nIndex]);	//5_오브젝트타입 체크.

			if (eType == eObjectType::None) { continue; }

			if (eType == eObjectType::Player && m_pPlayer != nullptr)
			{
				m_pPlayer->SetPos(x, y);
				m_pPlayer->SetMap(m_pMap);									//2_자기 위치 자기가 셋팅?
				continue;
			}

			auto* pObj = ObjectFactory::Make(eType, x, y);
			if (eType == eObjectType::Player)
			{
				m_pPlayer = static_cast<Player*>(pObj);
			}
			else
			{
				int nLevel = (int)eType / (int)eObjectType::LevelGap;		//5_오브젝트 깊이 체크.
				m_vcObj[nLevel - 1].push_back(pObj);						//5_저장하는변수 배열로 변경됨.
			}

			pObj->SetMap(m_pMap);											//2_오브젝트 맵에 셋팅.
		}
	}
}

void GameManager::ClearObject()												//2_ 오브젝트 날림.
{
	for (auto vc : m_vcObj)													//5_백터의 배열이라 레인지드포 2번돌림.
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}

		vc.clear();
	}
}

void GameManager::Update(float a_fDeltaTime)
{
	for (auto& vc : m_vcObj)
	{
		for (auto* pObj : vc)
		{
			pObj->Update(a_fDeltaTime);
		}
	}
		
	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	for (auto& vc  : m_vcObj)												//2_오브젝트에 렌더가 없어져서 삭제 했다가 3에서 다시 추가
	{
		for (auto* pObj : vc)
		{
			pObj->Render();
		}	
	}

	m_pPlayer->Render();

	//SetCursor(0, 0);														// 2_0,0부터 차례대로 맵 랜더.	5_삭제
	m_refMap->Render();
}

void GameManager::RemoveObject(class Object* a_pObj)						//2_오브젝트 삭제 추가.		5_오브젝트삭제에 깊이체크해서 삭제하는부분 추가.
{
	eObjectType eType = a_pObj->GetObjectType();							

	int nLevelIndex = (int)eType / (int)eObjectType::LevelGap;
	nLevelIndex -= 1;

	auto& vc = m_vcObj[nLevelIndex];


	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj;});
	assert(itor != vc.end());
	vc.erase(itor);
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
