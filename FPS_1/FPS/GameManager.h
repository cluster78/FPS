#pragma once

//#include "MapData.h"													 2_맵데이터가 static 이므로 인클루드 필요없음.

struct CharacterData
{
	float	fMoveSeepd;
	float	fBombTime;
	int		nBombPower;													//2_Base -> Bomb 로 변경.
	int		nBombCount;

	CharacterData();													//2_케릭터 데이터 추가. 현재 플레이어의 스텟조정
};

struct Explosion
{
	int x;
	int y;
	int pow;

	Explosion(int _x, int _y, int _pow) : x(_x), y(_y), pow(_pow)
	{}
};

struct CreateObj
{
	int x;
	int y;
	eObjectType type;

	CreateObj(int _x, int _y, eObjectType _type) : x(_x), y(_y), type(_type)
	{}
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

	static void CreateInstance()										//1_게임매니져 생성함수
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager * GetInstance()									//1_현재게임매니져 가져옴.
	{
		return m_pInstance;
	}

	static void ReleaseInstance()										//1_현재게임매니져 삭제 함수
	{
		m_pInstance->Release();											//2_게임매니져가 가지고 있는 맵 삭제 관련 코드 추가
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

public:																	//3_퍼블릭 추가.
	enum
	{
		MaxLife = 3,		// 플레이어 라이프 수
		RoundTime = 90,		// 90초

		MoveSpeed = 10,		// 이동 속도
		BombTime = 2,		// 2초											 3_ 2초로 시간 조정
		BombBasePower = 2,	// 2칸
		BombBaseCount = 1,	// 최초 폭탄 설치 갯수
	};

	enum class eGameState												//6_게임상태값 추가.
	{
		None,

		Run,
		End,
	};

	void Init();
	void Release();														//2_릴리즈 추가. 맵 데이터 삭제. 스테이지 변경될때 맵데이터 초기화하려고 추가하신듯?

	void GameInit();													//1_게임매니져가 불렸을때 값 셋팅.
	void StageStart();													// 1_맵, 오브젝트, 플레이어 셋팅.
	void StageEnd();

	void Update(float a_fDeltaTime);	
	void Render();	
	void PostRender();

	void ClearObject();													//2_오브젝트 전부 날림.
	class Object* CreateObject(eObjectType a_eObjType, int x, int y);			//6_오브젝트 생성함수 추가.

	void RemoveObject(class Object* a_pObj);							//2_특정 오브젝트만 날림
	void DropItem(class Object* a_pObj);		
	void GetBombData(OUT class Bomb* a_refBomb) const;						//2_폭탄 데이터 가져와서 셋팅
	void ObtainItem(eItem a_eItem);										//2_아이템 획득했을때 획득한 아이템 검사 및 플레이어 능력치 증가
	void Die(class Object* a_refObj);
	class Object* AddBomb(int a_nPlayerX, int a_nPlayerY);
	void ResistExplosion(Object* a_refBomb,int x, int y, int pow);
	bool MoveCheck(class Object* a_pMoveIgnoreObject = nullptr);
	void CheckExplosion(Object* a_refExplosion);
	void AddScore(int a_nScore);

private:
	void CreateExplosionRecursive(eDir a_eDir, int nBombX, int nBombY, int a_nRemainPower);
	bool FindObject_withPosition(eObjectType a_eObj, int x, int y);

private:																//2_프라이빗으로 변경
	// 오브젝트
	std::array<std::vector<class Object*>, (int)eObjectType::RenderDepthCount> m_arrObj;		//5_벡터 배열로 변경.
	class Player* m_pPlayer = nullptr;

	// 스테이지 정보
	int m_nNowStage = 0;
	float m_fGameTime = 0;	// 스테이지별 남은 시간
	class MapData* m_refMap = nullptr;									//2_타입값을 class 로 명시.
	char** m_pMap = nullptr;											//2_맵데이터 추가

	// 데이터
	int m_nNowLife = 0;		// 플레이어 라이프
	int m_nScore = 0;		// 점수

																		//2_폭탄담아놓을 큐 추가.		
	std::vector<class Object*> m_vcDelete;
	std::vector<CreateObj> m_vcCreate;
	std::vector<Explosion> m_vcExplosion;
																		//2_현재 플레이어 데이터 추가.
	CharacterData m_stPlayerData;

	eGameState m_eState = eGameState::None;

public:
	std::string m_sLog = "";
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())
