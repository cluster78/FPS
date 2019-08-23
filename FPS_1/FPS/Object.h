#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;
	virtual bool CanMove() const;

	bool Update(float a_fDelta);
	void Render();									//3_���� �߰�
	void SetMap(char** a_refMap);							//2_�ʵ����� �����Լ� �߰�. 3_�Ҹ��ڿ� �ִ� ���� ����� ��ġ ����.	5_�ζ��� ����
	void RenderClear();

	virtual void Init();									//2_��ź�̶� ����� ���úκ� �߰�.
	virtual bool Explosived();
	virtual bool Interaction(class Player* a_refHero);		//6_bool�� �����Ͽ� ���ϰ�����.

	inline void SetPos(int _x, int _y) { x = _x; y = _y; rt.x = _x; rt.y = _y; }	//2_�̵� �Լ��߰�.
	inline bool IsCross(const Object& a_refObj)				//6_��ħ �˻��Լ�
	{
		return rt.IsCross(a_refObj.rt);
	}
	inline bool IsCross(Object* a_refObj)
	{
		assert((a_refObj != nullptr) && " arg error");
		return IsCross(*a_refObj);
	}
	virtual Rect GetRendertRect() const;					//5_���� ���������Լ� �߰�.

	//virtual void Render();								2_���� ����. ������Ʈ�� �״� �ʿ��� �����Ͻŵ�.

protected:
	//void Clear();			6_����Ŭ����� ��Ī ����.
	virtual void _PreUpdate(float a_fDelta);				//5_�����ܰ��� ���� ����� �Լ� �߰�.
	virtual bool _Update(float a_fDelta);					//6_void���� bool������ ����.

public:
	int x;							
	int y;
	Rect rt;												//5_���� ������ ��ġ ������ ����.

protected:													//3_private -> protected �� ����.
	static RenderTile Empty;								//5_Empty���� �߰�
	char** m_refMap = nullptr;								//2_�� ������ �޾ƿ�.
	RenderTile*	m_pNowAni = nullptr;						//3_NowAni���� �߰�.
};
