#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// set background
	ofBackground(255);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// set variables!
	drag = 0.97f;
	attraction = 0.7;
	allign = 0.5;
	separation = 0.93;
	
	createBoids();
	randomizeBoids();
	
	// setup flocking variables
	zoneRadius =	60;
	lowThresh =		0.5f;
	highThresh =	0.95f;
	
	// setup mouse interaction
	mouseButton = -1;
	mouseRadius = 100;
	mouseForce	=	2;
	
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
	buttons.addListItem("Mouse");
	buttons.addSliderItem("Radius", 1, 300, mouseRadius);
	buttons.addSliderItem("Force", 0.01, 2, mouseForce);

	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
	flockBoids();
	updateBoids();
}

#pragma mark - DRAW
//--------------------------------------------------------------
void ofApp::draw(){
	drawNiceGuy();
	drawBoids();
	if(buttons.visible){
		ofSetColor(0);
		ofDrawBitmapString("FPS: "+ ofToString(ofGetFrameRate()), 10, ofGetHeight() - 15 );
	}
}

//--------------------------------------------------------------
void ofApp::drawNiceGuy(){
	// draw a face around the mouse if it's down
	ofNoFill();
	ofPushMatrix();
	ofTranslate(mousePos);
	if(mouseButton == OF_MOUSE_BUTTON_1){ // REPEL
		ofSetColor(255, 0, 0);
	}else if(mouseButton == OF_MOUSE_BUTTON_3 ){ // ATTRACT
		ofSetColor(0, 255, 0);
	}
	ofScale( mouseRadius/8, mouseRadius/8);
	if(mouseButton == OF_MOUSE_BUTTON_1){ // not so nice // REPEL
		ofDrawLine(-4, -5, -2, -4); // left eye
		ofDrawLine(4, -5, 2, -4); // right eye
		ofDrawLine(-4, 2, 4, 2); // mouth
		ofDrawLine(0, 0, 0, -4); // nose

	}else if( mouseButton == OF_MOUSE_BUTTON_3){ // nice // ATTRACT
		ofDrawLine(-4, -2, -3, -3); // left eye
		ofDrawLine(-3, -3, -2, -2);
		ofDrawLine(4, -2, 3, -3); // right eye
		ofDrawLine(3, -3, 2, -2);
		ofDrawLine(-5, 1, 0, 2); // mouth
		ofDrawLine( 0, 2, 5, 1); // mouth
		ofDrawLine(0, 0, 0, -4); // nose

	}
	ofBeginShape();
	// going around
	ofVertex( 0, -8);	// top
	ofVertex( 6, -6);	// right top
	ofVertex( 8, 0);	// right
	ofVertex( 6, 6);	// right bottom
	ofVertex( 0, 8);	// bottom
	ofVertex(-6, 6);	// bottom left
	ofVertex( -8, 0);	// left
	ofVertex(-6, -6);	// left top
	ofVertex( 0, -8);	// top
	
	ofEndShape();
	ofPopMatrix();
}

#pragma mark - BOIDS
//--------------------------------------------------------------
void ofApp::createBoids(){
	int numBoids = 500;
	for(int i = 0; i < numBoids; i++){
		Boid b;
		boids.push_back(b);
	}
}

//--------------------------------------------------------------
void ofApp::randomizeBoids(){
	for(int i =0; i< boids.size(); i++){
		boids[i].setPos(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		boids[i].vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
		boids[i].maxSpeed = 10 + ofRandom(10);
	}
}

//--------------------------------------------------------------
void ofApp::drawBoids(){
	ofEnableAlphaBlending();
	ofNoFill();
	ofSetColor(0, 100);
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
	
	ofPoint dir;
	float dist;
	
	for(int i = 0; i <boids.size();i++){
		for (int j = i+1; j < boids.size(); j++) {
			// optimize a little
			if(ABS(boids[i].pos.x - boids[j].pos.x) > zoneRadius ||
			   ABS(boids[i].pos.y - boids[j].pos.y) > zoneRadius
			   ){
				continue;
			}
			
			dir = boids[j].pos - boids[i].pos;
			dist = dir.length();
			
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
		
		if(mouseButton == OF_MOUSE_BUTTON_1){ // Repel to mouse
			dir = boids[i].pos - mousePos;
			dist = dir.length();
			if(dist < mouseRadius){
				boids[i].acc += dir.normalize() * (mouseRadius - dist)/mouseRadius * mouseForce;
			}
		}else if(mouseButton == OF_MOUSE_BUTTON_3){ // Attract to mouse
			dir = boids[i].pos - mousePos;
			dist = dir.length();
			if(dist < mouseRadius){
				boids[i].acc -= dir.normalize() * 0.1 * (mouseRadius - dist)/mouseRadius * mouseForce;
			}
		}
		
	}
	
}

#pragma mark - EVENTS
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
		case ' ':
			randomizeBoids();
			break;
		default:
			break;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	mousePos.set(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	mousePos.set(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouseButton = button;
	mousePos.set(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouseButton = -1;
	mousePos.set(x, y);
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