#include "pch.h"
#include "MapData.h"

MapData MapData::m_arrData[eGame::MaxStage] = { {}, };		//2_초기화. 추가.

MapData* MapData::Get(int a_nStage)
{
	return &m_arrData[a_nStage - 1];
}

void MapData::Init()					//4_맵 데이터 형태 변경(숫자에서 문자로)
{
	// 1스테이지
	m_arrData[0].x = 10;
	m_arrData[0].y = 10;
	m_arrData[0].mapOriginData = 		//2_m_arrData[0,1,2].map 변경.		
		"WWWWWWWWWW"
		"W      B W"
		"W B   B  W"
		"W  B     W"
		"W  B     W"
		"W  B     W"
		"W  B  M  W"
		"W  B     W"
		"W PIIIII W"
		"WWWWWWWWWW";
	m_arrData[0].MakeMapBuffer();				//2_1스테이지 만들어줌. 추가

	// 2스테이지
	m_arrData[1].x = 10;
	m_arrData[1].y = 10;
	m_arrData[1].mapOriginData =		
		"WWWWWWWWWW"
		"W  I   B W"
		"W B   B  W"
		"W  B     W"
		"W  B     W"
		"W  B     W"
		"W  B  M  W"
		"W  B     W"
		"W P      W"
		"WWWWWWWWWW";
	m_arrData[1].MakeMapBuffer();				//2_2스테이지 만들어줌.추가

	// 3스테이지
	m_arrData[2].x = 10;
	m_arrData[2].y = 10;
	m_arrData[2].mapOriginData =		
		"WWWWWWWWWW"
		"W      B W"
		"W B   B  W"
		"W  B     W"
		"W  B  I  W"
		"W  B     W"
		"W  B  M  W"
		"W  B     W"
		"W P      W"
		"WWWWWWWWWW";

	m_arrData[2].MakeMapBuffer();				//2_3스테이지 만들어줌.추가

	cout << "map ok" << endl;					//4_로그 추가.
}

void MapData::Release()
{
	for (auto& MapData : m_arrData)
	{
		MapData.ReleaseData();
	}
}

eObjectType MapData::DataToObjectType(char c)		//4_ 맵데이터가 문자로 바뀌면서 오브젝트타입을 한번 검사해서 리턴해주는 함수를 추가한듯.
{
	eObjectType eReturn = eObjectType::None;

	switch (c)
	{
	case ' ': { return eObjectType::None; } break;
	case 'W': { return eObjectType::Wall; } break;
	case 'B': { return eObjectType::Box; } break;
	case 'D': { return eObjectType::Door; } break;

	case 'I': { return eObjectType::Item; } break;
	//case 'O': { return eObjectType::Bomb; } break;		//5_폭탄 주석처리.
	case 'M': { return eObjectType::Monster; } break;
	case 'P': { return eObjectType::Player; } break;
	}

	assert(eReturn != eObjectType::None);
	return eReturn;
}




void MapData::MakeMapBuffer()
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	pMap = new char*[nY];

	for( int i=0; i<nY; ++i )
	{
		pMap[i] = new char[nX + 1];

		memset(pMap[i], ' ', sizeof(char)*(nX + 1));		//4_공백이 추가되는데 왜 추가해주는지 모르겠음.
		pMap[i][nX] = 0;
	}
}

void MapData::ReleaseData()
{
	int nY = y * TileSize;

	for (int i = 0; i < nY; ++i)
	{
		SAFE_DELETE_ARR(pMap[i])
	}

	SAFE_DELETE_ARR(pMap);
}

void MapData::Render()
{
	SetCursor(0, 0);				//4_ 커서위치 0,0으로 옮김. 랜더 위치잡아주려고 추가한듯?

	int nY = y * TileSize;				

	for (int i = 0; i < nY; ++i)
	{
		cout << pMap[i] << endl;
	}
}