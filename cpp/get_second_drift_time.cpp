#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
using namespace std;

int get_second_drift_time(string file_name, float left_hist_edge = 0, float right_hist_edge = 120, float left_fit_edge = 5, float right_fit_edge = 100, bool is_magnet = false)
{
    ifstream filein;
    filein.open(file_name.c_str(), ios::in);
    if(!filein.is_open())
    {
        cout<<"File not open!"<<endl;
        return 0;
    }

    Float_t dr_time;
    const string start_signal_signature = "  Signal simulation:";
    const string partial_signal_signature = " simulation:";
    string temp_word;
    float min_time, second_time;

    TH1F time_distr("Second_cluster_drift_time", "temp_name", 100, left_hist_edge, right_hist_edge);
    if(is_magnet)
        time_distr.SetTitle("second cluster drift time, max field;arrival_time [nsec]");
    else
        time_distr.SetTitle("second cluster drift time, zero field;arrival_time [nsec]");

    int track_counter = 0;
    for (string line; getline(filein, line); )
    {
        //if(time_distr.GetEntries() > 604) {cout<<"TEMP OUT line: "<<line<<endl;}
        if(line == start_signal_signature || line == partial_signal_signature) {
            min_time = 1000;
            second_time = 2000;
            for(int i = 0; i < 19; i++) getline(filein, line);

            filein >> temp_word;
            //if(time_distr.GetEntries() > 604) {cout<<"TEMP OUT word: "<<temp_word<<endl;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            if(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
            int counter = 0;
            while(true)
            {
                filein >> dr_time >> dr_time >> dr_time >> dr_time;
                //if(time_distr.GetEntries() > 604) {cout<<"TEMP OUT whiletrue: "<<temp_word<<endl;}
                //std::cout << "cluster number: " << temp_word << " drift_time: " << dr_time << endl;
                getline(filein, line);
                if(dr_time > 0 && dr_time < 200)
                {
                    getline(filein, line);
                    if(dr_time < min_time) {second_time = min_time; min_time = dr_time;}
                    if(dr_time < second_time && dr_time > min_time) second_time = dr_time;
                }
                filein >> temp_word;
                if(temp_word == "------" || temp_word == "Signal") break;
                if(temp_word == "1" || temp_word == "neBEM")
                {
                    //cout<<"AAAAAAAAA!!!!!!!!!!!!!!!!!!";
                    getline(filein, line);
                    filein >> temp_word;
                }
                while(temp_word == "!!!!!!") {getline(filein, line); filein >> temp_word;}
                if(++counter > 1000) break;
            }
            time_distr.Fill(second_time*1000);
            cout<<"MDT in #" << time_distr.GetEntries() <<" SIGNAL: " << min_time*1000 << " nsec; second time: " << 1000*second_time << " nsec" << endl;
        }
        //if(time_distr.GetEntries() == 3) break;
        //if(line == start_signal_signature) {
        //    cout<<"Find signal #"<< ++track_counter <<endl;
        //}
    }

    TFile save_hist("dr_time_store.root", "recreate");
    time_distr.Write();

    auto canv = new TCanvas("canv", "Find time resolution of second cluster arrival time", 300, 150, 1000, 600);
    //canv->SetFillColor(42);
    //canv->SetGrid();
    //canv->GetFrame()->SetFillColor(21);
    //canv->GetFrame()->SetBorderSize(12);
    //time_distr.SetTitle(filename.c_str());
    //time_distr.SetMarkerColor(2);
    //time_distr.SetMarkerStyle(8);
    //time_distr.SetMarkerSize(0.8);
    time_distr.SetLineColor(4);
    time_distr.SetLineWidth(2);
    //time_distr.GetXaxis()->SetRangeUser(0, 6);
    //time_distr.GetXaxis()->SetTitle("Position [V]");
    //time_distr.GetYaxis()->SetTitle("Stat");
    //canv->SetLogy();

    time_distr.Draw();
    //time_distr.GetYaxis()->SetRangeUser(y_min, y_max);

    auto fit = new TF1("fit_of_time","landau", left_fit_edge, right_fit_edge);
    fit->SetLineColor(7);
    fit->SetLineWidth(3);
    time_distr.Fit(fit, "R");

    gStyle->SetOptFit(1111);
    gStyle->SetOptStat(111111);
    canv->Update();
    canv->SaveAs("fitOutput_DriftTime.pdf");

    return 0;
}
