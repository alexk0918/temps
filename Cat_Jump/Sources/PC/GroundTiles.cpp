#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "GroundTiles.h"

using namespace Webfoot;

Tiles::Tiles(){
	tileImage = NULL;
}

void Tiles::Init(int tile){
	if (tile = 0){
		tileImage = theImages->Load("Floor");
		position.Set(0, theScreen->SizeGet().y - 20);
	}
	else{ tileImage = theImages->Load("Platform"); }
}

void Tiles::Deinit(){
	if (tileImage){
		theImages->Unload(tileImage);
		tileImage = NULL;
	}
}

void Tiles::Update(){

}

void Tiles::Draw(){

}