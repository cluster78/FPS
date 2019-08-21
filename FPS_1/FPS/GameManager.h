#pragma once

//#include "MapData.h"  2_맵데이터가 static 이므로 인클루드 필요없음.

struct CharacterData
{
	float	fMoveSeepd;
	float	fBombTime;
	int		nBombPower;		//2_Base -> Bomb 로 변경.
	int		nBombCount;

	CharacterData();		//2_케릭터 데이터 추가. 현재 플레이어의 스텟조정
};

class GameManager
{
#pragma region SINGLE_TON
private:
	static inline GameManager * m_pInstance = nullptr;
	GameManager();
	~GameManager();

	GameManager operator=(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager(const GameManager&) = delete;

public:

	static void CreateInstance()			//1_게임매니져 생성함수
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager * GetInstance()		//1_현재게임매니져 가져옴.
	{
		return m_pInstance;
	}

	static void ReleaseInstance()		//1_현재게임매니져 삭제 함수
	{
		m_pInstance->Release();			//2_게임매니져가 가지고 있는 맵 삭제 관련 코드 추가
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

	enum
	{
		MaxLife = 3,		// 플레이어 라이프 수
		RoundTime = 90,		// 90초

		MoveSpeed = 10,		// 이동 속도
		BombTime = 3,		// 3초
		BombBasePower = 2,	// 2칸
		BombBaseCount = 1,	// 최초 폭탄 설치 갯수
	};

	void Init();
	void Release();			//2_릴리즈 추가. 맵 데이터 삭제. 스테이지 변경될때 맵데이터 초기화하려고 추가하신듯?

	void GameInit();		//1_게임매니져가 불렸을때 값 셋팅.
	void StageStart();		// 1_맵, 오브젝트, 플레이어 셋팅.

	void Update(float a_fDeltaTime);	
	void Render();						

	void ClearObject();					//2_오브젝트 전부 날림.

	void RemoveObject(class Object* a_pObj);	//2_특정 오브젝트만 날림
	void DropItem(class Object* a_pObj);		
	void GetBombData(class Bomb* a_refBomb) const;	//2_폭탄 데이터 가져와서 셋팅
	void ObtainItem(eItem a_eItem);					//2_아이템 획득했을때 획득한 아이템 검사 및 플레이어 능력치 증가

private:		//2_프라이빗으로 변경
	// 오브젝트
	std::vector<class Object*> m_vcObj;
	class Player* m_pPlayer = nullptr;

	// 스테이지 정보
	int m_nNowStage = 0;
	float m_fGameTime = 0;	// 스테이지별 남은 시간
	class MapData* m_refMap = nullptr; //2_타입값을 class 로 명시.
	char** m_pMap = nullptr;			//2_맵데이터 추가

	// 데이터
	int m_nNowLife = 0;		// 플레이어 라이프
	int m_nScore = 0;		// 점수

	//2_폭탄담아놓을 큐 추가.		
	std::queue<class Bomb*> m_qBomb;

	//2_현재 플레이어 데이터 추가.
	CharacterData m_stPlayerData;
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())
