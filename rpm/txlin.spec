Summary:	A reimplementation of TXLib for Linux and macOS
Name:		txlin
Version:	174a
Release:	2
License:	ISC
Source0:	https://gitlab.com/timkoi/txlin/-/archive/master/txlin-master.tar.bz2
Group:		Development/Libraries
BuildArch:	noarch
Vendor:		Tim K
Provides:	pkgconfig(txlin)
Provides:	txlib-linux
Provides:	txlib
Provides:	TXLin.h
Requires:	gcc-c++
Requires:	pkgconfig(sdl2)

%description
TXLin is a reimplementation of TXLib library API for Linux and macOS.

%prep
if test -d ./txlin; then rm -r -f ./txlin; fi
mkdir txlin
tar --strip-components=1 -C ./txlin -xvjf %{_rpmdir}/../SOURCES/txlin-master.tar.bz2

%build
cd txlin
touch TXLib.h
echo "#ifndef TXLIN_TXLIB_COMPAT_H" > TXLib.h
echo "#define TXLIN_TXLIB_COMPAT_H" >> TXLib.h
echo "#warning \"Please include TXLin.h instead of TXLib.h when compiling TXLib/TXLin programs on Linux on macOS. This is generally more portable.\"" >> TXLib.h
echo "#include \"TXLin.h\"" >> TXLib.h
echo "#endif" >> TXLib.h
touch txlin.pc
echo "Name: TXLin" > txlin.pc
echo "Description: TXLin is a library providing TXLib API on Linux and macOS." >> txlin.pc
echo "Requires: sdl2" >> txlin.pc
echo "Version: 0.174" >> txlin.pc
echo "Libs: -lm" >> txlin.pc
echo "Cflags: -I/usr/include" >> txlin.pc

%install
mkdir -p $RPM_BUILD_ROOT/usr/include
mkdir -p $RPM_BUILD_ROOT/usr/share/pkgconfig
mkdir -p $RPM_BUILD_ROOT/etc/skel/.config/codeblocks/UserTemplates
mkdir -p $RPM_BUILD_ROOT/usr/share/txlin
cd txlin
cp TXLin.h $RPM_BUILD_ROOT/usr/include/TXLin.h
cp TXLib.h $RPM_BUILD_ROOT/usr/include/TXLib.h
cp txlin.pc $RPM_BUILD_ROOT/usr/share/pkgconfig/txlin.pc
cp -r templates/TXLinTemplate_CodeBlocks/ $RPM_BUILD_ROOT/usr/share/txlin/CodeBlocksTemplate
ln -s /usr/share/txlin/CodeBlocksTemplate "$RPM_BUILD_ROOT/etc/skel/.config/codeblocks/UserTemplates/TXLin Project"

%post
for UserAccountFolder in /home/*; do
	if test ! -d "$UserAccountFolder/.config/codeblocks"; then mkdir "$UserAccountFolder/.config/codeblocks"; fi
	mkdir -p "$UserAccountFolder/.config/codeblocks/UserTemplates" > /dev/null 2>&1
	ln -s /usr/share/txlin/CodeBlocksTemplate "$UserAccountFolder/.config/codeblocks/UserTemplates/TXLin Project"
	chown -R `dirname "$UserAccountFolder"`:`dirname "$UserAccountFolder"` "$UserAccountFolder/.config/codeblocks"
done

%preun
for UserAccountFolder in /home/*; do
	rm -r -f "$UserAccountFolder/.config/codeblocks/UserTemplates/TXLin Project"
done

%files
/usr/include/TXLib.h
/usr/include/TXLin.h
/usr/share/pkgconfig/txlin.pc
/etc/skel/.config/codeblocks
/usr/share/txlin/CodeBlocksTemplate
