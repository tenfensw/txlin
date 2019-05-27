// Digital Cat - a TXLin demo program
//
// Copyright (C) Tim K 2018-2019. Licensed under zlib license.

// change TXLIN_MACOS_VOICEOVERVOICE to other voice (such as "Alex") if you want
#define TXLIN_MACOS_VOICEOVERVOICE "Fred"
#ifdef _WIN32 // if on Windows, include TXLib.h
#include <TXLib.h>

// these functions are only available in TXLin, so here are dummy defines
#define TM_NONE -1
#define txSpeak(text) txSleep(2000)
#define txSelectMouse(state) (void)(state)
#define txSetClosable(value) (void)(value)
#else
#include <TXLin.h> // if on macOS and Linux, include TXLin.h
#endif

enum CatEmotions { Idle = 0, Happy = 1, Satisfied = 2, Sad = 3 };
enum FactsImages { Nothing = 0, LogitechMouse = 1, AppleMouse = 2, DellMouse = 3, NoTriangle = 4, VoiceOver = 5, Heart = 6 };

void drawCat(CatEmotions currentState); // these are the prototypes of our functions
void introCat();
void processCustomEvents();
void commandsMenu();
void eatMouse();
void facts();
void drawBeach();
void seperateThreadDrawingFunction(bool insideRealThread);
void speakAndPrint(const char* text, CatEmotions state = Idle, FactsImages image = Nothing);

static char* userName = nullptr; // a variable which will store the user's name
static COLORREF lawnGreen = { 124, 252, 0 }; // a variable which stores the color
static bool doRedraw = true; // a variable controlling the redraw capabilties

void seperateThreadDrawingFunction(bool insideRealThread) {
	if (insideRealThread == false || txIsMacOS())
		return;
	while (true) {
		if (doRedraw) {
			txThreadSleep(500);
			txSetColor(lawnGreen);
			txThreadLine(4, 18, 12, 18);
			txThreadRedrawWindow();
			txThreadSleep(500);
			txSetColor(TX_BLACK);
			txThreadLine(4, 18, 12, 18);
			txThreadRedrawWindow();
		}
	}
}

int main(int argc, char** argv) { // this is our main method. All the functions and calls made there will be executed when the program starts
	txCreateWindow(480, 320); // create a window with width=480 and height=320 (in pixels, obviously)
	txMessageBox("1. Be careful. This cat has an ability to freeze current thread for 5 or more seconds and make Mac and Linux believe that the program is about to crash.\n2. This demo sometimes hangs on macOS during the intro.\n3. To Linux users: If you don't have any TTS engines installed, then the program will run too fast.\n\nHave fun and welcome to TXLin camp!\n - Tim K\nAuthor of TXLin\n\nGreetz to ded32 for writing TXLib (the predecessor to TXLin).", "WARNING AND SOME TECHNICAL INFO");
	if (txMessageBox("I am gonna show you your new pet. Wanna see him now?", "Digital Cat example", MB_YESNO) == IDNO) {
		// txMessageBox shows a message box with the text specified with the first argument
		// It returns an int which tells you what button did the user press
		// In our case, we check if the user said no
		return 1; // exit our program with error code 1
	}
	txClear(); // clear the canvas
	txFloodFill(0, 0, TX_BLACK); // fill everything with black
	txSetClosable(false); // disallow quitting from the program using the close button
	txthread_t threadV = txCreateThread(seperateThreadDrawingFunction); // run cursor drawing in a seperate thread
	if (argc >= 2 && strcmp("-nointro", argv[1]) == 0)
		speakAndPrint("Intro skipped", Idle);
	else
		introCat(); // show the intro
	txSetFillColor(TX_BLACK); // set the fill color to black
	txClear(); // clear everything
	drawCat(Happy); // draw the initial happy pose of the cat
	while (!(GetAsyncKeyState(VK_DOWN))) { // do while down arrow key is not pressed
		txSleep(100); // wait 0.5 seconds (100 milliseconds)
		processCustomEvents(); // check for key presses
	}
	speakAndPrint("See you soon!", Happy); // say goodbye
	speakAndPrint(userName, Happy); // say the user's name
	txCancelThread(threadV); // stop the thread
	return 0; // exit with error code 0
}

void drawBeach() {
	txClear();
	doRedraw = false;
	txFillColor(102, 178, 255);
	txRectangle(0, 0, 480, 90);
	txFillColor(0, 0, 153);
	txRectangle(0, 90, 480, 180);
	txFillColor(255, 255, 153);
	txRectangle(0, 180, 480, 320);
	bool drPix = false;
	int distance = 3;
	for (int ypos = 180; ypos < 320; ypos++) {
		for (int xpos = 0; xpos < 480; xpos++) {
			if (drPix)
				txColor(153, 153, 0);
			else
				txColor(255, 255, 153);
			drPix = !(drPix);
			txSetPixel(xpos, ypos);
			xpos = xpos + distance;
			if ((distance % 3) == 0)
				distance = distance + 3;
			else
				distance = distance + 5;
			if (distance > 12)
				distance = distance - 10;
		}
		drPix = !(drPix);
		ypos = ypos + 3;
	}
	txSetFillColor(TX_BLACK);
	drawCat(Happy);
}

void processCustomEvents() {
	if (doRedraw)
		txRedrawWindow(); // update window contents and handle system events
	bool haveToClear = true;
	if (GetAsyncKeyState(VK_ESCAPE)) {
		commandsMenu();
		doRedraw = true;
		haveToClear = true;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		eatMouse();
		doRedraw = true;
		haveToClear = true;
	}
	else if (GetAsyncKeyState(VK_UP)) {
		facts();
		doRedraw = true;
		haveToClear = true;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		speakAndPrint("You have found an easter egg and gave", Happy);
		speakAndPrint("me a trip to the sea.", Happy);
		speakAndPrint("Thank you very much!", Satisfied);
		drawBeach();
		doRedraw = false;
		haveToClear = false;
	}
	else
		return;
	txSetFillColor(TX_BLACK);
	if (haveToClear)
		txClear();
	if (doRedraw)
		drawCat(Happy);
}

void eatMouse() {
	txSelectMouse(TM_NONE); // hide cursor by setting it to TM_NONE
	speakAndPrint("Your mouse is so tasty. Thank you!", Satisfied);
}

void facts() {
	speakAndPrint("1. My favorite singers are Little Big.", Happy);
	speakAndPrint("And my favorite song is Faradenza.", Happy);
	speakAndPrint("Search it on YouTube if you want.", Happy);
	speakAndPrint("2. I like mice.", Idle);
	speakAndPrint("Logitech mice are the tastiest.", Satisfied, LogitechMouse);
	speakAndPrint("Apple Magic Mouse is okay.", Idle, AppleMouse);
	speakAndPrint("But Dell mice is bad.", Sad, DellMouse);
	speakAndPrint("BERK.", Sad);
	speakAndPrint("3. I am drawn using txCircle and txLine functions.", Idle);
	speakAndPrint("And no, there is no usage of txTriangle", Idle, NoTriangle);
	speakAndPrint("4. Apple VoiceOver is my favorite voice.", Happy, VoiceOver);
	if (txIsMacOS()) // txIsMacOS() reports if the user uses macOS, txIsLinux() reports if the user runs Linux
		speakAndPrint("In fact, I am using VoiceOver right now!", Satisfied);
	else {
		speakAndPrint("Unfortunatelly, there is no VoiceOver on Linux.", Sad);
		speakAndPrint("But there is Festival at least.", Happy);
		speakAndPrint("And that is better than nothing.", Happy);
	}
	speakAndPrint("5. Tim K created a cat program, because he knows", Idle);
	speakAndPrint("that ded32, the developer of TXLib,", Idle);
	speakAndPrint("the predecessor to TXLin,", Idle);
	speakAndPrint("loves cats!", Satisfied, Heart);
	speakAndPrint("Yay!", Satisfied, Heart);
	speakAndPrint("And... that is it.", Idle);
}

void commandsMenu() {
	txSetColor(lawnGreen);
	txTextOut(4, 4, "Hold LEFT ARROW to feed.");
	txTextOut(4, 14, "Hold UP ARROW to listen to an interesting fact.");
	txTextOut(4, 24, "Hold DOWN ARROW to exit.");
	txSleep(5000);
	return;
}

void speakAndPrint(const char* text, CatEmotions state, FactsImages image) {
	if (text == nullptr)
		return;
	txBegin(); // Run txBegin() to turn off automatic window updates and reduce flickering
	txSetFillColor(TX_BLACK);
	txClear();
	drawCat(state);
	txSetColor(lawnGreen);
	if (image != Nothing) {
		txSetFillColor(TX_TRANSPARENT);
		if (image == LogitechMouse)
			txTextOut(21, 50, "     logi  ");
		else if (image == AppleMouse)
			txTextOut(21, 50, "     APPLE ");
		else if (image == DellMouse) {
			txTextOut(21, 50, "DELL");
			txLine(19, 18, 43, 124);
			txLine(43, 18, 19, 124);
		}
		else if (image == NoTriangle) {
			txTriangle(20, 61, 30, 20, 40, 61);
			txLine(19, 18, 43, 62);
			txLine(43, 18, 19, 62);
		}
		else if (image == VoiceOver) {
			txRectangle(20, 20, 80, 122);
			txRectangle(23, 23, 74, 102);
			txCircle(40, 107, 6);
			txTextOut(25, 25, "How can I help?");
			txLine(23, 88, 74, 88);
		}
		else if (image == Heart) {
			txSetColor(TX_RED);
			txLine(23, 23, 78, 78);
			txLine(78, 78, 133, 23);
			txLine(133, 23, 82, 23);
			txLine(82, 23, 78, 32);
			txLine(78, 32, 74, 23);
			txLine(74, 23, 23, 23);
			txSetColor(lawnGreen);
		}
		txSetFillColor(TX_BLACK);
	}
	txTextOut(4, 4, text);
	txEnd(); // turn on automatic window updates back
	txSpeak(text);
}



void introCat() {
	drawCat(Happy);
	speakAndPrint("Hello! I am Digital Cat!", Satisfied);
	speakAndPrint("I am really glad to see you viewing this demo.", Satisfied);
	speakAndPrint("As well as I am glad that you chose TXLin", Happy);
	speakAndPrint("as your starting point in C++ graphics.", Happy);
	speakAndPrint("TXLin is a really powerful library", Idle);
	speakAndPrint("that might look simple, but in reality", Idle);
	speakAndPrint("it is able to do a lot of things if you use it properly", Idle);
	speakAndPrint("TXLin was originally a port of TXLib to macOS", Idle);
	speakAndPrint("and Linux, but later", Happy);
	speakAndPrint("Tim K, the author of the port", Happy);
	speakAndPrint("added more features, such as TTS support using txSpeak", Idle);
	speakAndPrint("Which I use to talk to you right now", Satisfied);
	speakAndPrint("Anyway, I hope you will enjoy this demo", Idle);
	speakAndPrint("as well as I hope that you will love programming", Idle);
	speakAndPrint("If you are still unsure about what exactly can TXLin do,", Idle);
	speakAndPrint("then you will be able to see all of its capabilities", Idle);
	speakAndPrint("live");
	speakAndPrint("just by playing around with this demo.", Happy);
	speakAndPrint("Oh, I am sorry, but I forgot to ask you", Idle);
	speakAndPrint("What is your name?", Idle);
	// ask for user's name
	while (userName == nullptr)
		userName = txInputBox("What is your name?");
	speakAndPrint("Nice to meet you", Satisfied);
	speakAndPrint(userName, Satisfied);
	speakAndPrint("Also, I forgot to tell you", Idle);
	speakAndPrint("To open the commands menu,", Happy);
	speakAndPrint("Hold Esc.", Happy);
	speakAndPrint("Good luck and may the source be with you!", Satisfied); // quote from TXLib docs
	txSetFillColor(TX_BLACK);
	txClear();
}

void drawCat(CatEmotions currentState) {
	POINT windowCenter = { 240, 160 }; // window center coordinates
	int radius = 40; // cat head radius
	txSetFillColor(TX_TRANSPARENT); // disable flood-fill capabilities for now
	txSetColor(lawnGreen); // set our line color to black
	txCircle(windowCenter.x, windowCenter.y, radius); // draw a circle
	// now let's draw the ears
	txLine(windowCenter.x - (radius / 4), windowCenter.y - (2 * (radius / 2)), windowCenter.x - (radius / 2), windowCenter.y - (4 * (radius / 2)));
	txLine(windowCenter.x - (radius / 2), windowCenter.y - (4 * (radius / 2)), windowCenter.x - (3 * (radius / 4)), windowCenter.y - (1.3 * (radius / 2)));
	txLine(windowCenter.x - (radius / 4) + 16, windowCenter.y - (2 * (radius / 2)), windowCenter.x + (radius / 2), windowCenter.y - (4 * (radius / 2)));
	txLine(windowCenter.x + (radius / 2), windowCenter.y - (4 * (radius / 2)), windowCenter.x - (radius / 4) + 40, windowCenter.y - (1.3 * (radius / 2)));
	// now the eyes
	if (currentState == Satisfied) {
		txLine(windowCenter.x - 10, windowCenter.y - 10, windowCenter.x - 15, windowCenter.y);
		txLine(windowCenter.x - 15, windowCenter.y, windowCenter.x - 18, windowCenter.y - 10);
		txLine(windowCenter.x + 10, windowCenter.y - 10, windowCenter.x + 15, windowCenter.y);
		txLine(windowCenter.x + 15, windowCenter.y, windowCenter.x + 18, windowCenter.y - 10);
	}
	else {
		txLine(windowCenter.x - 10, windowCenter.y - 10, windowCenter.x - 10, windowCenter.y);
		txLine(windowCenter.x + 10, windowCenter.y - 10, windowCenter.x + 10, windowCenter.y);
	}
	// now draw the mouth
	txLine(windowCenter.x - 14, windowCenter.y + 15, windowCenter.x + 14, windowCenter.y + 15);
	if (currentState == Happy || currentState == Satisfied) {
		txLine(windowCenter.x - 14, windowCenter.y + 10, windowCenter.x - 14, windowCenter.y + 15);
		txLine(windowCenter.x + 14, windowCenter.y + 10, windowCenter.x + 14, windowCenter.y + 15);
	}
	else if (currentState != Idle) {
		txLine(windowCenter.x - 14, windowCenter.y + 18, windowCenter.x - 14, windowCenter.y + 15);
		txLine(windowCenter.x + 14, windowCenter.y + 18, windowCenter.x + 14, windowCenter.y + 15);
	}
}
