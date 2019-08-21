#pragma once

class MapData
{
public:

	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();
	static void Release();		//2_Release함수 추가.	//맵 데이터 생성 삭제부분과 그려주는 부분 추가.

private:
	static MapData m_arrData[eGame::MaxStage];		//2_맵데이터 static으로 추가.

private:
	void MakeMap();			//2_MakeMap() 추가	맵 제작.		
	void ReleaseData();			//2_ReleaseData() 추가.	현재 맵 데이터 삭제.

public:
	void Render();				//2_Render() 추가.

	int x;
	int y;
	const char* mapOriginData;		//2_오리진 데이터 추가.	 원본데이터가 게임 플레이로 인해 수정되는걸 방지.
	char** pMap = nullptr;			//2_pMap 추가.		제작, 변경된 맵 저장용.
	//std::string map;				//2_map 제거.
};