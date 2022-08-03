#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
using namespace std;

int get_shaper_signal_params(string file_name_prefix, int signal_count = 1, string out_prefix = "", int hist_bin_preset = 0)
{
    ifstream filein;
    string filename;

    double h1_l1 = 0., h1_l2 = 5., h1_r1 = 400., h1_r2 = 2500.;
    int h1_b1 = 400, h1_b2 = 200;
    double h4_l = 0, h4_r = 250;
    int h4_b = 50;
    double h5_l = 0, h5_r = 150;
    int h5_b = 50;
    double fit1_l = h4_r * 0.1, fit1_r = h4_r * 0.9;
    double fit2_l = h5_r * 0.1, fit2_r = h5_r * 0.9;

    switch(hist_bin_preset)
    {
        case 1: //1 cm tube; noAngle; noField; 1 mm dist; peaking time 25 nsec
        h4_b = 50;
        h4_l = 0;
        h4_r = 200;

        h5_b = 60;
        h5_l = 0;
        h5_r = 60;

        fit2_l = 10;
        fit2_r = 35;
        break;

        case 2: //1 cm tube; noAngle; noField; 2 mm dist; peaking time 25 nsec
        h4_b = 50;
        h4_l = 25;
        h4_r = 225;

        h5_b = 60;
        h5_l = 15;
        h5_r = 75;

        fit2_l = 25;
        fit2_r = 55;
        break;

        case 3: //1 cm tube; noAngle; noField; 3 mm dist; peaking time 25 nsec
        h4_b = 50;
        h4_l = 50;
        h4_r = 250;

        h5_b = 60;
        h5_l = 40;
        h5_r = 100;

        fit2_l = 50;
        fit2_r = 80;
        break;

        case 4: //1 cm tube; noAngle; noField; 4 mm dist; peaking time 25 nsec
        h4_b = 60;
        h4_l = 50;
        h4_r = 260;

        h5_b = 60;
        h5_l = 80;
        h5_r = 140;

        fit2_l = 90;
        fit2_r = 120;
        break;

        case 5: //1 cm tube; Angle; noField; 1 mm dist; peaking time 25 nsec
        h1_r2 = 4000.;

        h4_b = 50;
        h4_l = 20;
        h4_r = 220;

        h5_b = 60;
        h5_l = 0;
        h5_r = 60;

        fit2_l = 10;
        fit2_r = 25;
        break;

        case 6: //1 cm tube; Angle; noField; 2 mm dist; peaking time 25 nsec
        h1_r2 = 5000.;

        h4_b = 50;
        h4_l = 25;
        h4_r = 225;

        h5_b = 60;
        h5_l = 15;
        h5_r = 75;

        fit2_l = 25;
        fit2_r = 45;
        break;

        case 7: //1 cm tube; Angle; noField; 3 mm dist; peaking time 25 nsec
        h1_r2 = 6000.;

        h4_b = 50;
        h4_l = 50;
        h4_r = 250;

        h5_b = 60;
        h5_l = 40;
        h5_r = 100;

        fit2_l = 50;
        fit2_r = 70;
        break;

        case 8: //1 cm tube; Angle; noField; 4 mm dist; peaking time 25 nsec
        h1_r2 = 7000.;

        h4_b = 60;
        h4_l = 50;
        h4_r = 260;

        h5_b = 60;
        h5_l = 80;
        h5_r = 140;

        fit2_l = 90;
        fit2_r = 110;
        break;

        case 9: //1 cm tube; noAngle; Field; 1 mm dist; peaking time 25 nsec
        h1_r2 = 3000.;

        h4_b = 50;
        h4_l = 40;
        h4_r = 240;

        h5_b = 60;
        h5_l = 0;
        h5_r = 60;

        fit2_l = 14;
        fit2_r = 40;
        break;

        case 10: //1 cm tube; noAngle; Field; 2 mm dist; peaking time 25 nsec
        h1_r2 = 3000.;

        h4_b = 50;
        h4_l = 60;
        h4_r = 260;

        h5_b = 60;
        h5_l = 20;
        h5_r = 80;

        fit2_l = 30;
        fit2_r = 60;
        break;

        case 11: //1 cm tube; noAngle; Field; 3 mm dist; peaking time 25 nsec
        h1_r2 = 3000.;

        h4_b = 50;
        h4_l = 90;
        h4_r = 290;

        h5_b = 60;
        h5_l = 50;
        h5_r = 110;

        fit2_l = 60;
        fit2_r = 95;
        break;

        case 12: //1 cm tube; noAngle; Field; 4 mm dist; peaking time 25 nsec
        h1_r2 = 3000.;

        h4_b = 50;
        h4_l = 110;
        h4_r = 310;

        h5_b = 60;
        h5_l = 110;
        h5_r = 170;

        fit2_l = 115;
        fit2_r = 145;
        break;

        case 13: //1 cm tube; Angle; Field; 1 mm dist; peaking time 25 nsec
        h1_r2 = 7000.;

        h4_b = 50;
        h4_l = 40;
        h4_r = 240;

        h5_b = 60;
        h5_l = 0;
        h5_r = 60;

        fit2_l = 14;
        fit2_r = 25;
        break;

        case 14: //1 cm tube; Angle; Field; 2 mm dist; peaking time 25 nsec
        h1_r2 = 7000.;

        h4_b = 50;
        h4_l = 60;
        h4_r = 260;

        h5_b = 60;
        h5_l = 20;
        h5_r = 80;

        fit2_l = 30;
        fit2_r = 44;
        break;

        case 15: //1 cm tube; Angle; Field; 3 mm dist; peaking time 25 nsec
        h1_r2 = 7000.;

        h4_b = 50;
        h4_l = 90;
        h4_r = 290;

        h5_b = 60;
        h5_l = 50;
        h5_r = 110;

        fit2_l = 60;
        fit2_r = 80;
        break;


        case 16: //1 cm tube; Angle; Field; 4 mm dist; peaking time 25 nsec
        h1_r2 = 7000.;

        h4_b = 50;
        h4_l = 110;
        h4_r = 310;

        h5_b = 60;
        h5_l = 110;
        h5_r = 170;

        fit2_l = 113;
        fit2_r = 130;
        break;
    }

    TH2D signal_collection("SPICE_signals", "Garfield+LTSpice signals;Time [nsec];Amplitude [mV]", h1_b1, h1_l1, h1_r1, h1_b2, h1_l2, h1_r2); //h1
    TH1D time_of_signal_max("time_distr", "Time of signal extremum;Time [nsec]", h4_b, h4_l, h4_r); //h4
    TH1D time_of_low_threshold("time_distr2", "Moment of 10 mV crossing;Time [nsec]", h5_b, h5_l, h5_r); //h5

    for(int sigN = 1; sigN <= signal_count; sigN++)
    {
        filename = file_name_prefix + std::to_string(sigN) + ".sig.csv";
        filein.open(filename.c_str(), ios::in);
        if(!filein.is_open())
        {
            cout << "File <<" << filename << ">> not open!" << endl;
            return 0;
        }

        string line;
        getline(filein, line);
        getline(filein, line);

        double time, current, voltage;
        double signal_max = -1, signal_max_time = 0;
        bool thr_rec = false;

        while(!filein.eof())
        {
            filein >> time >> current >> voltage;
            //cout << "Signal #" << sigN << "   time: " << time*1000000000 << "   voltage: " << voltage*1000 << endl;

            signal_collection.Fill(time*1000000000, voltage*1000);

            if(signal_max < voltage)
            {
                signal_max = voltage;
                signal_max_time = time;
            }

            if(!thr_rec)
            {
                if(voltage > 0.01)
                {
                    time_of_low_threshold.Fill(time*1000000000);
                    //cout << "Signal #" << sigN << "   time for low thr crossing: " << time*1000000000 << endl;
                    thr_rec = true;
                }
            }
        }

        time_of_signal_max.Fill(signal_max_time*1000000000);
        //cout << "Signal #" << sigN << "   time for signal extremum: " << signal_max_time*1000000000 << endl << endl;

        filein.close();
        filein.clear();
    }

    auto canv = new TCanvas("canv", "Find average output", 300, 150, 1000, 600);
    //canv->SetFillColor(42);
    //canv->SetGrid();
    //canv->GetFrame()->SetFillColor(21);
    //canv->GetFrame()->SetBorderSize(12);
    //canv->SetLogy();
    gStyle->SetOptStat(0);

    signal_collection.Draw("COL");
    canv->Update();
    filename = out_prefix + "_allSig.pdf";
    canv->SaveAs(filename.c_str());

    gStyle->SetOptStat(1110);
    gStyle->SetOptFit(1111);
    gStyle->SetStatX(0.95);
    gStyle->SetStatY(0.92);
    canv->SetGrid(0, 0);

    time_of_signal_max.Draw();
    //auto fit1 = new TF1("fit_red1","gaus", fit1_l, fit1_r);
    //fit1->SetLineColor(6);
    //fit1->SetLineWidth(3);
    //time_of_signal_max.Fit(fit1, "R");
    canv->Update();
    filename = out_prefix + "_maxOfSig.pdf";
    canv->SaveAs(filename.c_str());

    time_of_low_threshold.Draw();
    auto fit2 = new TF1("fit_red2","gaus", fit2_l, fit2_r);
    //fit2->SetLineColor(6);
    fit2->SetLineWidth(3);
    time_of_low_threshold.Fit(fit2, "R");
    canv->Update();
    filename = out_prefix + "_thrCross.pdf";
    canv->SaveAs(filename.c_str());

    return 0;
}
