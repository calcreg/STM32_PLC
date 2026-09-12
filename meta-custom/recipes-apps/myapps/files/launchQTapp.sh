#!/bin/sh
export QT_QPA_PLATFORM=eglfs
export QT_QPA_EGLFS_KMS_CONFIG=/etc/qt5/eglfs.json
export QT_QPA_FONTDIR=/usr/share/fonts/ttf
export XDG_RUNTIME_DIR=/tmp/runtime-root
export QT_QPA_EVDEV_MOUSE_PARAMETERS=/dev/input/event2
export QT_FONT_DPI=90
#USE ONLY QCursor from appli
export QT_QPA_EGLFS_HIDECURSOR=0
export QT_QPA_EGLFS_NO_LIBINPUT=0
export QT_QPA_EGLFS_KMS_ATOMIC=0

if [ ! -e /etc/qt5/eglfs.json ]; then
	mkdir -p /etc/qt5
	cat > /etc/qt5/eglfs.json << EOF
{
    "device": "/dev/dri/card1",
    "hwmouse": false,
    "hwcursor": false,
    "pb_buffering": 2
}

EOF
fi


