SUMMARY = "Set console font early boot"
LICENSE = "CLOSED"

SRC_URI = "file://setfonts"

inherit update-rc.d

INITSCRIPT_NAME = "setfonts"
INITSCRIPT_PARAMS = "start 99 5 ."

do_install() {
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/setfonts ${D}${sysconfdir}/init.d/
}
