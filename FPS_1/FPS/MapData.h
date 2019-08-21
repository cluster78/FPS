#pragma once

class MapData
{
public:

	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();
	static void Release();		//2_Release�Լ� �߰�.	//�� ������ ���� �����κа� �׷��ִ� �κ� �߰�.

private:
	static MapData m_arrData[eGame::MaxStage];		//2_�ʵ����� static���� �߰�.

private:
	void MakeMap();			//2_MakeMap() �߰�	�� ����.		
	void ReleaseData();			//2_ReleaseData() �߰�.	���� �� ������ ����.

public:
	void Render();				//2_Render() �߰�.

	int x;
	int y;
	const char* mapOriginData;		//2_������ ������ �߰�.	 ���������Ͱ� ���� �÷��̷� ���� �����Ǵ°� ����.
	char** pMap = nullptr;			//2_pMap �߰�.		����, ����� �� �����.
	//std::string map;				//2_map ����.
};