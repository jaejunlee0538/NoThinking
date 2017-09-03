#include "stdafx.h"
#include "cSceneTest.h"


cSceneTest::cSceneTest()
{
}


cSceneTest::~cSceneTest()
{
}

void cSceneTest::Setup()
{
	g_pSceneManager->addScene("heitmap", new cMainGame);
}

void cSceneTest::Update()
{
	g_pSceneManager->update();
}

void cSceneTest::Render()
{
	g_pSceneManager->render();
}
