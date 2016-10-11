#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// set background
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// set variables!
	drag = 0.95f;
	attraction = 0.9;
	allign = 0.7;
	separation = 0.5;
	
	createBoids();
	randomizeBoids();
	
	// setup flocking variables
	zoneRadius =	100;
	lowThresh =		0.3f;
	highThresh =	0.9f;
	
	// setup buttons
	buttons.setup();
	buttons.addSliderItem("Drag", 0.75, 0.99, drag);
	buttons.addSliderItem("Attraction", 0.01, 0.99, attraction);
	buttons.addSliderItem("Allign", 0.01, 0.99, allign);
	buttons.addSliderItem("Separation", 0.01, 0.99, separation);
	buttons.addListItem("Flocking");
	buttons.addSliderItem("Radius", 10, 300, zoneRadius);
	buttons.addSliderItem("low threshold", 0.1, 1, lowThresh);
	buttons.addSliderItem("high threshold", 0.1, 1, highThresh);

}

//--------------------------------------------------------------
void ofApp::update(){
	flockBoids();
	updateBoids();
}

#pragma mark - DRAW

//--------------------------------------------------------------
void ofApp::draw(){
	drawBoids();
}

#pragma mark - BOIDS

//--------------------------------------------------------------
void ofApp::createBoids(){
	int numBoids = 50;
	for(int i = 0; i < numBoids; i++){
		Boid b;
		boids.push_back(b);
	}
}

//--------------------------------------------------------------
void ofApp::randomizeBoids(){
	for(int i =0; i< boids.size(); i++){
		boids[i].pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		boids[i].vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
	}
}

//--------------------------------------------------------------
void ofApp::drawBoids(){
	ofNoFill();
	ofSetColor(255, 0, 100);
	for(int i =0; i< boids.size(); i++){
		boids[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::updateBoids(){

	for (int i = 0; i < boids.size(); i++) {
		// update the position and speed
		boids[i].update(drag);
		// keep boid inside the screen!
		boids[i].keepInBounds(0, 0, ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::flockBoids(){
	
	for(int i = 0; i <boids.size();i++){
		for (int j = i+1; j < boids.size(); j++) {
			ofPoint dir = boids[j].pos - boids[i].pos;
			float dist = dir.length();
			
			
			if( dist <= zoneRadius ) {	// SEPARATION
				float percent = dist/zoneRadius;
				if( percent < lowThresh ) { // ... and is within the threshold limits, separate...
					float F = ( lowThresh/percent - 1.0f ) * 0.01;
					dir = dir.getNormalized() * F * separation;
					boids[i].acc -= dir;
					boids[j].acc += dir;
				} else if( percent < highThresh ) { // ... else if it is within the higher threshold limits, align...
					float threshDelta = highThresh - lowThresh;
					float adjustedPercent = ( percent - lowThresh )/threshDelta;
					float F = ( 0.5f - cos( adjustedPercent * M_PI * 2.0f ) * 0.5f + 0.5f ) * 0.01;
					boids[i].acc += boids[j].vel.getNormalized() * F * allign;
					boids[j].acc += boids[i].vel.getNormalized() * F * allign;
				}
				else { // ... else, attract.
					float threshDelta = 1.0f - highThresh;
					float adjustedPercent = ( percent - highThresh )/threshDelta;
					float F = ( 0.5f - cos( adjustedPercent * M_PI * 2.0f ) * 0.5f + 0.5f ) * 0.01;
					dir = dir.getNormalized() * F * attraction;
					boids[i].acc += dir;
					boids[j].acc -= dir;
				}
			}
		}
	}
	
}

#pragma mark - EVENTS
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}