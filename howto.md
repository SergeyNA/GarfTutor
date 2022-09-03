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

#### Disk space quota

During each run, Garfield creates log files named `garflast.dat` and `GKS_error.log`, making a backup of the files of the same name if they already exist. If your task requires a large amount of computing resources, then the size of these files will also be large. If you are worried about the amount of free disk space, then you need to clean up these files yourself.

#### Gas file creation

Before run any calculation in `&DRIFT` or `&SIGNAL` sections you should fill gas properties tables. There is many ways how to do it includint runtime calculations but I recommend using a pre-generated gas file with the required information. [Here](https://github.com/SergeyNA/GarfTutor/blob/main/garf_scripts/gas_file_calc) you can find the example script for creating *.gas file with filled gas properties tables for case with active magnetic field in my analysis.

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

#### Cluster info

For each call to the procedure for calculating the induced signal, Garfield provides information considering each formed cluster in the following format
```
  Signal simulation:
  ==================

  The track begins at (-0.60000002E+00, 0.30000001E+00, 0.00000000E+00)
  and ends at         ( 0.60000002E+00, 0.30000001E+00, 0.00000000E+00)


  A single group of electrodes is currently selected for read-out:

  Group 1 consists of:
     Wire 1 with label S at (x,y)=(0,0) and at 1750 V

  No solid is currently selected outside read-out.
  Table of the clusters
  =====================


     No      x-start      y-start      z-start   Drift time    Diffusion Pairs  Pair Arrival time Total charge
                [cm]         [cm]         [cm]   [microsec]   [microsec]               [microsec]  [electrons]

      1 -0.59351E+00  0.30000E+00 -0.22039E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      2 -0.56813E+00  0.30000E+00 -0.12439E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      3 -0.52977E+00  0.30000E+00 -0.13680E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      4 -0.44760E+00  0.30000E+00  0.39455E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      5 -0.44127E+00  0.30000E+00 -0.11006E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      6 -0.41997E+00  0.30000E+00  0.19017E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
      7 -0.39236E+00  0.29997E+00  0.64130E-04  0.14915E+00  0.40029E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14348E+00  0.18727E+05
      8 -0.39237E+00  0.29994E+00  0.12827E-03  0.14912E+00  0.40028E-02     1  Hit S wire 1, read out    
                                                                                   1  0.15065E+00  0.14414E+05
      9 -0.39238E+00  0.29992E+00  0.19240E-03  0.14911E+00  0.40023E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14974E+00  0.49622E+04
     10 -0.39239E+00  0.29989E+00  0.25654E-03  0.14911E+00  0.40033E-02     1  Hit S wire 1, read out    
                                                                                   1  0.15108E+00  0.36948E+05
     11 -0.39239E+00  0.29986E+00  0.32067E-03  0.14910E+00  0.40017E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14782E+00  0.63090E+04
     12 -0.39232E+00  0.30002E+00  0.47435E-05  0.14912E+00  0.40022E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14293E+00  0.36189E+04
     13 -0.39229E+00  0.30004E+00  0.94960E-05  0.14913E+00  0.40170E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14834E+00  0.55119E+04
     14 -0.39225E+00  0.30006E+00  0.14248E-04  0.14916E+00  0.40008E-02     1  Hit S wire 1, read out    
                                                                                   1  0.15659E+00  0.21231E+05
     15 -0.39222E+00  0.30008E+00  0.19001E-04  0.14910E+00  0.40027E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14728E+00  0.17281E+05
     16 -0.39218E+00  0.30010E+00  0.23753E-04  0.14908E+00  0.40016E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14785E+00  0.52790E+04
     17 -0.39215E+00  0.30012E+00  0.28505E-04  0.14926E+00  0.39982E-02     1  Hit S wire 1, read out    
                                                                                   1  0.13774E+00  0.20465E+05
     18 -0.39211E+00  0.30015E+00  0.33256E-04  0.14907E+00  0.40018E-02     1  Hit S wire 1, read out    
                                                                                   1  0.15012E+00  0.67770E+04
     19 -0.39208E+00  0.30017E+00  0.38007E-04  0.14906E+00  0.40009E-02     1  Hit S wire 1, read out    
                                                                                   1  0.15220E+00  0.17380E+05
     20 -0.38479E+00  0.30000E+00  0.39913E-05  0.14527E+00  0.39337E-02     1  Hit S wire 1, read out    
                                                                                   1  0.14595E+00  0.26026E+04
     21 -0.32948E+00  0.30002E+00  0.67610E-05  0.11968E+00  0.34451E-02     1  Hit S wire 1, read out    
                                                                                   1  0.12058E+00  0.15500E+05
     22 -0.32948E+00  0.30004E+00  0.13534E-04  0.11968E+00  0.34459E-02     1  Hit S wire 1, read out    
                                                                                   1  0.12713E+00  0.33671E+04
```

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

Garfield calculates the induced signal to the electrode. Readout electronics always make changes in reality. To simulate this effect, the convolution of the original induced signal with the transfer function is used. In my analysis, for greater realism, the LTspice package is used for these purposes. Therefore, the following code will save the data of the induced current to the anode wire.

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

## Getting induced signals

[Here](https://github.com/SergeyNA/GarfTutor/blob/main/garf_scripts/induced_signals_gen) is garfield script example for generating 50000 <ins>pure</ins><sup>*1</sup> anode signals in 6 mm SPD straw tube from uniformly distributed initial <ins>ionization particles</ins><sup>*2</sup> and saving it to the <ins>public folder</ins><sup>*3</sup>.

1. `pure signals` means "only induced signals on the anode wire, without noise and without influence of readout electronics"
2. `ionization particles` is a 1 GeV muon in perpendicular to the tube plane with uniformly distributed distance (with sign) to the anode wire from -rtube to +rtube
3. `public folder` on a server with restricted access

## Simulation of real electronic

To simulate a real electronics impact while reading the signal, I used the help of my colleague. He passed the induced signals from Garfield through the LTspice. 

#### Garfield output

LTspice uses the metric system so in the example above Garfield stores the induced signal in amps and seconds as in the picture below. This text files in SORIN format are the input for LTspice.

![garf text file with signal data](https://github.com/SergeyNA/GarfTutor/blob/main/img/garf_sig_file_format.png?raw=true)

#### LTspice output

After processing by LTspice we get signal files with the content as in the picture below

![spice text file with signal data](https://github.com/SergeyNA/GarfTutor/blob/main/img/spice_sig_file_format.png?raw=true)

## Mathematical description of the response

Even if we pass completely identical particles through the detector along the same trajectory, we will receive different signals at the output of the electronics due to random processes of the development of an electron avalanche. Therefore, we need to get a mathematical law that will correspond to the answer of the detector. The picture below shows an example of many hundreds of niseless signals from the same tracks.

![spice signal collection](https://github.com/SergeyNA/GarfTutor/blob/main/img/plot_spice_collection.png)

When we have accumulated enough SPICE processed signals we can proceed to the functional description of the detector response. The next step is to add white Gaussian noise to each of these signals. For clarity, we will skip this step. Then we must determine the detector response time for each of these signals. This happens at the moment of crossing the threshold, the value of which we must determine in advance. There are other ways to obtain a response, for example, the time of the signal maximum or the threshold value that is functionally dependent on the amplitude, but as tests show, they lead to a higher error. Therefore, in my analysis, I always used a constant threshold value. The statistics of time crossing for constant threshold is shown in the histogram below.

![hist with blob of spice signal response](https://github.com/SergeyNA/GarfTutor/blob/main/img/time_crossing_hist_fit.png?raw=true)

The better we describe the data of this histogram with a random distribution, the more realistic our representation of the detector response will be. I used the standard functionality provided by the root package for fitting. [Here](https://github.com/SergeyNA/GarfTutor/blob/main/cpp/get_shaper_signal_params.cpp) is a root script capable of building such histograms based on a set of spice signals.

## Parameter values used in my simulation

![hist with blob of spice signal response](https://github.com/SergeyNA/GarfTutor/blob/main/img/paremeter_sheme.png?raw=true)

+ straw diameter: 10 mm
+ anode diameter: 30 mkm
+ high voltage: 1750 V
+ gas mixture: Ar+CO<sub>2</sub> / 70:30 (%)
+ gas temperature: 25 celsius // it's better to use 20 celsius for your simulation
+ gas pressure: 1 atmosphere
+ ionization particle: 1 GeV muon
+ track angle alpha: 90° and 14°
+ Magnetic field: none and 1.5 Tesla along anode wire (z-axis in Garfield coordinates)

## Scripts used in simulation

### Collection of all induced signals to the one plot

[Here](https://github.com/SergeyNA/GarfTutor/blob/main/cpp/get_average_garf_signal.cpp) is a root script wich read N garfield signal files and plot the data on the same 2D hist. The output result is shown in the picture below.

![hist with all induced signal datapoints](https://github.com/SergeyNA/GarfTutor/blob/main/img/garf_sig_collection.png?raw=true)

### Second cluster drift time distribution

[Here](https://github.com/SergeyNA/GarfTutor/blob/main/cpp/get_second_drift_time.cpp) is a root script for parsing garfield output while signals are generated. It analise all [cluster tables](https://github.com/SergeyNA/GarfTutor/blob/main/howto.md#cluster-info) in input file and save second minimal (and minimal too, but do not plot) drift time value for each signal and plot it as shown below. 

![hist with second minimum drift time](https://github.com/SergeyNA/GarfTutor/blob/main/img/second_cluster_drift_time.png?raw=true)

## Repeating the analysis for any tube

If you want to create a response parameterization of straw tube detector using Garfield on a base of my analysis here is step by step instruction:

1. Generate a gas file for your detector's mixture
1. Choose a parameter for parameterization dependence and fixed all another variation values
1. Generate in Garfield statistically enough amount of signals for chosen case
1. Process the received signals in LTspice
1. Determine the detector response in functional form
1. Repeat steps above for each discrete parameter value in p.#2 inside chosen interval
1. Create general parameterization for any value inside chosen interval

## Known Issues

GasGain wrong calc; Missmatch Garfield and Garfield++; Transfer Function for Garfield++; Sigma value for strong magnetic field case is better
