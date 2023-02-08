#include "Frog.h"
#include "MainGame.h"
#include "MainUpdate.h"
#include "FrogMath.h"
#include <Array>

using namespace Webfoot;

MainGame MainGame::instance;

//==============================================================================

/// Main GUI
#define GUI_LAYER_NAME "MainGame"

//-----------------------------------------------------------------------------

MainGame::MainGame()
{
	player = NULL;
	//background = NULL;
	bBall = NULL;
	level0 = NULL;
	camera = NULL;
	gameSound = NULL;
}

//-----------------------------------------------------------------------------

void MainGame::Init()
{
   Inherited::Init();

   player = frog_new Cats();
   player->Init();

   level0 = frog_new TestLevel();
   level0->Init();
   
   /*
   camera = frog_new Camera();
   camera->Init();
   */
   camera = frog_new Camera();
   camera->x = 0;
   camera->y = 0;
   camera->offsetX = 0;
   camera->offsetY = 0;

   gameSound = frog_new Audio();
   gameSound->Init();

   //background = theImages->Load("background");
   bBall = frog_new BackgroundBall();
   bBall->Init();
}


//-----------------------------------------------------------------------------

void MainGame::Deinit()
{
   // Deinitialize and delete the ball.
	if (player){
		player->Deinit();
		frog_delete player;
		player = NULL;
	}
	if (background){
		theImages->Unload(background);
		background = NULL;
	}
	if (bBall)
	{
		bBall->Deinit();
		frog_delete bBall;
		bBall = NULL;
	}
	if (level0){
		level0->Deinit();
		frog_delete level0;
		level0 = NULL;
	}
	if (camera){
		frog_delete camera;
		camera = NULL;
	}
	if (gameSound){
		frog_delete gameSound;
		gameSound = NULL;
	}

   Inherited::Deinit();
}

//-----------------------------------------------------------------------------

const char* MainGame::GUILayerNameGet()
{
   return GUI_LAYER_NAME;
}

//-----------------------------------------------------------------------------

void MainGame::Update()
{
   Inherited::Update();

   unsigned int dt = theClock->LoopDurationGet();

   level0->Update(dt, player);
   player->Update(dt, level0->getHitDetection(), level0->bonkDetection());
   //camera->Update(dt, player->PositionGet());
   camera->update(player->PositionGet().x, player->PositionGet().y);
   bBall->Update(dt);
   gameSound->Update(dt, player);


   // Return to the previous menu if the escape key is pressed.
   if(!theStates->StateChangeCheck() && theKeyboard->KeyJustPressed(KEY_ESCAPE))
   {
      theMainGame->StateChangeTransitionBegin(true);
      theStates->Pop();
   }
}

//-----------------------------------------------------------------------------

void MainGame::Draw()
{
	//background->Draw();
	bBall->Draw(camera->x, camera->y);
	player->Draw();
	level0->Draw();
}

//==============================================================================
