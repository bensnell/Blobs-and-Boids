#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){    
//    ofSetBackgroundAuto(false);
//    ofBackground(0, 0, 0);
//    ofEnableAlphaBlending();
    
    myFlock.createFlock(500);
    
    myFlock.setPhysics(100, 10, 100, -2.0, -1.0, 1.0, 1.0, 0.1, 16, 116);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    myFlock.updateFlock();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0, 0, 0, 25);
    ofBackground(0, 0, 0);
    
    myFlock.renderFlock();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') ofToggleFullscreen();
    if (key == 'r') myFlock.resetFlock();
    if (key == 'c') myFlock.cursorWind != myFlock.cursorWind;
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
