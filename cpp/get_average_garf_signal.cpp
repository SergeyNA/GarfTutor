#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
using namespace std;

int get_average_garf_signal(string file_name_prefix, int signal_count = 1, double hist_y_bot_edge = 0, double hist_y_top_edge = 20, double hist_x_left_edge = 0.01, double hist_x_right_edge = 250.01)
{
    ifstream filein;
    string filename;

    const int sig_record_bins = 1000;
    vector<double> time_av(sig_record_bins);
    vector<double> signal_av(sig_record_bins);
    for(int i = 0; i < sig_record_bins; i++)
    {
        time_av[i] = i * (hist_x_right_edge - 0.01) / sig_record_bins;
        signal_av[i] = 0;
    }

    TH2D signal_collection("signals", "Garfield signals;Time [nsec];Current [#muA]", sig_record_bins, hist_x_left_edge, hist_x_right_edge, 100, hist_y_bot_edge, hist_y_top_edge);

    for(int sigN = 1; sigN <= signal_count; sigN++)
    {
        filename = file_name_prefix + std::to_string(sigN) + ".sig";
        filein.open(filename.c_str(), ios::in);
        if(!filein.is_open())
        {
            cout << "File <<" << filename << ">> not open!" << endl;
            return 0;
        }

        double time, current;

        for(int record = 0; record < sig_record_bins; record++)
        {
            filein >> time >> current;
            signal_collection.Fill(time*1000000000, -current*1000000);
            //cout << "Signal #" << sigN << "   time: " << time*1000000000 << "   current: " << current*1000000 << endl;
            signal_av[record] -= current*1000000;
        }

        filein.close();
        filein.clear();
    }

    //TFile save_hist("signals_store.root", "recreate");
    //signal_collection.Write();

    auto canv = new TCanvas("canv", "Find average signal", 300, 150, 1000, 600);
    //canv->SetFillColor(42);
    //canv->SetGrid();
    //canv->GetFrame()->SetFillColor(21);
    //canv->GetFrame()->SetBorderSize(12);
    //canv->SetLogy();
    gStyle->SetOptStat(0);

    signal_collection.Draw("COL");

    for( int i = 0; i < signal_av.size(); ++i ) {signal_av[i] /= signal_count;}
    auto signal_average = new TGraphErrors(time_av.size(), time_av.data(), signal_av.data(), nullptr, nullptr);
    //signal_average->SetMarkerColor(2);
    //signal_average->SetMarkerStyle(8);
    //signal_average->SetMarkerSize(1.);
    signal_average->SetLineColor(2);
    signal_average->SetLineWidth(2);
    signal_average->Draw("SAMEL");

    canv->Update();
    canv->SaveAs("garf_signals_collection.pdf");

    return 0;
}
