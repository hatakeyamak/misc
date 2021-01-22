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

const int nfiles=1;    //Specify no. of files
TFile *f;
//vector<int> col={kBlack,kOrange,kAzure+8,kRed,kBlue,kTeal+9,kOrange,kPink+1,kGreen,kCyan,kBlue,kRed};  //Specify Colors
vector<int> col={kBlack,kTeal+7,kOrange-4,kRed,kBlue,kTeal+9,kOrange,kPink+1,kGreen,kCyan,kBlue,kRed};  //Specify Colors

TString name;
bool saveCanvas=0, set0binsSmallValue = 1, sepSystStat = 1;
void set0PredSmall(TH1D*,double);
void setLastBinAsOverFlow(TH1D*);
void setMyRange(TH1D*,double,double);
void setMyRange(THStack*,double,double);
TString getLegName(TString);
TString getXaxisName(TString);
double data_Integral=0,mc_Integral=0, datatIntgrErr = 0, mcIntgrErr = 0, stackHistMinVal = 0.7;
TLatex textOnTop,intLumiE;
double intLumi=35.9;
void DataVsPredPostFit_KH(TString iFname, TString catName){
  TH1::SetDefaultSumw2(1);
  gStyle->SetOptStat(0);
  //  gStyle->SetOptStat("nemri");
  TString datasetName, sampleName;
  TString year1;
  
  f = new TFile(iFname);
  if(iFname.Contains("2016")){
    intLumi=35.8;
    year1 = "2016";
    // sampleName = "NonresPred_2016.root"; f[2] = new TFile(sampleName);
    // sampleName = "LostLepPred_2016.root";    f[1] = new TFile(sampleName);
  }
  else if(iFname.Contains("2017")){
    intLumi=41.5;
    year1 = "2017";
    // sampleName = "NonresPred_2017.root"; f[2] = new TFile(sampleName);
    // sampleName = "LostLepPred_2017.root";    f[1] = new TFile(sampleName);
  }
  else if(iFname.Contains("2018")){
    intLumi=59.5;
    year1 = "2018";
    // sampleName = "NonresPred_2018.root"; f[2] = new TFile(sampleName);
    // sampleName = "LostLepPred_2018.root";    f[1] = new TFile(sampleName);
  }
  else if(iFname.Contains("Run2")){
    intLumi=137;
    year1 = "Run2";
    // sampleName = "NonresPred_Run2.root"; f[2] = new TFile(sampleName);
    // sampleName = "LostLepPred_Run2.root";    f[1] = new TFile(sampleName);
  }
  
  vector<TString> name1;
  // vector<int> rebin;
  // vector<double> xLow,xHigh;
 
  name1.push_back("DataFit");
  name1.push_back("Twores"); 
  name1.push_back("Nononeres");
  
  TLegend *legend;//=new TLegend(0.6, 0.90,  0.98, 0.45);
  TCanvas *c_cA;
  TPad *p_top;
  TPad *p_bot;
  THStack *hs_hist;
  TH1D *h_sum, *h_predRelSyst, *h_predNoUnc;

  name=catName+year1;
  c_cA=new TCanvas(name,name,1200,800);//c_cA->Divide(4,2);
  p_top=new TPad(name+"_top",name+"_top",0,0.4,1,1);
  p_bot=new TPad(name+"_bot",name+"_bot",0,0.0,1,0.4);
  p_top->Draw();p_top->SetGridx();p_top->SetGridy();p_top->SetLogy();
  p_top->SetBottomMargin(0);
  p_bot->SetTopMargin(0);
  p_bot->SetBottomMargin(0.3);
  p_bot->Draw();p_bot->SetGridx();p_bot->SetGridy();    
  name="Stack";
  hs_hist = new THStack(name,name);

  //    legend=new TLegend(0.43,0.78,0.88,0.88);
  legend=new TLegend(0.5,0.65,0.85,0.88);
  legend->SetNColumns(2);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
    
  
  TH1D *h_data,*h_histE,*h_datacopy, *h_sig;
  c_cA->cd();
  name=name1[0];
  //    h_data=(TH1D*)f[0]->FindObjectAny(name);
  f->GetObject(name,h_data);
  //setLastBinAsOverFlow(h_data);
  c_cA->cd();p_top->cd();
  p_top->SetTickx();p_top->SetTicky();
  h_data->SetLineColor(kBlack);
  h_data->SetLineWidth(2);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerColor(h_data->GetLineColor());
  legend->AddEntry(h_data,"Data","lep");
  //gPad->Update();
  // gPad->BuildLegend(0.75,0.75,0.95,0.95,"");
  //mc_Integral = 0;
  for(int p=1;p<name1.size();p++){
    name=name1[p];
    f->GetObject(name,h_histE);
    //setLastBinAsOverFlow(h_histE);
    
    h_histE->SetLineColor(kBlack);
    h_histE->SetLineWidth(1);
    //      h_histE->SetMarkerStyle(21);
    h_histE->SetMarkerColor(col[p]);
    h_histE->SetFillColor(col[p]);
    
    hs_hist->Add(h_histE);
    legend->AddEntry(h_histE,getLegName(name1[p]),"f");
  }
  f->GetObject("TotalBG",h_sum);
  h_sum->SetLineColor(kBlack);
  h_sum->SetLineWidth(1);
  legend->AddEntry(h_sum,"Uncertainty","f");

  /*
  f->GetObject("Signal",h_sig);
  h_sig->SetLineColor(kRed);
  h_sig->SetLineWidth(2);
  if(h_sig->Integral() < 0){
    h_sig->Scale(-1);
    legend->AddEntry(h_sig,"(-)Signal","l");
  }
  else legend->AddEntry(h_sig,"Signal","l");
  */

  c_cA->cd();    p_top->cd();
  hs_hist->SetMinimum(stackHistMinVal);
  hs_hist->SetMaximum(10*hs_hist->GetMaximum());
  hs_hist->Draw("HIST");
  
  h_sum->SetFillColor(1);
  h_sum->SetFillStyle(3013);
  if(set0binsSmallValue){
    set0PredSmall(h_sum,1e-9+stackHistMinVal);
  }
  h_sum->Draw("e2 same");
  
  h_predNoUnc = (TH1D*)h_sum->Clone("predNoUnc");
  h_predRelSyst = (TH1D*)h_sum->Clone("PredRelUnc");
  for(int k=1;k<=h_predRelSyst->GetNbinsX();k++){
    double err = 0.;
    if(h_predRelSyst->GetBinContent(k) < 1e-9) err = 3.0;
    else
      err = h_predRelSyst->GetBinError(k)/h_predRelSyst->GetBinContent(k);
    h_predRelSyst->SetBinContent(k,1.0);
    h_predRelSyst->SetBinError(k,err);
    h_predRelSyst->SetFillColor(1);
    h_predRelSyst->SetFillStyle(3013);
    h_predNoUnc->SetBinError(k,0.);
  }  
  
  name = h_data->GetName();
  hs_hist->GetYaxis()->SetNdivisions(5);
  //    if(name.Contains("MuPt")) setMyRange(hs_hist,xLow,xHigh);
  h_data->Draw("x0e1 same");
  hs_hist->SetTitle(";;Events");
  hs_hist->GetYaxis()->SetTitleOffset(0.60);    
  hs_hist->GetYaxis()->SetTitleSize(0.07);
  hs_hist->GetYaxis()->SetLabelSize(0.07);

  //KH h_sig->Draw("hist same");
  
  c_cA->Modified();
  c_cA->Update();
  //    legend->SetNColumns(3);
  legend->Draw();
  
  TH1D *h_numr=(TH1D*)h_data->Clone();
  if(!sepSystStat) h_numr->Divide(h_sum);
  else h_numr->Divide(h_predNoUnc);
  h_numr->SetLineColor(kBlack);
  h_numr->SetMarkerColor(kBlack);
  h_numr->SetTitle(0);
  h_numr->GetXaxis()->SetTitle("p_{T}^{miss} (GeV)");
  h_numr->GetXaxis()->SetTitleOffset(0.96);
  h_numr->GetXaxis()->SetTitleSize(0.11);
  h_numr->GetXaxis()->SetLabelSize(0.11);
  
  h_numr->GetYaxis()->SetTitle("#frac{Data}{Prediction}");
  h_numr->GetYaxis()->SetTitleOffset(0.4);
  h_numr->GetYaxis()->SetTitleSize(0.11);
  h_numr->GetYaxis()->SetLabelSize(0.11);
  h_numr->GetYaxis()->SetNdivisions(505);
  h_numr->SetMaximum(1.99);
  h_numr->SetMinimum(0.01);
  c_cA->cd();    p_bot->cd();
  p_bot->SetTickx();p_bot->SetTicky();
  //    c_cB->cd(i+1);    p_bot->cd();
  h_numr->Draw("x0e1");
  if(sepSystStat){
    h_predRelSyst->Draw("e2 same");
    h_numr->Draw("x0e0 same");
  }
  else h_numr->Draw("x0e0");
  
  // cout<<h_numr->GetName()<<endl;
  // for(int j=1;j<=h_numr->GetNbinsX();j++){
  //   cout<<h_numr->GetBinContent(j)<<"\t"<<h_numr->GetBinError(j)<<endl;
  // }
  
  TLine *line, *line2;
  line = new TLine(h_numr->GetBinLowEdge(1),1.0, h_numr->GetBinLowEdge(h_numr->GetNbinsX()+1),1);
  
  line->SetLineStyle(3);
  line->Draw();
  line2 = new TLine(h_numr->GetBinLowEdge(1),data_Integral/mc_Integral, h_numr->GetBinLowEdge(h_numr->GetNbinsX()+1),data_Integral/mc_Integral);
  //    line2->SetLineStyle(3);
  line2->SetLineColor(kBlue);
  //    line2->Draw();
  
  c_cA->cd();    p_top->cd(); gPad->RedrawAxis();
  char name2[100];
  textOnTop.SetTextSize(0.06);
  intLumiE.SetTextSize(0.06);
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Preliminary}}");
  sprintf(name2,"#bf{%0.1f fb^{-1} (13 TeV)}",intLumi);
  intLumiE.DrawLatexNDC(0.7,0.91,name2);
  if(saveCanvas){name=catName+year1+".png";c_cA->SaveAs(name);}

  // cout<<"Integral in Data "<<data_Integral<<endl
  //     <<"Integral in MC "<<mc_Integral<<endl
  //     <<"Data/MC "<<data_Integral/mc_Integral<<endl;

}



TString getLegName(TString fname){
  if(fname.Contains("TTJets")) return "t#bar{t}";
  else if(fname.Contains("WJets")) return "W+Jets";
  else if(fname.Contains("ZJets")) return "Z+Jets";
  else if(fname.Contains("Rare")) return "Rare";
  else if(fname.Contains("ST__")) return "Single t";
  else if(fname.Contains("Nonres")) return "Non-resonant";
  else if(fname.Contains("Top")) return "Top";

  else if(fname.Contains("Nononeres")) return "0,1-resonant";
  else if(fname.Contains("Twores")) return "2-resonant";
  
  else return fname;
}
TString getXaxisName(TString axname){
  if(axname.Contains("NJets")) return "N_{Jets}";
  else if(axname.Contains("HT")) return "HT(GeV)";
  else if(axname.Contains("BTags")) return "b tags";
  else if(axname.Contains("ElePt")) return "e pT(GeV)";
  else if(axname.Contains("MuPt")) return "#mu pT(GeV)";
  else if(axname.Contains("MuEta")) return "#mu #eta";
  else if(axname.Contains("PhotonPt")) return "#gamma pT(GeV)";
  else if(axname.Contains("PhotonEta")) return "#gamma #eta";
  else if(axname.Contains("PhotonPhi")) return "#gamma #Phi";
  else if(axname.Contains("mTLep")) return "mT(l,p_{T}^{miss})(GeV)";
  else if(axname.Contains("dR_MuPho")) return "#DeltaR(#mu,#gamma)";
  else if(axname.Contains("AllSBin")) return "Bin Number";
  else if(axname.Contains("nVtx")) return "No. of primary vertices";
  else if(axname.Contains("dPhi_METjet1") || axname.Contains("dphi1_METjet1")) return "#Delta#Phi_{1}";
  else if(axname.Contains("dPhi_METjet2") || axname.Contains("dphi2_METjet2")) return "#Delta#Phi_{2}";
  else if(axname.Contains("dPhi_METBestPhoton") ) return "#Delta#Phi(MET,#gamma)";
  else if(axname.Contains("dPhi_Muon_Photon") ) return "#Delta#Phi(#mu,#gamma)";
  else if(axname.Contains("QMut") || axname.Contains("Qmut")) return "QMult";
  else if(axname.Contains("MT_Mu")) return "mT(#mu,p_{T}^{miss})(GeV)";
  else if(axname.Contains("METPhi")) return "p_{T}^{miss} #phi";
  else if(axname.Contains("MET")) return "p_{T}^{miss}(GeV)";
  else return axname;

}

void setMyRange(TH1D *h1,double xLow,double xHigh){
  double err=0;
  if(xHigh > 13000) return;
  if(xLow < 13000) return;
  int nMax=h1->FindBin(xHigh);
  h1->SetBinContent(nMax,h1->IntegralAndError(nMax,h1->GetNbinsX(),err));
  h1->SetBinError(nMax,err);
  for(int i=nMax+1;i<=h1->GetNbinsX()+1;i++){
    h1->SetBinContent(i,0);
    h1->SetBinError(i,0);
  }
  //  h1->GetXaxis()->SetRangeUser(xLow,xHigh);
}
void setMyRange(THStack *h1,double xLow,double xHigh){
  // double err=0;
  // if(xHigh > 13000) return;
  // int nMax=h1->FindBin(xHigh);
  // h1->SetBinContent(nMax,h1->IntegralAndError(nMax,h1->GetNbinsX(),err));
  // h1->SetBinError(nMax,err);
  // for(int i=nMax+1;i<=h1->GetNbinsX()+1;i++){
  //   h1->SetBinContent(i,0);
  //   h1->SetBinError(i,0);
  // }
  //h1->GetXaxis()->SetRangeUser(xLow,xHigh);
}

void set0PredSmall(TH1D* h, double val){
  double err=1.0;
  for(int i=1;i<=h->GetNbinsX();i++){
    if(h->GetBinContent(i) < 0.000001){
      err = h->GetBinError(i);
      cout<<"************* To make hashed errors visible, setting 0 pred bin "<<i<<" a value of "<<val<<" for hist "<<h->GetName()<<endl;
      h->SetBinContent(i,val);
      h->SetBinError(i,err);
      cout<<h->GetBinContent(i)<<" "<<h->GetBinError(i)<<" | ";
    }
  }
}
void setLastBinAsOverFlow(TH1D* h_hist){
  double lastBinCt =h_hist->GetBinContent(h_hist->GetNbinsX()),overflCt =h_hist->GetBinContent(h_hist->GetNbinsX()+1);
  double lastBinErr=h_hist->GetBinError(h_hist->GetNbinsX()),  overflErr=h_hist->GetBinError(h_hist->GetNbinsX()+1);

  lastBinCt = lastBinCt+overflCt;
  lastBinErr = sqrt( (lastBinErr*lastBinErr) + (overflErr*overflErr) );
  
  h_hist->SetBinContent(h_hist->GetNbinsX(),lastBinCt);
  h_hist->SetBinError(h_hist->GetNbinsX(),lastBinErr);
    
}
