SUMMARY = "OpenPLC v3 Runtime and Webserver for Linux"
HOMEPAGE = "https://github.com/thiagoralves/OpenPLC_v3"
LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464"

DEPENDS = "bison-native flex-native autoconf-native automake-native libtool-native"
#RDEPENDS:${PN} = "python3 python3-flask python3-pyserial libgpiod-tools packagegroup-core-buildessential bash "

RDEPENDS:${PN} = " \
    python3 \
    python3-flask \
    python3-flask-login \
    python3-flask-sqlalchemy \
    python3-sqlite3 \
    python3-flask-jwt-extended \
    python3-python-dotenv \
    python3-pyserial \
    libgpiod-tools \
    packagegroup-core-buildessential \
    bash \
"

SRC_URI = "gitsm://github.com/thiagoralves/OpenPLC_v3.git;protocol=https;branch=master \
           file://custom.cpp \
           file://openplc-init \
          "

SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

inherit update-rc.d

INITSCRIPT_NAME = "openplc"
INITSCRIPT_PARAMS = "defaults 99"

do_configure() {
    # Configuration de matiec (iec2c)
    cd ${S}/utils/matiec_src
    autoreconf --install --verbose
    ./configure --host=${HOST_SYS} --build=${BUILD_SYS} ${CONFIGUREOPTS}
}

do_compile() {
    # Compilation d'iec2c uniquement
    oe_runmake -C ${S}/utils/matiec_src
    install -d ${S}/utils/matiec
    cp ${S}/utils/matiec_src/iec2c ${S}/utils/matiec/iec2c
}

do_install() {
    # Deploiement des sources du serveur web et du core dans /var/www/openplc ou /etc/openplc
    install -d ${D}${sysconfdir}/openplc
    cp -r ${S}/webserver ${D}${sysconfdir}/openplc/

    # Si un fichier hardware sur mesure existe, on le déploie dans le core
    if [ -f ${WORKDIR}/custom.cpp ]; then
        cp ${WORKDIR}/custom.cpp ${D}${sysconfdir}/openplc/webserver/core/hardware_layer.cpp
    fi

    # Installation du traducteur iec2c pour l'interface Web
    install -d ${D}${sysconfdir}/openplc/utils/matiec
    install -m 0755 ${S}/utils/matiec/iec2c ${D}${sysconfdir}/openplc/utils/matiec/iec2c

    # Script d'initialisation SysVinit
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/openplc-init ${D}${sysconfdir}/init.d/openplc
}

FILES:${PN} += "${sysconfdir}/openplc ${sysconfdir}/init.d/openplc"
