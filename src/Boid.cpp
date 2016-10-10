//
//  Boid.cpp
//
//

#include "Boid.hpp"

//----------------------------------------------------
Boid::Boid(){
	speed = 0;
}

//----------------------------------------------------
Boid::Boid(float x, float y, float dirx, float diry){
	Boid(); // call the other costructor
	pos.set(x,y);
	vel.set(dirx,diry);
	mass = 5;
}

//----------------------------------------------------
void Boid::draw(){
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, 0);
	ofDrawEllipse(0, 0, 19,19);
	ofDrawLine(0, 0, 10*vel.x, 10*vel.y);
	ofPopMatrix();
}