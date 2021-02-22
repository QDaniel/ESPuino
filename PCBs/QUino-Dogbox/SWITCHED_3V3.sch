EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6100 3700 6100 3850
Wire Wire Line
	5900 3400 5750 3400
Wire Wire Line
	6300 3400 8600 3400
Text Label 6950 3400 0    50   ~ 0
SWITCHED_3V
$Comp
L ESP32-DevKit-Lipo_Rev_C:R R?
U 1 1 60EFC881
P 5750 3550
AR Path="/60EFC881" Ref="R?"  Part="1" 
AR Path="/60EF3972/60EFC881" Ref="R17"  Part="1" 
F 0 "R17" H 5800 3650 50  0000 C CNN
F 1 "10k/R0402" V 5950 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 5750 3480 30  0001 C CNN
F 3 "" V 5750 3550 30  0000 C CNN
F 4 "Value 1" H 5750 3550 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 5750 3550 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 5750 3550 60  0001 C CNN "Fieldname3"
	1    5750 3550
	0    -1   -1   0   
$EndComp
Connection ~ 5750 3400
Wire Wire Line
	6100 3850 5750 3850
Wire Wire Line
	5750 3850 5750 3700
Wire Wire Line
	7100 4150 7200 4150
$Comp
L ESP32-DevKit-Lipo_Rev_C:R R?
U 1 1 60EFC896
P 7200 4300
AR Path="/60EFC896" Ref="R?"  Part="1" 
AR Path="/60EF3972/60EFC896" Ref="R18"  Part="1" 
F 0 "R18" H 7200 4300 50  0000 C CNN
F 1 "10k/R0402" V 7000 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 7200 4230 30  0001 C CNN
F 3 "" V 7200 4300 30  0000 C CNN
F 4 "Value 1" H 7200 4300 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 7200 4300 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 7200 4300 60  0001 C CNN "Fieldname3"
	1    7200 4300
	0    -1   -1   0   
$EndComp
Connection ~ 7200 4150
Wire Wire Line
	6900 4450 7200 4450
$Comp
L ESP32-DevKit-Lipo_Rev_C:R R?
U 1 1 60EFC8A2
P 7500 4450
AR Path="/60EFC8A2" Ref="R?"  Part="1" 
AR Path="/60EF3972/60EFC8A2" Ref="R20"  Part="1" 
F 0 "R20" H 7500 4450 50  0000 C CNN
F 1 "4,7k/R0402" H 7500 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" H 7500 4380 30  0001 C CNN
F 3 "" V 7500 4450 30  0000 C CNN
F 4 "Value 1" H 7500 4450 60  0001 C CNN "Fieldname 1"
F 5 "Value2" H 7500 4450 60  0001 C CNN "Fieldname2"
F 6 "Value3" H 7500 4450 60  0001 C CNN "Fieldname3"
	1    7500 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4450 7200 4450
Connection ~ 7200 4450
$Comp
L Device:Q_NPN_BEC Q?
U 1 1 60EFC8AD
P 6900 4250
AR Path="/60EFC8AD" Ref="Q?"  Part="1" 
AR Path="/60EF3972/60EFC8AD" Ref="Q5"  Part="1" 
F 0 "Q5" V 7228 4250 50  0000 C CNN
F 1 "QBC817 NPN/BEC" V 7100 4200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 7100 4350 50  0001 C CNN
F 3 "~" H 6900 4250 50  0001 C CNN
	1    6900 4250
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 60EFC8B3
P 6100 3500
AR Path="/60EFC8B3" Ref="Q?"  Part="1" 
AR Path="/60EF3972/60EFC8B3" Ref="Q4"  Part="1" 
F 0 "Q4" V 6442 3500 50  0000 C CNN
F 1 "SI2302DS NMOS/GSD" V 6350 3350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6300 3600 50  0001 C CNN
F 3 "~" H 6100 3500 50  0001 C CNN
	1    6100 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 3850 6100 4150
Wire Wire Line
	6100 4150 6700 4150
Connection ~ 6100 3850
Text HLabel 4050 3400 0    50   Input ~ 0
VIN
Wire Wire Line
	4050 3400 4650 3400
Text HLabel 8600 3400 2    50   Output ~ 0
VSwitched
Text HLabel 8600 4450 2    50   Input ~ 0
EN
Text HLabel 8600 2900 2    50   Output ~ 0
VOUT
Wire Wire Line
	8600 2900 4650 2900
Wire Wire Line
	4650 2900 4650 3400
Connection ~ 4650 3400
Wire Wire Line
	4650 3400 5750 3400
Wire Wire Line
	7650 4450 8600 4450
Text HLabel 8600 4150 2    50   Output ~ 0
GND
Wire Wire Line
	7200 4150 8600 4150
$EndSCHEMATC
