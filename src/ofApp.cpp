#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//loads fonts
	fontLoad();
	//loads images
	gridLoad();
	
	//sets value of matches
	matchClickCount = 0;
	match1 = 2001;
	match2 = 2000;
	//game state init
	gameState = 0; // to do make game state 0 = start screen, 1 = main game, 2 = game over scenario, 3 = win
	gameLives = 3; //to do make lose state when game lives = 0 //also need text/visual to respond to number of lives
	winProg = 0; //this variable goes up as more things are matched
	//hides the cursor
	ofHideCursor();
	gridGen();
}

//--------------------------------------------------------------
void ofApp::update(){
	
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (gameState == 0) {//game start press any key
		background.draw(0, 0);
		titleFont.drawString("WELCOME TO Pen Island \n Click Mouse To Continue",50,100);
	}
	else if (gameState == 1) {//game play
		matchGame();
		if (gameLives < 0) {
			gameState = 2;
		}

	}
	else if (gameState == 2) { //gameover
		ofBackground(200, 25, 25);
		titleFont.drawString("game over \n press mouse to retry", 50, 100);

	}
	else if (gameState == 3) { //game win
		ofBackground(200, 100, 100);
		titleFont.drawString("congrats u won! and escaped pen island", 50, 100);

	}
	else {
		gameState = 2; //sets game state to automatic gameover in the case of edge cases
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
	if (gameState == 0) {
		gameState = 1;
	}
	else if (gameState == 1) {
		gridMatch();
	}
	else if (gameState == 2) {
		gameLives = 3;
		gameState = 1;
		winProg = 0;
	}
	

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::matchGame() {
	gridDrawProg = 0;
	//checks position of mouse for frame

	//drawcode 
	background.draw(0, 0);
	for (int i = 50; i < 450; i += 100) {
		for (int j = 50; j < 550; j += 100) {
			grid[gridPos[gridDrawProg]].draw(i, j);
			gridDrawProg++;
		}
	}

	grid[gridPos[match1Temp]].draw(700, 500);
	grid[gridPos[match2Temp]].draw(800, 500);
	//checks to see if mouse is in bounds of grid and if it is then shades the box it is over
	gridCheck();
	//draws new mouse cursor *extension* make it so that the mouse cursor looks good and changes when dragging+ clicking
	ofSetColor(255);
	ofFill();
	ofDrawRectangle(mouseX, mouseY, 50, 50);
	ofDrawBitmapString(match1 + match2, 600, 500);
	ofDrawBitmapString(gameLives, 600, 600);//debugging match function
	}

void ofApp::gridLoad() {
	//loads an array of images into the Grid vector
	grid.resize(11);
	grid[0].load("images/peaAva.png");
	grid[1].load("images/ballAva.png");
	grid[2].load("images/gelAva.png");
	grid[3].load("images/mechAva.png");
	grid[4].load("images/highAva.png");
	grid[5].load("images/brushAva.png");
	grid[6].load("images/colsAva.png");
	grid[7].load("images/markerAva.png");
	grid[8].load("images/fountainAva.png");
	grid[9].load("images/feltAva.png");
	grid[10].load("images/hetPen.png");
	//loads background image
	background.load("images/back.png");
}

void ofApp::fontLoad()
{
	//loads all of the required fonts into a texture
	titleFont.load("fonts/Larabie - PrimerPrint-Bold.ttf", 20,true,true,false,0.3,240);
	textFont.load("fonts/Larabie - PrimerPrint-Regular.ttf", 50, true, true, false, 0.3, 240);
}

void ofApp::gridGen() {

}

void ofApp::gridCheck() {
	int gridScanProg = 0;
	for (int i = 50; i < 450; i += 100) {
		for (int j = 50; j < 550; j += 100) {
			if ((mouseX > i && mouseX < i + 100) && (mouseY > j && mouseY < j + 100)) {
				ofSetColor(255, 100);
				ofFill();
				ofDrawRectangle(i, j, 100, 100);
				ofNoFill();
				return;
			}
			else {
				gridScanProg++;
			}
		}
	}
	return;
}

void ofApp::gridMatch() {

	//this function is currently v bugged and unfinished also could be simplified a ton using pointers but I dont feel comfortable
	//enough yet to do so.

	//currently set to scan the screen for the mouse position and then check to see if the last stored match matches the current one.
	int gridMatchProg = 0;
	for (int i = 50; i < 450; i += 100) {
		for (int j = 50; j < 550; j += 100) {
			if ((mouseX > i && mouseX < i + 100) && (mouseY > j && mouseY < j + 100)) {
				if (match1 > 1999) {
					match1 = gridPos[gridMatchProg];
					match1Temp=	gridMatchProg;
				}
				else if (match2 > 1999) {
					match2 = gridPos[gridMatchProg];
					match2Temp= gridMatchProg;
				}
			}
			gridMatchProg++;
		}
	}
	matchClickCount = (matchClickCount + 1) % 2;
	if (match1 == match2) {
		//TODO:add a graphic particle function to be called when matched.

		//if graphics match, then change their texture and then reset the match progress
		if (match1Temp == match2Temp) {
			match1 = 2001;
			match2 = 2000;
		}
		else {
			gridPos[match1Temp] = 10;
			gridPos[match2Temp] = 10;
			match1 = 2001;
			match2 = 2000;
			winProg++;
			//win condition set to 10 matches
			if (winProg == 10) {
				gameState = 3; //sets game win conditon
			}
		}
	}
	else if(match1!=match2 && matchClickCount==0) {
		//brings you closer to lose state
		gameLives = gameLives - 1;
		match1 = 2001;
		match2 = 2000;
	}

}