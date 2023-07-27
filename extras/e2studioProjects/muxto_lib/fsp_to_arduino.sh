#!/bin/bash

ARDUINO_MUXTO="MUXTO"
ARDUINO_CAPRI="CAPRI"
#
# MUXTO
#

echo "EXECUTING SCRIPT FOR $ARDUINO_MUXTO"
./_private_fsp2arduino.sh $ARDUINO_MUXTO

#
# CAPRI
#

echo "EXECUTING SCRIPT FOR $ARDUINO_CAPRI"
./_private_fsp2arduino.sh $ARDUINO_CAPRI

