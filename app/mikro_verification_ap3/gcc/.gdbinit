#*************************************************
#
# Connect to J-Link and debug application in flash on Cortex-M3
#
# Download to flash is performed.
#
# Connect to the J-Link gdb server
target remote localhost:2331

monitor reset

monitor halt

monitor endian little

monitor speed auto

monitor flash download = 1
