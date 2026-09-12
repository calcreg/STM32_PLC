SUMMARY = "Qt-based CAN bus reverse engineering and capture tool"
HOMEPAGE = "https://github.com/collin80/SavvyCAN"
LICENSE = "GPL-3.0-only | GPLv3"
LIC_FILES_CHKSUM = "file://LICENSE;md5=56eb122929929ab5d0d4112a7b906d09"

SRC_URI = "git://github.com/collin80/SavvyCAN.git;protocol=https;branch=master"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

DEPENDS = "qtbase qtserialport qtserialbus qtdeclarative qttools libsocketcan"
RDEPENDS_${PN} = "qtbase qtserialport qtserialbus qtserialbus-plugins can-utils qtdeclarative qttools libsocketcan"

inherit qmake5

# Qt graphics plugin requirements at runtime
#RRECOMMENDS:${PN} += "qtwayland"
#We have DRM/GPU Vivant already

# Force qmake to install under /usr instead of /usr/local
EXTRA_QMAKEVARS_PRE += "PREFIX=${prefix}"

do_install_append() {
    rm -rf ${D}${bindir}/help
    rm -rf ${D}${datadir}/savvycan
}

FILES_${PN} += " \
    ${bindir}/SavvyCAN \
    ${datadir}/icons \
    ${datadir}/applications \
"



