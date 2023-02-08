#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "Camera.h"

using namespace Webfoot;

/*
Camera::Camera(){

}

void Camera::Init(){
	float offsetX = 0;
	float offsetY = 0;
}

void Camera::Deinit(){

}

void Camera::Update(unsigned int dt, Point2F catPosition){
	position.x =  catPosition.x + offsetX;
	position.y = catPosition.y + offsetY;
}

void Camera::Draw(){

}
*/

Camera::Camera(){
	float x = 0;
	float y = 0;
	float offsetX = 0;
	float offsetY = 0;
}

void Camera::update(float playerX, float playerY) {
	x = playerX + offsetX;
	y = playerY + offsetY;
}