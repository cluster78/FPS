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
