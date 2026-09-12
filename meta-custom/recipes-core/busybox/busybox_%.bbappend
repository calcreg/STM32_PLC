
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://ntp.cfg"

#Other alternative is to do 
# bitbake -c menuconfig busybox
# activate :  Networking Utilities -> enable ntpd.
# bitbake -c diffconfig busybox
# Save the diff in this ntp.cfg config



