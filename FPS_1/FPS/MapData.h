#pragma once

class MapData
{
public:

	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();
	static void Release();		//2_Release�Լ� �߰�.  �� ������ ���� �����κа� �׷��ִ� �κ� �߰�.
	static eObjectType DataToObjectType(char c);	//4_������Ʈ Ÿ�� �о���� �Լ� �߰�
private:
	static MapData m_arrData[eGame::MaxStage];		//2_�ʵ����� static���� �߰�.

private:
	void MakeMapBuffer();			//2_MakeMap() �߰�	�� ����.	3_MakeMapBuffer()�� �̸� ����.
	void ReleaseData();			//2_ReleaseData() �߰�.	���� �� ������ ����.

public:
	void Render();				//2_Render() �߰�.

public:							//3_�ۺ� �߰�
	int x;
	int y;
	const char* mapOriginData;		//2_������ ������ �߰�.	 ���������Ͱ� ���� �÷��̷� ���� �����Ǵ°� ����.
	char** pMap = nullptr;			//2_pMap �߰�.		����, ����� �� �����.
	//std::string map;				//2_map ����.
};