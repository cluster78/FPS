#pragma once

//#include "MapData.h"  2_�ʵ����Ͱ� static �̹Ƿ� ��Ŭ��� �ʿ����.

struct CharacterData
{
	float	fMoveSeepd;
	float	fBombTime;
	int		nBombPower;		//2_Base -> Bomb �� ����.
	int		nBombCount;

	CharacterData();		//2_�ɸ��� ������ �߰�. ���� �÷��̾��� ��������
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

	static void CreateInstance()			//1_���ӸŴ��� �����Լ�
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager * GetInstance()		//1_������ӸŴ��� ������.
	{
		return m_pInstance;
	}

	static void ReleaseInstance()		//1_������ӸŴ��� ���� �Լ�
	{
		m_pInstance->Release();			//2_���ӸŴ����� ������ �ִ� �� ���� ���� �ڵ� �߰�
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

	enum
	{
		MaxLife = 3,		// �÷��̾� ������ ��
		RoundTime = 90,		// 90��

		MoveSpeed = 10,		// �̵� �ӵ�
		BombTime = 3,		// 3��
		BombBasePower = 2,	// 2ĭ
		BombBaseCount = 1,	// ���� ��ź ��ġ ����
	};

	void Init();
	void Release();			//2_������ �߰�. �� ������ ����. �������� ����ɶ� �ʵ����� �ʱ�ȭ�Ϸ��� �߰��Ͻŵ�?

	void GameInit();		//1_���ӸŴ����� �ҷ����� �� ����.
	void StageStart();		// 1_��, ������Ʈ, �÷��̾� ����.

	void Update(float a_fDeltaTime);	
	void Render();						

	void ClearObject();					//2_������Ʈ ���� ����.

	void RemoveObject(class Object* a_pObj);	//2_Ư�� ������Ʈ�� ����
	void DropItem(class Object* a_pObj);		
	void GetBombData(class Bomb* a_refBomb) const;	//2_��ź ������ �����ͼ� ����
	void ObtainItem(eItem a_eItem);					//2_������ ȹ�������� ȹ���� ������ �˻� �� �÷��̾� �ɷ�ġ ����

private:		//2_�����̺����� ����
	// ������Ʈ
	std::vector<class Object*> m_vcObj;
	class Player* m_pPlayer = nullptr;

	// �������� ����
	int m_nNowStage = 0;
	float m_fGameTime = 0;	// ���������� ���� �ð�
	class MapData* m_refMap = nullptr; //2_Ÿ�԰��� class �� ���.
	char** m_pMap = nullptr;			//2_�ʵ����� �߰�

	// ������
	int m_nNowLife = 0;		// �÷��̾� ������
	int m_nScore = 0;		// ����

	//2_��ź��Ƴ��� ť �߰�.		
	std::queue<class Bomb*> m_qBomb;

	//2_���� �÷��̾� ������ �߰�.
	CharacterData m_stPlayerData;
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())
