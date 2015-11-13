//
//  boid.h
//  blobs_and_boids
//
//  Created by Ben Snell on 11/12/15.
//
//

#ifndef __blobs_and_boids__boid__
#define __blobs_and_boids__boid__

#include "ofMain.h"

struct boid {
    
public:
    
    ofVec2f position;
    ofVec2f velocity;       // pixels per second
    ofVec2f acceleration;
//    float mass = 1.0;
    
    // temporary variables to help calculate all forces acting on boid
    ofVec2f globalForce;
    
    // temporary variables to handle alignment
    ofVec2f sumNeighborAlignments;
    int nNeighbors = 0;
    
};

class flockOfBoids {
    
public:
    
    int nBoids;
    vector<boid> boids; // holds all boids
    
    float mass = 1.0;
    
    // physics parameters (Atr > Sep > Aln)
    int rAttraction;    // radius of search
    int rSeparation;
    int rAlignment;
    // -2, 1
    float pAttraction;  // power of force (raise to power)
    float pSeparation;
    // 1, 1
    float sAttraction;  // strength of force (magnitude or scale factor)
    float sSeparation;
    // 1
    float wAlignment;   // weight of alignment

    float separationSpringOffset = 5.0; // higher numbers correlate to higher separation strength, but this number must be positive for force to behave like a compressing spring -- 5.0 seems to work well
    
    // amount that velocity and acceleration are intergrated each frame
    int accelerationStep;   // 16 seeems good
    int velocityStep;       // 116 seems good
    
    // ranges
    float minVel = 1./100.;   // 10 pixels per second
    float maxVel = 1./5.;    // 200 pixels per second
    
    // edge behavior
    Boolean wrapEdges = true;
    
    // enables "cursor wind" interaction
    Boolean cursorWind = false;
    
    void createFlock(int nBoids_);
    void setPhysics(int rAttraction_, int rSeparation_, int rAlignment_, float pAttraction_, float pSeparation_, float sAttraction_, float sSeparation_, float wAlignment_, int accelerationStep_, int velocityStep_, float separationSpringOffset_, float minVel_, float maxVel_);
    
//    void updateFlock(int timeStep); // time step is the amount of ellapsed time in ms since the last update of the flock
    
    void updateFlock();
    
    void renderFlock();
    
    void resetFlock();
    
};

#endif /* defined(__blobs_and_boids__boid__) */
