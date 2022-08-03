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
     23 -0.15569E+00  0.30000E+00  0.46378E-06  0.67832E-01  0.22148E-02     1  Hit S wire 1, read out    
                                                                                   1  0.66456E-01  0.11268E+04
     24 -0.15429E+00  0.29996E+00  0.35738E-04  0.67567E-01  0.22054E-02     1  Hit S wire 1, read out    
                                                                                   1  0.71520E-01  0.59606E+05
     25 -0.15430E+00  0.29993E+00  0.71492E-04  0.67561E-01  0.22090E-02     1  Hit S wire 1, read out    
                                                                                   1  0.71588E-01  0.79793E+03
     26 -0.15431E+00  0.29989E+00  0.10724E-03  0.67785E-01  0.21972E-02     1  Hit S wire 1, read out    
                                                                                   1  0.65821E-01  0.12013E+05
     27 -0.15432E+00  0.29986E+00  0.14299E-03  0.67533E-01  0.22056E-02     1  Hit S wire 1, read out    
                                                                                   1  0.68352E-01  0.16955E+05
     28 -0.15433E+00  0.29982E+00  0.17873E-03  0.67526E-01  0.22047E-02     1  Hit S wire 1, read out    
                                                                                   1  0.63936E-01  0.47475E+04
     29 -0.15428E+00  0.29996E+00  0.10711E-04  0.67604E-01  0.22120E-02     1  Hit S wire 1, read out    
                                                                                   1  0.66404E-01  0.10833E+04
     30 -0.15427E+00  0.29991E+00  0.21441E-04  0.67546E-01  0.22054E-02     1  Hit S wire 1, read out    
                                                                                   1  0.66323E-01  0.18396E+05
     31 -0.15427E+00  0.29987E+00  0.32170E-04  0.67539E-01  0.22050E-02     1  Hit S wire 1, read out    
                                                                                   1  0.65209E-01  0.25136E+05
     32 -0.15427E+00  0.29983E+00  0.42898E-04  0.67517E-01  0.22043E-02     1  Hit S wire 1, read out    
                                                                                   1  0.63459E-01  0.71683E+04
     33 -0.15426E+00  0.29978E+00  0.53624E-04  0.67586E-01  0.22023E-02     1  Hit S wire 1, read out    
                                                                                   1  0.64775E-01  0.69691E+04
     34 -0.15426E+00  0.29974E+00  0.64349E-04  0.67485E-01  0.22036E-02     1  Hit S wire 1, read out    
                                                                                   1  0.70592E-01  0.16368E+05
     35 -0.15426E+00  0.29970E+00  0.75072E-04  0.67469E-01  0.22021E-02     1  Hit S wire 1, read out    
                                                                                   1  0.66799E-01  0.16477E+05
     36 -0.15425E+00  0.29965E+00  0.85792E-04  0.67452E-01  0.22025E-02     1  Hit S wire 1, read out    
                                                                                   1  0.64602E-01  0.93329E+04
     37 -0.15425E+00  0.29961E+00  0.96508E-04  0.67458E-01  0.22029E-02     1  Hit S wire 1, read out    
                                                                                   1  0.65915E-01  0.26685E+05
     38 -0.13013E+00  0.30000E+00 -0.39210E-05  0.63626E-01  0.20937E-02     1  Hit S wire 1, read out    
                                                                                   1  0.66288E-01  0.11065E+05
     39 -0.90000E-01  0.30000E+00  0.31097E-06  0.58631E-01  0.19434E-02     1  Hit S wire 1, read out    
                                                                                   1  0.58643E-01  0.13539E+05
     40 -0.40563E-01  0.30002E+00  0.18824E-04  0.55048E-01  0.18377E-02     1  Hit S wire 1, read out    
                                                                                   1  0.56969E-01  0.26978E+04
     41 -0.40561E-01  0.30003E+00  0.37675E-04  0.55056E-01  0.18378E-02     1  Hit S wire 1, read out    
                                                                                   1  0.55088E-01  0.26651E+04
     42 -0.40559E-01  0.30005E+00  0.56529E-04  0.55054E-01  0.18388E-02     1  Hit S wire 1, read out    
                                                                                   1  0.57172E-01  0.26819E+04
     43 -0.40522E-01  0.29999E+00  0.28834E-05  0.55038E-01  0.18364E-02     1  Hit S wire 1, read out    
                                                                                   1  0.50073E-01  0.79592E+04
     44 -0.40479E-01  0.29998E+00  0.57911E-05  0.55030E-01  0.18371E-02     1  Hit S wire 1, read out    
                                                                                   1  0.51311E-01  0.14627E+05
     45 -0.40435E-01  0.29996E+00  0.86987E-05  0.55023E-01  0.18382E-02     1  Hit S wire 1, read out    
                                                                                   1  0.57440E-01  0.98062E+04
     46 -0.40392E-01  0.29995E+00  0.11606E-04  0.55024E-01  0.18357E-02     1  Hit S wire 1, read out    
                                                                                   1  0.51313E-01  0.10797E+05
     47 -0.40348E-01  0.29994E+00  0.14513E-04  0.55014E-01  0.18363E-02     1  Hit S wire 1, read out    
                                                                                   1  0.55626E-01  0.20356E+05
     48 -0.40305E-01  0.29993E+00  0.17420E-04  0.55086E-01  0.18362E-02     1  Hit S wire 1, read out    
                                                                                   1  0.54340E-01  0.80337E+04
     49 -0.40261E-01  0.29992E+00  0.20327E-04  0.55002E-01  0.18357E-02     1  Hit S wire 1, read out    
                                                                                   1  0.53343E-01  0.22254E+05
     50 -0.40218E-01  0.29991E+00  0.23233E-04  0.55001E-01  0.18371E-02     1  Hit S wire 1, read out    
                                                                                   1  0.54473E-01  0.27527E+05
     51  0.19590E-01  0.30000E+00  0.86018E-06  0.54346E-01  0.18139E-02     1  Hit S wire 1, read out    
                                                                                   1  0.52218E-01  0.30169E+05
     52  0.32751E-01  0.30000E+00  0.25226E-05  0.54724E-01  0.18260E-02     1  Hit S wire 1, read out    
                                                                                   1  0.53855E-01  0.14532E+05
     53  0.72485E-01  0.30000E+00 -0.67269E-06  0.57038E-01  0.18976E-02     1  Hit S wire 1, read out    
                                                                                   1  0.57212E-01  0.24794E+04
     54  0.15869E+00  0.30000E+00 -0.28532E-06  0.68384E-01  0.22332E-02     1  Hit S wire 1, read out    
                                                                                   1  0.69489E-01  0.29709E+04
     55  0.20018E+00  0.30023E+00  0.36271E-03  0.77244E-01  0.24722E-02     1  Hit S wire 1, read out    
                                                                                   1  0.73700E-01  0.86105E+04
     56  0.20018E+00  0.30046E+00  0.72547E-03  0.77324E-01  0.24744E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74069E-01  0.19276E+04
     57  0.20018E+00  0.30069E+00  0.10882E-02  0.77427E-01  0.24840E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77283E-01  0.10009E+05
     58  0.20018E+00  0.30092E+00  0.14510E-02  0.77487E-01  0.24795E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77551E-01  0.44920E+04
     59  0.20018E+00  0.30115E+00  0.18138E-02  0.77567E-01  0.24815E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75847E-01  0.21980E+04
     60  0.20018E+00  0.30137E+00  0.21766E-02  0.77653E-01  0.24830E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78203E-01  0.49490E+04
     61  0.20018E+00  0.30160E+00  0.25394E-02  0.77744E-01  0.24902E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79923E-01  0.25371E+05
     62  0.20018E+00  0.30183E+00  0.29023E-02  0.77828E-01  0.24872E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74729E-01  0.37684E+05
     63  0.20018E+00  0.30258E+00  0.40900E-02  0.78092E-01  0.24963E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77369E-01  0.14359E+05
     64  0.20011E+00  0.30270E+00  0.42667E-02  0.78115E-01  0.24957E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78118E-01  0.12501E+05
     65  0.20004E+00  0.30281E+00  0.44434E-02  0.78134E-01  0.24971E-02     1  Hit S wire 1, read out    
                                                                                   1  0.72611E-01  0.88993E+04
     66  0.19997E+00  0.30292E+00  0.46202E-02  0.78164E-01  0.25000E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78492E-01  0.16814E+04
     67  0.19989E+00  0.30304E+00  0.47969E-02  0.78185E-01  0.24990E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79164E-01  0.19445E+05
     68  0.19955E+00  0.30332E+00  0.46180E-02  0.78206E-01  0.24992E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80029E-01  0.99271E+03
     69  0.19921E+00  0.30360E+00  0.44391E-02  0.78228E-01  0.24991E-02     1  Hit S wire 1, read out    
                                                                                   1  0.73412E-01  0.11172E+04
     70  0.19896E+00  0.30391E+00  0.45133E-02  0.78278E-01  0.25002E-02     1  Hit S wire 1, read out    
                                                                                   1  0.81048E-01  0.10538E+05
     71  0.19871E+00  0.30423E+00  0.45875E-02  0.78334E-01  0.25019E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78916E-01  0.45305E+05
     72  0.19846E+00  0.30454E+00  0.46616E-02  0.78406E-01  0.25087E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80010E-01  0.36901E+05
     73  0.19830E+00  0.30464E+00  0.47952E-02  0.78390E-01  0.25032E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74141E-01  0.37524E+04
     74  0.19814E+00  0.30474E+00  0.49287E-02  0.78392E-01  0.25048E-02     1  Hit S wire 1, read out    
                                                                                   1  0.82294E-01  0.80135E+04
     75  0.19798E+00  0.30484E+00  0.50623E-02  0.78544E-01  0.25001E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78326E-01  0.38573E+03
     76  0.19782E+00  0.30494E+00  0.51959E-02  0.78389E-01  0.25051E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79999E-01  0.72039E+04
     77  0.19766E+00  0.30504E+00  0.53294E-02  0.78387E-01  0.25038E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74764E-01  0.91604E+04
     78  0.19750E+00  0.30514E+00  0.54630E-02  0.78539E-01  0.24992E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79380E-01  0.42029E+05
     79  0.19734E+00  0.30524E+00  0.55965E-02  0.78388E-01  0.25079E-02     1  Hit S wire 1, read out    
                                                                                   1  0.73794E-01  0.77503E+04
     80  0.19718E+00  0.30534E+00  0.57301E-02  0.78462E-01  0.25019E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77777E-01  0.28396E+04
     81  0.19702E+00  0.30544E+00  0.58636E-02  0.78568E-01  0.24977E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79925E-01  0.72079E+03
     82  0.19686E+00  0.30554E+00  0.59972E-02  0.78382E-01  0.25039E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78237E-01  0.40487E+05
     83  0.19667E+00  0.30565E+00  0.61486E-02  0.78377E-01  0.25033E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77233E-01  0.10277E+05
     84  0.19649E+00  0.30576E+00  0.63000E-02  0.78372E-01  0.25039E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79246E-01  0.31487E+05
     85  0.19631E+00  0.30588E+00  0.64513E-02  0.78388E-01  0.25035E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80248E-01  0.10579E+05
     86  0.19613E+00  0.30599E+00  0.66027E-02  0.78369E-01  0.25034E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75904E-01  0.10185E+05
     87  0.19595E+00  0.30610E+00  0.67541E-02  0.78370E-01  0.25034E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74168E-01  0.11842E+05
     88  0.19577E+00  0.30621E+00  0.69055E-02  0.78378E-01  0.25026E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79595E-01  0.18309E+05
     89  0.19558E+00  0.30633E+00  0.70568E-02  0.78369E-01  0.25033E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79212E-01  0.18115E+05
     90  0.19548E+00  0.30639E+00  0.71436E-02  0.78369E-01  0.25046E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77862E-01  0.11601E+05
     91  0.19538E+00  0.30646E+00  0.72304E-02  0.78363E-01  0.25025E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77458E-01  0.15880E+02
     92  0.19523E+00  0.30635E+00  0.72723E-02  0.78292E-01  0.25022E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77230E-01  0.51384E+04
     93  0.19508E+00  0.30624E+00  0.73142E-02  0.78218E-01  0.25007E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80277E-01  0.21277E+04
     94  0.19493E+00  0.30614E+00  0.73561E-02  0.78139E-01  0.24974E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77843E-01  0.16602E+05
     95  0.19478E+00  0.30603E+00  0.73980E-02  0.78090E-01  0.24957E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78514E-01  0.53046E+05
     96  0.19463E+00  0.30593E+00  0.74399E-02  0.78008E-01  0.24943E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79179E-01  0.23858E+04
     97  0.19448E+00  0.30582E+00  0.74818E-02  0.78050E-01  0.24868E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79080E-01  0.20392E+05
     98  0.19433E+00  0.30572E+00  0.75237E-02  0.77848E-01  0.24889E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79666E-01  0.43631E+04
     99  0.19418E+00  0.30561E+00  0.75656E-02  0.77777E-01  0.24868E-02     1  Hit S wire 1, read out    
                                                                                   1  0.73841E-01  0.20692E+03
    100  0.19394E+00  0.30544E+00  0.76338E-02  0.77654E-01  0.24830E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77967E-01  0.38607E+04
    101  0.19370E+00  0.30527E+00  0.77019E-02  0.77533E-01  0.24808E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78466E-01  0.13381E+05
    102  0.19345E+00  0.30510E+00  0.77701E-02  0.77418E-01  0.24771E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79277E-01  0.25363E+03
    103  0.19321E+00  0.30492E+00  0.78382E-02  0.77303E-01  0.24743E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77271E-01  0.35615E+05
    104  0.19299E+00  0.30477E+00  0.78998E-02  0.77385E-01  0.24658E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80307E-01  0.26514E+05
    105  0.19277E+00  0.30461E+00  0.79614E-02  0.77088E-01  0.24715E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78560E-01  0.18810E+04
    106  0.19278E+00  0.30503E+00  0.77234E-02  0.77240E-01  0.24727E-02     1  Hit S wire 1, read out    
                                                                                   1  0.81015E-01  0.37242E+05
    107  0.19279E+00  0.30545E+00  0.74853E-02  0.77389E-01  0.24795E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75943E-01  0.16084E+05
    108  0.19279E+00  0.30558E+00  0.74080E-02  0.77443E-01  0.24775E-02     1  Hit S wire 1, read out    
                                                                                   1  0.72136E-01  0.76039E+04
    109  0.19271E+00  0.30563E+00  0.73261E-02  0.77441E-01  0.24788E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74045E-01  0.12671E+05
    110  0.19262E+00  0.30568E+00  0.72442E-02  0.77448E-01  0.24802E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77280E-01  0.17770E+05
    111  0.19254E+00  0.30572E+00  0.71622E-02  0.77436E-01  0.24781E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75716E-01  0.80771E+04
    112  0.19245E+00  0.30577E+00  0.70803E-02  0.77436E-01  0.24789E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79793E-01  0.22820E+05
    113  0.19237E+00  0.30582E+00  0.69984E-02  0.77439E-01  0.24771E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80445E-01  0.40487E+05
    114  0.19228E+00  0.30586E+00  0.69165E-02  0.77438E-01  0.24809E-02     1  Hit S wire 1, read out    
                                                                                   1  0.82107E-01  0.30430E+05
    115  0.19220E+00  0.30591E+00  0.68346E-02  0.77424E-01  0.24792E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74756E-01  0.76780E+04
    116  0.19211E+00  0.30596E+00  0.67526E-02  0.77418E-01  0.25086E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78876E-01  0.72977E+04
    117  0.19203E+00  0.30601E+00  0.66707E-02  0.77430E-01  0.24981E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79562E-01  0.18449E+05
    118  0.19194E+00  0.30605E+00  0.65888E-02  0.77424E-01  0.24790E-02     1  Hit S wire 1, read out    
                                                                                   1  0.74074E-01  0.70123E+04
    119  0.19186E+00  0.30610E+00  0.65069E-02  0.77405E-01  0.25090E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79124E-01  0.44306E+04
    120  0.19177E+00  0.30615E+00  0.64250E-02  0.77415E-01  0.24768E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75482E-01  0.19347E+04
    121  0.19169E+00  0.30619E+00  0.63431E-02  0.77412E-01  0.24781E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78529E-01  0.46781E+04
    122  0.19160E+00  0.30624E+00  0.62611E-02  0.77414E-01  0.24788E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76915E-01  0.11777E+05
    123  0.19152E+00  0.30629E+00  0.61792E-02  0.77410E-01  0.24793E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75604E-01  0.56463E+04
    124  0.19143E+00  0.30634E+00  0.60973E-02  0.77406E-01  0.24766E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77534E-01  0.17858E+05
    125  0.19135E+00  0.30638E+00  0.60154E-02  0.77403E-01  0.24772E-02     1  Hit S wire 1, read out    
                                                                                   1  0.81213E-01  0.10907E+05
    126  0.19126E+00  0.30643E+00  0.59335E-02  0.77404E-01  0.24778E-02     1  Hit S wire 1, read out    
                                                                                   1  0.79661E-01  0.46121E+05
    127  0.19118E+00  0.30648E+00  0.58516E-02  0.77402E-01  0.24769E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77973E-01  0.76140E+04
    128  0.19109E+00  0.30652E+00  0.57696E-02  0.77383E-01  0.24835E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77766E-01  0.36538E+05
    129  0.19100E+00  0.30657E+00  0.56877E-02  0.77395E-01  0.24761E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76946E-01  0.13890E+05
    130  0.19092E+00  0.30662E+00  0.56058E-02  0.77394E-01  0.24759E-02     1  Hit S wire 1, read out    
                                                                                   1  0.72672E-01  0.10784E+05
    131  0.19083E+00  0.30667E+00  0.55239E-02  0.77392E-01  0.24765E-02     1  Hit S wire 1, read out    
                                                                                   1  0.82164E-01  0.19940E+05
    132  0.19075E+00  0.30671E+00  0.54420E-02  0.77389E-01  0.24757E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76988E-01  0.14730E+05
    133  0.19066E+00  0.30676E+00  0.53601E-02  0.77387E-01  0.24766E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80569E-01  0.91776E+04
    134  0.19058E+00  0.30681E+00  0.52782E-02  0.77386E-01  0.24766E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76563E-01  0.36065E+05
    135  0.19049E+00  0.30685E+00  0.51962E-02  0.77382E-01  0.24774E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77878E-01  0.96392E+04
    136  0.19041E+00  0.30690E+00  0.51143E-02  0.77812E-01  0.24670E-02     1  Hit S wire 1, read out    
                                                                                   1  0.73691E-01  0.41552E+05
    137  0.19032E+00  0.30695E+00  0.50324E-02  0.77380E-01  0.24765E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75749E-01  0.23979E+05
    138  0.19024E+00  0.30699E+00  0.49505E-02  0.77396E-01  0.24774E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78431E-01  0.67844E+04
    139  0.19015E+00  0.30704E+00  0.48686E-02  0.77379E-01  0.24768E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78927E-01  0.45371E+04
    140  0.19007E+00  0.30709E+00  0.47867E-02  0.77504E-01  0.24728E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75985E-01  0.46420E+04
    141  0.18998E+00  0.30714E+00  0.47048E-02  0.77375E-01  0.24759E-02     1  Hit S wire 1, read out    
                                                                                   1  0.75235E-01  0.17296E+03
    142  0.18990E+00  0.30718E+00  0.46229E-02  0.77368E-01  0.24763E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78599E-01  0.10149E+05
    143  0.18981E+00  0.30723E+00  0.45410E-02  0.77366E-01  0.24756E-02     1  Hit S wire 1, read out    
                                                                                   1  0.78864E-01  0.93648E+03
    144  0.18973E+00  0.30728E+00  0.44591E-02  0.77370E-01  0.24754E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76971E-01  0.70468E+04
    145  0.18964E+00  0.30732E+00  0.43772E-02  0.77363E-01  0.24763E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80282E-01  0.18659E+05
    146  0.18956E+00  0.30737E+00  0.42953E-02  0.77360E-01  0.24757E-02     1  Hit S wire 1, read out    
                                                                                   1  0.77358E-01  0.24698E+05
    147  0.18947E+00  0.30742E+00  0.42134E-02  0.77357E-01  0.24752E-02     1  Hit S wire 1, read out    
                                                                                   1  0.83195E-01  0.67797E+04
    148  0.20703E+00  0.30000E+00  0.38653E-05  0.78830E-01  0.25191E-02     1  Hit S wire 1, read out    
                                                                                   1  0.76716E-01  0.35163E+04
    149  0.20899E+00  0.30000E+00  0.11780E-06  0.79314E-01  0.25291E-02     1  Hit S wire 1, read out    
                                                                                   1  0.80167E-01  0.22169E+05
    150  0.23218E+00  0.29999E+00 -0.18712E-04  0.85501E-01  0.26859E-02     1  Hit S wire 1, read out    
                                                                                   1  0.89532E-01  0.24419E+04
    151  0.23219E+00  0.29999E+00 -0.37389E-04  0.85502E-01  0.26864E-02     1  Hit S wire 1, read out    
                                                                                   1  0.86071E-01  0.18746E+05
    152  0.23220E+00  0.29998E+00 -0.56065E-04  0.85634E-01  0.26833E-02     1  Hit S wire 1, read out    
                                                                                   1  0.85245E-01  0.48266E+04
    153  0.23221E+00  0.29998E+00 -0.74742E-04  0.85502E-01  0.26856E-02     1  Hit S wire 1, read out    
                                                                                   1  0.82965E-01  0.33120E+03
    154  0.23217E+00  0.29992E+00  0.32845E-04  0.85470E-01  0.26853E-02     1  Hit S wire 1, read out    
                                                                                   1  0.88183E-01  0.97077E+04
    155  0.23217E+00  0.29985E+00  0.65723E-04  0.85434E-01  0.26849E-02     1  Hit S wire 1, read out    
                                                                                   1  0.87705E-01  0.79373E+03
    156  0.23217E+00  0.29977E+00  0.98596E-04  0.85410E-01  0.26848E-02     1  Hit S wire 1, read out    
                                                                                   1  0.85347E-01  0.37536E+04
    157  0.23216E+00  0.29969E+00  0.13146E-03  0.85379E-01  0.26832E-02     1  Hit S wire 1, read out    
                                                                                   1  0.90580E-01  0.13175E+05
    158  0.23216E+00  0.29961E+00  0.16432E-03  0.85355E-01  0.26833E-02     1  Hit S wire 1, read out    
                                                                                   1  0.83979E-01  0.33017E+05
    159  0.23216E+00  0.29954E+00  0.19717E-03  0.85322E-01  0.26815E-02     1  Hit S wire 1, read out    
                                                                                   1  0.86908E-01  0.55543E+04
    160  0.25158E+00  0.30000E+00  0.10675E-05  0.91238E-01  0.28250E-02     1  Hit S wire 1, read out    
                                                                                   1  0.93435E-01  0.61510E+04
    161  0.25422E+00  0.30002E+00 -0.68248E-05  0.92069E-01  0.28450E-02     1  Hit S wire 1, read out    
                                                                                   1  0.94520E-01  0.89930E+04
    162  0.31789E+00  0.29999E+00 -0.98750E-05  0.11489E+00  0.33496E-02     1  Hit S wire 1, read out    
                                                                                   1  0.11292E+00  0.30702E+04
    163  0.33371E+00  0.30000E+00  0.72267E-06  0.12148E+00  0.34895E-02     1  Hit S wire 1, read out    
                                                                                   1  0.11861E+00  0.15396E+04
    164  0.52666E+00  0.30000E+00  0.98189E-05  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
    165  0.52666E+00  0.29999E+00  0.19687E-04  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
    166  0.52666E+00  0.29999E+00  0.29555E-04  0.00000E+00  0.00000E+00     1  Hit the tube, not read out
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

##  Repeating the analysis for any tube

If you want to create a response parameterization of straw tube detector using Garfield on a base of my analysis here is step by step instruction:

1. Generate a gas file for your detector's mixture
1. Choose a parameter for parameterization dependence and fixed all another variation values
1. Generate in Garfield statistically enough amount of signals for chosen case
1. Process the received signals in LTspice
1. Determine the detector response in functional form
1. Repeat steps above for each discrete parameter value in p.#2 inside chosen interval
1. Create general parameterization for any value inside chosen interval

## Known Issues

GasGain wrong calc; Missmatch Garfield and Garfield++; Transfer Function for Garfield++
