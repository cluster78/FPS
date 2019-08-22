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

	// 씬이랑은 관계없지만 나름 편하게 쓸법한 define 비슷한 값
	Scene_First = Intro,
};

enum class eObjectType
{
	None = 0,
	LevelGap = 1000,			//4_레벨 관련 이넘값 추가. 왜 추가됬는지 설명들었는데 이것만 봐서는 모르겠음.

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

enum class eItem	//eItem 이넘클래스 추가.
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
void SetCursorType(CURSOR_TYPE c);		//2_커서타입 추가.
void SetConsoleSize(int a_nWidth, int a_nHeight, int a_nX = 200, int a_nY = 200);	//4_콘솔 사이즈 변경 함수 추가

//using fpTask = void(*)();	 fpTask 제거.

struct RenderLine					//5_렌더라인 추가.
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

struct RenderTile								//5_렌더 타일 추가.
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

// 5_오브젝트 충돌처리용, 좌상단 0, 0기준
struct Rect
{
	float x;
	float y;
	float w;
	float h;

	bool IsCross(const Rect& rt)		//5_해당 좌표와 겹쳐있으면 false 아니면 true
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