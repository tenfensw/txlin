/*
TXLin

Copyright (c) 2018-2019, Tim K <timprogrammer@rambler.ru>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef TXLIN_H
#define TXLIN_H
#include <SDL.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <csignal>
#include <assert.h>
#include <cstdint>
#include <string>
#include <vector>
#include <execinfo.h>

#define HWND Uint32
#define DWORD unsigned long
#define HDC SDL_Renderer*
#define HPEN SDL_Renderer*
#define RGBQUAD Uint32
#define HFONT void*
#define LONG unsigned long
#define HBRUSH SDL_Renderer*
#define LOGFONT void
#define SHORT bool
#define CURSORREF SDL_SystemCursor

#define TXLIN_VERSION "TXLin [Ver: 1.74a, Rev: 106, Date: 2019-04-26 00:00:00]"
#define TXLIN_AUTHOR "Copyright (C) timkoi (Tim K, http://timkoi.gitlab.io/)"
#define TXLIN_VERSIONNUM 0x174a0
#ifdef TXLIN_MODULE
#define _TX_MODULE TXLIN_MODULE
#elif defined(_TX_MODULE)
#define TXLIN_MODULE _TX_MODULE
#else
#define TXLIN_MODULE "TXLin"
#define _TX_MODULE "TXLin"
#endif

#ifdef __clang__
#define TXLIN_COMPILER "Apple LLVM C++ Compiler"
#define __TX_FUNCTION__ __PRETTY_FUNCTION__
#elif defined(__INTEL_COMPILER)
#define TXLIN_COMPILER "Intel C++ Compiler"
#define __TX_FUNCTION__ __FUNCTION__
#elif defined(__GNUC__)
#define TXLIN_COMPILER "GNU C/C++ Compiler"
#define __TX_FUNCTION__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#pragma message("Windows is not supported by TXLin. And it will never be supported, because on Windows you should use TXLib.")
#elif defined(__SUNPRO_CC)
#error "Sun Studio is not supported by TXLin. It's too old, too buggy. Use GCC if you can."
#define TXLIN_COMPILER "Unsupported C++ compiler"
#define __TX_FUNCTION__ "(__TX_FUNCTION__ not supported with your compiler)"
#warning "TXLin does not support your C++ compiler. Continue at your own risk!"
#endif
#define __TX_FILENAME__ __FILE__

#ifdef __APPLE__
#define TXLIN_OPERATINGSYSTEM "Apple macOS"
#define TXLIN_NO_3D_ACCELERATION 1
#elif defined(__linux__)
#define TXLIN_OPERATINGSYSTEM "Linux"
#else
#define TXLIN_OPERATINGSYSTEM "Unsupported UNIX-like operating system"
#warning "TXLin cannot detect your current operating system. Use at your own risk."
#endif

#ifdef TXLIN_OLDCOMPILER
#define nullptr 0
#endif

#define THIS_IS_TXLIN

// compatibility defines (not really)
#define _TX_VERSION TXLIN_VERSION
#define _TX_AUTHOR TXLIN_AUTHOR
#define _TX_VER TXLIN_VERSIONNUM
#define __TX_COMPILER__ TXLIN_COMPILER
#define meow bark TXLIN_WARNING("meow is deprecated, use bark instead.");
#define bark ;
#define txPI 3.14

#define VK_UP SDL_SCANCODE_UP
#define VK_DOWN SDL_SCANCODE_DOWN
#define VK_LEFT SDL_SCANCODE_LEFT
#define VK_RIGHT SDL_SCANCODE_RIGHT
#define VK_ESCAPE SDL_SCANCODE_ESCAPE
#define VK_SHIFT SDL_SCANCODE_LSHIFT

// debug define
#ifdef TXLIN_DEBUG
#define DBGOUT if (0) std::cerr << "[TXLin/DEBUG/" << __LINE__ << "] "
#else
#define DBGOUT std::stringstream()
#endif
#define DBGINT(var) DBGOUT << #var << " = " << var << std::endl
#define TXLIN_WARNING(text) { if (getenv("TXLIN_DISABLEAPPWARNINGS") == nullptr) { std::cerr << "[TXLin/WARNING] " << text << std::endl; } }
#define TXLIN_WARNINGWITHMESSAGEBOX(text) { TXLIN_WARNING(text); txMessageBox((text), "TXLin", 0); }
#define TXLIN_WARNINGNOTIMPLEMENTED() TXLIN_WARNING(std::string(__PRETTY_FUNCTION__) + " is not implemented yet.")

// colors
#define TX_BLACK RGB(0, 0, 0)   
#define TX_BLUE RGB(0, 0, 128)
#define TX_GREEN RGB(0, 128, 0)   
#define TX_CYAN RGB(0, 128, 128)   
#define TX_RED RGB(128, 0, 0)   
#define TX_MAGENTA RGB(128, 0, 128)  
#define TX_BROWN RGB(128, 128, 0)
#define TX_ORANGE RGB(255, 128, 0)  
#define TX_GRAY RGB(160, 160, 160)   
#define TX_DARKGRAY RGB(128, 128, 128)
#define TX_LIGHTGRAY RGB(192, 192, 192)
#define TX_LIGHTBLUE RGB(0, 0, 255)   
#define TX_LIGHTGREEN RGB(0, 255, 128)   
#define TX_LIGHTCYAN RGB(0, 255, 255)   
#define TX_LIGHTRED RGB(255, 0, 128)
#define TX_LIGHTMAGENTA RGB(255, 0, 255)
#define TX_PINK RGB(255, 128, 255)
#define TX_YELLOW RGB(255, 255, 128)   
#define TX_WHITE RGB(255, 255, 255) 

#define TX_GREY TX_GRAY
#define TX_DARKGREY TX_DARKGRAY
#define TX_LIGHTGREY TX_LIGHTGRAY

#define TX_TRANSPARENT RGB(-1, -1, -1)

// CLI colors

#define FOREGROUND_BLUE 1
#define FOREGROUND_RED 4
#define FOREGROUND_INTENSITY 8
#define FOREGROUND_GREEN 2
#define FOREGROUND_BLACK         ( 0                                                         )
#define FOREGROUND_CYAN          ( FOREGROUND_BLUE       | FOREGROUND_GREEN                  )
#define FOREGROUND_MAGENTA       ( FOREGROUND_BLUE       | FOREGROUND_RED                    )
#define FOREGROUND_DARKYELLOW    ( FOREGROUND_GREEN      | FOREGROUND_RED                    )
#define FOREGROUND_LIGHTGRAY     ( FOREGROUND_BLUE       | FOREGROUND_GREEN | FOREGROUND_RED )
#define FOREGROUND_DARKGRAY      (                         FOREGROUND_INTENSITY              )
#define FOREGROUND_LIGHTBLUE     ( FOREGROUND_BLUE       | FOREGROUND_INTENSITY              )
#define FOREGROUND_LIGHTGREEN    ( FOREGROUND_GREEN      | FOREGROUND_INTENSITY              )
#define FOREGROUND_LIGHTCYAN     ( FOREGROUND_CYAN       | FOREGROUND_INTENSITY              )
#define FOREGROUND_LIGHTRED      ( FOREGROUND_RED        | FOREGROUND_INTENSITY              )
#define FOREGROUND_LIGHTMAGENTA  ( FOREGROUND_MAGENTA    | FOREGROUND_INTENSITY              )
#define FOREGROUND_YELLOW        ( FOREGROUND_DARKYELLOW | FOREGROUND_INTENSITY              )
#define FOREGROUND_WHITE         ( FOREGROUND_LIGHTGRAY  | FOREGROUND_INTENSITY              )

// dummy defines that are needed for API compatibility
#define FLOODFILLBORDER 0x0001
#define FLOODFILLSURFACE 0x0002
#define TA_LEFT 3
#define TA_RIGHT 4
#define TA_CENTER 5
#define TA_TOP 6
#define TA_BOTTOM 7

#define SND_ASYNC 80
#define SND_SYNC 81
#define SND_LOOP 82
#define SND_NOSTOP -1
#define SND_APPLICATION 84
#define SND_NODEFAULT -1

#ifdef TXLIN_TEXTSET_MAXWIDTH
#undef TXLIN_TEXTSET_MAXWIDTH
#warning "TXLIN_TEXTSET_MAXWIDTH and TXLIN_TEXTSET_MAXHEIGHT are now ignored as now txSelectFont works properly"
#endif
#ifdef TXLIN_TEXTSET_MAXHEIGHT
#undef TXLIN_TEXTSET_MAXHEIGHT
#warning "TXLIN_TEXTSET_MAXWIDTH and TXLIN_TEXTSET_MAXHEIGHT are now ignored as now txSelectFont works properly"
#endif
#define TXLIN_TEXTSET_HALFWIDTH (TXLIN_TEXTSET_MAXWIDTH / 2)
#define TXLIN_TEXTSET_HALFHEIGHT (TXLIN_TEXTSET_MAXHEIGHT / 2)

#define TXLIN_UNPORTABLEDEF_SQUARE(num) ((num) * (num))
#define txSqr(x) TXLIN_UNPORTABLEDEF_SQUARE((double)(x))
#define TXLIN_UNPORTABLEDEF_RMFILE(filename) std::system(std::string(std::string("rm -r -f \"") + std::string(filename) + '\"').c_str())

#define TXLIN_UNPORTABLEDEF_EVENTPROCESSING_PROCESSED 0
#define TXLIN_UNPORTABLEDEF_EVENTPROCESSING_QUIT 1
#define TXLIN_UNPORTABLEDEF_EVENTPROCESSING_NONE 2

#define TM_DEFAULT SDL_SYSTEM_CURSOR_ARROW
#define TM_WAIT SDL_SYSTEM_CURSOR_WAIT
#define TM_PROHIBITED SDL_SYSTEM_CURSOR_NO
#define TM_HAND SDL_SYSTEM_CURSOR_HAND
#define TM_NONE (CURSORREF)(14)

#define txGDI(function) TXLIN_WARNING(std::string(std::string("txGDI does not work on Mac OS X or Linux, because it is a Windows-specific function. As such, ") + std::string(#function) + std::string(" won't be called.")).c_str());

#define ROUND(x) (int)(round((double)(x)))
#ifndef TXLIN_DEBUG
#define verify(expr) (expr)
#else
#define verify(expr) assert(expr)
#endif
#define _ ,
#define txItoa(num) txLinUnportableNumToCPlusPlusString(num).c_str()
#define TX_ERROR(msg) { std::string txErrorMessage_tmp = "TX_ERROR() invoked on line " + txLinUnportableNumToCPlusPlusString(__LINE__) + " file \"" + std::string(__TX_FILENAME__) + "\".\nCompiler used: " + std::string(__TX_COMPILER__) + "\nOperating system used: " + std::string(TXLIN_OPERATINGSYSTEM) + "\n\nIn function " + std::string(__PRETTY_FUNCTION__) + ": " + std::string(msg) + "\n\nPlease contact the developer of this program to fix this error. Cannot continue."; \
                        txSetConsoleAttr(FOREGROUND_RED); \
                        std::cerr << txErrorMessage_tmp.c_str() << std::endl; \
                        txSetConsoleAttr(FOREGROUND_WHITE); \
                        txMessageBox(txErrorMessage_tmp.c_str(), "TX_ERROR"); \
                        abort(); \
                 }
#define txStackBackTrace() { std::cerr << "=====================================================" << std::endl; \
                             std::cerr << "             STACK BACKTRACE (TXLIN)" << std::endl; \
                             std::cerr << " FILE " << __TX_FILENAME__ << " LINE " << __LINE__ << std::endl; \
                             std::cerr << "=====================================================" << std::endl; \
                             txLinUnportableMacLinuxBacktrace(); \
                             std::cerr << "=====================================================" << std::endl; \
                              }

#ifdef _TX_ALLOW_KILL_PARENT
#warning "_TX_ALLOW_KILL_PARENT is ignored by TXLin."
#endif

struct POINT {
    double x;
    double y;   
};

struct SIZE {
    unsigned long cx;
    unsigned long cy;
};

struct COLORREF {
    int r;
    int g;
    int b;
};

inline bool operator==(const COLORREF& c1, const COLORREF& c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

inline bool operator!=(const COLORREF& c1, const COLORREF& c2) {
    return (c1.r != c2.r || c1.g != c2.g || c1.b != c2.b);
}

#ifndef TXLIN_NO_NAMESPACE
namespace TX {
#endif
    inline COLORREF RGB (int red, int green, int blue);

    static bool txLinUnportableHasInitializedTXLinInThisContext = false;
    static HWND txLinUnportableRecentlyCreatedWindow = -1;
    static unsigned txLinUnportableLastTerminalColor = 0x07;
    static bool txLinUnportableAutomaticWindowUpdates = true;
    static int TXLIN_TEXTSET_MAXWIDTH = 6;
    static int TXLIN_TEXTSET_MAXHEIGHT = 6;
    static COLORREF txLinUnportableLastFillColor = TX_TRANSPARENT;
    static COLORREF txLinUnportableLastDrawColor = TX_WHITE;
    static unsigned txLinUnportableTextAlign = TA_BOTTOM;

    inline HDC txDC();
    inline HWND txWindow();
    inline COLORREF txGetFillColor(HDC dc = txDC());
    inline bool txFloodFill (double x, double y, COLORREF color = txGetFillColor(), DWORD mode = FLOODFILLSURFACE, HDC dc = txDC(), COLORREF oldcolor = TX_TRANSPARENT);
    inline SIZE txGetTextExtent(const char* text, HDC dc = txDC());

    inline std::string txLinUnportableNumToCPlusPlusString(int num) {
        std::stringstream stream;
        stream << num;
        return stream.str();
    }

    inline int txLinUnportableSDLProcessOneEvent() {
        SDL_Event* eventHandler = (SDL_Event*)(malloc(sizeof(SDL_Event)));
        if (SDL_PollEvent(eventHandler) == 0)
            return TXLIN_UNPORTABLEDEF_EVENTPROCESSING_NONE;
        if (eventHandler->type == SDL_QUIT) {
            SDL_DestroyRenderer(txDC());
            SDL_DestroyWindow(SDL_GetWindowFromID(txWindow()));
            SDL_Quit();
            exit(0);
            return TXLIN_UNPORTABLEDEF_EVENTPROCESSING_QUIT;
        }
        return TXLIN_UNPORTABLEDEF_EVENTPROCESSING_PROCESSED;
    }

    inline void txLinUnportableMacLinuxBacktrace() {
#ifndef TXLIN_NO_BACKTRACE
        void* addressesBuffer = (void*)(calloc(10, sizeof(unsigned)));
        int countaddr = backtrace(&addressesBuffer, 10);
        char** arrayofcstrings = backtrace_symbols(&addressesBuffer, countaddr);
        for (int i = 0; i < countaddr; i++) 
            std::cerr << arrayofcstrings[i] << std::endl;
#else
        std::cerr << "Backtrace fetching was disabled during compile time." << std::endl;
#endif
    }

    inline HWND txWindow() {
        DBGINT(txLinUnportableRecentlyCreatedWindow);
        return txLinUnportableRecentlyCreatedWindow;
    }

    inline SDL_Point* txLinUnportablePointCapsToSDL(const POINT* points, int pointsCount) {
        SDL_Point* pointsFinal = (SDL_Point*)(calloc(pointsCount, sizeof(SDL_Point)));
        for (int i = 0; i < pointsCount; i++) {
            pointsFinal[i].x = (int)(points[i].x);
            pointsFinal[i].y = (int)(points[i].y);
        }
        return pointsFinal;
    }

    inline char* txClipboard(const char* flushText = nullptr) {
        if (SDL_HasClipboardText() == SDL_FALSE)
            return nullptr;
        if (flushText)
            SDL_SetClipboardText(flushText);
        return SDL_GetClipboardText();
    }

    inline int txGetRAM() {
        return SDL_GetSystemRAM();
    }

    inline void txLinUnportableUnexpectedSignalHandler(int signal) {
        SDL_Quit();
        exit(0);
    }

    inline bool txLinUnportableInitSDL() {
        signal(SIGTERM, txLinUnportableUnexpectedSignalHandler);
        signal(SIGKILL, txLinUnportableUnexpectedSignalHandler);
        return (SDL_Init(SDL_INIT_VIDEO) == 0);
    }

    inline int txLinUnportableModule(int number) {
        if (number < 0)
            return ((number) * (-1));
        return number;
    }

    inline void txRedrawWindow() {
        SDL_UpdateWindowSurface(SDL_GetWindowFromID(txWindow()));
        txLinUnportableSDLProcessOneEvent();
    }

    inline HWND txCreateWindow(double sizeX, double sizeY, bool centered = true) {
        if (txLinUnportableHasInitializedTXLinInThisContext && txLinUnportableInitSDL() == false)
            return -1;
        int x = SDL_WINDOWPOS_CENTERED;
        int y = SDL_WINDOWPOS_CENTERED;
        if (centered == false) {
            x = 2;
            y = 2;
        }
        SDL_Window* window = SDL_CreateWindow("TXLin", x, y, (int)(sizeX), (int)(sizeY), SDL_WINDOW_SHOWN);
        txLinUnportableRecentlyCreatedWindow = SDL_GetWindowID(window);
        SDL_UpdateWindowSurface(window);
        SDL_ShowWindow(window);
        SDL_RaiseWindow(window);
        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_Delay(500);
        DBGOUT << "Window shown" << std::endl;
        return txLinUnportableRecentlyCreatedWindow;
    }

    inline bool txIsLinux() {
#ifdef __linux__
        return true;
#else
        return false;
#endif
    }

    inline bool txIsMacOS() {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }

    inline bool txSpeak(const char* stringToSay) {
        if (stringToSay == nullptr)
            return false;
#ifdef __APPLE__
        return (std::system(std::string("say -v Daniel '" + std::string(stringToSay) + '\'').c_str()) == 0);
#else
        if (std::system("command -v espeak > /dev/null 2>&1") == 0)
            return (std::system(std::string("espeak '" + std::string(stringToSay) + '\'').c_str()) == 0);
        else if (std::system("command -v festival > /dev/null 2>&1") == 0)
            return (std::system(std::string("echo '" + std::string(stringToSay) + "' | festival --tts").c_str()) == 0);
        TXLIN_WARNING("No TTS engines are installed on your computer. Please install espeak or festival.");
        return false;
#endif
    }

    inline const char* txCPUVendor() {
#ifdef __APPLE__
        if (std::system("test `sysctl machdep.cpu.vendor | cut -d ':' -f2 | sed  's/ //g'` = \"GenuineIntel\"") == 0)
            return "Intel";
        else if (std::system("test `sysctl machdep.cpu.vendor | cut -d ':' -f2 | sed  's/ //g'` = \"AuthenticAMD\"") == 0)
            return "AMD";
        else if (std::system("test `sysctl machdep.cpu.vendor | cut -d ':' -f2 | sed  's/ //g'` = \" lrpepyh vr\"") == 0)
            return "Parallels";
        else if (std::system("test `sysctl machdep.cpu.vendor | cut -d ':' -f2 | sed  's/ //g'` = \"VMwareVMware\"") == 0)
            return "VMware";
        return "IBM";
#else
        if (std::system("lscpu | grep Vendor | grep -q GenuineIntel") == 0)
            return "Intel";
        else if (std::system("lscpu | grep Vendor | grep -q AuthenticAMD") == 0)
            return "AMD";
        else if (std::system("lscpu | grep Vendor | grep -q CentaurHauls") == 0 || std::system("lscpu | grep Vendor | grep -q CyrixInstead") == 0 || std::system("lscpu | grep Vendor | grep -q \"VIA VIA VIA\"") == 0)
            return "VIA";
        else if (std::system("lscpu | grep Vendor | grep -q GenuineTMx86") == 0)
            return "Transmeta";
        else if (std::system("lscpu | grep Vendor | grep -q \" lrpepyh vr\"") == 0)
            return "Parallels";
        else if (std::system("lscpu | grep Vendor | grep -q VMwareVMware") == 0)
            return "VMware";
        else if (std::system("lscpu | grep Vendor | grep -q KVMKVMKVM") == 0 || std::system("lscpu | grep Vendor | grep -q \"bhyve bhyve \"") == 0)
            return "QEMU";
        else if (std::system("lscpu | grep Vendor | grep -q \"Microsoft Hv\"") == 0)
            return "Microsoft";
        return "Unknown";
#endif
        return "Unknown";
    }

    inline bool txSetDefaults(HDC dc = txDC()) {
        DBGOUT << "called txSetDefaults" << std::endl;
        SDL_Renderer* rendererContext = dc;
        if (rendererContext == nullptr)
            return false;
        SDL_SetRenderDrawColor(rendererContext, 255, 255, 255, 0);
        //SDL_RenderClear(rendererContext);
        return true;
    }


    HDC txDC() {
        DBGOUT << "called txDC()" << std::endl;
        SDL_Window* window = SDL_GetWindowFromID(txWindow());
        if (window == nullptr)
            return nullptr;
        SDL_Renderer* resultRenderer = SDL_GetRenderer(window);
        if (resultRenderer == nullptr) {
            DBGOUT << "regenerating renderer" << std::endl;
    #if !defined(TXLIN_NO_3D_ACCELERATION)
            resultRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #else
            resultRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    #endif
            txSetDefaults(resultRenderer);
            txRedrawWindow();
            //txSetDefaults(resultRenderer);
        }
        return resultRenderer;
    }

    inline RGBQUAD* txVideoMemory(HDC dc = txDC()) {
        return (RGBQUAD*)(SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow()))->pixels);
    }


    inline bool txOK() {
        return txLinUnportableHasInitializedTXLinInThisContext;
    }


    inline POINT txGetExtent (HDC dc = txDC()) {
        POINT result;
        result.x = 0.0;
        result.y = 0.0;
        int xSet = 0;
        int ySet = 0;
        if (SDL_GetRendererOutputSize(dc, &xSet, &ySet) != 0)
            return result;
        result.x = (double)(xSet);
        result.y = (double)(ySet);
        return result;
    }

    inline bool txSelectMouse(CURSORREF mouseId = TM_DEFAULT) {
        if (mouseId == TM_NONE) {
            SDL_ShowCursor(SDL_DISABLE);
            return true;
        }
        SDL_ShowCursor(SDL_ENABLE);
        SDL_Cursor* mousePointer = SDL_CreateSystemCursor(mouseId);
        if (mousePointer == nullptr)
            return false;
        SDL_SetCursor(mousePointer);
        return true;
    }

    inline int txGetExtentX (HDC dc = txDC()) {
        return (int)(txGetExtent(dc).x);
    }


    inline int txGetExtentY (HDC dc = txDC()) {
         return (int)(txGetExtent(dc).y);
    }


    inline const char* txVersion() {
        return TXLIN_VERSION;
    }

    inline unsigned txVersionNumber() {
        return TXLIN_VERSIONNUM;
    }

    const char* txGetModuleFileName (bool fileNameOnly = true) {
        if (fileNameOnly)
            return nullptr;
        return SDL_GetWindowTitle(SDL_GetWindowFromID(txWindow()));
    }

    COLORREF RGB (int red, int green, int blue) {
        COLORREF result = { red, green, blue };
        return result;
    }

    HPEN txSetColor (COLORREF color, double thickness = 1, HDC dc = txDC()) {
        (void)(thickness);
        SDL_Renderer* rendererContext = dc;
        if (rendererContext == nullptr)
            return nullptr;
        txLinUnportableLastDrawColor.r = color.r;
        txLinUnportableLastDrawColor.g = color.g;
        txLinUnportableLastDrawColor.b = color.b;
        SDL_SetRenderDrawColor(rendererContext, color.r, color.g, color.b, 0);
        return rendererContext;
    }

    COLORREF txColor (double red, double green, double blue) {
        COLORREF color = { (int)(red), (int)(green), (int)(blue) };
        txSetColor(color);
        return color;
    }

    COLORREF txGetColor (HDC dc = txDC()) {
        COLORREF result = { 255, 255, 255 };
        if (dc == nullptr)
            return result;
        result = txLinUnportableLastDrawColor;
        return result;
    }

    COLORREF txFillColor (double red, double green, double blue) {
        txLinUnportableLastFillColor.r = (int)(red);
        txLinUnportableLastFillColor.g = (int)(green);
        txLinUnportableLastFillColor.b = (int)(blue);
        return txLinUnportableLastFillColor;
    } 

    COLORREF txGetFillColor (HDC dc) {
        return txLinUnportableLastFillColor;
    }

    COLORREF txExtractColor (COLORREF color, COLORREF component) {
        // does not work yet
        COLORREF resultingColor = color;
        resultingColor.r = resultingColor.r - component.r;
        resultingColor.g = resultingColor.g - component.g;
        resultingColor.b = resultingColor.b - component.b;
        return resultingColor;
    }


    bool txClear (HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        COLORREF oldC = txGetColor();
        txSetColor(txGetFillColor());
        SDL_RenderClear(dc);
        txSetColor(oldC);
        return true;
    }


    inline bool txSetPixel (double x, double y, COLORREF color = txGetColor(), HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        COLORREF oldC = txGetColor();
        txSetColor(color);
        SDL_RenderDrawPoint(dc, (int)(x), (int)(y));
        txSetColor(oldC);
        return true;
    }

    inline bool txPixel (double x, double y, double red, double green, double blue, HDC dc = txDC()) {
        return txSetPixel(x, y, RGB((int)(red), (int)(green), (int)(blue)), dc);
    }

    Uint32 txLinUnportableGetPixel(SDL_Surface* surface, int x, int y) {
        // from http://sdl.beuc.net/sdl.wiki/Pixel_Access
        int bpp = surface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        switch(bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;
        }
    }

    inline COLORREF txGetPixel (double x, double y, HDC dc = txDC()) {
        COLORREF result = { 255, 255, 255 };
        if (dc == nullptr)
            return result;
        Uint32 pixelRaw = txLinUnportableGetPixel(SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow())), (int)(x), (int)(y));
        Uint8 red;
        Uint8 green;
        Uint8 blue;
        SDL_GetRGB(pixelRaw, SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow()))->format, &red, &green, &blue);
        result.r = (int)(red);
        result.g = (int)(green);
        result.b = (int)(blue);
        return result;
    }

    inline bool txUpdateWindow(bool doUpdate = true) {
        txLinUnportableAutomaticWindowUpdates = doUpdate;
        if (doUpdate)
            txRedrawWindow();
        return doUpdate;
    }

    inline bool txLine (double x0, double y0, double x1, double y1, HDC dc = txDC()) {
        if (dc == nullptr) {
            DBGOUT << "dc is nullptr, return false" << std::endl;
            return false;
        }
        /*
        DBGINT(x0);
        DBGINT(y0);
        DBGINT(x1);
        DBGINT(y1);
        DBGOUT << "SDL_RenderDrawLine" << std::endl;
        */
        SDL_RenderDrawLine(dc, (int)(x0), (int)(y0), (int)(x1), (int)(y1));
        //DBGOUT << "txRedrawWindow()" << std::endl;
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow(); 
        //DBGOUT << "return true;" << std::endl;
        return true;
    }

    inline bool txRectangle (double x0, double y0, double x1, double y1, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        SDL_Rect rectangle;
        rectangle.x = (int)(x0);
        rectangle.y = (int)(y0);
        rectangle.w = txLinUnportableModule(x1 - x0);
        rectangle.h = txLinUnportableModule(y1 - y0);
        SDL_RenderDrawRect(dc, &rectangle);
        if (txGetFillColor() != TX_TRANSPARENT)
            txFloodFill(x0, y0, txGetFillColor(), FLOODFILLSURFACE, dc, txGetColor());
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow(); 
        return true;
    }

    inline bool txPolygon (const POINT* points, int numPoints, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        SDL_Point* sdlPoints = txLinUnportablePointCapsToSDL(points, numPoints);
        SDL_RenderDrawPoints(dc, sdlPoints, numPoints);
        if (txGetFillColor() != TX_TRANSPARENT)
            txFloodFill((double)(sdlPoints[0].x), (double)(sdlPoints[0].y), txGetFillColor(), FLOODFILLSURFACE, dc, txGetColor());
        free(sdlPoints);
        sdlPoints = nullptr;
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow(); 
        return true;
    } 

    inline bool txCircle (double x, double y, double r) {
        int xtmp = (int)(r);
        int ytmp = 0;
        txSetPixel((int)(x) + xtmp, (int)(y) + ytmp);
        if ((int)(r) > 0) {
            txSetPixel((int)(x) + xtmp, (ytmp * (-1)) + (int)(y));
            txSetPixel((int)(x) + ytmp, xtmp + (int)(y));
            txSetPixel((int)(x) + (ytmp * (-1)), xtmp + (int)(y));
        }
        int P = 1 - (int)(r);
        while (xtmp > ytmp) {
            ytmp = ytmp + 1;
            if (P <= 0)
                P = P + (2 * ytmp) + 1;
            else {
                xtmp = xtmp - 1;
                P = P + (2 * ytmp) - (2 * xtmp) + 1;
            }
            if (xtmp < ytmp)
                break;
            txSetPixel((int)(x) + xtmp, ytmp + (int)(y));
            txSetPixel((int)(x) + (xtmp * (-1)), ytmp + (int)(y));
            txSetPixel((int)(x) + xtmp, (ytmp * (-1)) + (int)(y));
            txSetPixel((int)(x) + (xtmp * (-1)), (ytmp * (-1)) + (int)(y));
            if (xtmp != ytmp) {
                txSetPixel((int)(x) + ytmp, xtmp + (int)(y));
                txSetPixel((int)(x) + ((-1) * ytmp), xtmp + (int)(y));
                txSetPixel((int)(x) + ytmp, ((-1) * xtmp) + (int)(y));
                txSetPixel((int)(x) + ((-1) * ytmp), ((-1) * xtmp) + (int)(y));
            }
        }
    #ifdef TXLIN_NEEDTOFILLALLFIGURES
        if (txGetFillColor() != TX_TRANSPARENT)
            txFloodFill((x + (r / 2)), (y + (r / 2)), txGetFillColor(), FLOODFILLSURFACE, txDC(), txGetColor());
    #endif
        return true;
    }

    bool txFloodFill (double x, double y, COLORREF color, DWORD mode, HDC dc, COLORREF oldcolor) {
        if (dc == nullptr)
            return false;
        COLORREF realOld = oldcolor;
        if (realOld.r == -1 && realOld.g == -1 && realOld.b == -1)
            realOld = txGetPixel(x, y, dc);
        if (x >= txGetExtentX() || y >= txGetExtentY())
            return false;
#ifdef TXLIN_FAST_UNSTABLE_FLOODFILL
#warning "This flood fill algorithm might be faster, but it crashes a lot. Use at your own risk."
        TXLIN_WARNING("txFloodFill() was built with TXLIN_FAST_UNSTABLE_FLOODFILL macros enabled. This means that this function might crash at some point because of stack overflow.");
        if (txGetPixel(x, y, dc) == realOld) {
            txSetPixel(x, y, color, dc);
            txFloodFill(x + 1, y, color, mode, dc, realOld);
            txFloodFill(x, y + 1, color, mode, dc, realOld);
            txFloodFill(x - 1, y, color, mode, dc, realOld);
            txFloodFill(x, y - 1, color, mode, dc, realOld);
        }
#else
        txUpdateWindow(false);
        std::vector<int> vXPos;
        COLORREF oldDrawColor = txGetColor();
        txSetColor(color);
        for (int ypos = (int)(y); ypos < txGetExtentY(); ypos++) {
            vXPos.clear();
            std::vector<int> lineStart;
            int lastxpos = 0;
            for (int xpos = (int)(x); xpos < txGetExtentX(); xpos++) {
                if (txGetPixel(xpos, ypos, dc) == realOld)
                    vXPos.push_back(xpos);
            }
            if (vXPos.size() > 1)
                txLine(vXPos.front(), ypos, vXPos.back(), ypos, dc);
        }
        txSetColor(oldDrawColor);
        txUpdateWindow(true);
#endif
        return true;

    }

    /*


    bool txArc (double x0, double y0, double x1, double y1, double startAngle, double totalAngle, HDC dc = txDC());


    bool txPie (double x0, double y0, double x1, double y1, double startAngle, double totalAngle, HDC dc = txDC());


    bool txChord (double x0, double y0, double x1, double y1, double startAngle, double totalAngle, HDC dc = txDC());


    bool txFloodFill (double x, double y, COLORREF color = TX_TRANSPARENT, DWORD mode = FLOODFILLSURFACE, HDC dc = txDC());
    */

    bool txTriangle (double x1, double y1, double x2, double y2, double x3, double y3) {
        if (txLine(x1, y1, x2, y2) && txLine(x2, y2, x3, y3) && txLine(x3, y3, x1, y1))
            return true;
        return false;
    }

    inline void txLinUnportableSDLEventLoop() {
        bool stop = false;
        while (stop == false) {
            if (txLinUnportableSDLProcessOneEvent() == TXLIN_UNPORTABLEDEF_EVENTPROCESSING_QUIT) {
                stop = true;
                break;
            }
        }
        return;
    }

    inline int txBegin() {
        bool result = txUpdateWindow(false);
        if (result)
            return 0;
        return 1;
    }

    inline int txEnd() {
        bool result = txUpdateWindow(true);
        if (result) {
            txLinUnportableSDLProcessOneEvent();
            return 0;
        }
        return 1;
    }

    inline void txLinUnportableMonolithicCharacterSet(int x, int y, const char character) {
        char upperChar = (char)(toupper(character));
        if (upperChar == ' ') {
            DBGOUT << "space" << std::endl;
        }
        else if (upperChar == '.')
            txSetPixel((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        else if (upperChar == '\n' || upperChar == '\r' || upperChar == '\0') {
            TXLIN_WARNING("Newline character was found in the string specified.");
        }
        else if (upperChar == '!') {
            txLinUnportableMonolithicCharacterSet(x, y, '.');
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT - 2);
        }
        else if (upperChar == '+') {
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == ',')
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT - 2, (int)(x) - 1, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT + 2);
        else if (upperChar == 'A') {
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y));
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'B' || upperChar == '6' || upperChar == '9') {
            if (upperChar == '9')
                txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            else
                txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            //txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            if (upperChar != '6')
                txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'C') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'D') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'E' || upperChar == 'F' || upperChar == '3') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            if (upperChar != 'F')
                txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            if (upperChar != '3')
                txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            else
                txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'G') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'H') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'I')
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        else if (upperChar == 'J') {
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'K') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'L') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'M') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'N') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'P' || upperChar == 'R') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT + 2);
            if (upperChar == 'R')
                txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'Q') {
            txCircle((int)(x), (int)(y), (int)(TXLIN_TEXTSET_HALFHEIGHT));
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'S' || upperChar == '5') {
            if (upperChar == 'S')
                txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            else {
                txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + 1);
                txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + 1, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            }
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'T') {
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'U') {
             txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
             txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
             txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'V') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'W') {
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'X') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'Y') {
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'Z') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == '1') {
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == '2') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == '4') {
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == '7') {
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == '8') {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else {
            txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y));
        }
    }

    inline bool txTextOut(double x, double y, const char* text, HDC dc = txDC(), bool ignoreTextAlignSettings = false) {
        if (dc == nullptr)
            return false;
        if (ignoreTextAlignSettings == false) {
            if (txLinUnportableTextAlign == TA_CENTER)
                return txTextOut((x - (txGetTextExtent(text, dc).cx / 2)), y, text, dc, true);
            else if (txLinUnportableTextAlign == TA_TOP)
                return txTextOut(x, y - (txGetTextExtent(text, dc).cy), text, dc, true);
        }
        int posx = (int)(x);
        for (int i = 0; i < strlen(text); i++) {
            txLinUnportableMonolithicCharacterSet(posx, (int)(y), text[i]);
            posx = posx + TXLIN_TEXTSET_MAXWIDTH + 3;
        }
        return true;
    }

    inline HFONT txSelectFont (const char* name, double sizeY, HDC dc = txDC()) {
        (void)(dc);
        (void)(name);
        TXLIN_TEXTSET_MAXWIDTH = ((int)(sizeY) / 2);
        if (TXLIN_TEXTSET_MAXWIDTH < 4)
            TXLIN_TEXTSET_MAXWIDTH = 4;
        TXLIN_TEXTSET_MAXHEIGHT = TXLIN_TEXTSET_MAXWIDTH;
        TXLIN_WARNING(std::string("txSelectFont(const char* name, double sizeY, HDC dc) 'name' parameter is ignored, because TXLin uses its own monolithic font engine rather than FontConfig. Thus, the font \"" + std::string(name) + "\" is not available."));
        return nullptr;
    }

    unsigned txSetTextAlign (unsigned align = TA_BOTTOM, HDC dc = txDC()) {
        if (dc == nullptr)
            return 0;
        txLinUnportableTextAlign = align;
        return TA_BOTTOM;
    }

    inline void txTextCursor(bool value = true) {
        // does not work yet
        (void)(value);
        TXLIN_WARNING("txTextCursor(bool value) was added to TXLin for source compatibility. It actually does nothing, because there is no easy and cross-platform way to turn off cursor blinking on both Linux and Mac OS X.");
    }

    inline HBRUSH txSetFillColor(COLORREF color = TX_TRANSPARENT, HDC dc = txDC()) {
        if (dc == nullptr)
            return nullptr;
        txFillColor(color.r, color.g, color.b);
        return dc;
    }

    /*
    inline bool txEllipse(double x0, double y0, double x1, double y1, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        int width = txLinUnportableModule((int)(x1 - x0));
        int height = txLinUnportableModule((int)(y1 - y0));
        for (int y = (height * (-1)); y < (height + 1); y++) {
            for (int x = (width * (-1)); x < (width + 1); x++) {
                if ((TXLIN_UNPORTABLEDEF_SQUARE(x) * (TXLIN_UNPORTABLEDEF_SQUARE(height)) <= (TXLIN_UNPORTABLEDEF_SQUARE(width) * TXLIN_UNPORTABLEDEF_SQUARE(height))))
                    txSetPixel((int)(x0) + x, (int)(y0) + y);
            }
        }
        return true;
    }
    */

    //inline bool txEllipse(double rx_dbl, double ry_dbl, double x_dbl, double y_dbl, HDC dc = txDC()) {
    inline bool txLinUnportableEllipseClassicImplementation(double x0, double y0, int width, int height, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        int hh = TXLIN_UNPORTABLEDEF_SQUARE(height);
        int ww = TXLIN_UNPORTABLEDEF_SQUARE(width);
        int hhww = hh * ww;
        int xz = width;
        int dx = 0;
        for (int x = (width * (-1)); x <= width; x++)
            txSetPixel((int)(x0) + x, y0, txGetColor(), dc);

        // now do both halves at the same time, away from the diameter
        for (int y = 1; y <= height; y++) {
            int xa = xz - (dx - 1);  // try slopes of dx - 1 or more
            for (; xa > 0; xa--)
                if ((TXLIN_UNPORTABLEDEF_SQUARE(xa) * hh) + (TXLIN_UNPORTABLEDEF_SQUARE(y) * ww) <= hhww)
                    break;
            dx = xz - xa;  // current approximation of the slope
            xz = xa;

            for (int x = (xz * (-1)); x <= xz; x++) {
                txSetPixel((int)(x0) + x, (int)(y0) - y, txGetColor(), dc);
                txSetPixel((int)(x0) + x, (int)(y0) + y, txGetColor(), dc);
            }
        }
        return true;
    }

    #define txSticky() txLinUnportableSDLEventLoop()

    inline bool txEllipse(double x0, double y0, double x1, double y1, HDC dc = txDC()) {
        int height = txLinUnportableModule((int)(y1 - y0));
        int width = txLinUnportableModule((int)(x1 - x0));
        int x0_new = (int)(x0) + (width / 2);
        int y0_new = (int)(y0) + (height / 2);
        return txLinUnportableEllipseClassicImplementation(x0_new, y0_new, width, height, dc);
    }

    SIZE txGetTextExtent(const char* text, HDC dc) {
        SIZE sizeOfText;
        sizeOfText.cx = 0.0;
        sizeOfText.cy = 0.0;
        if (dc == nullptr || text == nullptr)
            return sizeOfText;
        sizeOfText.cx = (unsigned long)(strlen(text) * TXLIN_TEXTSET_MAXWIDTH);
        sizeOfText.cy = (unsigned long)(TXLIN_TEXTSET_MAXHEIGHT);
        return sizeOfText;
    }

    inline int txGetTextExtentY(const char* text, HDC dc = txDC()) {
        return txGetTextExtent(text, dc).cy;
    }

    inline int txGetTextExtentX(const char* text, HDC dc = txDC()) {
        return txGetTextExtent(text, dc).cx;
    }

    inline double txSleep(double time = 0) {
        SDL_Delay(time);
        return time;
    }

    inline double txQueryPerformance() {
        TXLIN_WARNING("txQueryPerformance() was kept in TXLin for compatibility purposes. It will always return a const value.");
        return 7.9;
    }

    inline POINT txMousePos() {
        int x = 1;
        int y = 1;
        SDL_GetGlobalMouseState(&x, &y);
        POINT result = { (double)(x), (double)(y) };
        return result;
    }

    inline int txMouseX() {
        return (int)(txMousePos().x);
    }

    inline int txMouseY() {
        return (int)(txMousePos().y);
    }

    inline int txMessageBox(const char* text, const char* header = "TXLin", unsigned flags = 0) {
        if (text == nullptr || header == nullptr)
            return 1;
        if (flags != 0)
            TXLIN_WARNING("txMessageBox(const char* text, const char* header, unsigned flags) flags parameter is ignored because there are portability issues.");
        return SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, header, text, nullptr);
    }

    inline bool txNotifyIcon(unsigned flags, const char* title, const char* format, ...) {
        if (title == nullptr || format == nullptr)
            return false;
        if (flags != 0)
            TXLIN_WARNING("txNotifyIcon(unsigned flags, const char* title, const char* format, ...) flags parameter is ignored because there are portability issues.");
    #ifdef __APPLE__
        return (std::system(std::string(std::string("osascript -e 'display notification \"") + std::string(format) + std::string("\" with title \"") + std::string(title) + std::string("\"'")).c_str()) == 0);
    #else
        if (std::system("which notify-send > /dev/null 2>&1") != 0) {
            TXLIN_WARNINGWITHMESSAGEBOX("notify-send is not installed on your system, please install it so that notifications would work.");
            return false;
        }
        return (std::system(std::string(std::string("notify-send -u low '") + std::string(title) + std::string("' '") + std::string(format) + "'").c_str()) == 0);
    #endif
    }

    inline char* txLinUnportableMacLinuxPath(const char* wpathstring) {
        if (wpathstring == nullptr)
            return nullptr;
        char* result = (char*)(calloc(strlen(wpathstring), sizeof(char)));
        for (int i = 0; i < strlen(wpathstring); i++) {
            if (wpathstring[i] != '\\')
                result[i] = wpathstring[i];
            else
                result[i] = '/';
        }
        result[strlen(wpathstring)] = '\0';
        return result;
    }

    inline char* txTextDocument(const char* filename) {
        char* filename2 = txLinUnportableMacLinuxPath(filename);
        if (filename2 == nullptr)
            return nullptr;
        std::ifstream istream(filename2);
        std::string str((std::istreambuf_iterator<char>(istream)), std::istreambuf_iterator<char>());
        char* final = (char*)(calloc(str.size(), sizeof(char)));
        strcpy(final, str.c_str());
        return final;
    }

    inline char* txPassword() {
        const char* saveSocket = "/tmp/txlin-passwordbox.sock";
#ifdef __APPLE__
        if (std::system(std::string("osascript -e 'display dialog \"Type your password\" default answer \"\" with hidden answer' > " + std::string(saveSocket)).c_str()) != 0)
#else
        if (std::system(std::string("zenity --password > " + std::string(saveSocket)).c_str()) != 0)
#endif
            return nullptr;
        char* readAnswerCString = txTextDocument(saveSocket);
        if (readAnswerCString == nullptr || strlen(readAnswerCString) == 0) {
            TXLIN_UNPORTABLEDEF_RMFILE(saveSocket);
            return nullptr;
        }
        std::string readAnswer = readAnswerCString;
        free(readAnswerCString);
        TXLIN_UNPORTABLEDEF_RMFILE(readAnswerCString);
#ifdef __APPLE__
        size_t lastOfText = readAnswer.find_last_of(":");
        if (lastOfText == std::string::npos)
            return nullptr;
        std::string toSetUserSelected = "";
        for (size_t i = (lastOfText + 1); i < readAnswer.size(); i++)
            toSetUserSelected = toSetUserSelected + readAnswer.at(i);
        readAnswer = toSetUserSelected;
#endif
        char* realAnswer = (char*)(calloc(readAnswer.size(), sizeof(char)));
        strcpy(realAnswer, readAnswer.c_str());
        if (realAnswer[readAnswer.size() - 1] == '\n')
            realAnswer[readAnswer.size() - 1] = '\0';
        return realAnswer;
    }

    inline char* txInputBox(const char* text, const char* caption = "TXLin", const char* input = "") {
        const char* saveSocket = "/tmp/txlin-platformnativeinputbox.sock";
        if (text == nullptr || caption == nullptr || input == nullptr)
            return nullptr;
    #ifdef __APPLE__
        std::system(std::string(std::string("osascript -e 'display dialog \"") + std::string(text) + std::string("\" default answer \"") + std::string(input) + std::string("\" with title \"") + std::string(caption) + std::string("\"' > ") + std::string(saveSocket) + std::string(" 2>/dev/null")).c_str());
    #else
        if (std::system("which zenity > /dev/null 2>&1") != 0) {
            TXLIN_WARNINGWITHMESSAGEBOX("GNOME zenity is not installed on your system, please install it so that input boxes would work.");
            return nullptr;
        }
        std::system(std::string(std::string("zenity --entry --text='") + std::string(caption) + ':' + ' ' + std::string(text) + std::string("' --entry-text='") + std::string(input) + '\'' + std::string(" > ") + std::string(saveSocket) + std::string(" 2>/dev/null")).c_str());
    #endif
        char* userAnsweredCString = txTextDocument(saveSocket);
        if (userAnsweredCString == nullptr)
            return nullptr;
        std::string userAnswered(userAnsweredCString);
        free(userAnsweredCString);
    #ifdef __APPLE__
        size_t lastOfText = userAnswered.find_last_of(":");
        if (lastOfText == std::string::npos)
            return (char*)(calloc(1, sizeof(char)));
        std::string toSetUserSelected = "";
        for (size_t i = (lastOfText + 1); i < userAnswered.size(); i++)
            toSetUserSelected = toSetUserSelected + userAnswered.at(i);
        userAnswered = toSetUserSelected;
    #endif
        char* allocatedBufferReturned = (char*)(calloc(userAnswered.size(), sizeof(char)));
        strcpy(allocatedBufferReturned, userAnswered.c_str());
        SDL_RaiseWindow(SDL_GetWindowFromID(txWindow()));
        if (allocatedBufferReturned[userAnswered.size() - 1] == '\n')
            allocatedBufferReturned[userAnswered.size() - 1] = '\0';
        return allocatedBufferReturned;
    }

    inline LOGFONT* txFontExist(const char* name) {
        (void)(name);
        return nullptr;
    }

    /*
    inline int txLinUnportableToLinuxColors(unsigned bitColor, bool isBackground = false) {
        int addCoef = 0;
        if (isBackground)
            addCoef = 10;
        if (bitColor == 0x0)
            return (31 + addCoef);
        else if (bitColor == 0x1)
            return (34 + addCoef);
        else if (bitColor == 0x2)
            return (32 + addCoef);
        else if (bitColor == 0x3)
            return (36 + addCoef);
        else if (bitColor == 0x4 || bitColor == 0xC)
            return (31 + addCoef);
        else if (bitColor == 0x5 || bitColor == 0xD)
            return (35 + addCoef);
        else if (bitColor == 0x6 || bitColor == 0xE)
            return (33 + addCoef);
        else
            return -1;

    }
    */

    inline std::string txLinUnportableToLinuxColors(unsigned bitColor, bool isBackground = false) {
        if (bitColor == 0x1)
            return "\033[1;34m";
        else if (bitColor == 0x2)
            return "\033[1;32m";
        else if (bitColor == 0x3)
            return "\033[1;36m";
        else if (bitColor == 0x4 || bitColor == 0xC)
            return "\033[1;31m";
        else if (bitColor == 0x5 || bitColor == 0xD)
            return "\033[1;35m";
        else if (bitColor == 0x6 || bitColor == 0xE)
            return "\033[1;33m";
        else
            return "\033[0m";

    }

    inline std::string txLinUnportableIntToString(int num) {
        std::stringstream stream;
        stream << num;
        return stream.str();
    }

    inline void txSetConsoleAttr(unsigned colors = 0x07) {
        txLinUnportableLastTerminalColor = colors;
        unsigned colors2 = colors;
        if (colors2 > 0x9) {
            while (colors2 >= 0x10)
                colors2 = colors2 - 0x10;
        }
        printf("%s", txLinUnportableToLinuxColors(colors2, false).c_str());
        return;
    }

    inline unsigned txGetConsoleAttr() {
        return txLinUnportableLastTerminalColor;
    }

    inline bool txClearConsole() {
        return (std::system("clear") == 0);
    }

    inline void SetWindowText(HWND windowDescriptor, const char* title) {
        SDL_SetWindowTitle(SDL_GetWindowFromID(windowDescriptor), title);
        return;
    }

    inline bool GetAsyncKeyState(Uint8 key) {
        const Uint8* states = SDL_GetKeyboardState(NULL);
        if (states[key])
            return true;
        return false;
    }

    inline bool txPlaySound(const char* filename2, unsigned mode = SND_ASYNC) {
        char* filename = txLinUnportableMacLinuxPath(filename2);
        std::string playerWithoutArgs = "play";
        std::string player = "play";
    #ifdef __APPLE__
        playerWithoutArgs = "afplay";
        player = "afplay -q 1 -d";
    #else
        if (std::system("which play > /dev/null 2>&1") != 0) {
            TXLIN_WARNINGWITHMESSAGEBOX("SoX is required to play audio files. It is not installed on your system. Please install it to continue.");
            free(filename);
            return false;
        }
    #endif
        if (filename == nullptr || strlen(filename) < 2) {
            std::system(std::string("killall " + playerWithoutArgs).c_str());
            if (filename != nullptr)
                TXLIN_UNPORTABLEDEF_RMFILE(filename);
            return true;
        }
        std::string stdStringFilename = filename;
        if (stdStringFilename.find("/") == std::string::npos)
            stdStringFilename = std::string(getcwd(nullptr, 256)) + "/" + stdStringFilename;
        std::string cmd = player + ' ' + stdStringFilename;
        if (mode == SND_ASYNC)
            cmd = cmd + " &";
        else if (mode == SND_LOOP)
            cmd = "sh -c \"touch /tmp/txlinplay.tmp; while test -f /tmp/txlinplay.tmp; do " + cmd + "; done\" &";
        else if (mode == SND_APPLICATION)
    #ifdef __APPLE__
            cmd = "open \"" + stdStringFilename + '\"' + std::string(" &");
    #else
            cmd = "xdg-open \"" + stdStringFilename + '\"' + std::string(" &");
    #endif
        else if (mode == -1) {
            TXLIN_WARNING("Unsupported txPlaySound(const char* filename, unsigned mode) argument");
            free(filename);
            return false;
        }
        free(filename);
        return (std::system(cmd.c_str()) == 0);
    }

    inline void txDump(const void* address, const char* name) {
        txSetConsoleAttr(FOREGROUND_LIGHTMAGENTA);
        printf("{<%p>}", address);
        txSetConsoleAttr(FOREGROUND_WHITE);
        printf("\n");
        const unsigned char* p = (const unsigned char*)(address);
        unsigned x = 0;
        unsigned attr = FOREGROUND_WHITE;
        txSetConsoleAttr (FOREGROUND_WHITE);
        printf ("\n%*.*s ", (int)(sizeof(address)) * 2, (int)(sizeof(address)) * 2, ((name)? name : ""));
        txSetConsoleAttr (FOREGROUND_YELLOW);
        for (x = 0; x < 16; x++)
            printf ("%02X ", x);
        for (x = 0; x < 16; x++)
            printf ("%X",    x);

        for (int y = 0; y < 16; y++, p += 16) {
            txSetConsoleAttr (FOREGROUND_YELLOW);
            printf ("\n" "%*p ", (int)(sizeof(address)) * 2, p);
            int color = FOREGROUND_LIGHTGREEN;
            for (x = 0; x < 16; x++) {
                txSetConsoleAttr (color + x/4%2); 
                printf ("%02X ", p[x]); 
            }
            for (x = 0; x < 16; x++) { 
                txSetConsoleAttr (color + x/4%2); 
                printf ("%c", (isprint (p[x]) && !iscntrl (p[x]))? p[x] : '.'); 
            }
        }
        txSetConsoleAttr(attr);
        printf ("\n");
    }

    inline bool txLock(bool wait = true) {
        (void)(wait);
        TXLIN_WARNING("txLock(bool wait) is kept in TXLin for compatibility purposes and does nothing.");
        return false;
    }

    inline bool txUnlock() {
        TXLIN_WARNING("txUnlock() is kept in TXLin for compatibility purposes and does nothing.");
        return false;
    }

    inline bool txSaveImage(const char* filename, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        return (SDL_SaveBMP(SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow())), filename) == 0);
    }

    inline HDC txLoadImage(const char* filename, unsigned imageFlags = 0, unsigned loadFlags = 0) {
        (void)(imageFlags);
        (void)(loadFlags);
        if (filename == nullptr)
            return nullptr;
        return (SDL_CreateSoftwareRenderer(SDL_LoadBMP(filename)));
    }

    inline bool txDeleteDC(HDC dc) {
        if (dc == nullptr)
            return false;
        SDL_DestroyRenderer(dc);
        return true;
    }

    inline bool txBitBlt(HDC destImage, double xDest, double yDest, double width = 0.0, double height = 0.0, HDC sourceImage = txDC(), double xSource = 0.0, double ySource = 0.0) {
        if (sourceImage == nullptr || destImage == nullptr)
            return false;
        TX_ERROR("This function is currently unavailable.");
        int kickstartSourceX = (int)(xSource);
        int kickstartSourceY = (int)(ySource);
        int kickstartDestX = (int)(xDest);
        int kickstartDestY = (int)(yDest);
        for (int cy = kickstartSourceY; cy < (int)(height); cy++) {
            for (int cx = kickstartSourceX; cx < (int)(width); cx++) {
                COLORREF clrPix = txGetPixel(cx, cy, sourceImage);
                txSetPixel(kickstartDestX, kickstartDestY, clrPix, destImage);
                kickstartDestX = kickstartDestX + 1;
                kickstartDestY = kickstartDestY + 1;
                if (kickstartDestX >= (int)(width)) {
                    kickstartDestX = (int)(xDest);
                    break;
                }
            }
            kickstartDestY = kickstartDestY + 1;
            if (kickstartDestY >= (int)(height))
                break;
        }
        return true;
    }

    inline bool txBitBlt(double xDest, double yDest, HDC sourceImage, double xSource = 0.0, double ySource = 0.0) {
        return false;
    }

    inline bool txTransparentBlt(HDC destImage, double xDest, double yDest, double width, double height, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, COLORREF transColor = TX_BLACK) {
        if (destImage == nullptr || sourceImage == nullptr)
            return false;
        (void)(transColor);
        return txBitBlt(destImage, xDest, yDest, width, height, sourceImage, xSource, ySource);
    }

    inline bool txTransparentBlt(double xDest, double yDest, HDC sourceImage, COLORREF transColor = TX_BLACK, double xSource = 0.0, double ySource = 0.0) {
        if (sourceImage == nullptr)
            return false;
        int width = 0;
        int height = 0;
        SDL_GetRendererOutputSize(sourceImage, &width, &height);
        return txTransparentBlt(txDC(), xDest, yDest, (double)(width), (double)(height), sourceImage, xSource, ySource);
    }


    inline bool txAlphaBlend(HDC destImage, double xDest, double yDest, double width, double height, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, double alpha = 1.0) {
        if (destImage == nullptr || sourceImage == nullptr)
            return false;
        (void)(alpha);
        return txBitBlt(destImage, xDest, yDest, width, height, sourceImage, xSource, ySource);
    }

    inline bool txAlphaBlend(double xDest, double yDest, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, double alpha = 1.0) {
        if (sourceImage == nullptr)
            return false;
        int width = 0;
        int height = 0;
        SDL_GetRendererOutputSize(sourceImage, &width, &height);
        return txAlphaBlend(txDC(), xDest, yDest, (double)(width), (double)(height), sourceImage, xSource, ySource);
    }
#ifndef TXLIN_NO_NAMESPACE
}

using namespace TX;
#endif

#endif