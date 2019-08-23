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
	m_eState = eGameState::Run;				//6_현재 게임상태 업데이트.

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

			//auto* pObj = ObjectFactory::Make(eType, x, y);
			//if (eType == eObjectType::Player)
			//{
			//	m_pPlayer = static_cast<Player*>(pObj);
			//}
			//else
			//{
			//	int nLevel = (int)eType / (int)eObjectType::LevelGap;		//5_오브젝트 깊이 체크.
			//	m_vcObj[nLevel - 1].push_back(pObj);						//5_저장하는변수 배열로 변경됨.
			//}

			//pObj->SetMap(m_pMap);											//2_오브젝트 맵에 셋팅.

			CreateObject(eType, x, y);	//6_오브젝트 생성함수 호출
		}
	}
}

void GameManager::StageEnd()
{
	m_eState = eGameState::End;		//6_스테이지 종료상태 변경.
}


void GameManager::ClearObject()												//2_ 오브젝트 날림.
{
	for (auto& vc : m_arrObj)													//5_백터의 배열이라 레인지드포 2번돌림.
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}
		vc.clear();
	}
}

void GameManager::CreateObject(eObjectType a_eObjType, int x, int y)
{
	auto* pObj = ObjectFactory::Make(a_eObjType, x, y);

	if (a_eObjType == eObjectType::Player)
	{
		m_pPlayer = static_cast<Player*>(pObj);
		m_pPlayer->SetStat(&m_stPlayerData);
	}
	else
	{
		int nDepthIndex = (int)a_eObjType / (int)eObjectType::RenderDepthGap;
		nDepthIndex -= 1;

		m_arrObj[nDepthIndex].push_back(pObj);
	}

	pObj->SetMap(m_pMap);
}


void GameManager::Update(float a_fDeltaTime)
{
	int nSize = m_arrObj.size();

	static std::vector<class Object*> vcDelete;
	vcDelete.clear();

	for (int i = 1; i < nSize; ++i)
	{
		auto& arrObj = m_arrObj[i];

		for (auto* pObj : arrObj)
		{
			Object* p = nullptr;

			if (pObj->Update(a_fDeltaTime) == true)
			{
				p = pObj;
			}

			if (pObj->Interaction(m_pPlayer) == true)
			{
				p = pObj;
			}

			if (p != nullptr)
			{
				vcDelete.push_back(p);
			}
		}
	}

	// 인터렉션 이후 삭제해야할 오브젝트 삭제
	for (auto* pDeleteObj : vcDelete)
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	vcDelete.clear();
		
	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	for (auto& vc  : m_arrObj)												//2_오브젝트에 렌더가 없어져서 삭제 했다가 3에서 다시 추가
	{
		for (auto* pObj : vc)
		{
			pObj->Render();
		}	
	}

	m_pPlayer->Render();

	//SetCursor(0, 0);														// 2_0,0부터 차례대로 맵 랜더.	5_삭제
	m_refMap->Render();

	if (m_eState == eGameState::End)
	{
		StageStart();
	}

	cout << "pos : " << m_pPlayer->rt.x << " /// " << m_pPlayer->rt.y << endl;
	COORD center = m_pPlayer->rt.Center();

	cout << "center : " << center.X << " /// " << center.Y << endl;

	if (m_sLog.size() > 0)
	{
		cout << m_sLog.c_str() << endl;
		m_sLog.clear();
	}
}

void GameManager::RemoveObject(class Object* a_pObj)						//2_오브젝트 삭제 추가.		5_오브젝트삭제에 깊이체크해서 삭제하는부분 추가.
{
	eObjectType eType = a_pObj->GetObjectType();							

	int nLevelIndex = (int)eType / (int)eObjectType::RenderDepthGap;
	nLevelIndex -= 1;

	auto& vc = m_arrObj[nLevelIndex];

	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj;});
	assert(itor != vc.end());
	vc.erase(itor);

	SAFE_DELETE(a_pObj);
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

void GameManager::Die(class Object* a_refObj)		//6_죽으면 죽음표시
{
	cout << "Player Die" << endl;
}


bool GameManager::AddBomb(int a_nPlayerX, int a_nPlayerY)		//6_폭탄 추가 함수.
{
	int nX = a_nPlayerX / TileSize;
	int nY = a_nPlayerY / TileSize;
	constexpr static int nIndex = ((int)eObjectType::Bomb / (int)eObjectType::RenderDepthGap) - 1;

	bool bExsistBomb = false;

	for (auto* pObj : m_arrObj[nIndex])
	{
		if (pObj->GetObjectType() == eObjectType::Bomb)
		{
			bExsistBomb = pObj->rt.IsIn(a_nPlayerX, a_nPlayerY);

			if (bExsistBomb == true)
			{
				break;
			}
		}
	}

	if (bExsistBomb == true)
	{
		return false;
	}

	CreateObject(eObjectType::Bomb, nX, nY);
	return true;

}

void GameManager::ResistExplosion(int a_nBombX, int a_nBombY, int a_nPower)		//6_폭발 저항?
{
	m_pPlayer->m_nPutBombCount -= 1;											//놔둔 폭탄 숫자 하나 감소.
}

#include "Bomb.h"
void GameManager::GetBombData(Bomb* a_refBomb) const		//2_폭탄 데이터 가져옴.
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}
