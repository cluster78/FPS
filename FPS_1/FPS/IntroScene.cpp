#include "pch.h"
#include "IntroScene.h"

#include "SceneManager.h"

IntroScene::IntroScene(class SceneManager* a_pParent) : Scene(a_pParent)
{

}

IntroScene::~IntroScene() {}

eScene IntroScene::GetScene() const
{
	return eScene::Intro;
}

void IntroScene::Update(float a_fDeltaTime)
{
	if (IsKeyDown(eKey::A) == true)				//인트로씬에서 A키를 누르면 게임씬으로 넘어가는거 추가.
	{
		m_refParent->ChangeScene(eScene::Game);
	}

}

void IntroScene::Render()
{
	SetCursor(0, 0);							//커서 0,0 으로 옮김 추가.
	cout << "Intro Scene" << endl;
	cout << "Press Any Key" << endl;
}
