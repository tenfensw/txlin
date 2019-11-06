# TXLin
Copyright (c) Tim K 2018-2019 <timprogrammer@rambler.ru>. http://meow.roveramd.com/txlin

TXLin is a TXLib-compatible library that provides a simple way to draw graphics in C++ programs. Unlike TXLib, which uses GDI and, thus, works only on Windows, TXLin uses SDL2 and, as such, can work on Linux, macOS and even FreeBSD.

If you are using Windows, then you should use TXLib: http://ded32.ru/

## Building
Just like TXLib, TXLin does not require to be built as it is a one-header library. However, this library depends on SDL2, which needs to be installed manually.

On Ubuntu/Debian/elementaryOS Linux, you should be able to install it like this:
```
sudo apt install libsdl2-dev
```
On Mageia/OpenMandriva Linux, this command will install SDL2 development files and headers:
```
sudo dnf install 'pkgconfig(sdl2)'
```
On macOS, you should install MacPorts from https://www.macports.org and then run:
```
sudo port install libsdl2
```

***Then*** you should generate pkg-config files and ``txlin-macflags`` script and install one of them to ``/usr/local`` on a Mac or to ``/usr`` on Linux. This is done automatically, so all you have to do is to run this command:
```
sudo ./generate-pkgconfig.sh --install-with-txlin
```

After that, you are ready to use TXLin with your IDE or via terminal.

&#x1F534; **PLEASE READ THIS ARTICLE IF YOU ARE PLANNING TO USE TXLIN WITH CLION OR CMAKE: https://gist.github.com/RoverAMD/1d74cc76d828b8289ee7a6a48655a727**

## Porting TXLib apps to TXLin
The amount of porting work to be done depends on the complexity of the application and its dependence on Windows-specific API. For most TXLib apps, portng to TXLin is just a matter of replacing ``#include "TXLib.h"`` with ``#include "TXLin.h"``. For apps that rely on TXLib's "sticky" window functionality (the window with the drawing canvas does not close after all graphical operations were compiled unless the user clicked the close button), ``txSticky()`` should be added right before the ``return 0`` statement. Apps that load resources or operate with Windows NT paths (paths that use ``\\`` as the seperator intead of UNIX ``/`` seperator) have to be modified so that they used ``/`` as the seperator for directories. 

More information about removed features or functions that act differently, see the porting guide: http://gitlab.com/timkoi/txlin/blob/master/porting-guide.md.

## Documentation
TXLin's API is mostly the same as in TXLib, so you can read TXLib documentation here: http://storage.ded32.net.ru/Lib/TX/TXUpdate/Doc/HTML.ru/index.htm

TXLin contains some new, exclusive features, that might appeal to TXLib application developers (text-to-speech AP, file I/O API, threading API, etc). They are described in the porting guide: http://gitlab.com/timkoi/txlin/blob/master/porting-guide.md
