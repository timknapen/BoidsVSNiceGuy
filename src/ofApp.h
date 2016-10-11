#pragma once

#include "ofMain.h"
#include "ofxButtons.h"
#include "Boid.hpp"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	
	// BOIDS
	vector < Boid > boids;  // the list of boids!
	float drag;				// slow down
	float attraction;		// amount of attraction force between boids
	float allign;			// amount of allign force between boids
	float separation;		// amount of separation force between boids (avoidance)
	
	// BOID functions
	void createBoids();		// create the boids
	void randomizeBoids();	// set boids to random new positions
	void drawBoids();		// draw all boids
	void updateBoids();		// update the boids positions!
	void flockBoids();		// do flocking
	
	// GUI!
	ButtonManager buttons;
	float zoneRadius, lowThresh, highThresh;
};
