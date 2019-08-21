#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();							//2_��ź�̶� ����� ���úκ� �߰�.
	virtual void Update(float a_fDelta);
	virtual void Render();							//3_���� �߰�
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }	//2_�̵� �Լ��߰�.
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr);m_refMap = a_refMap;  }	//2_�ʵ����� �����Լ� �߰�. 3_�Ҹ��ڿ� �ִ� ���� ����� ��ġ ����.


	//virtual void Render();				2_���� ����. ������Ʈ�� �״� �ʿ��� �����Ͻŵ�.

public:
	int x;							
	int y;

protected:		//3_private -> protected �� ����.
	char** m_refMap = nullptr;		//2_�� ������ �޾ƿ�.
	RenderTile*	m_pNowAni = nullptr;	//3_NowAni���� �߰�.
};
