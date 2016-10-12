//
//  Boid.cpp
//
//

#include "Boid.hpp"

//----------------------------------------------------
Boid::Boid(){
	maxSpeed = 20;
	
	// create the points for the tail
	for(int i = 0; i < 30; i++){
		tail.push_back(ofPoint());
	}
}

//----------------------------------------------------
Boid::Boid(float x, float y, float dirx, float diry){
	Boid(); // call the other constructor
	pos.set(x,y);
	vel.set(dirx,diry);
	
	// set the tail to the position
	for(int i = 0; i < tail.size(); i++){
		tail[i].set(pos);
	}
}

//----------------------------------------------------
void Boid::draw(){
	double rot = getAngle();
	
	// draw the tail
	for(int i = 0; i < tail.size()-1; i++){
		ofDrawLine(tail[i].x, tail[i].y, tail[i+1].x, tail[i+1].y);
	}
	
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, 0);
	ofRotateZ( 180.0f *rot / PI);
	
	// draw a simple triangle
	ofBeginShape();
	ofVertex(-10, -3);
	ofVertex(0, 0);
	ofVertex(-10, 3);
	ofEndShape();
	ofPopMatrix();
}

//----------------------------------------------------
void Boid::update(float drag){

	// add a tiny little bit of noise to the motion
	vel += ofPoint( vel.x * ofRandom(-0.1, 0.1), vel.y * ofRandom(-0.1, 0.1));
	
	// add the acceleration to the velocity
	vel += acc;

	// keep velocity within reasonable amounts
	if( vel.length() > maxSpeed){
		vel.normalize();
		vel *= maxSpeed;
	}

	// drag adds "resistance"
	vel *= drag;

	// add the speed to the position
	pos += vel;
	
	// set acceleration back to 0
	acc.set( 0, 0 );
	
	// update the tail
	for(int i = 0; i < tail.size()-1; i++){
		tail[i] = tail[i+1];
	}
	tail[tail.size()-1] = pos;
}

//----------------------------------------------------
void Boid::keepInBounds(float minX, float minY, float maxX, float maxY){
	bool jump = false;
	if(pos.x < minX ){
		pos.x = maxX;
		jump = true;
	}
	if(pos.x > maxX){
		pos.x = minX;
		jump = true;
	}
	if(pos.y < minY){
		pos.y = maxY;
		jump = true;
	}
	if(pos.y > maxY){
		pos.y = minY;
		jump = true;
	}
	if(jump){
		setPos(pos.x, pos.y);
	}
}

//----------------------------------------------------
void Boid::bounceOffBounds(float minX, float minY, float maxX, float maxY){
	if(pos.x < minX ){
		pos.x = minX;
		vel.x = -vel.x;		// bounce on X axis
	}
	if(pos.x > maxX){
		pos.x = maxX;
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
void Boid::setPos(float x, float y){
	pos.set(x,y);
	for(int i = 0; i < tail.size(); i++){
		tail[i].set(x,y);
	}
}

//----------------------------------------------------
double Boid::getAngle(){
	float x = 1;
	float y = 0;
	return -atan2( vel.x*y - vel.y*x, vel.x*x + vel.y*y );
}

