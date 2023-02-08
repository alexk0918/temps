#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "MiddleGround.h"

using namespace Webfoot;

TestLevel::TestLevel(){
	floor = NULL;
	tileOne = NULL;
	leftWall = NULL;
	cliff = NULL;

}

void TestLevel::Init(){
	floor = theImages->Load("Floor");
	tileOne = theImages->Load("platform");
	
	leftWall = theImages->Load("LeftWall");
	cliff = theImages->Load("Cliff");

	floorPos = Point2F::Create(0, theScreen->SizeGet().y - 80.0f);
	leftWallPos = Point2F::Create(0, floorPos.y- leftWall->SizeGet().y);
	
	tileOnePosition.Set(floorPos.x + 400, floorPos.y - 75);
	//tileOnePosition.Set(floorPos.x + 300, floorPos.y-5);
	onGround = FALSE;
}

void TestLevel::Deinit(){
	if (floor){
		theImages->Unload(floor);
		floor = NULL;	
	}
	if (tileOne){
		theImages->Unload(tileOne);
		tileOne = NULL;
	}
	if (leftWall){
		theImages->Unload(leftWall);	
		leftWall = NULL;
	}
	if (cliff){
		theImages->Unload(cliff);
		cliff = NULL;
	}
}

void TestLevel::Update(unsigned int dt, Cats* player){

	playerPos = player->PositionGet();
	playerVelocity = player->VelocityGet();

	if (playerVelocity.y != 0.0f){
		onGround = FALSE;
	}

	//the first box
	//checks top to make sure cat lands on it
	if ((playerPos.x <= tileOnePosition.x + tileOne->SizeGet().x + 10) && (playerPos.x >= tileOnePosition.x) && ((playerPos.y <= tileOnePosition.y - 15) && (playerPos.y >= tileOnePosition.y - 20))){
		player->PositionSet(playerPos.x, tileOnePosition.y - 20);
		groundCheck = TRUE;
	}
	//if its in the bounds otherwise push it out and change velocity
	else if ((playerPos.x <= tileOnePosition.x + tileOne->SizeGet().x + 10.0f) && (playerPos.x >= tileOnePosition.x - 10) && (playerPos.y >= tileOnePosition.y - 15)){
		if ((player->directionFacing() == FALSE) && (playerPos.x > tileOnePosition.x)){
			player->PositionSet(tileOnePosition.x + tileOne->SizeGet().x + 12.0f, playerPos.y);
		}
		else{ player->PositionSet(tileOnePosition.x - 12.0f, playerPos.y); }
		//player->VelocitySet(playerVelocity.x * -1, playerVelocity.y);
	}
	else{ groundCheck = FALSE; }

	//right cliff
	//checks top to make sure cat lands on it
	if ((playerPos.x >= theScreen->SizeGet().x - cliff->SizeGet().x) && (playerPos.y <= theScreen->SizeGet().y - cliff->SizeGet().y) && (playerPos.y >= theScreen->SizeGet().y - cliff->SizeGet().y-20)){
		player->PositionSet(playerPos.x, theScreen->SizeGet().y - cliff->SizeGet().y - 20);
		groundCheck = TRUE;
	}
	//if its in the bounds otherwise push it out
	else if ((playerPos.x >= theScreen->SizeGet().x - cliff->SizeGet().x) && (playerPos.y >= theScreen->SizeGet().y - cliff->SizeGet().y)){
		player->PositionSet(theScreen->SizeGet().x - cliff->SizeGet().x , playerPos.y);
		if (onGround != TRUE){
			player->VelocitySet(playerVelocity.x, playerVelocity.y);
		}
	}

	if (groundCheck == FALSE){
		onGround = FALSE;
	}
	else
	{
		onGround = TRUE;
	}

	//ground and walls
	if (playerPos.y >= floorPos.y - 25){
		onGround = TRUE;
		if (playerPos.y >= floorPos.y - 20){
			player->PositionSet(playerPos.x, floorPos.y - 25);
		}
	}
	if ((playerPos.x <= leftWall->SizeGet().x+15)&&(playerPos.y >= theScreen->SizeGet().y-leftWall->SizeGet().y)-80){
		if (onGround == TRUE){
			DebugPrintf("Wall \n");
			player->PositionSet(leftWall->SizeGet().x + 20, playerPos.y);
		}
		else
		{
			player->PositionSet(leftWall->SizeGet().x + 25, playerPos.y);
			DebugPrintf("Sending velocity change");
			player->VelocitySet(playerVelocity.x, playerVelocity.y);
		}
	}



}

void  TestLevel::Draw(){
	floor->Draw(floorPos);
	tileOne->Draw(tileOnePosition);
	leftWall->Draw(Point2F::Create(0, floorPos.y - leftWall->SizeGet().y));
	cliff->Draw(Point2F::Create(theScreen->SizeGet().x - cliff->SizeGet().x, theScreen->SizeGet().y - cliff->SizeGet().y));
}

void TestLevel::FloorDetection(Point2F catPosition, Point2F catVelocity){

}