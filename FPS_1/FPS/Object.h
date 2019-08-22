#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Update(float a_fDelta);
	virtual void Render();									//3_���� �߰�
	void SetMap(char** a_refMap);							//2_�ʵ����� �����Լ� �߰�. 3_�Ҹ��ڿ� �ִ� ���� ����� ��ġ ����.	5_�ζ��� ����

	virtual void Init();									//2_��ź�̶� ����� ���úκ� �߰�.
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);
	inline void SetPos(int _x, int _y) { x = _x; y = _y; }	//2_�̵� �Լ��߰�.
	
	virtual Rect GetRendertRect() const;					//5_���� ���������Լ� �߰�.

	//virtual void Render();								2_���� ����. ������Ʈ�� �״� �ʿ��� �����Ͻŵ�.

protected:
	void Clear();
	virtual void _PreUpdate(float a_fDelta);				//5_�����ܰ��� ���� ����� �Լ� �߰�.
	virtual void _Update(float a_fDelta);

public:
	int x;							
	int y;
	Rect rt;												//5_���� ������ ��ġ ������ ����.

protected:													//3_private -> protected �� ����.
	static RenderTile Empty;								//5_Empty���� �߰�
	char** m_refMap = nullptr;								//2_�� ������ �޾ƿ�.
	RenderTile*	m_pNowAni = nullptr;						//3_NowAni���� �߰�.
};
