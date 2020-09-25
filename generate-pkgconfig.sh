#!/bin/sh
rm -r -f txlin.pc txlin-macflags
LIBS="-pthread -DTXLIN_PTHREAD -lm -lSDL2_ttf"
CFLAGS="-pthread -DTXLIN_PTHREAD"
VERSION=1.76

touch txlin.pc
cat >>txlin.pc<<EOF
Name: TXLin
Description: TXLin is a library providing TXLib API on Linux and macOS.
Requires: sdl2
Version: $VERSION
Libs: $LIBS
Cflags: $CFLAGS
EOF

cat >>txlin-macflags<<EOF
#!/bin/sh
if test "\$1" = "--cflags"; then
	echo "$CFLAGS -I/usr/local/include \$(sdl2-config --cflags)"
elif test "\$1" = "--libs"; then
	echo "\$(sdl2-config --libs) $LIBS "
fi
exit 0
EOF

chmod 755 txlin-macflags

if test "$1" = "--install"; then
	if test `uname` = "Darwin"; then
		cp txlin-macflags /usr/local/bin/txlin-macflags
	else
		mkdir -p /usr/share/pkgconfig > /dev/null 2>&1
		cp txlin.pc /usr/share/pkgconfig/txlin.pc
	fi
	if test "$?" != "0"; then
		exit 1
	fi
elif test "$1" = "--install-with-txlin"; then
	if sh "$0" --install; then
		echo "Installed pkgconfig files"
	else
		echo "Did not install pkgconfig files, cannot install the library itself. Maybe run \"sudo $0 $*\" (without quotes, obviously)?"
		exit 2
	fi
	PATHD=/usr/local/include
	if test `uname` != "Darwin"; then
		PATHD=/usr/include
	fi
	mkdir -p $PATHD > /dev/null 2>&1
	cp TXLin.h $PATHD/TXLin.h
	if command -v sdl2-config > /dev/null 2>&1; then
		echo "SDL2 found, everything should be working properly"
	else
		echo "WARNING! SDL2 development files were not found on your computer. Without them, TXLin won't work. Please install them before using the library."
	fi
fi
exit 0
