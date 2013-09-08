#!/bin/sh


#---------------------------------------------------------
# MACROS
#
# Each of the following can be added to the HMCSIM_MACROS
#     option below in order to enable/disable certain
#     options.
# 
# HMCSIM LIBRARY MAJOR VERSION NUMBER
# -DHMC_MAJOR_VERSION=n
#
# HMCSIM LIBRARY MINOR VERSION NUMBER
# -DHMC_MINOR_VERSION=n
#
# HMCSIM LIBRARY VENDOR ID
# -DHMC_VENDOR_ID=n
#
# HMCSIM PRODUCT REVISION [8-bit unsigned int]
# -DHMC_PRODUCT_REVISION=n
#
# HMCSIM PROTOCOL REVISION [8-bit unsigned int]
# -DHMC_PROTOCOL_REVISION=n
#
# HMCSIM PHY REVISION [8-bit unsigned int]
# -DHMC_PHY_REVISION=n
#
# HMCSIM PHYSICAL LINK SPEED
# 0 = 15Gpbs
# 1 = 10Gpbs
# -DHMC_PHY_SPEED={0,1}
#	
#---------------------------------------------------------

HMCSIM_MACROS=

CC=gcc

CXX=g++

INC=-I./include/

CFLAGS=-O2 -Wall -g $(INC) $(HMCSIM_MACROS)

CXXFLAGS=-O2 -Wall -g $(INC) $(HMCSIM_MACROS)

AR=ar
AROPTS=rcs

DOXYGEN=`which doxygen`

#-- EOF 
