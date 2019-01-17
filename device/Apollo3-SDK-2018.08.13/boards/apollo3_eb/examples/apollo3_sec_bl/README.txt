To exercise this program:
Flash the main program at 0x10000 (MAIN_PROGRAM_ADDR_IN_FLASH)
Link this program at the address suitable for SBL (0xC000 or 0xC100) depending
nonsecure or secure configuration
To test OTA - construct images using magic numbers in the range matching
AM_IMAGE_MAGIC_CUST
To test INFO0 key area access - need to keep INFO0->Security->PLONEXIT as 0


