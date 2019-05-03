# Porting from TXLib to TXLin

Usually, the process is straight-forward and the only thing is required is changing the header from TXLib.h to TXLin.h. However, there are still some quirks that you need to know if your application is a lot more complex than just printing "Hello world" on the screen.

## Detecting when TXLin should be used.
This is pretty straight-forward:
```
#ifdef _WIN32
#include "TXLib.h"
#else
#include "TXLin.h"
#endif
```

## Detecting TXLib from the source code
TXLib defines a special macro ``THIS_IS_TXLIN``. You can check for its presence using the ``#ifdef`` macro conditional. Example:
```
#ifdef THIS_IS_TXLIN
txSetConsoleAttr(TX_LIGHTGREEN);
printf("You use TXLin on Linux or macOS. I like both of these operating systems.\n");
#else
txSetConsoleAttr(TX_RED);
printf("You use TXLib on Windows. I prefer macOS over Windows.\n")
#endif
```

## Use txSticky() to keep the window opened
When you open a window in TXLib, it tends not to close until the user does so. However, this is not the case with TXLin. Due to SDL limitations, a function that imitates TXLib's "sticky window" functionality was added to TXLin. That function is ``txSticky()``. This function keeps the window open until the user clicks the close button or presses Command+Q (Alt+F4 on Linux) on his/her keyboard. If you do not add this function after you finish drawing everything on the drawing canvas, then you'll never see the resulting window and canvas.

Here's a simple Hello world program in TXLin:
```
#include "TXLin.h"

int main() {
	txCreateWindow(320, 480);
	txTextOut(6, 6, "Hello, TXLin!");
	return 0;
}
```

Now, if you compile and run this piece of code, you will see nothing happen on the screen. To actually see the window, we will add ``txSticky()`` after all our drawing operations, in this case, after ``txTextOut``:
```
#include "TXLin.h"

int main() {
	txCreateWindow(320, 480);
	txTextOut(6, 6, "Hello, TXLin!");
#ifdef THIS_IS_TXLIN // to avoid incompatibility with TXLib and TXLin
	txSticky();
#endif
	return 0;
}
```

Now you should see a window with the text "Hello, TXLin!" appear on your screen. It won't go away until you click the close button.

## Configurable and const static variables from TXLib are not available
So if you try change one of them in your program and then try to compile it with TXLin, you will get an error. To fix that, wrap around the code that modifies these variables in an ``#ifndef THIS_IS_TXLIN`` block. For example:
```
#ifndef THIS_IS_TXLIN
// change TXLib variables
_txLogName = "txlib_debuginfo.log";
#endif
```
## MAX, MIN, asserted, ROUND and other macroses listed on http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/a00034.htm#ga0b75271f60823b3c49a42cdd3c196ce5 are unavailable in TXLin (though there are exceptions)
Using this macroses requires them to be reimplemented. However, they are planned to be added to a newer version of TXLin. 

However, these macroses and defines are available in TXLin:
 - _TX_DESTROY_3D (it actually turns off 3D acceleration in SDL2)
 - 	__TX_COMPILER__ (reports the compiler used)
 -  __TX_FUNCTION__ (reports the name of the function from which this macros was used)
 - _TX_MODULE (reports the name of the module for debug purposes)
 - txGDI (but it does nothing, it just throws a warning that there is no GDI on Linux or macOS)

 The rest of the macroses (for now) have to be declared after the ``#include "TXLin.h"`` line, example:
 ```
#include "TXLin.h"
#ifndef MAX // when it finally gets added to TXLin, do not redefine it
#define MAX( a, b ) ( ((a) > (b))? (a) : (b) )
#endif

int main() {
	txCreateWindow(60, 70);
	txSetColor(TX_MAGENTA);
	int number1 = 3;
	int number2 = 4;
	if (MAX(3, 4) == 4)
		txTextOut(2, 2, "4 is bigger than 3, your compiler is good");
	else
		txTextOut(2, 2, "3 can't be bigger than 4, fix your compiler first!");
	return 0;
}
```

## txSqr and txPI are now just macroses
txSqr function is actually a macros in TXLin. It points to a different define called ``TXLIN_UNPORTABLEDEF_SQUARE``. And yes, it won't troll the user anymore.

txPI is also a macros now and its value is just 3.14.

## TXLin's Monolithic Font
TXLin draws all the letters and characters by itself using its own built-in font. This was added so that the library would be more portable. However, the font has a fixed size of 6px and it cannot be changed on runtime. It can only be changed while linking the application. This limitation will be removed in a future release, however, for now you'll have to set the font width and height by yourself before the ``#include "TXLin.h"`` line if ypu was to change the font size. For example:

```
#define TXLIN_TEXTSET_WIDTH 12
#define TXLIN_TEXTSET_HEIGHT 12
#include "TXLin.h"

int main() {
	txCreateWindow(400, 400);
	txSetColor(TX_GREEN);
	txTextOut(60, 60, "This font is huge!");
	return 0;
}
```

Because TXLin provides its own font, other fonts cannot be used. This means that functions like txSelectFont will do nothing. Also, text alignment is not supported. It will be added to a future release.

## txInputBox returns a char*, not a const char*
This means that you'll have to free the memory allocated by the string returned by txInputBox by yourself.
```
char* favoriteColor = txInputBox("What is your favorite color?");
if (favoriteColor == nullptr)
	txMessageBox("I can't read the answer you've entered. Sorry. :-("); // your should not free a nullptr library
else {
	txMessageBox(favoriteColor, "Your favorite color is...");
	free(favoriteColor); // free the memory allocated by the result string
}
```

## txHSL2RGB and txRGB2HSL are not available (txDialog is not available either)
There is actually a reason for this. Both of these functions, as well as the txDialog class, are really rarely used.

## Notice for C++98 compilers users
When building your program, right before the ``#include "TXLin.h"`` you'll have to add this line:
```
#define nullptr 0
```
This is needed because TXLin uses nullptr, not NULL, and, as such, most C++98 compilers (and there is no nullptr in C++98) fail to build the library. This is a workaround for these compilers.