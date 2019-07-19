/*
TXLin

Copyright (c) 2018-2019, Tim K <timprogrammer@rambler.ru>

TXLin's licensing terms are different from other libraries. See
LICENSE file in the source folder for more info.
*/

#ifndef TXLIN_H
#define TXLIN_H
#include <SDL.h>
#include <SDL_ttf.h>
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
#include <string>
#include <vector>
#include <execinfo.h>
#ifdef TXLIN_PTHREAD
#include <pthread.h>
#endif

#define HWND Uint32
#define DWORD unsigned long
#define HDC SDL_Renderer*
#define HPEN SDL_Renderer*
#define HBITMAP void*
#define RGBQUAD Uint32
#define HFONT void*
#define LONG unsigned long
#define HBRUSH SDL_Renderer*
#define LOGFONT unsigned int
#define SHORT unsigned int
#define CURSORREF SDL_SystemCursor
#ifdef TXLIN_PTHREAD
#define txthread_t pthread_t
#endif

#define TXLIN_VERSION "TXLin [Ver: 1.76a, Rev: 119, Date: 2019-07-19 17:51:00]"
#define TXLIN_AUTHOR "Copyright (C) timkoi (Tim K, http://timkoi.gitlab.io/)"
#define TXLIN_VERSIONNUM 0x176a119
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
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"
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
#elif defined(__linux__)
#define TXLIN_OPERATINGSYSTEM "Linux"
#elif defined(__FreeBSD__)
#define TXLIN_OPERATINGSYSTEM "FreeBSD"
#define TXLIN_NO_CPU_DETECTION 1
#else
#define TXLIN_OPERATINGSYSTEM "Unsupported UNIX-like operating system"
#define TXLIN_NO_CPU_DETECTION 1
#warning "TXLin cannot detect your current operating system. Use at your own risk."
#endif
#define TXLIN_NO_3D_ACCELERATION 1

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
#define txPI 3.14159265358979323846

#define VK_UP SDL_SCANCODE_UP
#define VK_DOWN SDL_SCANCODE_DOWN
#define VK_LEFT SDL_SCANCODE_LEFT
#define VK_RIGHT SDL_SCANCODE_RIGHT
#define VK_ESCAPE SDL_SCANCODE_ESCAPE
#define VK_SHIFT SDL_SCANCODE_LSHIFT
#define VK_SPACE SDL_SCANCODE_KP_SPACE
#define VK_CONTROL SDL_SCANCODE_LCTRL
#define VK_MENU SDL_SCANCODE_LALT

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

#define MB_ABORTRETRYIGNORE 0x00000002L
#define MB_CANCELTRYCONTINUE 0x00000006L
#define MB_OK 0x00000000L
#define MB_OKCANCEL 0x00000001L
#define MB_RETRYCANCEL 0x00000005L
#define MB_YESNO 0x00000004L
#define MB_YESNOCANCEL 0x00000003L

#define IDABORT 3
#define IDCANCEL 2
#define IDCONTINUE 11
#define IDIGNORE 5
#define IDNO 7
#define IDOK 1
#define IDRETRY 4
#define IDTRYAGAIN IDRETRY
#define IDYES 6

#define txGDI(function) TXLIN_WARNING(std::string(std::string("txGDI does not work on Mac OS X or Linux, because it is a Windows-specific function. As such, ") + std::string(#function) + std::string(" won't be called.")).c_str());

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define ROUND(x) (round((double)(x)))
#define SIZEARR(array) (int)(((double)(sizeof(array)) / (double)(sizeof(array[0]))))
#ifndef TXLIN_DEBUG
#define verify(expr) (expr)
#define TX_DEBUG_ERROR(msg) (void)(msg)
#else
#define verify(expr) assert(expr)
#define TX_DEBUG_ERROR(msg) TX_ERROR(msg)
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

#define txRandom(b1, b2) (b1)

#ifdef _TX_ALLOW_KILL_PARENT
#warning "_TX_ALLOW_KILL_PARENT is ignored by TXLin."
#endif

#ifndef TXLIN_MACOS_VOICEOVERVOICE
#define TXLIN_MACOS_VOICEOVERVOICE "Daniel"
#endif

#if __cplusplus < 201103L
#define nullptr 0
#warning "Your C++ compiler either does not support C++11 or, by default, operates in C++98 preprocessing mode. Please enable the C++11 mode by adding the \"-std=c++0x\" flag to your compiler. TXLin uses some features that are only present in C++11 in some cases, so you might get errors if you do not enable C++11."
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

struct RECT {
    double left;
    double top;
    double right;
    double bottom;
};

struct COORD {
    unsigned int X;
    unsigned int Y;
};

struct SMALL_RECT {
    unsigned int Left;
    unsigned int Top;
    unsigned int Right;
    unsigned int Bottom;
};

struct TXTYPE_SDLSURFRENDER {
    SDL_Surface* surface;
    SDL_Renderer* renderer;
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
    static int TXLIN_TEXTSET_MAXWIDTH = 12;
    static int TXLIN_TEXTSET_MAXHEIGHT = 12;
    static COLORREF txLinUnportableLastFillColor = TX_TRANSPARENT;
    static COLORREF txLinUnportableLastDrawColor = TX_WHITE;
    static unsigned txLinUnportableTextAlign = TA_BOTTOM;
    static bool txLinUnportableAllowExit = true;
    static int txLinUnportableLineThickness = 1;
    static bool txLinUnportableUseMonolithic = false;
    static std::vector<TXTYPE_SDLSURFRENDER> txLinUnportableDCSurfaces = std::vector<TXTYPE_SDLSURFRENDER>();

    inline HDC txDC();
    inline HWND txWindow();
    inline COLORREF txGetFillColor(HDC dc = txDC());
    inline bool txFloodFill (double x, double y, COLORREF realOld = txGetFillColor(), DWORD mode = FLOODFILLSURFACE, HDC dc = txDC());
    inline SIZE txGetTextExtent(const char* text, HDC dc = txDC());
    inline bool txClear(HDC dc = txDC());
    inline HBRUSH txSetFillColor(COLORREF color = TX_TRANSPARENT, HDC dc = txDC());
    inline char* txInputBox_nonNativeSDLRender(const char* text, const char* caption = "TXLin", const char* input = "", char mask = ' ');
    inline bool txNotifyIcon_nonNativeSDLRender(const char* text, const char* title);
    inline int txMessageBox(const char* text, const char* header = "TXLin", unsigned flags = MB_OK);
    inline void txSetConsoleAttr(unsigned colors = 0x07);
    inline bool txEllipse(double x0, double y0, double x1, double y1, HDC dc = txDC());

    inline std::string txLinUnportableNumToCPlusPlusString(int num) {
        std::stringstream stream;
        stream << num;
        return stream.str();
    }

    inline int txLinUnportableSDLProcessOneEvent() {
        SDL_Event* eventHandler = (SDL_Event*)(malloc(sizeof(SDL_Event)));
        if (SDL_PollEvent(eventHandler) == 0) {
            free(eventHandler);
            return TXLIN_UNPORTABLEDEF_EVENTPROCESSING_NONE;
        }
        if (eventHandler->type == SDL_QUIT && txLinUnportableAllowExit) {
            free(eventHandler);
            SDL_DestroyRenderer(txDC());
            SDL_DestroyWindow(SDL_GetWindowFromID(txWindow()));
            TTF_Quit();
            SDL_Quit();
            exit(0);
            return TXLIN_UNPORTABLEDEF_EVENTPROCESSING_QUIT;
        }
        free(eventHandler);
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

    HWND txWindow() {
        DBGINT(txLinUnportableRecentlyCreatedWindow);
        return txLinUnportableRecentlyCreatedWindow;
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

    inline bool txGetClosable() {
        return txLinUnportableAllowExit;
    }

    inline bool txSetClosable(bool value = true) {
        txLinUnportableAllowExit = value;
        return txLinUnportableAllowExit;
    }

    inline bool txMacOSOlderThanMavericks() {
#ifdef __APPLE__
        return (std::system("test `defaults read loginwindow SystemVersionStampAsString | cut -d '.' -f2` -lt 9") == 0);
#else
        return false;
#endif
    }

    inline int fsizeof(const char* filename) {
        if (filename == nullptr)
            return 0;
        FILE* fileDescriptor = fopen(filename, "r");
        if (fileDescriptor == nullptr)
            return 0;
        fseek(fileDescriptor, 0L, SEEK_END);
        long out = ftell(fileDescriptor);
        fclose(fileDescriptor);
        return (int)(out);
    }

    inline char* txTextDocument(const char* filename) {
        char* filename2 = txLinUnportableMacLinuxPath(filename);
        if (filename2 == nullptr) {
            TXLIN_WARNING("filename specified as nullptr.")
            return nullptr;
        }
        char* final = (char*)(calloc(fsizeof(filename) + 1, sizeof(char)));
        FILE* fileDescriptor = fopen(filename, "r");
        if (fileDescriptor == nullptr)
            return nullptr;
        int characterRepresentedAsInt = 0;
        int loc = 0;
        while ((characterRepresentedAsInt = getc(fileDescriptor)) != EOF) {
            final[loc] = (char)(characterRepresentedAsInt);
            loc = loc + 1;
        }
        fclose(fileDescriptor);
        return final;
    }

    inline bool txWriteDocument(const char* contents, const char* filename) {
        if (filename == nullptr || contents == nullptr)
            return false;

        FILE* fileDescriptor = fopen(filename, "w");
        if (fileDescriptor == nullptr)
            return false;

        fputs(contents, fileDescriptor);
        fclose(fileDescriptor);
        return true;
    }

    inline char* txSelectDocument(const char* text = "Please select a file to continue.", const char* filter = "*") {
        if (text == nullptr || filter == nullptr)
            return nullptr;
        std::string selectSocket = "/tmp/txlin-select.sock";
#ifdef __APPLE__
        if (txMacOSOlderThanMavericks())
            return txInputBox_nonNativeSDLRender(text, "TXLin Fallback File Selection Dialog");
        if (std::system(std::string("osascript -e 'choose file with prompt \"" + std::string(text) + "\"' of type {\"" + std::string(filter) + "\"} 2>/dev/null | sed 's+:+/+g' | cut -d '/' -f2- > " + selectSocket).c_str()) != 0)
#else
        if (std::system("which zenity > /dev/null 2>&1") != 0)
            return txInputBox_nonNativeSDLRender(text, "TXLin Fallback File Selection Dialog");
        if (std::system(std::string("zenity --file-selection --file-filter=\"" + std::string(filter) + "\" > " + selectSocket).c_str()) != 0)
#endif
            return nullptr;
        char* resultingText = txTextDocument(selectSocket.c_str());
        TXLIN_UNPORTABLEDEF_RMFILE(selectSocket.c_str());
#ifdef __APPLE__
        std::string resultingTextMacOpt = resultingText;
        free(resultingText);
        resultingText = (char*)(calloc(resultingTextMacOpt.size() + 1, sizeof(char)));
        resultingTextMacOpt = '/' + resultingTextMacOpt;
        strcpy(resultingText, resultingTextMacOpt.c_str());
#endif
        if (resultingText[strlen(resultingText) - 1] == '\n')
            resultingText[strlen(resultingText) - 1] = '\0';
        return resultingText;
    }

    inline bool txRemoveDocument(const char* filename2) {
        if (filename2 == nullptr)
            return false;
        char* filename = txLinUnportableMacLinuxPath(filename2);
        bool res = (TXLIN_UNPORTABLEDEF_RMFILE(filename) == 0);
        free(filename);
        return res;
    }

    inline unsigned long GetTickCount() {
        return (unsigned long)(SDL_GetTicks());
    }

    #define Sleep(ms) txSleep(ms)

    inline bool GetWindowRect(HWND window, RECT* where) {
        if (where == nullptr)
            return false;
        int basex = 0;
        int basey = 0;
        int width = 0;
        int height = 0;
        SDL_Window* wOrig = SDL_GetWindowFromID(window);
        if (wOrig == nullptr)
            return false;
        SDL_GetWindowPosition(wOrig, &basex, &basey);
        SDL_GetWindowSize(wOrig, &width, &height);
        where->left = basex;
        where->top = basey;
        where->right = basex + width;
        where->bottom = basey + height;
        return true;
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
        if ((SDL_Init(SDL_INIT_VIDEO) == 0) == false) {
            TXLIN_WARNING("SDL_GetError(): " + std::string(SDL_GetError()) + ", your program probably won't start due to SDL2 problems");
            return false;
        }
        if (TTF_Init() != 0) {
            TXLIN_WARNING("TTF_GetError(): " + std::string(TTF_GetError()) + ", your program probably won't display any text due to SDL2_ttf problems");
            return false;
        }
        txLinUnportableDCSurfaces.clear();
        return true;
    }

    inline int txLinUnportableModule(int number) {
        if (number < 0)
            return ((number) * (-1));
        return number;
    }

    inline void txRedrawWindow(bool mtFunc = false) {
        for (int i = 0; i < txLinUnportableDCSurfaces.size(); i++) {
            if (txLinUnportableDCSurfaces.at(i).renderer != nullptr)
                SDL_RenderPresent(txLinUnportableDCSurfaces.at(i).renderer);
        }
        SDL_UpdateWindowSurface(SDL_GetWindowFromID(txWindow()));
        if (mtFunc == false)
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
        txSetFillColor(TX_BLACK);
        txClear(txDC());
        SDL_UpdateWindowSurface(window);
        TXTYPE_SDLSURFRENDER windowRType = { SDL_GetWindowSurface(window), SDL_GetRenderer(window) };
        txLinUnportableDCSurfaces.push_back(windowRType);
        SDL_ShowWindow(window);
        SDL_RaiseWindow(window);
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

    inline bool txIsFreeBSD() {
#ifdef __FreeBSD__
        return true;
#else
        return false;
#endif
    }

    inline bool txLinUnportableFileExists(const char* file) {
        std::ifstream inputStream(file);
        return inputStream.good();
    }

    inline const char* txLinUnportableFindFont() {
#ifdef __APPLE__
        return "/System/Library/Fonts/Apple Symbols.ttf";
#else
        std::vector<const char*> fontsList;
        if (getenv("TXLIN_FONTFILE") != nullptr)
            fontsList.push_back(getenv("TXLIN_FONTFILE"));
        fontsList.push_back("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        fontsList.push_back("/usr/share/fonts/truetype/DejaVuSans.ttf");
        fontsList.push_back("/usr/share/fonts/dejavu/DejaVuSans.ttf");
        fontsList.push_back("/usr/share/fonts/TTF/DejaVuSans.ttf");
        for (int i = 0; i < fontsList.size(); i++) {
            if (txLinUnportableFileExists(fontsList.at(i))) {
                txLinUnportableUseMonolithic = false;
                return fontsList.at(i);
            }
        }
        txLinUnportableUseMonolithic = true;
        return nullptr;
#endif
    }

    inline LOGFONT* txFontExist(const char* name) {
        if (strcmp("System", name) == 0)
            return (LOGFONT*)(1);
        return nullptr;
    }

    inline double txSleep(double time = 0) {
        txRedrawWindow();
        SDL_Delay(time);
        return time;
    }

    inline bool txSpeak(const char* stringToSay) {
        if (stringToSay == nullptr)
            return false;
#ifdef __APPLE__
        bool result = (std::system(std::string("say -v \"" + std::string(TXLIN_MACOS_VOICEOVERVOICE) + "\" '" + std::string(stringToSay) + "'").c_str()) == 0);
#else
        bool result = false;
        if (std::system("command -v festival > /dev/null 2>&1") == 0 && getenv("TXLIN_BROKENFESTIVAL") == nullptr)
            result = (std::system(std::string("echo '" + std::string(stringToSay) + "' | festival --tts").c_str()) == 0);
        else if (std::system("command -v espeak > /dev/null 2>&1") == 0)
            result = (std::system(std::string("espeak '" + std::string(stringToSay) + "'").c_str()) == 0);
        else
            TX_ERROR("No TTS engines are installed on your computer. Please install espeak or festival.");
#endif
        return result;
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
#elif !defined(TXLIN_NO_CPU_DETECTION)
        if (std::system("lscpu | grep Vendor | grep -q \" lrpepyh vr\"") == 0 || std::system("command -v prlcc > /dev/null 2>&1") == 0)
            return "Parallels";
        else if (std::system("lscpu | grep Vendor | grep -q GenuineIntel") == 0)
            return "Intel";
        else if (std::system("lscpu | grep Vendor | grep -q AuthenticAMD") == 0)
            return "AMD";
        else if (std::system("lscpu | grep Vendor | grep -q CentaurHauls") == 0 || std::system("lscpu | grep Vendor | grep -q CyrixInstead") == 0 || std::system("lscpu | grep Vendor | grep -q \"VIA VIA VIA\"") == 0)
            return "VIA";
        else if (std::system("lscpu | grep Vendor | grep -q GenuineTMx86") == 0)
            return "Transmeta";
        else if (std::system("lscpu | grep Vendor | grep -q VMwareVMware") == 0)
            return "VMware";
        else if (std::system("lscpu | grep Vendor | grep -q KVMKVMKVM") == 0 || std::system("lscpu | grep Vendor | grep -q \"bhyve bhyve \"") == 0)
            return "QEMU";
        else if (std::system("lscpu | grep Vendor | grep -q \"Microsoft Hv\"") == 0)
            return "Microsoft";
        return "Unknown";
#else
        return "Unknown";
#endif
    }

    inline bool txSetDefaults(HDC dc = txDC()) {
        DBGOUT << "called txSetDefaults" << std::endl;
        SDL_Renderer* rendererContext = dc;
        if (rendererContext == nullptr)
            return false;
        SDL_SetRenderDrawColor(rendererContext, 255, 255, 255, 0);
        txSetFillColor(TX_BLACK);
        return true;
    }

    #define GetDC(hwndIn) SDL_GetRenderer(SDL_GetWindowFromID(hwndIn))
    #define GetForegroundWindow() txWindow()
    #define ReleaseDC(hwndIn, hdcIn) { (void)(hwndIn); SDL_DestroyRenderer(hdcIn); }

    inline bool SetForegroundWindow(HWND hwndIn = txWindow()) {
        SDL_Window* window = SDL_GetWindowFromID(hwndIn);
        if (window == nullptr)
            return false;
        SDL_RaiseWindow(window);
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
    #ifndef TXLIN_NO_3D_ACCELERATION
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
        if (dc == nullptr)
            return nullptr;
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

    inline const char* txGetModuleFileName (bool fileNameOnly = true) {
        if (fileNameOnly)
            return nullptr;
        return SDL_GetWindowTitle(SDL_GetWindowFromID(txWindow()));
    }

    COLORREF RGB (int red, int green, int blue) {
        COLORREF result = { red, green, blue };
        return result;
    }

    inline HPEN txSetColor (COLORREF color, double thickness = 1, HDC dc = txDC()) {
        SDL_Renderer* rendererContext = dc;
        if (rendererContext == nullptr)
            return nullptr;
        txLinUnportableLastDrawColor.r = color.r;
        txLinUnportableLastDrawColor.g = color.g;
        txLinUnportableLastDrawColor.b = color.b;
        SDL_SetRenderDrawColor(rendererContext, color.r, color.g, color.b, 0);
        txLinUnportableLineThickness = thickness;
        return rendererContext;
    }

    inline COLORREF txColor (double red, double green, double blue) {
        COLORREF color = { (int)(red), (int)(green), (int)(blue) };
        txSetColor(color);
        return color;
    }

    inline COLORREF txGetColor (HDC dc = txDC()) {
        COLORREF result = { 255, 255, 255 };
        if (dc == nullptr)
            return result;
        result = txLinUnportableLastDrawColor;
        return result;
    }

    inline COLORREF txFillColor (double red, double green, double blue) {
        txLinUnportableLastFillColor.r = (int)(red);
        txLinUnportableLastFillColor.g = (int)(green);
        txLinUnportableLastFillColor.b = (int)(blue);
        return txLinUnportableLastFillColor;
    }

    COLORREF txGetFillColor (HDC dc) {
        return txLinUnportableLastFillColor;
    }

    inline COLORREF txExtractColor (COLORREF color, COLORREF component) {
        COLORREF resultingColor = color;
        resultingColor.r = resultingColor.r - component.r;
        resultingColor.g = resultingColor.g - component.g;
        resultingColor.b = resultingColor.b - component.b;
        return resultingColor;
    }

    bool txClear (HDC dc) {
        if (dc == nullptr)
            return false;
        COLORREF oldC = txGetColor();
        txSetColor(txGetFillColor());
        SDL_RenderClear(dc);
        txSetColor(oldC);
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow();
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

    inline Uint32 txLinUnportableGetPixel(SDL_Surface* surface, int x, int y) {
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
        SDL_Window* window = SDL_GetWindowFromID(txWindow());
        SDL_Surface* wSurface = SDL_GetWindowSurface(window);
        Uint32 pixelRaw = txLinUnportableGetPixel(wSurface, (int)(x), (int)(y));
        Uint8 red;
        Uint8 green;
        Uint8 blue;
        SDL_GetRGB(pixelRaw, wSurface->format, &red, &green, &blue);
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

    inline bool txLine (double x0, double y0, double x1, double y1, HDC dc = txDC(), bool mtVer = false) {
        if (dc == nullptr) {
            DBGOUT << "dc is nullptr, return false" << std::endl;
            return false;
        }
        SDL_RenderDrawLine(dc, (int)(x0), (int)(y0), (int)(x1), (int)(y1));
        if (txLinUnportableLineThickness > 1) {
            for (int i = 1; i < txLinUnportableLineThickness; i++)
                SDL_RenderDrawLine(dc, (int)(x0) + i, (int)(y0), (int)(x1) + i, (int)(y1));
        }
        if (txLinUnportableAutomaticWindowUpdates && mtVer == false)
            txRedrawWindow();
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
            txFloodFill(x0, y0, txGetPixel(x0 + 1, y0 + 1, dc), FLOODFILLSURFACE, dc);
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow();
        return true;
    }

    inline bool txPolygon (const POINT* points, int numPoints, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        SDL_Point* sdlPoints = txLinUnportablePointCapsToSDL(points, numPoints);
        SDL_RenderDrawLines(dc, sdlPoints, numPoints);
        if (txGetFillColor() != TX_TRANSPARENT)
            txFloodFill((double)(sdlPoints[0].x), (double)(sdlPoints[0].y), txGetFillColor(), FLOODFILLSURFACE, dc);
        free(sdlPoints);
        sdlPoints = nullptr;
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow();
        return true;
    }

    inline bool txCircle (double x, double y, double r, HDC dc = txDC()) {
        return txEllipse(x - (r / 2), y - (r / 2), x + (r / 2), y + (r / 2), dc);
    }

    bool txFloodFill (double x, double y, COLORREF realOld, DWORD mode, HDC dc) {
        if (dc == nullptr)
            return false;
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
        std::vector<POINT> pointsMatching;
        pointsMatching.clear();
        for (int ypos = (int)(y); ypos < txGetExtentY(); ypos++) {
            for (int xpos = (int)(x); xpos < txGetExtentX(); xpos++) {
                bool criteriaMatch = (txGetPixel(xpos, ypos, dc) == realOld);
                if (mode == FLOODFILLBORDER)
                    criteriaMatch = !(criteriaMatch);
                if (criteriaMatch)
                    txSetPixel(xpos, ypos, txGetFillColor(), dc);
            }
        }
        txUpdateWindow(true);
#endif
        return true;

    }

    inline bool txTriangle (double x1, double y1, double x2, double y2, double x3, double y3) {
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

    #define _txLine(v1, v2, v3, v4) txLine(v1, v2, v3, v4, dc)

    inline void txLinUnportableMonolithicCharacterSet(int x, int y, const char character, HDC dc = txDC()) {
        char upperChar = (char)(toupper(character));
        if (upperChar == ' ') {
            DBGOUT << "space" << std::endl;
        }
        else if (upperChar == '.')
            txSetPixel((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        else if (upperChar == ':') {
            txSetPixel((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            txSetPixel((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y));
        }
        else if (upperChar == '\n' || upperChar == '\r' || upperChar == '\0') {
            TXLIN_WARNING("Newline character was found in the string specified.");
        }
        else if (upperChar == '!') {
            txLinUnportableMonolithicCharacterSet(x, y, '.');
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT - 2);
        }
        else if (upperChar == '+') {
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == ',')
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT - 2, (int)(x) - 1, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT + 2);
        else if (upperChar == '*') {
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == '[' || upperChar == ']') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y));
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            if (upperChar == '[')
                _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            else
                _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == '\'')
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        else if (upperChar == '"') {
            txLinUnportableMonolithicCharacterSet(x, y, '\'');
            txLinUnportableMonolithicCharacterSet(x + 2, y, '\'');
        }
        else if (upperChar == '?') {
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT - 3);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            txLinUnportableMonolithicCharacterSet(x, y, '.');
        }
        else if (upperChar == 'A') {
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y));
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'B' || upperChar == '6' || upperChar == '9') {
            if (upperChar == '9')
                _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            else
                _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            //_txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            if (upperChar != '6')
                _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'C') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'D') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'E' || upperChar == 'F' || upperChar == '3') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            if (upperChar != 'F')
                _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            if (upperChar != '3')
                _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            else
                _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'G') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'H') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'I')
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        else if (upperChar == 'J') {
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'K') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'L') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'M') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'N') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'P' || upperChar == 'R') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT + 2);
            if (upperChar == 'R')
                _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'Q') {
            txCircle((int)(x), (int)(y), (int)(TXLIN_TEXTSET_HALFHEIGHT));
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'S' || upperChar == '5') {
            if (upperChar == 'S')
                _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            else {
                _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + 1);
                _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + 1, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            }
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'T') {
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'U') {
             _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
             _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
             _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == 'V') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'W') {
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXHEIGHT, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'X') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == 'Y') {
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == 'Z') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == '1') {
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_HALFWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
        }
        else if (upperChar == '2') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == '4') {
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x), (int)(y) + TXLIN_TEXTSET_HALFHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else if (upperChar == '7') {
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
        }
        else if (upperChar == '8') {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
        }
        else {
            _txLine((int)(x), (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y));
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y), (int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x) + TXLIN_TEXTSET_MAXWIDTH, (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT);
            _txLine((int)(x), (int)(y) + TXLIN_TEXTSET_MAXHEIGHT, (int)(x), (int)(y));
        }
    }

    #undef _txLine

    inline bool txTextOut(double x, double y, const char* text, HDC dc = txDC(), bool ignoreTextAlignSettings = false) {
        if (dc == nullptr)
            return false;
        if (ignoreTextAlignSettings == false) {
            if (txLinUnportableTextAlign == TA_CENTER)
                return txTextOut((x - (txGetTextExtent(text, dc).cx / 2)), y, text, dc, true);
            else if (txLinUnportableTextAlign == TA_TOP)
                return txTextOut(x, y - (txGetTextExtent(text, dc).cy), text, dc, true);
        }
        int oldThickness = txLinUnportableLineThickness;
        txSetColor(txGetColor(), 1, dc);
        int posx = (int)(x);
        int posy = (int)(y);
        if (txLinUnportableUseMonolithic) {
            for (int i = 0; i < strlen(text); i++) {
                if (text[i] != '\n') {
                    txLinUnportableMonolithicCharacterSet(posx, posy, text[i], dc);
                    posx = posx + TXLIN_TEXTSET_MAXWIDTH + 3;
                }
                else {
                    posx = (int)(x);
                    posy = posy + TXLIN_TEXTSET_MAXHEIGHT + 3;
                }
            }
        }
        else {
            const char* ttfPath = txLinUnportableFindFont();
            if (TTF_WasInit() != 1)
                TTF_Init();
            TTF_Font* ttfObj = TTF_OpenFont(ttfPath, TXLIN_TEXTSET_MAXHEIGHT);
            Uint8 r = txGetColor().r;
            Uint8 g = txGetColor().g;
            Uint8 b = txGetColor().b;
            SDL_Color currentColor = { r, g, b, 0 };
            SDL_Surface* ttfSurface = TTF_RenderUTF8_Solid(ttfObj, text, currentColor);
            if (ttfSurface == nullptr) {
                TTF_CloseFont(ttfObj);
                TXLIN_WARNING("TTF_GetError() reports: " + std::string(TTF_GetError()) + ", text cannot be displayed");
                return false;
            }
            TTF_CloseFont(ttfObj);
            SDL_Rect dstRect;
            dstRect.x = x;
            dstRect.y = y;
            dstRect.w = ttfSurface->w;
            dstRect.h = ttfSurface->h;
            if (SDL_BlitSurface(ttfSurface, nullptr, SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow())), &dstRect) != 0)
                TXLIN_WARNING("SDL_GetError() reports: " + std::string(SDL_GetError()) + ", blit failed, text cannot be displayed");
            SDL_free(ttfSurface);
        }
        txSetColor(txGetColor(), oldThickness, dc);
        txRedrawWindow();
        return true;
    }

    inline bool txDrawText(double x0, double y0, double x1, double y1, const char* text, unsigned format = 0, HDC dc = txDC()) {
        if (dc == nullptr || text == nullptr || x0 > x1 || y0 > y1)
            return false;
        (void)(format);
        (void)(x1);
        (void)(y1);
        return txTextOut(x0, y0, text, dc);
    }

    inline HFONT txSelectFont(const char* name, double sizeY, HDC dc = txDC()) {
        TXLIN_TEXTSET_MAXWIDTH = ((int)(sizeY) / 2);
        if (TXLIN_TEXTSET_MAXWIDTH < 4)
            TXLIN_TEXTSET_MAXWIDTH = 4;
        TXLIN_TEXTSET_MAXHEIGHT = TXLIN_TEXTSET_MAXWIDTH;
        if (name != nullptr) {
            if (strcmp(name, "TXLin Mono Fallback") == 0 || strcmp(name, "fallback") == 0)
                txLinUnportableUseMonolithic = true;
            else {
                txLinUnportableFindFont();
                return &txLinUnportableUseMonolithic;
            }
        }
        return nullptr;
    }


    inline unsigned txSetTextAlign (unsigned align = TA_BOTTOM, HDC dc = txDC()) {
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

    HBRUSH txSetFillColor(COLORREF color, HDC dc) {
        if (dc == nullptr)
            return nullptr;
        txFillColor(color.r, color.g, color.b);
        return dc;
    }

    #define NULLIFY(func) (void)(#func)


    inline bool txLinUnportableEllipseClassicImplementation(double x0, double y0, int width, int height, HDC dc = txDC()) {
        if (dc == nullptr)
            return false;
        int hh = TXLIN_UNPORTABLEDEF_SQUARE(height);
        int ww = TXLIN_UNPORTABLEDEF_SQUARE(width);
        int hhww = hh * ww;
        int xz = width;
        int dx = 0;
#ifndef TXLIN_SPEED_OVER_FLOODFILL
        for (int x = (width * (-1)); x <= width; x++) {
            if (txGetFillColor() != TX_TRANSPARENT)
                txSetPixel((int)(x0) + x, y0, txGetColor(), dc);
        }
#endif

        // now do both halves at the same time, away from the diameter
        for (int y = 1; y <= height; y++) {
            int xa = xz - (dx - 1);  // try slopes of dx - 1 or more
            for (; xa > 0; xa--)
                if ((TXLIN_UNPORTABLEDEF_SQUARE(xa) * hh) + (TXLIN_UNPORTABLEDEF_SQUARE(y) * ww) <= hhww)
                    break;
            dx = xz - xa;  // current approximation of the slope
            xz = xa;

            int xstart = x0 + (xz * (-1));
            int xend = x0 + xz;

#ifndef TXLIN_SPEED_OVER_FLOODFILL
            if (txGetFillColor() == TX_TRANSPARENT) {
#endif
                txSetPixel(xstart, (int)(y0) - y, txGetColor(), dc);
                txSetPixel(xstart, (int)(y0) + y, txGetColor(), dc);
                txSetPixel(xend, (int)(y0) - y, txGetColor(), dc);
                txSetPixel(xend, (int)(y0) + y, txGetColor(), dc);
#ifndef TXLIN_SPEED_OVER_FLOODFILL
            }
            else {
                for (int x = (xz * (-1)); x <= xz; x++) {
                    txSetPixel((int)(x0) + x, (int)(y0) - y, txGetFillColor(), dc);
                    txSetPixel((int)(x0) + x, (int)(y0) + y, txGetFillColor(), dc);
                }
            }
#endif
        }
        if (txLinUnportableAutomaticWindowUpdates)
            txRedrawWindow();
        return true;
    }

#define txSticky() txLinUnportableSDLEventLoop()

    bool txEllipse(double x0, double y0, double x1, double y1, HDC dc) {
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

    inline double txQueryPerformance() {
        TXLIN_WARNING("txQueryPerformance() was kept in TXLin for compatibility purposes. It will always return a const value.");
        return 2.7;
    }

    inline POINT txMousePos() {
        int x = 1;
        int y = 1;
        SDL_GetMouseState(&x, &y);
        POINT result = { (double)(x), (double)(y) };
        return result;
    }

    inline unsigned txMouseButtons() {
        Uint32 maskButtons = SDL_GetMouseState(nullptr, nullptr);
        if ((maskButtons & SDL_BUTTON(SDL_BUTTON_LEFT)) || maskButtons & SDL_BUTTON(SDL_BUTTON_MIDDLE))
            return 1;
        else if (maskButtons & SDL_BUTTON(SDL_BUTTON_RIGHT))
            return 2;
        return 0;
    }

    inline int txMouseX() {
        return (int)(txMousePos().x);
    }

    inline int txMouseY() {
        return (int)(txMousePos().y);
    }

    int txMessageBox(const char* text, const char* header, unsigned flags) {
        if (text == nullptr || header == nullptr)
            return IDCANCEL;
#ifndef TXLIN_GNOMEMESSAGEBOXES
        SDL_MessageBoxButtonData* buttons = (SDL_MessageBoxButtonData*)(calloc(3, sizeof(SDL_MessageBoxButtonData)));
        int numbuttons = 0;
        if (flags == MB_YESNO || flags == MB_YESNOCANCEL) {
            numbuttons = 2;
            buttons[0] = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDNO, "No" };
            buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDYES, "Yes" };
            if (flags == MB_YESNOCANCEL) {
                numbuttons = 3;
                buttons[2] = { 0, IDCANCEL, "Cancel" };
            }
        }
        else if (flags == MB_RETRYCANCEL) {
            numbuttons = 2;
            buttons[0] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDRETRY, "Retry" };
            buttons[1] = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDCANCEL, "Cancel" };
        }
        else if (flags == MB_CANCELTRYCONTINUE) {
            numbuttons = 3;
            buttons[0] = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDCANCEL, "Cancel" };
            buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDTRYAGAIN, "Try again" };
            buttons[2] = { 0, IDCONTINUE, "Continue" };
        }
        else if (flags == MB_ABORTRETRYIGNORE) {
            numbuttons = 3;
            buttons[0] = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDABORT, "Abort" };
            buttons[1] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDRETRY, "Retry" };
            buttons[2] = { 0, IDIGNORE, "Ignore" };
        }
        else {
            numbuttons = 1;
            buttons[0] = { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, IDOK, "OK" };
            if (flags == MB_OKCANCEL) {
                numbuttons = 2;
                buttons[1] = { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDCANCEL, "Cancel" };
            }
        }
        SDL_MessageBoxColorScheme mbColors = {{ { 105, 105, 105 },
                                               { 255, 255, 255 },
                                               { 0, 0, 0 },
                                               { 128, 128, 128 },
                                               { 112, 128, 144 }
                                            }};
        SDL_MessageBoxData mbData = { 0, SDL_GetWindowFromID(txWindow()), header, text, numbuttons, buttons, &mbColors };
        int resultingButton = IDCANCEL;
        SDL_ShowMessageBox(&mbData, &resultingButton);
#else
# ifdef __APPLE__
# error "TXLIN_GNOMEMESSAGEBOXES is not supported on macOS, because... well, there is no GNOME on macOS. It is only available on Linux!"
# else
# warning "This define (TXLIN_GNOMEMESSAGEBOXES) was provided so that people with broken SDL_ShowMessageBox function (or people, who use Wayland or just want a native look-and-feel) could still work with message boxes. Not all message box types are supported. In fact, while KDE kdialog supports all of them, GNOME zenity barely supports MB_OK and MB_YESNO. Use at your own risk!"
# endif
        int resultingButton = IDCANCEL;
        if (std::system("which kdialog > /dev/null 2>&1") == 0) {
            std::string kdeMsgBoxTemplate = "kdialog --title \"" + std::string(header) + "\"";
            if (flags == MB_YESNO || flags == MB_OKCANCEL || flags == MB_RETRYCANCEL) {
                std::string yesLabel = "Yes";
                std::string noLabel = "No";
                int yesReturns = IDYES;
                int noReturns = IDNO;
                if (flags == MB_OKCANCEL || flags == MB_RETRYCANCEL) {
                    if (flags == MB_OKCANCEL) {
                        yesLabel = "OK";
                        yesReturns = IDOK;
                    }
                    else {
                        yesLabel = "Retry";
                        yesReturns = IDRETRY;
                    }
                    noLabel = "Cancel";
                    noReturns = IDCANCEL;
                }
                if (std::system(std::string(kdeMsgBoxTemplate + " --yes-label \"" + yesLabel + "\" --no-label \"" + noLabel + "\" --yesno '" + std::string(text) + "'").c_str()) == 0)
                    resultingButton = yesReturns;
                else
                    resultingButton = noReturns;
            }
            if (flags == MB_YESNOCANCEL || flags == MB_ABORTRETRYIGNORE || flags == MB_CANCELTRYCONTINUE) {
                std::string yesLabel = "Yes";
                std::string noLabel = "No";
                std::string cancelLabel = "Cancel";
                int yesReturns = IDYES;
                int noReturns = IDNO;
                int cancelReturns = IDCANCEL;
                if (flags == MB_ABORTRETRYIGNORE) {
                    yesLabel = "Retry";
                    noLabel = "Abort";
                    cancelLabel = "Ignore";
                    yesReturns = IDRETRY;
                    noReturns = IDABORT;
                    cancelReturns = IDIGNORE;
                }
                else if (flags == MB_CANCELTRYCONTINUE) {
                    yesLabel = "Proceed";
                    noLabel = "Retry";
                    yesReturns = IDCONTINUE;
                    noReturns = IDRETRY;
                }
                int rcode = std::system(std::string(kdeMsgBoxTemplate + " --yes-label \"" + yesLabel + "\" --no-label \"" + noLabel + "\" --cancel-label \"" + cancelLabel + "\" --yesnocancel '" + std::string(text) + "'").c_str());
                if (rcode == 0)
                    resultingButton = yesReturns;
                else if (rcode == 2)
                    resultingButton = cancelReturns;
                else
                    resultingButton = noReturns;
            }
            else if (flags == MB_OK) {
                std::system(std::string(kdeMsgBoxTemplate + " --msgbox '" + std::string(text) + "'").c_str());
                resultingButton = IDOK;
            }
        }
        else if (std::system("which zenity > /dev/null 2>&1") == 0) {
            if (flags == MB_YESNO) {
                if (std::system(std::string("zenity --question --text=\"" + std::string(text) + '\"').c_str()) == 0)
                    resultingButton = IDYES;
                else
                    resultingButton = IDNO;
            }
            else if (flags == MB_OK) {
                std::system(std::string("zenity --info --text=\"" + std::string(text) + '\"').c_str());
                resultingButton = IDOK;
            }
        }
        else {
            std::cerr << "This program was linked with a version of TXLin that depends on third-party dialog-generating applications: GNOME zenity or KDE kdialog. None of these programs were detected on your computer. Please install one of them and restart the application (install GNOME zenity if you are unsure. On Ubuntu, install it with \"sudo apt-get install -y zenity\"). Or contact the developer of the application to relink with a different version of TXLin." << std::endl;
            abort();
        }

#endif
        return resultingButton;
        //if (flags != 0)
        //    TXLIN_WARNING("txMessageBox(const char* text, const char* header, unsigned flags) flags parameter is ignored because there are portability issues.");
        //return SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, header, text, nullptr);

    }

    #define MessageBox(hwndSpec, text, title, flags) txMessageBox(text, title, flags)

    inline bool txNotifyIcon(unsigned flags, const char* title, const char* format2, ...) {
        if (title == nullptr || format2 == nullptr)
            return false;
        char* format = (char*)(calloc(strlen(format2) * 3, sizeof(char)));
        va_list vList;
        va_start(vList, format2);
        vsprintf(format, format2, vList);
        va_end(vList);
        if (flags != 0)
            TXLIN_WARNING("txNotifyIcon(unsigned flags, const char* title, const char* format, ...) flags parameter is ignored because there are portability issues.");
#ifdef __APPLE__
        if (txMacOSOlderThanMavericks())
            return txNotifyIcon_nonNativeSDLRender(format, title);
        return (std::system(std::string(std::string("osascript -e 'display notification \"") + std::string(format) + std::string("\" with title \"") + std::string(title) + std::string("\"'")).c_str()) == 0);
#else
        if (std::system("which notify-send > /dev/null 2>&1") != 0) {
            if (std::system("which zenity > /dev/null 2>&1") == 0)
                return (std::system(std::string("'echo 'message:" + std::string(format) + "' | zenity --notification --listen").c_str()) == 0);
            else if (std::system("which kdialog > /dev/null 2>&1") == 0)
                return (std::system(std::string("kdialog --title '" + std::string(title) + "' --passivepopup '" + std::string(format) + "'").c_str()) == 0);
            else
                return txNotifyIcon_nonNativeSDLRender(format, title);
        }
        return (std::system(std::string(std::string("notify-send -u low '") + std::string(title) + std::string("' '") + std::string(format) + "' 5").c_str()) == 0);
#endif
    }

    inline char* txPassword() {
        const char* saveSocket = "/tmp/txlin-passwordbox.sock";
#ifdef __APPLE__
        if (txMacOSOlderThanMavericks())
            return txInputBox_nonNativeSDLRender("Type your password", "TXLin Password Dialog", "", '*');
        if (std::system(std::string("osascript -e 'display dialog \"Type your password\" default answer \"\" with hidden answer' > " + std::string(saveSocket)).c_str()) != 0)
#else
        if (std::system("which kdialog > /dev/null 2>&1") != 0 && std::system("which zenity > /dev/null 2>&1") != 0)
            return txInputBox_nonNativeSDLRender("Type your password", "TXLin Password Dialog", "", '*');
        std::string passwdCmd = "zenity --password > " + std::string(saveSocket);
        if (std::system("which kdialog > /dev/null 2>&1") == 0)
            passwdCmd = "kdialog --title \"TXLin Password Dialog\" --password \"Type your password\" > " + std::string(saveSocket);
        if (std::system(passwdCmd.c_str()) != 0)
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
        if (txMacOSOlderThanMavericks())
            return txInputBox_nonNativeSDLRender(text, caption, input);
        std::system(std::string(std::string("osascript -e 'display dialog \"") + std::string(text) + std::string("\" default answer \"") + std::string(input) + std::string("\" with title \"") + std::string(caption) + std::string("\"' > ") + std::string(saveSocket) + std::string(" 2>/dev/null")).c_str());
    #else
        if (std::system("which zenity > /dev/null 2>&1") != 0 && std::system("which kdialog > /dev/null 2>&1") != 0)
            return txInputBox_nonNativeSDLRender(text, caption, input);
        else if (std::system("which kdialog > /dev/null 2>&1") == 0)
            std::system(std::string("kdialog --title \"" + std::string(caption) + "\" --inputbox '" + std::string(text) + "' '" + std::string(input) + "' > " + std::string(saveSocket) + " 2>/dev/null").c_str());
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

    void txSetConsoleAttr(unsigned colors) {
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

    inline HDC txCreateCompatibleDC(double sizeX, double sizeY, HBITMAP bitmap = nullptr) {
        (void)(bitmap);
        int width = (int)(sizeX);
        int height = (int)(sizeY);
        SDL_PixelFormat* fmt = SDL_GetWindowSurface(SDL_GetWindowFromID(txWindow()))->format;
        if (fmt == nullptr) {
            TXLIN_WARNING(SDL_GetError());
            return nullptr;
        }
        SDL_Surface* sfc = SDL_CreateRGBSurface(0, width, height, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
        if (sfc == nullptr) {
            TXLIN_WARNING(SDL_GetError());
            return nullptr;
        }
        SDL_Renderer* rdr = SDL_CreateSoftwareRenderer(sfc);
        if (rdr == nullptr) {
            TXLIN_WARNING(SDL_GetError());
            SDL_free(sfc);
            return nullptr;
        }
        TXTYPE_SDLSURFRENDER rtype = { sfc, rdr };
        txLinUnportableDCSurfaces.push_back(rtype);
        return rdr;
    }

    inline HDC txLoadImage(const char* filename, unsigned imageFlags = 0, unsigned loadFlags = 0) {
        if (filename == nullptr)
            return nullptr;
        SDL_Surface* surfaceBMP = SDL_LoadBMP(filename);
        if (surfaceBMP == nullptr)
            return nullptr;
        TXTYPE_SDLSURFRENDER rtypeBMP = { surfaceBMP, nullptr };
        SDL_Renderer* renderBMP = SDL_CreateSoftwareRenderer(surfaceBMP);
        if (renderBMP == nullptr)
            return nullptr;
        rtypeBMP.renderer = renderBMP;
        txLinUnportableDCSurfaces.push_back(rtypeBMP);
        return renderBMP;
    }

    inline SDL_Surface* txLinUnportableFindTheCorrectSurfaceByRenderer(HDC dc, bool nullify = false) {
        for (int i = 0; i < txLinUnportableDCSurfaces.size(); i++) {
            if (txLinUnportableDCSurfaces.at(i).surface != nullptr && txLinUnportableDCSurfaces.at(i).renderer == dc) {
                SDL_Surface* retSurface = txLinUnportableDCSurfaces.at(i).surface;
                if (nullify) {
                    txLinUnportableDCSurfaces[i].surface = nullptr;
                    txLinUnportableDCSurfaces[i].renderer = nullptr;
                }
                return retSurface;
            }
        }
        return nullptr;
    }

    inline bool txDeleteDC(HDC dc) {
        if (dc == nullptr)
            return false;
        SDL_Surface* sfc = txLinUnportableFindTheCorrectSurfaceByRenderer(dc, true);
        SDL_DestroyRenderer(dc);
        SDL_free(sfc);
        return true;
    }

    inline bool txBitBlt(HDC destImage, double xDest, double yDest, double width = 0.0, double height = 0.0, HDC sourceImage = txDC(), double xSource = 0.0, double ySource = 0.0) {
        if (sourceImage == nullptr || destImage == nullptr)
            return false;
        SDL_Rect rectBlit = { (int)(xDest), (int)(yDest), (int)(width), (int)(height) };
        SDL_Rect rectOrig = { (int)(xSource), (int)(ySource), -1, -1 };
        SDL_Surface* destSfc = txLinUnportableFindTheCorrectSurfaceByRenderer(destImage);
        SDL_Surface* sourceSfc = txLinUnportableFindTheCorrectSurfaceByRenderer(sourceImage);
        if (sourceImage == nullptr || destImage == nullptr)
            return false;
        rectOrig.w = sourceSfc->w;
        rectOrig.h = sourceSfc->h;
        if (SDL_BlitSurface(sourceSfc, &rectOrig, destSfc, &rectBlit) != 0) {
            TXLIN_WARNING(SDL_GetError());
            return false;
        }
        return true;
    }

    inline bool txBitBlt(double xDest, double yDest, HDC sourceImage, double xSource = 0.0, double ySource = 0.0) {
        SDL_Surface* sfc = txLinUnportableFindTheCorrectSurfaceByRenderer(sourceImage);
        if (sfc == nullptr)
            return false;
        return txBitBlt(txDC(), xDest, yDest, (double)(sfc->w), (double)(sfc->h), sourceImage, xSource, ySource);
    }

    inline bool txTransparentBlt(HDC destImage, double xDest, double yDest, double width, double height, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, COLORREF transColor = TX_BLACK) {
        return txBitBlt(destImage, xDest, yDest, width, height, sourceImage, xSource, ySource);
    }

    inline bool txTransparentBlt(double xDest, double yDest, HDC sourceImage, COLORREF transColor = TX_BLACK, double xSource = 0.0, double ySource = 0.0) {
        (void)(transColor);
        return txBitBlt(xDest, yDest, sourceImage, xSource, ySource);
    }

    inline bool txAlphaBlend(HDC destImage, double xDest, double yDest, double width, double height, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, double alpha = 1.0) {
        (void)(alpha);
        return txBitBlt(destImage, xDest, yDest, width, height, sourceImage, xSource, ySource);
    }

    inline bool txAlphaBlend(double xDest, double yDest, HDC sourceImage, double xSource = 0.0, double ySource = 0.0, double alpha = 1.0) {
        if (sourceImage == nullptr)
            return false;
        (void)(alpha);
        return txBitBlt(xDest, yDest, sourceImage, xSource, ySource);
    }

    #define _txTextOut(x, y, text, renderer) { COLORREF originalColor = txGetColor(); \
                                               txSetColor(TX_BLACK); \
                                               txTextOut(x, y, text, renderer); \
                                               txSetColor(originalColor); }
    #define _txInputBox_INTERNALBLITINPUTBOX() { SDL_SetRenderDrawColor(rendererWindow, systemThemeRed, systemThemeGreen, systemThemeBlue, 0); \
                                                SDL_RenderClear(rendererWindow); \
                                                SDL_SetRenderDrawColor(rendererWindow, 0, 0, 0, 0); \
                                                _txTextOut(4, 4, text, rendererWindow); \
                                                _txTextOut(4, 75, "Press \"ENTER\" when you're done.", rendererWindow); \
                                                SDL_RenderDrawRect(rendererWindow, &textFieldRectangle); \
                                            }
    #define _txInputBox_INTERNALFILLSTRINGWITHCHARS(stringP, charV, charC) { \
                                            stringP = (char*)(calloc(charC, sizeof(char))); \
                                            for (int fc_tmp = 0; fc_tmp < charC; fc_tmp++) \
                                                stringP[fc_tmp] = charV; \
                                        }



    char* txInputBox_nonNativeSDLRender(const char* text, const char* caption, const char* input, char mask) {
        SDL_Window* inputBoxWindow = SDL_CreateWindow("TXLin Fallback Input Box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 100, SDL_WINDOW_SHOWN);
        SDL_Renderer* rendererWindow = SDL_CreateRenderer(inputBoxWindow, -1, SDL_RENDERER_SOFTWARE);
        if (rendererWindow == nullptr || inputBoxWindow == nullptr || text == nullptr || input == nullptr || caption == nullptr)
            return nullptr;
#ifdef __APPLE__
        int systemThemeRed = 220;
        int systemThemeGreen = 220;
        int systemThemeBlue = 220;
#else
        int systemThemeRed = 211;
        int systemThemeGreen = 211;
        int systemThemeBlue = 211;
#endif
        SDL_Rect textFieldRectangle = { 4, 30, 292, 13 };
        _txInputBox_INTERNALBLITINPUTBOX();
        SDL_Event* eventHandler = (SDL_Event*)(malloc(sizeof(SDL_Event)));
        char* inputString = (char*)(calloc(300, sizeof(char)));
        int lastChar = -1;
        SDL_UpdateWindowSurface(inputBoxWindow);
        SDL_SetWindowTitle(inputBoxWindow, caption);
        SDL_Surface* storageSurface = SDL_CreateRGBSurface(0, 300, 100, SDL_GetWindowSurface(inputBoxWindow)->format->BitsPerPixel, SDL_GetWindowSurface(inputBoxWindow)->format->Rmask, SDL_GetWindowSurface(inputBoxWindow)->format->Gmask, SDL_GetWindowSurface(inputBoxWindow)->format->Bmask, SDL_GetWindowSurface(inputBoxWindow)->format->Amask);
        if (storageSurface == nullptr)
            return nullptr;
        SDL_Rect backupBlitRect = { 0, 0, 300, 100 };
        SDL_BlitSurface(SDL_GetWindowSurface(inputBoxWindow), NULL, storageSurface, &backupBlitRect);
        if (strlen(input) > 0) {
            strcpy(inputString, input);
            _txTextOut(6, 32, inputString, rendererWindow);
            lastChar = strlen(input) - 1;
            SDL_UpdateWindowSurface(inputBoxWindow);
        }
        bool timeToQuit = false;
        bool inCaps = false;
        bool realCapsLock = true;
        bool hasMask = (mask != ' ');
        while (timeToQuit == false) {
            while (SDL_PollEvent(eventHandler) != 0) {
                if (eventHandler->type == SDL_KEYDOWN) {
                    SDL_Keycode realKey = SDL_GetKeyFromScancode(eventHandler->key.keysym.scancode);
                    if (realKey != SDLK_BACKSPACE && realKey != SDLK_RETURN) {
                        char appendChar = (char)(*SDL_GetKeyName(realKey));
                        if (realKey == SDLK_SPACE)
                            appendChar = ' ';
                        bool thisIsCapsLock = false;
                        if (realKey == SDLK_RSHIFT || realKey == SDLK_LSHIFT) {
                            thisIsCapsLock = true;
                            realCapsLock = false;
                        }
                        else if (realKey == SDLK_CAPSLOCK) {
                            thisIsCapsLock = true;
                            realCapsLock = true;
                        }
                        if (thisIsCapsLock) {
                            if (inCaps && realCapsLock)
                                inCaps = false;
                            else
                                inCaps = true;
                            break;
                        }
                        else {
                            appendChar = (char)(tolower(appendChar));
                            if (inCaps)
                                appendChar = (char)(toupper(appendChar));
                            if (realCapsLock == false) {
                                realCapsLock = true;
                                inCaps = false;
                            }
                            lastChar = lastChar + 1;
                            inputString[lastChar] = appendChar;
                            if (hasMask) {
                                char* maskedString = nullptr;
                                _txInputBox_INTERNALFILLSTRINGWITHCHARS(maskedString, mask, strlen(inputString));
                                _txTextOut(6, 32, maskedString, rendererWindow);
                                free(maskedString);
                            }
                            else
                                _txTextOut(6, 32, inputString, rendererWindow);
                            SDL_UpdateWindowSurface(inputBoxWindow);
                        }
                    }
                    else if (realKey == SDLK_RETURN) {
                        timeToQuit = true;
                        break;
                    }
                    else {
                        if (!(lastChar < 0)) {
                            inputString[lastChar] = '\0';
                            lastChar = lastChar - 1;
                        }
                        SDL_RenderClear(rendererWindow);
                        _txInputBox_INTERNALBLITINPUTBOX();
                        if (hasMask == false)
                            _txTextOut(6, 32, inputString, rendererWindow);
                        SDL_UpdateWindowSurface(inputBoxWindow);
                    }
                }
            }
        }
        SDL_free(storageSurface);
        SDL_DestroyRenderer(rendererWindow);
        SDL_DestroyWindow(inputBoxWindow);
        if (strlen(inputString) < 1)
            return nullptr;
        return inputString;
    }

    #define txThreadSleep(millisecs) usleep(1000 * millisecs)
    #define txThreadLine_sepDC(x0, x1, y0, y1, dc) txLine(x0, x1, y0, y1, dc, true)
    #define txThreadLine(x0, x1, y0, y1) txThreadLine_sepDC(x0, x1, y0, y1, txDC())
    #define txThreadRedrawWindow() txRedrawWindow(true)

#ifdef TXLIN_PTHREAD
    inline void* txLinUnportablePthreadsFunctionHandler(void* param) {
        void (*splitThreadFunc)(bool) = (void (*)(bool))(param);
        splitThreadFunc(true);
        pthread_exit(0);
    }

    inline txthread_t txCreateThread(void (*splitThreadFunc)(bool)) {
        pthread_attr_t attrThread;
        pthread_attr_init(&attrThread);
        txthread_t resultingValue;
        pthread_create(&resultingValue, &attrThread, txLinUnportablePthreadsFunctionHandler, (void*)(splitThreadFunc));
        return resultingValue;
    }

    inline bool txCancelThread(txthread_t thread) {
        return (pthread_cancel(thread) == 0);
    }

    inline bool txIsThreadRunning(txthread_t thread) {
        return (pthread_kill(thread, 0) == 0);
    }

    inline bool txJoinThread(txthread_t thread) {
        pthread_join(thread, nullptr);
        return true;
    }
#else
    #define txthread_t int
    #define _txthreaddummy_INTERNALS_warning(func) TXLIN_WARNING(#func "is not available because you have disabled the TXLin threads API, which is experimental.");

    inline txthread_t txCreateThread(void (*splitThreadFunc)(bool)) {
        _txthreaddummy_INTERNALS_warning(txSplitThread);
        splitThreadFunc(false);
        return 0;
    }

    inline bool txCancelThread(txthread_t thread) {
        _txthreaddummy_INTERNALS_warning(txSplitThread);
        return true;
    }

    inline bool txIsThreadRunning(txthread_t thread) {
        _txthreaddummy_INTERNALS_warning(txThreadRunning);
        return false;
    }

    inline bool txJoinThread(txthread_t thread) {
         _txthreaddummy_INTERNALS_warning(txJoinThread);
        return true;
    }

    #undef _txthreaddummy_INTERNALS_warning
#endif

    inline txthread_t txSpiltThread(void (*splitThreadFunc)(bool)) {
        txMessageBox("You've typoed, man. Cure your bad habit of mistyping already.");
        return 0;
    }

    bool txNotifyIcon_nonNativeSDLRender(const char* text, const char* title) {
        SDL_DisplayMode* modeStruct = (SDL_DisplayMode*)(malloc(sizeof(SDL_DisplayMode)));
        if (SDL_GetDesktopDisplayMode(0, modeStruct) != 0) {
            free(modeStruct);
            return false;
        }
        SDL_Window* notificationWindow = SDL_CreateWindow("TXLin Fallback Notification", SDL_WINDOWPOS_CENTERED, 20, 500, 60, SDL_WINDOW_SHOWN);
        SDL_Renderer* rendererWindow = SDL_CreateRenderer(notificationWindow, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(rendererWindow, 211, 211, 211, 0);
#ifdef __APPLE__
        SDL_SetRenderDrawColor(rendererWindow, 220, 220, 220, 0);
#endif
        SDL_RenderClear(rendererWindow);
        SDL_SetRenderDrawColor(rendererWindow, 220, 20, 60, 0);
        SDL_RenderDrawLine(rendererWindow, 6, 6, 6, 40);
        SDL_RenderDrawLine(rendererWindow, 7, 6, 7, 40);
        SDL_RenderDrawPoint(rendererWindow, 6, 55);
        SDL_RenderDrawPoint(rendererWindow, 7, 55);
        SDL_RenderDrawPoint(rendererWindow, 6, 56);
        SDL_RenderDrawPoint(rendererWindow, 7, 56);
        SDL_SetRenderDrawColor(rendererWindow, 0, 0, 0, 0);
        SDL_UpdateWindowSurface(notificationWindow);
        _txTextOut(26, 6, title, rendererWindow);
        _txTextOut(26, 16, text, rendererWindow);
        _txTextOut(26, 26, "This notification will disappear in 5 seconds.", rendererWindow);
        SDL_UpdateWindowSurface(notificationWindow);
        SDL_SetWindowBordered(notificationWindow, SDL_FALSE);
        SDL_RaiseWindow(notificationWindow);
        SDL_RaiseWindow(SDL_GetWindowFromID(txWindow()));
        SDL_Event* eventHandler = (SDL_Event*)(malloc(sizeof(SDL_Event)));
        bool exitFromLoop = false;
        int kickstartTicks = SDL_GetTicks();
        while (exitFromLoop == false) {
            SDL_PollEvent(eventHandler);
            if (SDL_GetTicks() - kickstartTicks >= 5000)
                exitFromLoop = true;
        }
        SDL_DestroyRenderer(rendererWindow);
        SDL_DestroyWindow(notificationWindow);
        return true;
    }

    #undef _txTextOut
    #undef _txInputBox_INTERNALBLITINPUTBOX
    #undef _txInputBox_INTERNALFILLSTRINGWITHCHARS

#ifndef TXLIN_NO_NAMESPACE
}

using namespace TX;
#endif

#endif
