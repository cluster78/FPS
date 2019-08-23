#pragma once

//#include "MapData.h"													 2_�ʵ����Ͱ� static �̹Ƿ� ��Ŭ��� �ʿ����.

struct CharacterData
{
	float	fMoveSeepd;
	float	fBombTime;
	int		nBombPower;													//2_Base -> Bomb �� ����.
	int		nBombCount;

	CharacterData();													//2_�ɸ��� ������ �߰�. ���� �÷��̾��� ��������
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

	static void CreateInstance()										//1_���ӸŴ��� �����Լ�
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager * GetInstance()									//1_������ӸŴ��� ������.
	{
		return m_pInstance;
	}

	static void ReleaseInstance()										//1_������ӸŴ��� ���� �Լ�
	{
		m_pInstance->Release();											//2_���ӸŴ����� ������ �ִ� �� ���� ���� �ڵ� �߰�
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

public:																	//3_�ۺ� �߰�.
	enum
	{
		MaxLife = 3,		// �÷��̾� ������ ��
		RoundTime = 90,		// 90��

		MoveSpeed = 10,		// �̵� �ӵ�
		BombTime = 2,		// 2��											 3_ 2�ʷ� �ð� ����
		BombBasePower = 2,	// 2ĭ
		BombBaseCount = 1,	// ���� ��ź ��ġ ����
	};

	enum class eGameState												//6_���ӻ��°� �߰�.
	{
		None,

		Run,
		End,
	};

	void Init();
	void Release();														//2_������ �߰�. �� ������ ����. �������� ����ɶ� �ʵ����� �ʱ�ȭ�Ϸ��� �߰��Ͻŵ�?

	void GameInit();													//1_���ӸŴ����� �ҷ����� �� ����.
	void StageStart();													// 1_��, ������Ʈ, �÷��̾� ����.
	void StageEnd();

	void Update(float a_fDeltaTime);	
	void Render();	
	void PostRender();

	void ClearObject();													//2_������Ʈ ���� ����.
	class Object* CreateObject(eObjectType a_eObjType, int x, int y);			//6_������Ʈ �����Լ� �߰�.

	void RemoveObject(class Object* a_pObj);							//2_Ư�� ������Ʈ�� ����
	void DropItem(class Object* a_pObj);		
	void GetBombData(OUT class Bomb* a_refBomb) const;						//2_��ź ������ �����ͼ� ����
	void ObtainItem(eItem a_eItem);										//2_������ ȹ�������� ȹ���� ������ �˻� �� �÷��̾� �ɷ�ġ ����
	void Die(class Object* a_refObj);
	class Object* AddBomb(int a_nPlayerX, int a_nPlayerY);
	void ResistExplosion(Object* a_refBomb,int x, int y, int pow);
	bool MoveCheck(class Object* a_pMoveIgnoreObject = nullptr);
	void CheckExplosion(Object* a_refExplosion);
	void AddScore(int a_nScore);

private:
	void CreateExplosionRecursive(eDir a_eDir, int nBombX, int nBombY, int a_nRemainPower);
	bool FindObject_withPosition(eObjectType a_eObj, int x, int y);

private:																//2_�����̺����� ����
	// ������Ʈ
	std::array<std::vector<class Object*>, (int)eObjectType::RenderDepthCount> m_arrObj;		//5_���� �迭�� ����.
	class Player* m_pPlayer = nullptr;

	// �������� ����
	int m_nNowStage = 0;
	float m_fGameTime = 0;	// ���������� ���� �ð�
	class MapData* m_refMap = nullptr;									//2_Ÿ�԰��� class �� ���.
	char** m_pMap = nullptr;											//2_�ʵ����� �߰�

	// ������
	int m_nNowLife = 0;		// �÷��̾� ������
	int m_nScore = 0;		// ����

																		//2_��ź��Ƴ��� ť �߰�.		
	std::vector<class Object*> m_vcDelete;
	std::vector<CreateObj> m_vcCreate;
	std::vector<Explosion> m_vcExplosion;
																		//2_���� �÷��̾� ������ �߰�.
	CharacterData m_stPlayerData;

	eGameState m_eState = eGameState::None;

public:
	std::string m_sLog = "";
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())
