# GarfTutor

Welcome to the my handmade instruction for using old fortran-based version of Garfield. All examples here oriented on usage my analysis for parameterization of straw tube response in SPD experiment.

## Getting started

I'm assuming you already have Garfield and CERN root packages installed. My version is 7.45 (Magboltz 7.08) for Garfield and 6.24/06 for ROOT but I think that examples here should work well in any future (and many previous) versions. Also I am using signals processed in LTspice but asking my colleagues for help with this. So if you want to completely repeat the examples here you should be able to use LTspice package too.

## General Garfield info

#### Garfield help pages

The old version of Garfield has a very detailed manual for all supported commands. Just in case, here are a couple of links to the same thing:

- [official Garfield help](https://garfield.web.cern.ch/help/)
- [alternative source for link above](https://cmd.inp.nsk.su/old/cmd2/manuals/cernlib/garfield/help/garfield.html)

#### Running Garfield in batch mode

Use `garfield-9` command for running interactive Garfield interface. But I prefer batch compatible mode with the following syntax:

``` fortran
garfield-9 < File_name_with_list_of_Garfield_instructions > File_name_with_Garfield_output_log
```

#### Gas file creation

Before run any calculation in `&DRIFT` or `&SIGNAL` sections One should fill gas properties tables. There is many ways how to do it includint runtime calculations but I recommend using a pre-generated gas file with the required information. [Here](https://github.com/SergeyNA/GarfTutor/blob/main/garf_scripts/gas_file_calc) you can find the example script for creating *.gas file with filled gas properties tables for case with active magnetic field in my analysis.

If you want to create a similar file for another gas mixture, then pay attention to the following parameters:

+ [Magnetic field inside detector](https://garfield.web.cern.ch/help/garfield.html#Ref0293)
+ [Gas mix compound, field range, calculation precision](https://garfield.web.cern.ch/help/garfield_31.html#Ref0340)
+ [Ion mobility](https://garfield.web.cern.ch/help/garfield_40.html#Ref0419)
+ [Temperature](https://garfield.web.cern.ch/help/garfield_31.html#Ref0501)
+ [Pressure](https://garfield.web.cern.ch/help/garfield_31.html#Ref0463)
+ [Energy loss through ionisation of a particle that traverses the gas](https://garfield.web.cern.ch/help/garfield_31.html#Ref0336)
+ [Penning effect](https://garfield.web.cern.ch/help/garfield_57.html#Ref0573)

### Signal readout

The main information on how Garfield calculates the signal can be found [here](https://garfield.web.cern.ch/help/garfield_120.html#Ref1010) and [here](https://fdocuments.net/document/garfield-a-drift-chamber-simulation-program-users-kobayashseminarfilescerngarfield.html?page=1 "garfield manual pdf Version 4.29 Rob Veenhof").

#### Ion mobility

Grafield does not allow signal calculation without information about the ion drift velocity. Garfield++ version is able evaluate it on one's own. In Garfieild this is your responsibility. I have a very comfortable case in my analysis. Gas mixture is very simple and well researched so I can just take the [measured data](https://www.sciencedirect.com/science/article/abs/pii/0092640X76900012 "I do not remeber the exact part of publication").

```
******************
        &GAS
******************

get {gas_file} // load gas properties

Vector E_Ar_Ar K_Ar_Ar
   0  1.53
   8  1.53
  10  1.53
  12  1.53
  15  1.52
  20  1.51
  25  1.49
  30  1.47
  40  1.44
  50  1.41
  60  1.38
  80  1.32
 100  1.27
 120  1.22
 150  1.16
 200  1.06
 250  0.99
 300  0.95
 400  0.85
 500  0.78
 600  0.72
 800  0.63
1000  0.56
1200  0.51
1500  0.46
2000  0.40

//conversion to the Garfield units
Global E_Ar_Ar = E_Ar_Ar*250/720
Global K_Ar_Ar = K_Ar_Ar*0.000001

add ion-mobility K_Ar_Ar vs E_Ar_Ar
extrapolation low-ion-mobility constant high-ion-mobility linear

**************
&OPTIMISE
**************

penning Ar* {penn} // still measured value
```

#### Transfer function

The program calculates the induced signal to the electrode. Readout electronics always make changes in reality. To simulate this effect, the convolution of the original induced signal with the transfer function is used. In my analysis, for greater realism, the LTspice package is used for these purposes. Therefore, the following code will save the data of the induced current to the anode wire.

```
**************
&SIGNAL
**************

Area {-rtube} {-rtube} {rtube} {rtube}
Window 0 0.00025 // 0-250 nsec time range; zero time - moment of 1st electron produced by ionization process start moving 
avalanche townsend
sel s // s is a char label for anode wire in the tube
track {x_start, y_start, 0, x_end, y_end, 0} muon energy 1 GeV
Signal avalanche average-signal 2 new electron-pulse ION-PULSE DETAILED-ION-TAIL
write-signals file="{sig_name}" units ampere second format SORIN
```

#### Noise

Currently noise impact do not consider

## Known Issues

GasGain wrong calc; Missmatch Garfield and Garfield++; Transfer Function for Garfield++
