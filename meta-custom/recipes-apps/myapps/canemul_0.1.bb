SUMMARY = "Tools canemul to generate various can events to test SavvyCAN"
DESCRIPTION = "Custom recipe for my application canemul"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
# Where to find the source (local or github)
SRC_URI="file://canemul"
# Where to keep downloaded sources (in tmp/work/...)
S="${WORKDIR}/canemul"
#Pass arguments to linker
TARGET_CC_ARCH += "${LDFLAGS}"
#Cross compiler source code
do_compile(){
	${CC} -o canemul canemul.c
}

# Create /usr/bin in rootfs and copy program
do_install(){
	install -d ${D}${bindir}
	install -m 0755 canemul ${D}${bindir}
}

