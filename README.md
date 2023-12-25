# E220-900T22S（JP）Arduino Library
<div style="text-align: right;">
Auther: Nihinihikun

2023/12/25
</div>

## Attension!
Obey your local radio laws. We Do Not have any responsibility.

## Overview
- E220-900T22S(JP) is a LoRa module.
- This library supports Arduino. 

## Hardware
- supply-voltage: 3.3~5.5V, reccomend:5.0V
- logic-level: 3.3V
- center-frequency:920.6~928.0MHz
- receiving-sensitivity:-124dBm
- interface:UART

get from datasheet

If you want to get details, see datasheet.


## Source
### Main
- E220.h
- E220.cpp

### Config
- E220_config.h
- E220_config.cpp

### Examples
- config.ino
    - If you change hardware-configuration, use this file.
- test1.ino
    - example when rssi-byte off.
- test2.ino
    - example when rssi-byte on.

## Usage
See each README.md in each folder.
