# Master makefile for the Microboard libraries
include Makefile.inc

TARGETS := \
  atmega \
  lpc1114 \
  pic16f

.PHONY: all clean

all:
	for f in $(TARGETS); do make -C $(SOURCE)/$$f; done

clean:
	for f in $(TARGETS); do make -C $(SOURCE)/$$f clean; done
	rm -rf $(WORKING) $(LIBS)

