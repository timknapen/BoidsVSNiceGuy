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
	
	// Nice Guy
	void drawNiceGuy();
	
	// BOIDS
	vector < Boid > boids;  // the list of boids!
	float drag;				// slow down
	float attraction;		// amount of attraction force between boids
	float allign;			// amount of allign force between boids
	float separation;		// amount of separation force between boids (avoidance)
	bool bDoFlocking;		// be able to switch off flocking interaction

	// BOID functions
	void createBoids();		// create the boids
	void randomizeBoids();	// set boids to random new positions
	void drawBoids();		// draw all boids
	void updateBoids();		// update the boids positions!
	void flockBoids();		// do flocking
	void mouseInteraction();// avoid or attract mouse
	
	// GUI!
	ButtonManager buttons;
	float zoneRadius, lowThresh, highThresh;
	
	// the mouse
	int		mouseBehaviour; // 0  = nothing, 1 = attract, 2 = repel
	ofPoint	mousePos;
	float	mouseRadius;
	float	mouseForce;
	bool	bDrawMouse;
};
