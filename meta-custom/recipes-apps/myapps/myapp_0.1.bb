SUMMARY = "txo Tools myapp and GPIO_Prog_Regan"
DESCRIPTION = "Custom recipe for my application myapp.c and GPIO_Prog_Regan.c"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
# Where to find the source (local or github)
SRC_URI="file://src"
# Where to keep downloaded sources (in tmp/work/...)
S="${WORKDIR}/src"
#Pass arguments to linker
TARGET_CC_ARCH += "${LDFLAGS}"
#Cross compiler source code
do_compile(){
	${CC} -o myapp myapp.c
	${CC} -o GPIO_Prog_Regan GPIO_Prog_Regan.c
}

# Create /usr/bin in rootfs and copy program
do_install(){
	install -d ${D}${bindir}
	install -m 0755 myapp ${D}${bindir}
	install -m 0755 GPIO_Prog_Regan ${D}${bindir}
}

