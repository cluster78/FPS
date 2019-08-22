#include "pch.h"
#include "Ani.h"

//Ani::Ani()		//5_������ ����.
//{
//}

Ani::~Ani()
{
}

void Ani::Resize(int a_nAniTypeCount)
{
	m_vcAni.resize(a_nAniTypeCount);
}

void Ani::Add(int a_nAni, const RenderTile& tile)
{
	assert(a_nAni < m_vcAni.size() && "logic error - Call Resize");
	m_vcAni[a_nAni].push_back(tile);
}

void Ani::Add(int a_nAniType, const std::initializer_list<RenderTile>& tiles)		//5_����Ʈ�� �޾������.
{
	for (auto& tile : tiles)
	{
		Add(a_nAniType, tile);
	}
}

void Ani::SetState(int a_nAni, int a_nCut /*= 0*/)
{
	m_pCurrentAni = &m_vcAni[a_nAni];

	m_nAniType = a_nAni;
	m_nCut = a_nCut;
	m_nNowMaxCut = m_pCurrentAni->size();
	m_fNowTile = 0.0f;				//5_�ʱⰪ ����
}

void Ani::NextCut()					//5_�������� ���������� �Ѱ���.
{
	++m_nCut;
	m_nCut %= m_nNowMaxCut;
}

void Ani::Update(float a_fDeltaTime)	//5_�ִϸ��̼� �ð��Ǹ� ���������� �Ѱ���.
{
	m_fNowTile += a_fDeltaTime;
	if (m_fNowTile > a_fCutTime)
	{
		NextCut();
		m_fNowTile = 0;
	}
}


RenderTile* Ani::Get()
{
	RenderTile* r = &(*m_pCurrentAni)[m_nCut++];
	//m_nCut %= m_nNowMaxCut;		5_����
	return r;
}
