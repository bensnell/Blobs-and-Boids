#pragma once

#include "ofMain.h"
#include "boid.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    flockOfBoids myFlock;
    
    // GUI
    
    ofxPanel panel;
    
    ofParameter<int> atr_radius;
    ofParameter<float> atr_power;
    ofParameter<float> atr_strength;
    ofParameterGroup atr_params;
    
    ofParameter<int> sep_radius;
    ofParameter<float> sep_power;
    ofParameter<float> sep_strength;
    ofParameter<float> spring_offset;
    ofParameterGroup sep_params;
    
    ofParameter<int> aln_radius;
    ofParameter<float> aln_weight;
    ofParameterGroup aln_params;
    
    ofParameter<int> step_acc;
    ofParameter<int> step_vel;
    ofParameter<float> min_vel;
    ofParameter<float> max_vel;
    ofParameterGroup timing_params;
    
    ofParameter<bool> bWind;
    ofParameter<bool> bWrap;
    ofParameter<float> boid_mass;
    ofParameterGroup visual_params;
    
    Boolean bDrawGui = true;
    
};
