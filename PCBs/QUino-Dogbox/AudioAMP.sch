EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title "ESPuino Complete"
Date "2021-02-16"
Rev "0.1"
Comp "espuino Comunity"
Comment1 "https://forum.espuino.de"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 950  1250 0    50   Input ~ 0
VIN
Text HLabel 1000 1550 0    50   Output ~ 0
GND
Text HLabel 950  1850 0    50   Input ~ 0
DIN
Text HLabel 950  2100 0    50   Output ~ 0
LRC
Text HLabel 950  2350 0    50   Input ~ 0
CLK
Text HLabel 950  2600 0    50   Input ~ 0
EN_SD
Text HLabel 1450 2900 0    50   Output ~ 0
HEADPHONE_DETECT
$Comp
L power:GND #PWR0127
U 1 1 608862A6
P 1400 1550
F 0 "#PWR0127" H 1400 1300 50  0001 C CNN
F 1 "GND" V 1405 1422 50  0000 R CNN
F 2 "" H 1400 1550 50  0001 C CNN
F 3 "" H 1400 1550 50  0001 C CNN
	1    1400 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 1550 1150 1550
Text Notes 2500 1050 0    200  ~ 40
Audio AMP
$Comp
L Connector:Conn_01x07_Male J5
U 1 1 611B3314
P 3200 2100
F 0 "J5" H 3172 2124 50  0000 R CNN
F 1 "Conn_01x07_Male" H 3172 2033 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 3200 2100 50  0001 C CNN
F 3 "~" H 3200 2100 50  0001 C CNN
F 4 "0" H 3200 2100 50  0001 C CNN "JLCPCB BOM"
	1    3200 2100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	950  1250 2300 1250
Wire Wire Line
	2300 1250 2300 1800
Wire Wire Line
	2300 1800 3000 1800
Wire Wire Line
	1150 1550 1150 1650
Wire Wire Line
	1150 1650 2200 1650
Wire Wire Line
	2200 1650 2200 1900
Wire Wire Line
	2200 1900 3000 1900
Connection ~ 1150 1550
Wire Wire Line
	1150 1550 1000 1550
Wire Wire Line
	3000 2000 2100 2000
Wire Wire Line
	2100 2000 2100 1850
Wire Wire Line
	2100 1850 950  1850
Wire Wire Line
	950  2100 3000 2100
Wire Wire Line
	950  2350 2100 2350
Wire Wire Line
	2100 2350 2100 2200
Wire Wire Line
	2100 2200 3000 2200
Wire Wire Line
	3000 2300 2200 2300
Wire Wire Line
	2200 2300 2200 2600
Wire Wire Line
	2200 2600 950  2600
Wire Wire Line
	1450 2900 2300 2900
Wire Wire Line
	2300 2900 2300 2400
Wire Wire Line
	2300 2400 3000 2400
$EndSCHEMATC
