#include<iostream>
#include<iomanip>
#include"TH1.h"
#include"TROOT.h"
#include"TH2.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<string>
#include<vector>
#include"TGraphErrors.h"
#include"TGraph.h"
#include"TLegend.h"
#include"TLatex.h"
#include"TCanvas.h"
#include"THStack.h"
#include"TStyle.h"

void extractPostFits_KH(TString fName="fitDiagnostics.root", TString catName="wt", TString fNameData=""){
  TString name;
  //KH TString dirNameFormat = "ch1_ch2_SR_ht_2";
  //   TString dirNameFormat = "ch1_ch3_ch4_SR_WHT_4";
  
  TFile *f = TFile::Open(fName);
  //KH TFile *fData = TFile::Open(fNameData);
  
  name = catName+"_PostFitPredictions_Run2.root";
  TFile *fout = new TFile(name,"recreate");

  TString keyword, dirName = "shapes_fit_b", dataHist;

  /* KH
  if(catName=="wt" || catName=="FBW"){ keyword = "wt"; dataHist = "METvBin_WtWm1AK8_1b";}
  if(catName=="ht" || catName=="FBH"){ keyword = "ht"; dataHist = "METvBin_HtHm1AK8_1b";}
  if(catName=="WHT" || catName=="FBWH"){ keyword = "WHT";  dataHist = "METvBin_FBWH_SR";}
  if(catName=="WT" || catName=="FBW"){ keyword = "WT";  dataHist = "METvBin_FBW_SR";}
  if(catName=="HT" || catName=="FBH"){ keyword = "HT";  dataHist = "METvBin_FBH_SR";}
  */
  keyword = "2T2M";

  //KH TH1D *h_data = (TH1D*)fData->Get(dataHist);
  
  double metbins[10] = {200,250,300,350,400,450,500,600,800,1200.};
  TH1D *h_data = new TH1D("h_data","h_data",9,metbins);

  h_data->Draw();
  fout->cd(); h_data->Write("Data");

  TH1D *h_twores = (TH1D*)h_data->Clone("Twores"); 
  TH1D *h_oneres = (TH1D*)h_data->Clone("Oneres"); 
  TH1D *h_nonres = (TH1D*)h_data->Clone("Nonres");
  TH1D *h_nononeres = (TH1D*)h_data->Clone("Nononeres");
  TH1D *h_total = (TH1D*)h_data->Clone("Total");
  TH1D *h_totalBG = (TH1D*)h_data->Clone("TotalBG");
  TH1D *h_sig = (TH1D*)h_data->Clone("Signal");
  TH1D *h_dataFit = (TH1D*)h_data->Clone("DataFit");
  TGraphAsymmErrors *g_data; 
  
  h_twores->Reset();
  h_oneres->Reset();
  h_nonres->Reset();
  h_total->Reset();
  h_totalBG->Reset();
  h_sig->Reset();

  TString name0;
  TH1F *h1;
  for(int i=1;i<=h_data->GetNbinsX();i++){
    name0 = dirName+"/"+"ch1_ch"+to_string(i)+"_SR"+keyword+"_"+to_string(i);
    //    name0 = dirName+"/"+"ch1_ch3_ch"+to_string(i)+"_SR_"+keyword+"_"+to_string(i);
    cout<<name0<<endl;
    
    name = name0+"/twores";
    f->GetObject(name,h1);
    h_twores->SetBinContent(i,h1->GetBinContent(1));
    h_twores->SetBinError(i,h1->GetBinError(1));

    name = name0+"/oneres";
    f->GetObject(name,h1);
    h_oneres->SetBinContent(i,h1->GetBinContent(1));
    h_oneres->SetBinError(i,h1->GetBinError(1));

    name = name0+"/nonres";
    f->GetObject(name,h1);
    h_nonres->SetBinContent(i,h1->GetBinContent(1));
    h_nonres->SetBinError(i,h1->GetBinError(1));
    h_nononeres->SetBinContent(i,h1->GetBinContent(1));
    h_nononeres->SetBinError(i,h1->GetBinError(1));

    name = name0+"/total";
    f->GetObject(name,h1);
    h_total->SetBinContent(i,h1->GetBinContent(1));
    h_total->SetBinError(i,h1->GetBinError(1)); 

    name = name0+"/total_background";
    f->GetObject(name,h1);
    h_totalBG->SetBinContent(i,h1->GetBinContent(1));
    h_totalBG->SetBinError(i,h1->GetBinError(1)); 

    name = name0+"/total_signal";
    f->GetObject(name,h1);
    h_sig->SetBinContent(i,h1->GetBinContent(1));
    h_sig->SetBinError(i,h1->GetBinError(1));

    name = name0+"/data";
    f->GetObject(name,g_data);
    double *y = g_data->GetY();
    h_dataFit->SetBinContent(i,y[0]);
    h_dataFit->SetBinError(i,sqrt(y[0]));

  }
  h_nononeres->Add(h_oneres);

  //Print out
  printf("0,1-resonant, 2-resonant, total BG\n");
  for(int i=1;i<=h_data->GetNbinsX();i++){
    printf("%6.2f +- %4.2f, %6.2f +- %4.2f, %6.2f +- %4.2f\n",
	   h_nononeres->GetBinContent(i),h_nononeres->GetBinError(i),
	   h_twores->GetBinContent(i),h_twores->GetBinError(i),
	   h_totalBG->GetBinContent(i),h_totalBG->GetBinError(i)
	   );
  }

  fout->cd();
  h_twores->Write();
  h_oneres->Write();
  h_nonres->Write();
  h_nononeres->Write();
  h_total->Write();
  h_totalBG->Write();
  h_sig->Write();
  h_dataFit->Write();
  
  
}
