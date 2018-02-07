#pragma once

#include "ofMain.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//function that draws the matchgame
		void matchGame();
		//Grid Generation Function
		void gridGen();
		//Loads all of the images into a vector
		void gridLoad();
		//this function loads all of the fonts required in setup
		void fontLoad();
		//checks to see if the mouse is over any grid squares
		void gridCheck();
		//stores which grids are within memory
		void gridMatch();
		//grid stores the images of each of the squares and gridPos stores thier position in the 4x5 grid
		std::vector<ofImage> grid;
		std::vector<int> gridPos = {0,1,0,3,7,4,2,3,5,6,4,1,2,8,7,6,8,9,5,9 };
		int gridDrawProg=0;
		int gridCheckProg;
		int mouseOverPos;
		//match memory
		int match1, match2, match1Temp, match2Temp, matchClickCount;
		//game state manipulation variables
		int gameState, gameLives, winProg;
		//Image Buffers
		ofImage background;
		//extension thing turn hetPen and homoPen into arrays
		ofImage hetPen;
		ofImage homoPen;

		ofTrueTypeFont titleFont, textFont;

		
};
