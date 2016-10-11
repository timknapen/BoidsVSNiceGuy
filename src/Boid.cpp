//
//  Boid.cpp
//
//

#include "Boid.hpp"

//----------------------------------------------------
Boid::Boid(){
	maxSpeed = 20;
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
	double rot = getAngle();
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, 0);
	ofRotateZ( 180.0f *rot / PI);
	
	// draw a simple triangle
	ofBeginShape();
	ofVertex(0, -2);
	ofVertex(10, 0);
	ofVertex(0, 2);
	ofEndShape();
	
	ofPopMatrix();
}

//----------------------------------------------------
void Boid::update(float drag){

	// add the acceleration to the velocity
	vel += acc;

	// keep velocity within reasonable amounts
	if( vel.length() > maxSpeed){
		vel.normalize();
		vel *= maxSpeed;
	}
	// speed needs to be at least 1
	/*
	if( vel.length() < 1){
		vel.normalize();
	}
	*/
	// drag adds "resistance"
	vel *= drag;

	// add the speed to the position
	pos += vel;
	
	// set acceleration back to 0
	acc.set( 0, 0 );
	
}

//----------------------------------------------------
void Boid::keepInBounds(float minX, float minY, float maxX, float maxY){
	if(pos.x < minX ){
		pos.x = minX;
		vel.x = -vel.x;		// bounce on X axis
	}
	if(pos.x > maxX){
		pos.x = ofGetWidth();
		vel.x = -vel.x;		// bounce on X axis
	}
	if(pos.y < minY){
		pos.y = minY;
		vel.y = -vel.y;		// bounce on Y axis
	}
	if(pos.y > maxY){
		pos.y = maxY;
		vel.y = -vel.y;		// bounce on Y axis
	}
}

//----------------------------------------------------
double Boid::getAngle(){
	float x = 1;
	float y = 0;
	return -atan2( vel.x*y - vel.y*x, vel.x*x + vel.y*y );
}

