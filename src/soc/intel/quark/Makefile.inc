#
# This file is part of the coreboot project.
#
# Copyright (C) 2015-2016 Intel Corporation.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

ifeq ($(CONFIG_SOC_INTEL_QUARK),y)

subdirs-y += romstage
subdirs-y += ../../../cpu/x86/tsc

bootblock-y += bootblock/esram_init.S
bootblock-y += bootblock/bootblock.c
bootblock-y += i2c.c
bootblock-y += reg_access.c
bootblock-y += tsc_freq.c
bootblock-y += uart_common.c

verstage-y += i2c.c
verstage-y += reg_access.c
verstage-y += tsc_freq.c
verstage-$(CONFIG_ENABLE_BUILTIN_HSUART1) += uart_common.c

romstage-y += i2c.c
romstage-y += memmap.c
romstage-y += reg_access.c
romstage-$(CONFIG_STORAGE_TEST) += storage_test.c
romstage-y += tsc_freq.c
romstage-$(CONFIG_ENABLE_BUILTIN_HSUART1) += uart_common.c
romstage-$(CONFIG_PLATFORM_USES_FSP2_0) += reset.c

postcar-y += fsp2_0.c
postcar-y += i2c.c
postcar-y += memmap.c
postcar-y += reg_access.c
postcar-y += tsc_freq.c
postcar-$(CONFIG_ENABLE_BUILTIN_HSUART1) += uart_common.c

ramstage-$(CONFIG_HAVE_ACPI_TABLES) += acpi.c
ramstage-y += chip.c
ramstage-y += ehci.c
ramstage-$(CONFIG_PLATFORM_USES_FSP1_1) += fsp1_1.c
ramstage-$(CONFIG_PLATFORM_USES_FSP2_0) += fsp2_0.c
ramstage-y += gpio_i2c.c
ramstage-y += i2c.c
ramstage-y += lpc.c
ramstage-y += memmap.c
ramstage-y += northcluster.c
ramstage-y += reg_access.c
ramstage-$(CONFIG_PLATFORM_USES_FSP2_0) += reset.c
ramstage-y += sd.c
ramstage-$(CONFIG_STORAGE_TEST) += storage_test.c
ramstage-y += tsc_freq.c
ramstage-$(CONFIG_ENABLE_BUILTIN_HSUART1) += uart_common.c
ramstage-$(CONFIG_ENABLE_BUILTIN_HSUART1) += uart.c

CPPFLAGS_common += -I$(src)/soc/intel/quark
CPPFLAGS_common += -I$(src)/soc/intel/quark/include
CPPFLAGS_common += -I$(src)/soc/intel/quark/include/soc/fsp

# Chipset microcode path
CPPFLAGS_common += -I3rdparty/blobs/soc/intel/quark

# Since FSP-M runs in CAR we need to relocate it to a specific address
$(CONFIG_FSP_M_CBFS)-options := -b $(CONFIG_FSP_ESRAM_LOC)

# Add the FSP binary to the CBFS image
cbfs-files-$(CONFIG_ADD_FSP_RAW_BIN) += fsp.bin
fsp.bin-file := $(call strip_quotes,$(CONFIG_FSP_FILE))
fsp.bin-position := $(CONFIG_FSP_LOC)
fsp.bin-type := raw

# Add the chipset microcode file to the CBFS image
cbfs-files-$(CONFIG_ADD_RMU_FILE) += rmu.bin
rmu.bin-file := $(call strip_quotes,$(CONFIG_RMU_FILE))
rmu.bin-position := $(CONFIG_RMU_LOC)
rmu.bin-type := raw

endif # CONFIG_SOC_INTEL_QUARK
