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

	ClearObject();															//5_ClearObject() �ҷ����°ɷ� ����.
	
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
	m_eState = eGameState::Run;				//6_���� ���ӻ��� ������Ʈ.

	ClearObject();															//2_�������� �Ѿ�� ������Ʈ �������ε�.

	m_refMap =  MapData::Get(m_nNowStage);									//2_���� ���������� ���缭 �ʵ����� ������.
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);				//2_���۵ǰų� ����� �� �� ���ٸ� ����.

	int nWidth = m_refMap->x;												//2_���� �߰�
	int nHeight = m_refMap->y;												//2_���� �߰�
	const std::string& sRef = m_refMap->mapOriginData;						//2_�����ʵ����� ����.?
	m_pMap = m_refMap->pMap;												//2_���� ���� ���� or ����� ������ ���.

	//2_�� ���� �߰�
	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int nIndex = y * nWidth + x;
			//eObjectType eType = (eObjectType)(sRef[nIndex] - '0');
			eObjectType eType = MapData::DataToObjectType(sRef[nIndex]);	//5_������ƮŸ�� üũ.

			if (eType == eObjectType::None) { continue; }

			if (eType == eObjectType::Player && m_pPlayer != nullptr)
			{
				m_pPlayer->SetPos(x, y);
				m_pPlayer->SetMap(m_pMap);									//2_�ڱ� ��ġ �ڱⰡ ����?
				continue;
			}

			//auto* pObj = ObjectFactory::Make(eType, x, y);
			//if (eType == eObjectType::Player)
			//{
			//	m_pPlayer = static_cast<Player*>(pObj);
			//}
			//else
			//{
			//	int nLevel = (int)eType / (int)eObjectType::LevelGap;		//5_������Ʈ ���� üũ.
			//	m_vcObj[nLevel - 1].push_back(pObj);						//5_�����ϴº��� �迭�� �����.
			//}

			//pObj->SetMap(m_pMap);											//2_������Ʈ �ʿ� ����.

			CreateObject(eType, x, y);	//6_������Ʈ �����Լ� ȣ��
		}
	}
}

void GameManager::StageEnd()
{
	m_eState = eGameState::End;		//6_�������� ������� ����.
}


void GameManager::ClearObject()												//2_ ������Ʈ ����.
{
	for (auto& vc : m_arrObj)													//5_������ �迭�̶� ���������� 2������.
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}
		vc.clear();
	}
}

Object* GameManager::CreateObject(eObjectType a_eObjType, int x, int y)
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
	return pObj;
}


void GameManager::Update(float a_fDeltaTime)
{
	m_vcDelete.clear();
	int nSize = m_arrObj.size();

	/*static std::vector<class Object*> vcDelete;
	vcDelete.clear();*/

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
				m_vcDelete.push_back(p);
			}
		}
	}

	//// ���ͷ��� ���� �����ؾ��� ������Ʈ ����
	//for (auto* pDeleteObj : vcDelete)
	//{
	//	pDeleteObj->RenderClear();
	//	RemoveObject(pDeleteObj);
	//}
	//vcDelete.clear();
		
	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	for (auto& vc  : m_arrObj)												//2_������Ʈ�� ������ �������� ���� �ߴٰ� 3���� �ٽ� �߰�
	{
		for (auto* pObj : vc)
		{
			pObj->Render();
		}	
	}

	m_pPlayer->Render();

	//SetCursor(0, 0);														// 2_0,0���� ���ʴ�� �� ����.	5_����
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

void GameManager::PostRender()
{
	for (auto* pDeleteObj : m_vcDelete)
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	m_vcDelete.clear();

	for (auto& ex : m_vcExplosion)
	{
		int nBombX = ex.x;
		int nBombY = ex.y;
		int nPow = ex.pow;

		CreateObject(eObjectType::Explosion, nBombX, nBombY);

		CreateExplosionRecursive(eDir::Left, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Top, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Right, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Bottom, nBombX, nBombY, nPow);
	}

	m_vcExplosion.clear();
}

void GameManager::CreateExplosionRecursive(eDir a_eDir, int nBombX, int nBombY, int a_nRemainPower)
{
	switch (a_eDir)
	{
		case eDir::Left:	{ nBombX -= 1; } break;
		case eDir::Top:		{ nBombY -= 1; } break;
		case eDir::Right:	{ nBombX += 1; } break;
		case eDir::Bottom:	{ nBombY += 1; } break;
	}

	CreateObject(eObjectType::Explosion, nBombX, nBombY);

	--a_nRemainPower;
	if (a_nRemainPower == 0) { return; }

	CreateExplosionRecursive(a_eDir, nBombX, nBombY, a_nRemainPower);
}

void GameManager::RemoveObject(class Object* a_pObj)						//2_������Ʈ ���� �߰�.		5_������Ʈ������ ����üũ�ؼ� �����ϴºκ� �߰�.
{
	eObjectType eType = a_pObj->GetObjectType();							

	int nLevelIndex = (int)eType / (int)eObjectType::RenderDepthGap;
	nLevelIndex -= 1;

	auto& vc = m_arrObj[nLevelIndex];

	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj;});
	//assert(itor != vc.end());
	
	if (itor != vc.end())
	{
		vc.erase(itor);
		SAFE_DELETE(a_pObj);
	}
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

void GameManager::Die(class Object* a_refObj)		//6_������ ����ǥ��
{
	cout << "Player Die" << endl;
}


Object* GameManager::AddBomb(int a_nPlayerX, int a_nPlayerY)		//6_��ź �߰� �Լ�.
{
	if (FindObject_withPosition(eObjectType::Bomb, a_nPlayerX, a_nPlayerY) == false)
	{
		int nX = a_nPlayerX / TileSize;
		int nY = a_nPlayerY / TileSize;

		return CreateObject(eObjectType::Bomb, nX, nY);
	}

	return nullptr;
	
	/*constexpr static int nIndex = ((int)eObjectType::Bomb / (int)eObjectType::RenderDepthGap) - 1;

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
	}*/
}

bool GameManager::FindObject_withPosition(eObjectType a_eObj, int x, int y)
{
	int nX = x / TileSize;
	int nY = y / TileSize;
	int nIndex = ((int)a_eObj / (int)eObjectType::RenderDepthGap) - 1;

	for (auto* pObj : m_arrObj[nIndex])
	{
		if (pObj->GetObjectType() == a_eObj)
		{
			if (pObj->rt.IsIn(x, y) == true)
			{
				return true;
			}
		}
	}

	return false;
}

void GameManager::ResistExplosion(Object* a_refBomb,  int x, int y, int pow)		//6_���� ����?
{
	m_pPlayer->ResetBomb(a_refBomb);											//���� ��ź ���� �ϳ� ����.
	m_vcExplosion.emplace_back(x / TileSize, y / TileSize, pow);
}

bool GameManager::MoveCheck(Object* a_pMoveIgnoreObject)
{
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			if (a_pMoveIgnoreObject == pObj) { continue; }

			if (pObj->CanMove() == true) { continue; }

			if (pObj->IsCross(m_pPlayer) == true)
			{
				return false;
			}
		}
	}

	return true;
}

void GameManager::CheckExplosion(Object* a_refExplosion)
{
	int nIndex = (int)eObjectType::RenderDepth3 - 1;
	const auto& vc = m_arrObj[nIndex];

	for (auto* pObj : vc)
	{
		if (pObj == a_refExplosion) { continue; }

		if (a_refExplosion->IsCross(pObj) == true)
		{
			if (pObj->Explosived() == true)
			{
				m_vcDelete.push_back(pObj);
			}
		}
	}
}

void GameManager::AddScore(int a_nScore)
{
	m_nScore += m_nScore;
}

#include "Bomb.h"
void GameManager::GetBombData(Bomb* a_refBomb) const		//2_��ź ������ ������.
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}
