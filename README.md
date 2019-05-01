# TXLin
TXLin is a TXLib-compatible library that provides a simple way to draw graphics in C++ programs. Unlike TXLib, which uses GDI and, thus, works only on Windows, TXLin uses SDL2 and, as such, can work on Linux and Mac OS X.

If you are using Windows, then you should use TXLib: http://ded32.ru/

## Building
Just like TXLib, TXLin does not require to be built as it is a one-header library. However, this library depends on SDL2, which needs to be installed manually.

On Ubuntu Linux, you should be able to install it like this:
```
sudo apt install libsdl2-dev
```
On Mageia/OpenMandriva Linux, this command will install SDL2 development files and headers:
```
urpmi 'pkgconfig(sdl2)'
```

Then, when linking your applications, you should add `sdl2-config --cflags --libs` to your compiler flags. For example:
```
clang++ my_txlin_program.cpp -o my_txlin_program -I. -std=c++0x `sdl2-config --cflags --libs`
``` 

## Porting TXLib apps to TXLin
It's easy. Just replace ``#include "TXLib.h"`` with ``#include "TXLin.h"`` and you're good to go.

## Documentation
TXLin's API is mostly the same as in TXLib, so you can read TXLib documentation here: http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/index.htm

There are still differences between TXLin and TXLib. See http://gitlab.com/timkoi/txlin/blob/master/porting-guide.md for more info.