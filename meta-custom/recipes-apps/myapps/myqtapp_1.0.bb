SUMMARY = "THIS IS A MINIMAL QT5 APPLI"
DESCRIPTION = "Custom Mimimal qt5 appli"
LICENSE = "MIT"

#LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835c9145a4f1b1e0d2f7b3b3d8b7b79"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "\
    file://cpp/main.cpp \
    file://cpp/helloworld.pro \
    file://cpp/resources.qrc \
    file://cpp/images/mycursor.png \
    file://pinguin.jpeg \
    file://launchQTapp.sh \
"

S = "${WORKDIR}/cpp"

inherit qmake5

DEPENDS += "qtbase"

FILES:${PN} += "${bindir}/helloworld ${bindir}/launchQTapp.sh"
FILES:${PN} += "${sysconfdir}/pinguin.jpeg"
do_install_append() {
        install -d ${D}${sysconfdir}
        install -m 0644 ${WORKDIR}/pinguin.jpeg ${D}${sysconfdir}
	install -m 0755 ${WORKDIR}/launchQTapp.sh ${D}${bindir}
}




