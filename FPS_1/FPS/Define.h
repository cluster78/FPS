#pragma once

using std::cout;
using std::endl;

enum class eUpdateState
{
	Run,
	Final,
};

enum class eKey
{
	None = -1,

	A,
	Left,
	W,
	Up,
	S,
	Right,
	D,
	Down,
	SPACE,
	Fire,

	Max,
};

enum class eInputState : short
{
	None	= 0b00,
	Down	= 0b11,
	Press	= 0b01,
	Up		= 0b10,
};

enum class eScene
{
	Intro,
	Game,
	GameOver,

	// ���̶��� ��������� ���� ���ϰ� ������ define ����� ��
	Scene_First = Intro,
};

enum class eObjectType
{
	None = 0,
	LevelGap = 1000,			//4_���� ���� �̳Ѱ� �߰�. �� �߰������ �������µ� �̰͸� ������ �𸣰���.

	Level1 = LevelGap * 1,
	Level2 = LevelGap * 2,
	Level3 = LevelGap * 3,
	LevelMax = 3,

	Wall = Level1 + 1,
	Box,
	Door,

	Item = Level2 + 1,
	Bomb,

	Player = Level3 + 1,
	Monster,
	
};

enum class eItem	//eItem �̳�Ŭ���� �߰�.
{
	None = -1,

	PowerUp,
	BombCount,
	SpeedUp,

	Max,
};

enum eGame
{
	MaxStage = 3,
	TileSize = 5,
};

#define SAFE_DELETE(x)		{ if((x) != nullptr ) { delete (x); (x) = nullptr; } }
#define SAFE_DELETE_ARR(x)	{ if((x) != nullptr ) { delete[] (x); (x) = nullptr; } }

using RenderTile = char[TileSize][TileSize];

enum class CURSOR_TYPE { NOCURSOR, SOLIDCURSOR, NORMALCURSOR };

void SetCursor(const COORD& a_stPos);
void SetCursor(int a_nPosX, int a_nPosY);
void SetCursorType(CURSOR_TYPE c);		//2_Ŀ��Ÿ�� �߰�.
void SetConsoleSize(int a_nWidth, int a_nHeight, int a_nX = 200, int a_nY = 200);	//4_�ܼ� ������ ���� �Լ� �߰�

//using fpTask = void(*)();	 fpTask ����.

struct RenderLine					//5_�������� �߰�.
{
	RenderLine() = default;

	RenderLine(std::initializer_list<char> a)		
	{
		assert(a.size() <= TileSize);

		int nIndex = 0;
		for (auto& _c : a)
		{
			c[nIndex++] = _c;
		}

		c[TileSize] = 0;
	}

	RenderLine(const char* s)
	{
		int nLen = strlen(s);
		assert(nLen <= TileSize);

		strcpy_s(c, sizeof(char)*(TileSize + 1), s);
	}

	operator const char*() const
	{
		return c;
	}

	char c[TileSize + 1];
};

struct RenderTile								//5_���� Ÿ�� �߰�.
{
	RenderTile() = default;
	RenderTile(std::initializer_list<RenderLine> a)
	{
		assert(a.size() <= TileSize);

		int nIndex = 0;
		for (auto& _c : a)
		{
			l[nIndex++] = _c;
		}
	}

	RenderLine& operator[](int a_nIndex)
	{
		assert(a_nIndex >= 0 && a_nIndex <= TileSize);
		return l[a_nIndex];
	}

	RenderLine l[TileSize];

};

// 5_������Ʈ �浹ó����, �»�� 0, 0����
struct Rect
{
	float x;
	float y;
	float w;
	float h;

	bool IsCross(const Rect& rt)		//5_�ش� ��ǥ�� ���������� false �ƴϸ� true
	{
		if ((x >= rt.x + rt.w) ||
			(x + w <= rt.x) ||
			(y >= rt.y + h) ||
			(y + h <= rt.y))
		{
			return false;
		}

		return true;
	}
};