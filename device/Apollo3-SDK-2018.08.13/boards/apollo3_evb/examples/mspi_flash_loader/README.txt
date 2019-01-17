The binary must be linked to run from MSPI flash address range
(as specified by BIN_INSTALL_ADDR). The location and size of the binary
in internal flash are specified using BIN_ADDR_FLASH & BIN_SIZE

This example has been enhanced to use the new 'binary patching' feature
This example will not build if proper startup/linker files are not used.

Steps:
1. coremark.bin has been created to run out of external flash @ 0x04000000

2. ./mspi_loader_binary_combiner.py --loaderbin iar/bin/mspi_flash_loader.bin --appbin coremark.bin --flags 0x2 --outbin loader_coremark

3. Now flash this binary (loader_coremark.bin) at 0xC000.

