EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title "ESPuino Complete"
Date "2021-02-16"
Rev "0.1"
Comp "espuino Comunity"
Comment1 "https://forum.espuino.de"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ProjectLib:CH340T(SSOP20W) U?
U 1 1 603FA087
P 5200 3500
AR Path="/603FA087" Ref="U?"  Part="1"
AR Path="/602F0C3D/603FA087" Ref="U3"  Part="1"
F 0 "U3" H 5200 4150 60  0000 C CNN
F 1 "CH340T(SSOP20W)" H 5200 2800 60  0000 C CNN
F 2 "ESP32-DevKit-LiPo-Rev:SSOP20-0.65-7.6X5.2MM" H 5200 2750 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811151532_WCH-Jiangsu-Qin-Heng-CH340T_C8689.pdf" H 4700 1150 60  0000 C CNN
F 4 "PB-Free" H 5200 3500 50  0001 C CNN "Note"
	1    5200 3500
	1    0    0    -1
$EndComp
$Comp
L ProjectLib:C C?
U 1 1 603FA09C
P 3700 3000
AR Path="/603FA09C" Ref="C?"  Part="1"
AR Path="/602F0C3D/603FA09C" Ref="C4"  Part="1"
F 0 "C4" V 3650 2775 50  0000 L CNN
F 1 "22uF/6.3V/20%/X5R/C0603" V 3650 3050 25  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3700 3000 60  0001 C CNN
F 3 "" H 3700 3000 60  0000 C CNN
F 4 "Value 1" H 3700 3000 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 3700 3000 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 3700 3000 60  0001 C CNN "Fieldname3"
	1    3700 3000
	0    1    1    0
$EndComp
$Comp
L ProjectLib:GND #PWR?
U 1 1 603FA0A2
P 3400 3300
AR Path="/603FA0A2" Ref="#PWR?"  Part="1"
AR Path="/602F0C3D/603FA0A2" Ref="#PWR0106"  Part="1"
F 0 "#PWR0106" H 3400 3050 50  0001 C CNN
F 1 "GND" V 3405 3127 50  0000 C CNN
F 2 "" H 3400 3300 60  0000 C CNN
F 3 "" H 3400 3300 60  0000 C CNN
	1    3400 3300
	0    1    1    0
$EndComp
$Comp
L ProjectLib:C C?
U 1 1 603FA0AB
P 3700 3100
AR Path="/603FA0AB" Ref="C?"  Part="1"
AR Path="/602F0C3D/603FA0AB" Ref="C5"  Part="1"
F 0 "C5" V 3650 2875 50  0000 L CNN
F 1 "100nF/10V/10%/X7R/C0402" V 3650 3150 25  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 3700 3100 60  0001 C CNN
F 3 "" H 3700 3100 60  0000 C CNN
F 4 "Value 1" H 3700 3100 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 3700 3100 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 3700 3100 60  0001 C CNN "Fieldname3"
	1    3700 3100
	0    1    1    0
$EndComp
$Comp
L ProjectLib:GND #PWR?
U 1 1 603FA0B1
P 3400 3000
AR Path="/603FA0B1" Ref="#PWR?"  Part="1"
AR Path="/602F0C3D/603FA0B1" Ref="#PWR0107"  Part="1"
F 0 "#PWR0107" H 3400 2750 50  0001 C CNN
F 1 "GND" V 3405 2827 50  0000 C CNN
F 2 "" H 3400 3000 60  0000 C CNN
F 3 "" H 3400 3000 60  0000 C CNN
	1    3400 3000
	0    1    1    0
$EndComp
$Comp
L ProjectLib:GND #PWR?
U 1 1 603FA0B7
P 3400 3100
AR Path="/603FA0B7" Ref="#PWR?"  Part="1"
AR Path="/602F0C3D/603FA0B7" Ref="#PWR0108"  Part="1"
F 0 "#PWR0108" H 3400 2850 50  0001 C CNN
F 1 "GND" V 3405 2927 50  0000 C CNN
F 2 "" H 3400 3100 60  0000 C CNN
F 3 "" H 3400 3100 60  0000 C CNN
	1    3400 3100
	0    1    1    0
$EndComp
$Comp
L ProjectLib:C C?
U 1 1 603FA0C0
P 3400 3800
AR Path="/603FA0C0" Ref="C?"  Part="1"
AR Path="/602F0C3D/603FA0C0" Ref="C2"  Part="1"
F 0 "C2" V 3350 3650 50  0000 L CNN
F 1 "27pF/50V/5%/C0G/C0402" V 3350 3850 40  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 3400 3800 60  0001 C CNN
F 3 "" H 3400 3800 60  0000 C CNN
F 4 "Value 1" H 3400 3800 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 3400 3800 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 3400 3800 60  0001 C CNN "Fieldname3"
	1    3400 3800
	0    1    1    0
$EndComp
$Comp
L ProjectLib:C C?
U 1 1 603FA0C9
P 3400 4000
AR Path="/603FA0C9" Ref="C?"  Part="1"
AR Path="/602F0C3D/603FA0C9" Ref="C3"  Part="1"
F 0 "C3" V 3350 3850 50  0000 L CNN
F 1 "27pF/50V/5%/C0G/C0402" V 3350 4050 40  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 3400 4000 60  0001 C CNN
F 3 "" H 3400 4000 60  0000 C CNN
F 4 "Value 1" H 3400 4000 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 3400 4000 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 3400 4000 60  0001 C CNN "Fieldname3"
	1    3400 4000
	0    1    1    0
$EndComp
Text Label 9000 3100 2    60   ~ 12
GPIO1\U0TXD
Text Label 9000 3000 2    60   ~ 12
GPIO3\U0RXD
Text Label 9000 3200 2    60   ~ 12
ESP_EN
Text Label 9000 4300 2    60   ~ 12
GPIO0
Text Notes 8125 3475 0    60   ~ 12
Auto program\n
Text Notes 7950 3600 0    60   ~ 12
DTR  RTS->EN  IO0
Text Notes 8025 3700 0    60   ~ 12
1
Text Notes 8275 3700 0    60   ~ 12
1
Text Notes 8525 3700 0    60   ~ 12
1
Text Notes 8750 3700 0    60   ~ 12
1
Text Notes 8025 3800 0    60   ~ 12
0
Text Notes 8275 3800 0    60   ~ 12
0
Text Notes 8525 3800 0    60   ~ 12
1
Text Notes 8750 3800 0    60   ~ 12
1
Text Notes 8025 3900 0    60   ~ 12
1
Text Notes 8275 3900 0    60   ~ 12
0
Text Notes 8525 3900 0    60   ~ 12
0
Text Notes 8750 3900 0    60   ~ 12
1
Text Notes 8025 4000 0    60   ~ 12
0
Text Notes 8275 4000 0    60   ~ 12
1
Text Notes 8525 4000 0    60   ~ 12
1
Text Notes 8750 4000 0    60   ~ 12
0
Text Label 9000 4900 2    60   ~ 12
GPIO2
Text Label 6900 4900 0    60   ~ 12
D_Com
Wire Wire Line
	3600 3000 3400 3000
Wire Wire Line
	3600 3100 3400 3100
Wire Wire Line
	3400 3300 4700 3300
Connection ~ 4400 3000
Wire Wire Line
	3800 3000 4400 3000
Wire Wire Line
	3300 3800 3200 3800
Wire Wire Line
	3200 3800 3200 3900
Wire Wire Line
	3300 4000 3200 4000
Wire Notes Line
	7950 3400 7950 4025
Wire Notes Line
	7950 3600 8900 3600
Wire Notes Line
	8900 3400 8900 4025
Wire Notes Line
	8900 3400 7950 3400
Wire Notes Line
	8900 4025 7950 4025
Wire Notes Line
	7950 3500 8900 3500
Wire Notes Line
	8175 3600 8175 4025
Wire Notes Line
	8425 3600 8425 4025
Wire Notes Line
	8675 3600 8675 4025
Wire Wire Line
	4400 3000 4700 3000
Text Label 3200 2600 0    60   ~ 12
+5V_USB
$Comp
L ProjectLib:TESTPAD D_Com?
U 1 1 603FA11A
P 6400 4900
AR Path="/603FA11A" Ref="D_Com?"  Part="1"
AR Path="/602F0C3D/603FA11A" Ref="D_Com1"  Part="1"
F 0 "D_Com1" H 6650 4900 50  0000 C CNN
F 1 "TESTPAD" H 6300 4785 50  0001 L BNN
F 2 "TestPoint:TestPoint_Pad_D3.0mm" H 6160 4825 20  0001 C CNN
F 3 "" V 6400 4900 60  0000 C CNN
F 4 "Value 1" H 6400 4900 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 6400 4900 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 6400 4900 60  0001 C CNN "Fieldname3"
	1    6400 4900
	-1   0    0    1
$EndComp
$Comp
L ProjectLib:Crystal_GND Q?
U 1 1 603FA120
P 4400 3900
AR Path="/603FA120" Ref="Q?"  Part="1"
AR Path="/602F0C3D/603FA120" Ref="Q1"  Part="1"
F 0 "Q1" V 4400 3975 50  0000 L CNN
F 1 "Q12MHz/20pF/10ppm/4P/3.2x2.5mm" V 4575 3125 40  0000 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm_HandSoldering" V 4491 3983 60  0001 L CNN
F 3 "" H 4400 3900 60  0000 C CNN
	1    4400 3900
	0    1    1    0
$EndComp
Wire Wire Line
	3500 3800 4400 3800
Wire Wire Line
	3500 4000 4400 4000
Connection ~ 4400 3800
Wire Wire Line
	4400 3800 4700 3800
Connection ~ 4400 4000
Wire Wire Line
	4400 4000 4700 4000
Wire Wire Line
	4300 3900 3200 3900
Connection ~ 3200 3900
Wire Wire Line
	3200 3900 3200 4000
NoConn ~ 5700 3400
NoConn ~ 5700 3600
NoConn ~ 5700 3800
NoConn ~ 5700 3700
NoConn ~ 5700 4000
Wire Wire Line
	3800 3100 4500 3100
Wire Wire Line
	4400 2600 4400 3000
Connection ~ 7900 3000
Wire Wire Line
	7900 3000 9200 3000
Text Notes 4300 2400 0    200  ~ 40
USB to UART
Connection ~ 4500 3100
Wire Wire Line
	4500 3100 4700 3100
Wire Wire Line
	6500 4900 7800 4900
Connection ~ 7800 4600
Wire Wire Line
	7800 4900 7800 4600
Wire Wire Line
	8100 4900 9200 4900
Wire Wire Line
	8100 4800 8100 4900
Wire Wire Line
	8100 4300 8100 4400
Wire Wire Line
	7800 4600 7900 4600
Wire Wire Line
	8100 4300 9200 4300
$Comp
L ProjectLib:BAT54C(SOT23-3) D?
U 1 1 603FA166
P 8100 4600
AR Path="/603FA166" Ref="D?"  Part="1"
AR Path="/602F0C3D/603FA166" Ref="D5"  Part="1"
F 0 "D5" V 8150 4725 60  0000 L CNN
F 1 "BAT54C(SOT23-3)" V 8050 4725 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 8100 4600 60  0001 C CNN
F 3 "" H 8100 4600 60  0001 C CNN
	1    8100 4600
	0    1    -1   0
$EndComp
$Comp
L ProjectLib:R R?
U 1 1 603FA16F
P 6550 4200
AR Path="/603FA16F" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA16F" Ref="R14"  Part="1"
F 0 "R14" H 6550 4300 50  0000 C CNN
F 1 "2.2k/R0402" H 6550 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 6550 4130 30  0001 C CNN
F 3 "" V 6550 4200 30  0000 C CNN
F 4 "Value 1" H 6550 4200 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 6550 4200 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 6550 4200 60  0001 C CNN "Fieldname3"
	1    6550 4200
	1    0    0    -1
$EndComp
$Comp
L ProjectLib:R R?
U 1 1 603FA178
P 6550 3500
AR Path="/603FA178" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA178" Ref="R12"  Part="1"
F 0 "R12" H 6550 3600 50  0000 C CNN
F 1 "2.2k/R0402" H 6550 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 6550 3430 30  0001 C CNN
F 3 "" V 6550 3500 30  0000 C CNN
F 4 "Value 1" H 6550 3500 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 6550 3500 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 6550 3500 60  0001 C CNN "Fieldname3"
	1    6550 3500
	1    0    0    -1
$EndComp
Wire Wire Line
	6700 3500 6800 3500
$Comp
L ProjectLib:Q_NPN_BEC Q?
U 1 1 603FA17F
P 7000 3500
AR Path="/603FA17F" Ref="Q?"  Part="1"
AR Path="/602F0C3D/603FA17F" Ref="Q2"  Part="1"
F 0 "Q2" H 7191 3546 50  0000 L CNN
F 1 "BC817-40(SOT23)" H 7191 3455 40  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 7200 3600 29  0001 C CNN
F 3 "" H 7000 3500 60  0000 C CNN
	1    7000 3500
	1    0    0    -1
$EndComp
Wire Wire Line
	7100 3300 7100 3200
Wire Wire Line
	7100 3700 7100 3800
Wire Wire Line
	6700 4200 6800 4200
$Comp
L ProjectLib:Q_NPN_BEC Q?
U 1 1 603FA189
P 7000 4200
AR Path="/603FA189" Ref="Q?"  Part="1"
AR Path="/602F0C3D/603FA189" Ref="Q3"  Part="1"
F 0 "Q3" H 7191 4154 50  0000 L CNN
F 1 "BC817-40(SOT23)" H 7191 4245 40  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 7200 4300 29  0001 C CNN
F 3 "" H 7000 4200 60  0000 C CNN
	1    7000 4200
	1    0    0    1
$EndComp
Wire Wire Line
	7100 4400 7100 4600
Wire Wire Line
	7100 4000 7100 3900
Wire Wire Line
	7600 4600 7800 4600
Wire Wire Line
	7100 4600 7300 4600
$Comp
L ProjectLib:R R?
U 1 1 603FA193
P 7450 4600
AR Path="/603FA193" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA193" Ref="R15"  Part="1"
F 0 "R15" H 7450 4500 50  0000 C CNN
F 1 "220R/R0402" H 7450 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7380 4600 30  0001 C CNN
F 3 "" H 7450 4600 30  0000 C CNN
	1    7450 4600
	1    0    0    1
$EndComp
Connection ~ 6000 3100
Wire Wire Line
	5700 3100 6000 3100
Wire Wire Line
	6000 3100 6400 3100
Wire Wire Line
	6700 3000 7500 3000
$Comp
L ProjectLib:R R?
U 1 1 603FA1A1
P 8700 2600
AR Path="/603FA1A1" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA1A1" Ref="R16"  Part="1"
F 0 "R16" H 8525 2650 50  0000 C CNN
F 1 "NA/R0402" H 8700 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 8700 2530 30  0001 C CNN
F 3 "" V 8700 2600 30  0000 C CNN
F 4 "Value 1" H 8700 2600 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 8700 2600 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 8700 2600 60  0001 C CNN "Fieldname3"
	1    8700 2600
	1    0    0    -1
$EndComp
Wire Wire Line
	5700 3000 6400 3000
Wire Wire Line
	6000 2600 6000 3100
Connection ~ 4400 2600
Wire Wire Line
	4400 2600 5000 2600
$Comp
L ProjectLib:R R?
U 1 1 603FA1B4
P 5150 2600
AR Path="/603FA1B4" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA1B4" Ref="R8"  Part="1"
F 0 "R8" H 4950 2650 50  0000 C CNN
F 1 "10k/R0402" H 5500 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 5150 2530 30  0001 C CNN
F 3 "" V 5150 2600 30  0000 C CNN
F 4 "Value 1" H 5150 2600 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 5150 2600 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 5150 2600 60  0001 C CNN "Fieldname3"
	1    5150 2600
	1    0    0    -1
$EndComp
Wire Wire Line
	5300 2600 6000 2600
$Comp
L ProjectLib:D_Schottky D?
U 1 1 603FA1BB
P 6550 3100
AR Path="/603FA1BB" Ref="D?"  Part="1"
AR Path="/602F0C3D/603FA1BB" Ref="D3"  Part="1"
F 0 "D3" H 6750 3150 50  0000 C CNN
F 1 "1N5819S4/SOD123" H 6000 3150 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 6550 3232 60  0001 C CNN
F 3 "" H 6550 3100 60  0000 C CNN
	1    6550 3100
	-1   0    0    -1
$EndComp
Wire Wire Line
	6700 3100 9200 3100
$Comp
L ProjectLib:D_Schottky D?
U 1 1 603FA1C2
P 6550 3000
AR Path="/603FA1C2" Ref="D?"  Part="1"
AR Path="/602F0C3D/603FA1C2" Ref="D2"  Part="1"
F 0 "D2" H 6350 3050 50  0000 C CNN
F 1 "1N5819S4/SOD123" H 7100 3050 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 6550 3132 60  0001 C CNN
F 3 "" H 6550 3000 60  0000 C CNN
	1    6550 3000
	1    0    0    -1
$EndComp
Wire Wire Line
	7100 3900 6200 3900
Wire Wire Line
	6200 3500 6400 3500
Connection ~ 6200 3500
Wire Wire Line
	6200 3900 6200 3500
Wire Wire Line
	5700 3500 6200 3500
Wire Wire Line
	5700 3300 6000 3300
Wire Wire Line
	6000 4200 6400 4200
Wire Wire Line
	7100 3800 6000 3800
Connection ~ 6000 3800
Wire Wire Line
	6000 3300 6000 3800
Wire Wire Line
	6000 3800 6000 4200
NoConn ~ 5700 3900
$Comp
L ProjectLib:R R?
U 1 1 603FA1D8
P 5150 2700
AR Path="/603FA1D8" Ref="R?"  Part="1"
AR Path="/602F0C3D/603FA1D8" Ref="R9"  Part="1"
F 0 "R9" H 4950 2750 50  0000 C CNN
F 1 "10k/R0402" H 5500 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 5150 2630 30  0001 C CNN
F 3 "" V 5150 2700 30  0000 C CNN
F 4 "Value 1" H 5150 2700 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 5150 2700 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 5150 2700 60  0001 C CNN "Fieldname3"
	1    5150 2700
	1    0    0    -1
$EndComp
Wire Wire Line
	5000 2700 4500 2700
Wire Wire Line
	4500 2700 4500 3100
Wire Wire Line
	5300 2700 7500 2700
Wire Wire Line
	7500 2700 7500 3000
Connection ~ 7500 3000
Wire Wire Line
	7500 3000 7900 3000
Connection ~ 3200 4000
Wire Wire Line
	2600 3600 4700 3600
Wire Wire Line
	2600 3400 2600 2600
Connection ~ 2600 2600
Wire Wire Line
	2600 2600 2300 2600
Text HLabel 9200 4900 2    50   Output ~ 0
GPIO_2
Text HLabel 9200 4300 2    50   Output ~ 0
GPIO_0
Text HLabel 9200 3200 2    50   Output ~ 0
GPIO_EN
Text HLabel 9200 3100 2    50   Output ~ 0
GPIO_TX
Text HLabel 9200 3000 2    50   Input ~ 0
GPIO_RX
Text Label 3650 3500 0    50   ~ 0
UD-
Text Label 3650 3600 0    50   ~ 0
UD+
$Comp
L ProjectLib:R R?
U 1 1 60AA0810
P 2900 3650
AR Path="/60AA0810" Ref="R?"  Part="1"
AR Path="/602F0C3D/60AA0810" Ref="R19"  Part="1"
F 0 "R19" V 3050 3700 50  0000 L CNN
F 1 "0 /R0402" V 3150 3500 40  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 2900 3580 30  0001 C CNN
F 3 "" V 2900 3650 30  0000 C CNN
F 4 "Value 1" H 2900 3650 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 2900 3650 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 2900 3650 60  0001 C CNN "Fieldname3"
	1    2900 3650
	0    -1   -1   0
$EndComp
$Comp
L Connector:USB_B_Micro J4
U 1 1 60B038B1
P 2300 3600
F 0 "J4" H 2357 4067 50  0000 C CNN
F 1 "USB_B_Micro" H 2357 3976 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 2450 3550 50  0001 C CNN
F 3 "~" H 2450 3550 50  0001 C CNN
	1    2300 3600
	1    0    0    -1
$EndComp
Wire Wire Line
	2900 3500 4700 3500
Wire Wire Line
	2600 3700 2800 3700
Wire Wire Line
	2800 3700 2800 3800
Wire Wire Line
	2800 3800 2900 3800
NoConn ~ 2600 3800
Wire Wire Line
	2200 4000 2300 4000
Wire Wire Line
	2300 4000 3200 4000
Connection ~ 2300 4000
Wire Wire Line
	3200 4000 3200 4250
Wire Wire Line
	7100 3200 9200 3200
Text HLabel 2300 2600 0    50   Output ~ 0
5V_USB
$Comp
L ProjectLib:TESTPAD GND?
U 1 1 603FA151
P 3100 4250
AR Path="/603FA151" Ref="GND?"  Part="1"
AR Path="/602F0C3D/603FA151" Ref="GND1"  Part="1"
F 0 "GND1" H 3300 4250 50  0000 C CNN
F 1 "TESTPAD" H 3000 4135 50  0001 L BNN
F 2 "TestPoint:TestPoint_Pad_D3.0mm" H 2860 4175 20  0001 C CNN
F 3 "" V 3100 4250 60  0000 C CNN
F 4 "Value 1" H 3100 4250 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 3100 4250 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 3100 4250 60  0001 C CNN "Fieldname3"
	1    3100 4250
	-1   0    0    1
$EndComp
Connection ~ 3200 4250
Wire Wire Line
	3200 4250 3200 4650
Text HLabel 9200 2600 2    50   Input ~ 0
3V3
Wire Wire Line
	7900 2600 8550 2600
Wire Wire Line
	7900 2600 7900 3000
Wire Wire Line
	8850 2600 9200 2600
Text HLabel 2300 4650 0    50   Output ~ 0
GND
Wire Wire Line
	3200 4650 2300 4650
Wire Wire Line
	2600 2600 4400 2600
$EndSCHEMATC
