#include "pch.h"
#include "MapData.h"

MapData MapData::m_arrData[eGame::MaxStage] = { {}, };		//2_�ʱ�ȭ. �߰�.

MapData* MapData::Get(int a_nStage)
{
	return &m_arrData[a_nStage - 1];
}

void MapData::Init()					//4_�� ������ ���� ����(���ڿ��� ���ڷ�)
{
	// 1��������
	m_arrData[0].x = 10;
	m_arrData[0].y = 10;
	m_arrData[0].mapOriginData = 		//2_m_arrData[0,1,2].map ����.		
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
	m_arrData[0].MakeMapBuffer();				//2_1�������� �������. �߰�

	// 2��������
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
	m_arrData[1].MakeMapBuffer();				//2_2�������� �������.�߰�

	// 3��������
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

	m_arrData[2].MakeMapBuffer();				//2_3�������� �������.�߰�

	cout << "map ok" << endl;					//4_�α� �߰�.
}

void MapData::Release()
{
	for (auto& MapData : m_arrData)
	{
		MapData.ReleaseData();
	}
}

eObjectType MapData::DataToObjectType(char c)		//4_ �ʵ����Ͱ� ���ڷ� �ٲ�鼭 ������ƮŸ���� �ѹ� �˻��ؼ� �������ִ� �Լ��� �߰��ѵ�.
{
	eObjectType eReturn = eObjectType::None;

	switch (c)
	{
	case ' ': { return eObjectType::None; } break;
	case 'W': { return eObjectType::Wall; } break;
	case 'B': { return eObjectType::Box; } break;
	case 'D': { return eObjectType::Door; } break;

	case 'I': { return eObjectType::Item; } break;
	//case 'O': { return eObjectType::Bomb; } break;		//5_��ź �ּ�ó��.
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

		memset(pMap[i], ' ', sizeof(char)*(nX + 1));		//4_������ �߰��Ǵµ� �� �߰����ִ��� �𸣰���.
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
	SetCursor(0, 0);				//4_ Ŀ����ġ 0,0���� �ű�. ���� ��ġ����ַ��� �߰��ѵ�?

	int nY = y * TileSize;				

	for (int i = 0; i < nY; ++i)
	{
		cout << pMap[i] << endl;
	}
}