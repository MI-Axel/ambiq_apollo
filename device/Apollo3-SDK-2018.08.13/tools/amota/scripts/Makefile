#*******************************************************************************
#
# Simple Makefile to prepare binaries for AMOTA.
#
#*******************************************************************************

FLAG_ADDR_APOLLO1 = 0x6000
LOAD_ADDR_APOLLO1 = 0x8000
BOOTBIN_APOLLO1 =../../../boards/apollo1_evb/examples/multi_boot/keil/bin/multi_boot.bin

# Apollo1 EVB +AM_BLE shield board
UPDATEBIN_APOLLO1_AM_BLE =../../../boards/apollo1_evb_am_ble/examples/freertos_amota_blinky/keil/bin/freertos_amota_blinky.bin
APPBIN_APOLLO1_AM_BLE =../../../boards/apollo1_evb_am_ble/examples/freertos_amota/keil/bin/freertos_amota.bin
APPBIN_APOLLO1_AM_BLE_ETHERMIND =../../../boards/apollo1_evb_am_ble/examples/mindtree_amota/keil/bin/mindtree_amota.bin

# Apollo1 EVB +EM3904 discreet board
UPDATEBIN_APOLLO1_EM9304 =../../../boards/apollo1_evb_em9304/examples/freertos_amota_blinky/keil/bin/freertos_amota_blinky.bin
APPBIN_APOLLO1_EM9304 =../../../boards/apollo1_evb_em9304/examples/freertos_amota/keil/bin/freertos_amota.bin
APPBIN_APOLLO1_EM9304_ETHERMIND =../../../boards/apollo1_evb_em9304/examples/mindtree_amota/keil/bin/mindtree_amota.bin

FLAG_ADDR_APOLLO2 = 0x6000
LOAD_ADDR_APOLLO2 = 0x8000
BOOTBIN_APOLLO2 =../../../boards/apollo2_evb/examples/multi_boot/keil/bin/multi_boot.bin

# Apollo2 EVB +AM_BLE shield board
UPDATEBIN_APOLLO2_AM_BLE =../../../boards/apollo2_evb_am_ble/examples/freertos_amota_blinky/keil/bin/freertos_amota_blinky.bin
APPBIN_APOLLO2_AM_BLE =../../../boards/apollo2_evb_am_ble/examples/freertos_amota/keil/bin/freertos_amota.bin
APPBIN_APOLLO2_AM_BLE_ETHERMIND =../../../boards/apollo2_evb_am_ble/examples/mindtree_amota/keil/bin/mindtree_amota.bin

# Apollo2 EVB+EM3904 discreet board
UPDATEBIN_APOLLO2_EM9304 =../../../boards/apollo2_evb_em9304/examples/freertos_amota_blinky/keil/bin/freertos_amota_blinky.bin
APPBIN_APOLLO2_EM9304 =../../../boards/apollo2_evb_em9304/examples/freertos_amota/keil/bin/freertos_amota.bin
APPBIN_APOLLO2_EM9304_ETHERMIND =../../../boards/apollo2_evb_em9304/examples/mindtree_amota/keil/bin/mindtree_amota.bin

# Apollo2-BLUE EVB
UPDATEBIN_APOLLO2_BLUE =../../../boards/apollo2_blue_evb/examples/freertos_amota_blinky/keil/bin/freertos_amota_blinky.bin
APPBIN_APOLLO2_BLUE =../../../boards/apollo2_blue_evb/examples/freertos_amota/keil/bin/freertos_amota.bin
APPBIN_APOLLO2_BLUE_ETHERMIND =../../../boards/apollo2_blue_evb/examples/mindtree_amota/keil/bin/mindtree_amota.bin

all: $(BOOTBIN_APOLLO1) $(BOOTBIN_APOLLO2) \
	$(APPBIN_APOLLO1_AM_BLE) $(UPDATEBIN_APOLLO1_AM_BLE) \
	$(APPBIN_APOLLO1_EM9304) $(UPDATEBIN_APOLLO1_EM9304) \
	$(APPBIN_APOLLO2_BLUE) $(UPDATEBIN_APOLLO2_BLUE) \
	$(APPBIN_APOLLO2_AM_BLE) $(UPDATEBIN_APOLLO2_AM_BLE) \
	$(APPBIN_APOLLO2_EM9304) $(UPDATEBIN_APOLLO2_EM9304) \
	$(APPBIN_APOLLO1_EM9304_ETHERMIND) \
	$(APPBIN_APOLLO1_AM_BLE_ETHERMIND) \
	$(APPBIN_APOLLO2_BLUE_ETHERMIND) \
	$(APPBIN_APOLLO2_EM9304_ETHERMIND) \
	$(APPBIN_APOLLO2_AM_BLE_ETHERMIND) \

	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO1}" --appbin "${APPBIN_APOLLO1_AM_BLE}" --flag-addr ${FLAG_ADDR_APOLLO1} --load-address ${LOAD_ADDR_APOLLO1} -o starter_binary_apollo1_am_ble
	python3 ota_binary_converter.py --appbin "${UPDATEBIN_APOLLO1_AM_BLE}" --load-address ${LOAD_ADDR_APOLLO1} -o update_binary_apollo1_am_ble
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO1}" --appbin "${APPBIN_APOLLO1_EM9304}" --flag-addr ${FLAG_ADDR_APOLLO1} --load-address ${LOAD_ADDR_APOLLO1} -o starter_binary_apollo1_em9304
	python3 ota_binary_converter.py --appbin "${UPDATEBIN_APOLLO1_EM9304}" --load-address ${LOAD_ADDR_APOLLO1} -o update_binary_apollo1_em9304
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_BLUE}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_blue
	python3 ota_binary_converter.py --appbin "${UPDATEBIN_APOLLO2_BLUE}" --load-address ${LOAD_ADDR_APOLLO2} -o update_binary_apollo2_blue
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_AM_BLE}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_am_ble
	python3 ota_binary_converter.py --appbin "${UPDATEBIN_APOLLO2_AM_BLE}" --load-address ${LOAD_ADDR_APOLLO2} -o update_binary_apollo2_am_ble
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_EM9304}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_em9304
	python3 ota_binary_converter.py --appbin "${UPDATEBIN_APOLLO2_EM9304}" --load-address ${LOAD_ADDR_APOLLO2} -o update_binary_apollo2_em9304

	# Mindtree based AMOTA
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO1}" --appbin "${APPBIN_APOLLO1_AM_BLE_ETHERMIND}" --flag-addr ${FLAG_ADDR_APOLLO1} --load-address ${LOAD_ADDR_APOLLO1} -o starter_binary_apollo1_am_ble_ethermind
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO1}" --appbin "${APPBIN_APOLLO1_EM9304_ETHERMIND}" --flag-addr ${FLAG_ADDR_APOLLO1} --load-address ${LOAD_ADDR_APOLLO1} -o starter_binary_apollo1_em9304_ethermind
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_BLUE_ETHERMIND}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_blue_ethermind
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_AM_BLE_ETHERMIND}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_am_ble_ethermind
	python3 bootloader_binary_combiner.py --bootbin "${BOOTBIN_APOLLO2}" --appbin "${APPBIN_APOLLO2_EM9304_ETHERMIND}" --flag-addr ${FLAG_ADDR_APOLLO2} --load-address ${LOAD_ADDR_APOLLO2} -o starter_binary_apollo2_em9304_ethermind

$(BOOTBIN_APOLLO1):
	$(MAKE) -C ../../../boards/apollo1_evb/examples/multi_boot/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO1_AM_BLE):
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/freertos_amota/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO1_AM_BLE_ETHERMIND):
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/mindtree_amota/keil/ $(MAKECMDGOALS)

$(UPDATEBIN_APOLLO1_AM_BLE):
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO1_EM9304):
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/freertos_amota/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO1_EM9304_ETHERMIND):
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/mindtree_amota/keil/ $(MAKECMDGOALS)

$(UPDATEBIN_APOLLO1_EM9304):
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)


$(BOOTBIN_APOLLO2):
	$(MAKE) -C ../../../boards/apollo2_evb/examples/multi_boot/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_BLUE):
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/freertos_amota/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_BLUE_ETHERMIND):
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/mindtree_amota/keil/ $(MAKECMDGOALS)

$(UPDATEBIN_APOLLO2_BLUE):
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_AM_BLE):
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/freertos_amota/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_AM_BLE_ETHERMIND):
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/mindtree_amota/keil/ $(MAKECMDGOALS)

$(UPDATEBIN_APOLLO2_AM_BLE):
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_EM9304):
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/freertos_amota/keil/ $(MAKECMDGOALS)

$(APPBIN_APOLLO2_EM9304_ETHERMIND):
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/mindtree_amota/keil/ $(MAKECMDGOALS)

$(UPDATEBIN_APOLLO2_EM9304):
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)


clean:
	rm -rf *.bin
	$(MAKE) -C ../../../boards/apollo1_evb/examples/multi_boot/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/freertos_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/mindtree_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_am_ble/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/freertos_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/mindtree_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo1_evb_em9304/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb/examples/multi_boot/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/freertos_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/mindtree_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_blue_evb/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/freertos_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/mindtree_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_am_ble/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/freertos_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/mindtree_amota/keil/ $(MAKECMDGOALS)
	$(MAKE) -C ../../../boards/apollo2_evb_em9304/examples/freertos_amota_blinky/keil/ $(MAKECMDGOALS)
	