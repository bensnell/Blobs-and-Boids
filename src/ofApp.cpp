#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){    
//    ofSetBackgroundAuto(false);
//    ofBackground(0, 0, 0);
//    ofEnableAlphaBlending();
    
//    panel.getParameter().addListener(this,&ofApp::paramChanged);
//    panel.addListener(this,&ofApp::paramChanged);
    
    myFlock.createFlock(500);
    
    atr_params.setName("Attraction");
    atr_params.add(atr_radius.set("radius", 100, 1, 1000));
    atr_params.add(atr_power.set("power", -2.0, -5.0, 5.0));
    atr_params.add(atr_strength.set("strength", 1.0, 0.0, 20.0));
    
    sep_params.setName("Separation");
    sep_params.add(sep_radius.set("radius", 10, 1, 1000));
    sep_params.add(sep_power.set("power", -1.0, -5.0, 5.0));
    sep_params.add(sep_strength.set("strength", 1.0, 0.0, 20.0));
    sep_params.add(spring_offset.set("spring offset", 5.0, -15.0, 15.0));
    
    aln_params.setName("Alignment");
    aln_params.add(aln_radius.set("radius", 100, 1, 1000));
    aln_params.add(aln_weight.set("weight", 0.1, 0.0, 1.0));
    
    timing_params.setName("Timing");
    timing_params.add(step_acc.set("acceleration step", 16, 1, 1000));
    timing_params.add(step_vel.set("velocity step", 116, 1, 1000));
    timing_params.add(min_vel.set("minimum velocity", 0.01, 0.0001, 1.0));
    timing_params.add(max_vel.set("maximum velocity", 0.2, 0.0001, 1.0));
    
    visual_params.setName("Visuals");
    visual_params.add(bWind.set("wind", false));
    visual_params.add(bWrap.set("wrap edges", true));
    visual_params.add(boid_mass.set("boid mass", 1.0, 0.001, 10.0));
    
    panel.setup();
    panel.add(atr_params);
    panel.add(sep_params);
    panel.add(aln_params);
    panel.add(timing_params);
    panel.add(visual_params);
    
//    myFlock.setPhysics(100, 10, 100, -2.0, -1.0, 1.0, 1.0, 0.1, 16, 116, 5.0, 0.01, 0.2);
    
    myFlock.setPhysics(atr_radius, sep_radius, aln_radius, atr_power, sep_power, atr_strength, sep_strength, aln_weight, step_acc, step_vel, spring_offset, min_vel, max_vel);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    myFlock.setPhysics(atr_radius, sep_radius, aln_radius, atr_power, sep_power, atr_strength, sep_strength, aln_weight, step_acc, step_vel, spring_offset, min_vel, max_vel);
    myFlock.mass = boid_mass;
    myFlock.wrapEdges = bWrap;
    myFlock.cursorWind = bWind;
    
    myFlock.updateFlock();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0, 0, 0, 25);
    ofBackground(0, 0, 0);
    
    myFlock.renderFlock();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    
    if (bDrawGui) {
        panel.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') ofToggleFullscreen();
    if (key == 'r') myFlock.resetFlock();
//    if (key == 'c') myFlock.cursorWind = !myFlock.cursorWind;
    if (key == 'g') bDrawGui = !bDrawGui;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
