#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();							//2_��ź�̶� ����� ���úκ� �߰�.
	virtual void Update(float a_fDelta);
	virtual void Explosived(class Bomb* a_refBomb);		
	virtual void Interaction(class Hero* a_refHero);	//������Ʈ ��ȣ�ۿ� �Լ�

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }	//2_�̵� �Լ��߰�.
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr); }	//2_�ʵ����� �����Լ� �߰�.


	//virtual void Render();				2_���� ����. ������Ʈ�� �״� �ʿ��� �����Ͻŵ�.

public:
	int x;							
	int y;

private:
	char** m_refMap = nullptr;		//2_�� ������ �޾ƿ�.
};
