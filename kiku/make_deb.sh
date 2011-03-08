#!/bin/sh
################################################################################
## This file is part of CodeLite IDE and is released
## under the terms of the GNU General Public License as published by
##    the Free Software Foundation; either version 2 of the License, or
##    (at your option) any later version.
##
## Modified for kiku
################################################################################


## Copy files to the fakeroot directory structure
cur_rev=1
arch=`uname -m`

if [ "${arch}" = "i686" ]; then
    arch="i386"
elif [ "${arch}" = "x86_64" ]; then
    arch="amd64"
fi

## Parse command line argument for getting install prefix
parseCommandLine()
{
    case $1 in
        "-d")   PREFIX="/usr";;

        "-u")   PREFIX="/usr"
                cur_rev="${cur_rev}-ubuntu0";;

        "--help" | "-h")    usage
                            exit 0;;
        *   )   usage
                exit 1;;
    esac
}

## Show help
usage()
{
    cat <<EOF
Usage:
  `basename $0` [options]

Options:
  -h | --help   this help screen
  -d            make deb-package for Debian
  -u            make deb-package for Ubuntu

EOF
}

## Making control and postinst files
generateDebianFiles()
{
	cat > fakeroot/DEBIAN/control <<EOF
Package: kiku
Version: 0.${cur_rev}
Section: Accessibility
Priority: optional
Architecture: ${arch}
Essential: no
Depends: libx11-6, libc6, libgcc1, libstdc++6, libasound2, zlib1g, libexpat1, libtiff4, libjpeg62, libpng12-0, libsm6, libxxf86vm1, libglib2.0-0, libfontconfig1, libfreetype6, libpango1.0-0, libcairo2, libgtk2.0-0, libatk1.0-0, libxosd2, libxext6, libxinerama1, libnotify1, libdbus-glib-1-2, libdbus-1-3
Installed-Size: ${inst_size}
Maintainer: Patrick Sebastien [kiku@11h11.com]
Description: Voice recognition
     Kiku is a simple voice recognition software to control your OS.

EOF

    cat > fakeroot/DEBIAN/postinst <<EOF
#!/bin/sh
echo "Running postinst step..."

## Menu updating
if [ "\$1" = "configure" ] && [ -x "\`which update-menus 2>/dev/null\`" ]; then
    update-menus
fi
## Update mime database
if [ "\$1" = "configure" ] && [ -x "\`which update-mime-database 2>/dev/null\`" ]; then
   update-mime-database ${PREFIX}/share/mime
fi
## Update mime icon
if [ "\$1" = "configure" ] && [ -x "\`which update-icon-caches 2>/dev/null\`" ]; then
   update-icon-caches ${PREFIX}/share/icons/hicolor
fi
echo "Done"
EOF
    cat > fakeroot/DEBIAN/postrm <<EOF
#!/bin/sh
echo "Running postrm step..."

## Menu updating
if [ "\$1" = "configure" ] && [ -x "\`which update-menus 2>/dev/null\`" ]; then
    update-menus
fi
## Update mime database
if [ "\$1" = "configure" ] && [ -x "\`which update-mime-database 2>/dev/null\`" ]; then
   update-mime-database ${PREFIX}/share/mime
fi
## Update mime icon
if [ "\$1" = "configure" ] && [ -x "\`which update-icon-caches 2>/dev/null\`" ]; then
   update-icon-caches ${PREFIX}/share/icons/hicolor
fi
echo "Done"
EOF
    chmod 0755 fakeroot/DEBIAN/postinst
	chmod 0755 fakeroot/DEBIAN/postrm
}

## Making destop file
generateDesktopFile()
{
    rm -fr fakeroot/usr/share/applications/kiku.desktop
    cp -fr kiku.desktop fakeroot/usr/share/applications/kiku.desktop
    chmod +x fakeroot/usr/share/applications/kiku.desktop
}

## Making menu entry for WMs
generateMenuFile()
{
    rm -fr fakeroot/usr/share/menu/kiku
    echo "?package(kiku):needs=\"x11\" section=\"Applications/Accessibility\" \ " >> fakeroot/usr/share/menu/kiku
    echo "        title=\"kiku\" command=\"${PREFIX}/bin/kiku\" \ " >> fakeroot/usr/share/menu/kiku
    echo "        icon=\"${PREFIX}/share/kiku/images/kiku.png\" " >> fakeroot/usr/share/menu/kiku
    echo "" >> fakeroot/usr/share/menu/kiku
}

## Parse command line options
parseCommandLine $1

EXE_NAME=kiku

## clear previous packaged files
rm -fr fakeroot
mkdir -p fakeroot/DEBIAN/
mkdir -p fakeroot/${PREFIX}/bin/

cp ./Release/${EXE_NAME} fakeroot/${PREFIX}/bin/kiku
mkdir -p fakeroot/${PREFIX}/share/kiku
mkdir -p fakeroot/${PREFIX}/share/kiku/images
mkdir -p fakeroot/usr/share/applications/
mkdir -p fakeroot/usr/share/menu/


cp -pr kiku.png fakeroot/${PREFIX}/share/kiku/images/
cp -pr AUTHORS fakeroot/${PREFIX}/share/kiku/
cp -pr COPYING fakeroot/${PREFIX}/share/kiku/

## Clean all .svn files
find fakeroot -name ".svn" | xargs rm -fr

## Get installed size
inst_size=`du -s fakeroot/usr/ | awk -F" " '{ print $1 }'`

## Make debain files
generateDebianFiles

## Make desktop file
generateDesktopFile

## Make menu entry
generateMenuFile

chmod +x fakeroot/${PREFIX}/bin/kiku

fakeroot dpkg -b fakeroot/ ./
