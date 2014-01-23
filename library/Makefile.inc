# Common definitions used by multiple child Makefiles
TOPDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

# Set the location for tools
INCLUDE   = $(TOPDIR)/include
SOURCE    = $(TOPDIR)/src
WORKING   = $(TOPDIR)/out
LIBS      = $(TOPDIR)/libs

