#include "pch.h"
#include "MapData.h"

MapData MapData::m_arrData[eGame::MaxStage] = { {}, };		//2_�ʱ�ȭ. �߰�.

MapData* MapData::Get(int a_nStage)
{
	return &m_arrData[a_nStage];
}

void MapData::Init()
{
	// 1��������
	m_arrData[0].x = 10;
	m_arrData[0].y = 10;
	m_arrData[0].mapOriginData = 		//2_m_arrData[0,1,2].map ����.		
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[0].MakeMapBuffer();				//2_1�������� �������. �߰�

	// 2��������
	m_arrData[1].x = 10;
	m_arrData[1].y = 10;
	m_arrData[1].mapOriginData =		
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[1].MakeMapBuffer();				//2_2�������� �������.�߰�

	// 3��������
	m_arrData[2].x = 10;
	m_arrData[2].y = 10;
	m_arrData[2].mapOriginData =		
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";

	m_arrData[2].MakeMapBuffer();				//2_3�������� �������.�߰�
}

void MapData::Release()
{
	for (auto& MapData : m_arrData)
	{
		MapData.ReleaseData();
	}
}

void MapData::MakeMapBuffer()
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	pMap = new char*[nY];

	for( int i=0; i<nY; ++i )
	{
		pMap[i] = new char[nX + 1];
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
	int nY = y * TileSize;				

	for (int i = 0; i < nY; ++i)
	{
		cout << pMap[i] << endl;
	}
}