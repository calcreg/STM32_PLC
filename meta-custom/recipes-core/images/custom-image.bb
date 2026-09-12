SUMMARY = "My custom images Linux (Regan -- 27.11.21) "

IMAGE_INSTALL = "packagegroup-core-boot ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image
inherit extrausers

#Set rootfs to 200MiB by default
IMAGE_OVER_HEAD_FACTORY ?="1.0"
IMAGE_ROOTFS_SIZE ?= "204800"
#change root passwword (note the capital -P which is different from linux command)
EXTRA_USERS_PARAMS="\
	usermod -P 'toor' root \
	"
# Include our custom application
IMAGE_INSTALL += " myapp myqtapp util-linux"
#To activate graphical display on HDMI
IMAGE_INSTALL += " mesa libdrm kmscube qtbase qtbase-plugins"

#Font is too tiny on screen
IMAGE_INSTALL += " kbd kbd-consolefonts"

#To manage ipk packets on target
IMAGE_INSTALL += " opkg"

#Missing plugins definition to display
DISTRO_FEATURES_append = " opengl egl"

#We need modetest
IMAGE_INSTALL += " libdrm-tests"

#QT FONTS
IMAGE_INSTALL += " liberation-fonts fontconfig myfonts"

#CONNECTION SSH
#EXTRA_IMAGE_FEATURES += " ssh-server-dropbear"
# Installe OpenSSH et configure le démarrage automatique
EXTRA_IMAGE_FEATURES += "ssh-server-openssh"

#Install SavvyCan Qt5 software
IMAGE_INSTALL += " savvycan"

#TO be able to use ip link set for can
IMAGE_INSTALL += " iproute2 can-utils"

