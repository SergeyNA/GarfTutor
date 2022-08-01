# GarfTutor

Welcome to the my handmade instruction for using old fortran-based version of Garfield. All examples here oriented on usage my analysis for parameterization of straw tube response in SPD experiment.

## Getting started

I'm assuming you already have Garfield and CERN root packages installed. My version is 7.45 (Magboltz 7.08) for Garfield and 6.24/06 for ROOT but I think that examples here should work well in any future (and many previous) versions. Also I am using signals processed in LTspice but asking my colleagues for help with this. So if you want to completely repeat the examples here you should be able to use LTspice package too.

## General Garfield info

#### Garfield help pages

The old version of Garfield has a very detailed manual for all supported commands. Just in case, here are a couple of links to the same thing:

[official Garfield help](https://garfield.web.cern.ch/help/)
[alternative source for link above](https://cmd.inp.nsk.su/old/cmd2/manuals/cernlib/garfield/help/garfield.html)

#### Running Garfield in batch mode

Use `garfield-9` command for running interactive Garfield interface. But I prefer batch compatible mode with the following syntax:

``` fortran
garfield-9 < File_name_with_list_of_Garfield_instructions > File_name_with_Garfield_output_log
```

#### Gas file creation

Before run any calculation in `&DRIFT` or `&SIGNAL` sections One should fill gas properties tables. There is many ways how to do it includint runtime calculations but I recommend using a pre-generated gas file with the required information

## Known Issues

Missmatch Garfield and Garfield++; Transfer Function for Garfield++
