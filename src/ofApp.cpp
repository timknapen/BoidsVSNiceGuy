#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// set background
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// set variables!
	drag = 0.95f;
	attraction = allign = separation = 0.1;
	
	createBoids();
	randomizeBoids();
}

//--------------------------------------------------------------
void ofApp::update(){
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