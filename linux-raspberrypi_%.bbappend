FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:" 

SRC_URI += "file://0001-Add-mgpio-module-for-controlling-LED-on-GPIO27.patch" 

KERNEL_MODULE_AUTOLOAD += "mgpio"