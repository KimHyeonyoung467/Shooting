#include "pch.h"
#include "DemoGameApp.h"

#include "..//ShootModule//PlayScene.h"
#include "..//ShootModule//MenuScene.h"
#include "..//ShootModule//EndScene.h"

DemoGameApp::DemoGameApp() :
	m_scene(make_shared<Scenes::SceneManager>())
	, m_player(PlayerObject::create(m_scene))
{

}

void DemoGameApp::Initialize()
{
	__super::Initialize();

	// 씬 생성 
	m_scene->CreateScene("Menu", make_unique<Scenes::MenuScene>());
	m_scene->CreateScene("Play", make_unique<Scenes::PlayScene>());
	m_scene->CreateScene("End", make_unique<Scenes::EndScene>());

	m_scene->ChangeScene("Play");

	m_scene->getcurentScene()->Initialize();

	// GameObject 추가 
	m_player->Initialize();
	m_scene->getcurentScene()->addGameObject(m_player);

	// function 등록을 위한 람다 형식 정의 
	// 디버깅 시 의미를 알기 어려우니 주의. 
	auto enemyFactory = [this]()->GameObject*
		{
			return EnemyObject::create(m_player->getTransform(), m_scene);
		};

	// function 에  등록하여서 생성 
	if (m_scene->getcurentScene())
	{
		m_scene->getcurentScene()->SetEnemyCreator(enemyFactory);
	}

	if (m_player->IsDead())
	{
		m_scene->ChangeScene("End");
	}
}

void DemoGameApp::update()
{
	__super::update();

	m_scene->update();
}

void DemoGameApp::Render()
{
	__super::Render();

	// 씬 매니저의 렌더 호출. 
	m_scene->Render();

	endDraw();
}


