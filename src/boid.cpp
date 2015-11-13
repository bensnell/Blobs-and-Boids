//
//  boid.cpp
//  blobs_and_boids
//
//  Created by Ben Snell on 11/12/15.
//
//

#include "boid.h"

// initialize boids
void flockOfBoids::createFlock(int nBoids_) {
    
    nBoids = nBoids_;
    
    for (int i = 0; i < nBoids; i++) {
        boid tempBoid;
        
        // start with random position and velocity
        tempBoid.position = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        tempBoid.velocity = ofVec2f(ofRandom(minVel, maxVel), ofRandom(minVel, maxVel));
        
        // multiply each velocity by 0.5*(floor(ofRandom(0, 2)) - 0.5) to get a positive or negative number
        
        // start with no forces acting on boid (F = 0)
        // Since F = ma and a = F / m, a = 0
        tempBoid.acceleration = ofVec2f(0., 0.);
        
        boids.push_back(tempBoid);
    }
}

// set the physics of the system
void flockOfBoids::setPhysics(int rAttraction_, int rSeparation_, int rAlignment_, float pAttraction_, float pSeparation_, float sAttraction_, float sSeparation_, float wAlignment_, int accelerationStep_, int velocityStep_) {
    
    rAttraction = rAttraction_;
    rSeparation = rSeparation_;
    rAlignment = rAlignment_;
    pAttraction = pAttraction_;
    pSeparation = pSeparation_;
    sAttraction = sAttraction_;
    sSeparation = sSeparation_;
    wAlignment = wAlignment_;
    accelerationStep = accelerationStep_;
    velocityStep = velocityStep_;
}

// update the positions of the flock according to the physics, etc.
void flockOfBoids::updateFlock() {
    
    // reset global force and alignment helpers
    for (int i = 0 ; i < nBoids; i++) {
        
        boids[i].globalForce = ofVec2f(0., 0.);
        
        boids[i].sumNeighborAlignments = ofVec2f(0., 0.);
        boids[i].nNeighbors = 0;
        
        if (cursorWind) {
            // Add "wind" according to mouse position
            boids[i].globalForce += ofVec2f((ofGetMouseX() - ofGetWidth()/2.)/1000000., (ofGetMouseY() - ofGetHeight()/2.)/1000000.);
        }
    }
    
    // -----------------------------------
    // ---------- GLOBAL FORCES ----------
    // -----------------------------------
    
    // update forces on the boids
    for (int i = 0; i < nBoids - 1; i++) {      // boid i
        for (int j = i + 1; j < nBoids; j++) {  // boid j
            
            // find the distance between these two boids
            ofVec2f pDiff = boids[j].position - boids[i].position;
            float dist = pDiff.length();
            
            // ----------- ATTRACTION ------------
            
            if (dist < rAttraction) {
            
                // force of attraction on I from J
                float magAttraction = sAttraction * pow(dist, pAttraction);
                ofVec2f fAttractionIJ = pDiff.getScaled(magAttraction);
                boids[i].globalForce += fAttractionIJ;
                boids[j].globalForce += -fAttractionIJ;
            }
                
            // ----------- SEPARATION ------------
            
            if (dist < rSeparation) {
                
                // force of separation on I from J
                float magSeparation = 5 + sSeparation * pow(dist, pSeparation);
                ofVec2f fSeparationIJ = -pDiff.getScaled(magSeparation);
                boids[i].globalForce += fSeparationIJ;
                boids[j].globalForce += -fSeparationIJ;
            }
            
            // ------------ ALIGNMENT ------------
            
            if (dist < rAlignment) {
            
                // add normalized direction vector of i to j and j to i and increase their neightbor count
                boids[i].sumNeighborAlignments += boids[j].velocity.getNormalized();
                boids[i].nNeighbors++;
                
                boids[j].sumNeighborAlignments += boids[i].velocity.getNormalized();
                boids[j].nNeighbors++;
            }
        }
    }
    
    // -----------------------------------
    // ------- FINALIZE ALIGNMENT --------
    // -----------------------------------
    
    // weight the alignment
    for (int i = 0; i < nBoids; i++) {
        ofVec2f tempAlignment;
        tempAlignment = wAlignment * boids[i].velocity.getNormalized() + (1.0 - wAlignment) * boids[i].sumNeighborAlignments / (float)boids[i].nNeighbors;
        boids[i].velocity = tempAlignment.scale(boids[i].velocity.length());
    }
    
    // -----------------------------------
    // ------------ POSITIONS ------------
    // -----------------------------------
    
    // update positions of each boid
    for (int i = 0; i < nBoids; i++) {
        
        // acceleration = force / mass
        boids[i].acceleration = boids[i].globalForce * boids[i].mass;
        
        // velocity += accleration * time step
        boids[i].velocity += boids[i].acceleration * accelerationStep; // CHANGE
        
        // clamp velocity
        if (boids[i].velocity.length() > maxVel) boids[i].velocity.scale(maxVel);
        
        // dampening
//        boids[i].velocity *= 0.96;
        
        // position += velocity * time
        boids[i].position += boids[i].velocity * velocityStep;
        
        // update boundaries of particles
        if (wrapEdges) {    // torus wrap
            if (boids[i].position.x < 0 || boids[i].position.x > ofGetWidth()) {
                float tempPos = boids[i].position.x + (float)ofGetWidth();
                boids[i].position.x = fmod(tempPos, (float)ofGetWidth());
            }
            if (boids[i].position.y < 0 || boids[i].position.y > ofGetHeight()) {
                float tempPos = boids[i].position.y + (float)ofGetHeight();
                boids[i].position.y = fmod(tempPos, (float)ofGetHeight());
            }
        } else {            // bounce
            if (boids[i].position.x < 0 || boids[i].position.x > ofGetWidth()) {
                boids[i].velocity.x *= -1.;
            }
            if (boids[i].position.y < 0 || boids[i].position.y > ofGetHeight()) {
                boids[i].velocity.y *= -1.;
            }
        }
    }
}

// render the flock to screen
void flockOfBoids::renderFlock() {

    for (int i = 0; i < nBoids; i++) {
        ofSetColor(255);

        ofCircle(boids[i].position, 1.2);
    }
    
}

// reset flock
void flockOfBoids::resetFlock() {
    
    for (int i = 0; i < nBoids; i++) {
        
        boids[i].position = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        boids[i].velocity = ofVec2f(ofRandom(minVel, maxVel), ofRandom(minVel, maxVel));
        boids[i].acceleration = ofVec2f(0., 0.);
    }
}