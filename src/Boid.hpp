//
//  Boid.hpp
//
//

#ifndef Boid_hpp
#define Boid_hpp

#include "ofMain.h"

class Boid{

public:// All attributes and functions here can be called by other classes
	
	// The constructor
	Boid();
	Boid(float x, float y, float dirx, float diry); // Another constructor!
	
	void draw();				// draw the Boid to screen
	void update(float drag);	// update position, speed, etc.
	void keepInBounds(float minX, float minY, float maxX, float maxY);
	
	ofPoint pos;	// my position vector
	ofPoint vel;	// my velocity vector
	ofPoint acc;	// my acceleration vector ( F = m * a )
	
	float maxSpeed;
	
	vector <ofPoint > tail;
	
private:
	// all attributes and functions here can only be called by the instance/class itself
	double getAngle();	// get the angle in degrees
};

#endif /* Boid_hpp */
