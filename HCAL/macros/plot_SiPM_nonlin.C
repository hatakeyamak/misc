#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"

Double_t pol2(Double_t *x, Double_t *par);
vector<double> func_nonlin(vector<double> charge, unsigned int nTS1, unsigned int nTS2, 
			   unsigned int option, double fracPreviousTS);

//
// main method
//
void plot_SiPM_nonlin(){

  //
  // Check a few pulse shape from splash
  // https://twiki.cern.ch/twiki/pub/CMS/HcalRunIICom/RAW_shape_table_v2.xls
  //

  //vector<double> charge = {84.3, 196.3, 44879.3, 1202483.1, 489679.8,
  //200274.2, 97868.4, 63336.2, 47260.8, 37734.7};
  vector<double> charge = {121.6, 140.3, 145499.0, 342367.1, 89533.0, 
			   25732.4, 10456.2, 6600.0, 4449.5, 3436.8};
  unsigned int nTS1=2; // 0-9 convention, determine the TS range used for corrections
  unsigned int nTS2=7; //
  
  //
  //
  //
  vector<double> charge1 = func_nonlin(charge,nTS1,nTS2,0,0.);
  vector<double> charge2 = func_nonlin(charge,nTS1,nTS2,1,0.);
  vector<double> charge3 = func_nonlin(charge,nTS1,nTS2,2,0.);
  vector<double> charge4 = func_nonlin(charge,nTS1,nTS2,2,0.4);
  vector<double> charge5 = func_nonlin(charge,nTS1,nTS2,3,0.);

  //
  // Plotting
  //
  TH1F *charge_org = new TH1F("charge_org","charge_org",10,0.,10.); // original charge, no correction
  TH1F *charge_1   = new TH1F("charge_1","charge_1",10,0.,10.); // use existing function, apply TS-to-TS
  TH1F *charge_2   = new TH1F("charge_2","charge_2",10,0.,10.); // use existing function, apply based on total fC
  TH1F *charge_3   = new TH1F("charge_3","charge_3",10,0.,10.); // paolo's procedure
  TH1F *charge_4   = new TH1F("charge_4","charge_4",10,0.,10.); // similar to paolo's procedure, but use Q(TS-1)+Q(TS)
  TH1F *charge_5   = new TH1F("charge_5","charge_5",10,0.,10.); // similar to paolo's procedure, but use pol2

  for (unsigned int ibin=0; ibin<charge.size(); ibin++){
    charge_org->SetBinContent(ibin+1,charge[ibin]);
    charge_1->SetBinContent(ibin+1,charge1[ibin]);
    charge_2->SetBinContent(ibin+1,charge2[ibin]);
    charge_3->SetBinContent(ibin+1,charge3[ibin]);
    charge_4->SetBinContent(ibin+1,charge4[ibin]);
    charge_5->SetBinContent(ibin+1,charge5[ibin]);
  }

  //
  // TCanvas 1
  //
  TCanvas *tc1 = new TCanvas("tc1","tc1",800,600);
  gPad->SetGrid(1);
  gStyle->SetOptStat(0);

  charge_org->SetMaximum(*std::max_element(charge.begin(), charge.end())*2.);  
  charge_org->SetLineWidth(3);  
  charge_org->SetLineColor(1);  
  charge_1->SetLineColor(2);  
  charge_2->SetLineColor(4);  
  charge_3->SetLineColor(6);  
  charge_4->SetLineColor(8);  
  charge_5->SetLineColor(7);  

  charge_org->SetTitleSize(0.05,"XY");
  charge_org->GetYaxis()->SetTitle("Charge (fC)");
  charge_org->GetXaxis()->SetTitle("TS");
  charge_org->SetTitle("");  
  charge_org->Draw();  

  charge_1->Draw("same");  
  charge_2->Draw("same");  
  charge_3->Draw("same");  
  //charge_4->Draw("same");  
  //charge_5->Draw("same");  

  TAxis *axis = charge_org->GetXaxis();
  int bmin = axis->FindBin(nTS1); 
  int bmax = axis->FindBin(nTS2); 
  std::cout << bmin << " " << bmax << std::endl;
  std::cout << charge_2->Integral(bmin,bmax) << std::endl;
  std::cout << charge_3->Integral(bmin,bmax) << std::endl;
  std::cout << charge_4->Integral(bmin,bmax) << std::endl;
  std::cout << charge_5->Integral(bmin,bmax) << std::endl;

  TLegend *tl1 = new TLegend(0.48,0.5,0.95,0.8);
  tl1->AddEntry(charge_org,"Raw Charge");
  tl1->AddEntry(charge_1,"Use function in DB, Q in each TS");
  tl1->AddEntry(charge_2,"Use function in DB, overall Q");
  tl1->AddEntry(charge_3,"Paolo's procedure");
  //tl1->AddEntry(charge_4,"Paolo's procedure but based on Q(TS)+0.4*Q(TS-1)");
  //tl1->AddEntry(charge_5,"Paolo's procedure but use the pol2");
  tl1->Draw();
  tc1->SaveAs("plot_SiPM_nonlin.pdf");

  //
  // TCanvas 2
  //
  TCanvas *tc2 = new TCanvas("tc2","tc2",800,600);
  gPad->SetGrid(1);
  gStyle->SetOptStat(0);

  charge_3->SetMaximum(*std::max_element(charge.begin(), charge.end())*2.);  
  charge_3->SetLineWidth(3);  
  charge_3->SetLineColor(1);  
  charge_3->SetLineColor(6);  
  charge_4->SetLineColor(2);  
  charge_5->SetLineColor(4);  

  charge_3->SetTitleSize(0.05,"XY");
  charge_3->GetYaxis()->SetTitle("Charge (fC)");
  charge_3->GetXaxis()->SetTitle("TS");
  charge_3->SetTitle("");  
  charge_3->Draw();  

  //charge_1->Draw("same");  
  //charge_2->Draw("same");  
  charge_3->Draw();  
  charge_4->Draw("same");  
  charge_5->Draw("same");  

  TLegend *tl2 = new TLegend(0.48,0.5,0.95,0.8);
  tl2->AddEntry(charge_org,"Raw Charge");
  //tl2->AddEntry(charge_1,"Use function in DB, Q in each TS");
  //tl2->AddEntry(charge_2,"Use function in DB, overall Q");
  tl2->AddEntry(charge_3,"Paolo's procedure");
  tl2->AddEntry(charge_4,"+ based on Q(TS)+0.4*Q(TS-1)");
  tl2->AddEntry(charge_5,"+ use the pol2 for each TS");
  tl2->Draw();
  tc2->SaveAs("plot_SiPM_nonlin_2.pdf");

  charge_3->Print("all");
  charge_5->Print("all");

}

//
// pol2
//
Double_t pol2(Double_t *x, Double_t *par)
{
  Float_t xx =x[0];
  Double_t f = par[0] + par[1]*xx + par[2]*xx*xx;
  return f;
}

//
// Corrected charges for SiPM non-linearity
//
vector<double> func_nonlin(vector<double> charge, 
			   unsigned int nTS1, 
			   unsigned int nTS2, 
			   unsigned int option, double fracPreviousTS=0.)
{
  
  vector<double> correctedCharge; // corrected charge which we want to return

  // aux
  double corr, npix;


  // Define the non-linearity function
  // https://twiki.cern.ch/twiki/pub/CMS/HcalSiPMCharacteristics/HcalSiPMCharacteristics_2017plan1_v1.0_data.txt
  TF1 *f1 = new TF1("func_nonlin",pol2,0,25000.,3); //this is the overall corr function based on integrated charge
  f1->SetParameters(1.,2.71238e-05,1.32877e-10);
  //f1->SetParNames("p1","p2");
  // f1->Print();
  // std::cout << f1->GetParameter(0) << std::endl;
  // std::cout << f1->GetParameter(1) << std::endl;
  // std::cout << f1->GetParameter(2) << std::endl;

  //
  // Check the numbers of pixels fired based on the input charge (total charge, charge in each TS etc etc)
  //
  double npixelPerfC = 1./40.; // e.g. 20k pixels / 800,000 fC
  vector<double> npixel;       // [0-9] for individual TS
  for (std::vector<double>::const_iterator it = charge.begin() ; it != charge.end(); ++it){
    npixel.push_back(npixelPerfC * (*it));
  }
  
  // 
  // Finalize option=0
  // 
  if (option==0){
    for (unsigned int ibin=0; ibin<charge.size(); ibin++)
      correctedCharge.push_back( charge[ibin]*f1->Eval(npixel[ibin]) ); // or correcting only a certain ranges?
    return correctedCharge;
  }

  //
  // Various sums
  //
  double sumpx=0.;  // sum of charge(TS) [0-9]
  double sumpx2=0.; // sum of charge(TS)^2 [0-9] or charge(TS)*[charge(TS)+frac*charge(TS-1)]  
  for (unsigned int ibin=TMath::Max((unsigned int)0,nTS1); ibin<TMath::Min((unsigned int)npixel.size(),nTS2+1); 
       ibin++){
    sumpx  += npixel[ibin];
    if (ibin>=1) sumpx2 += npixel[ibin]*( npixel[ibin]+fracPreviousTS*npixel[ibin-1] );
    else         sumpx2 += npixel[ibin]*npixel[ibin];
  }
  
  //
  // Overall correction  
  //
  double corrAll=0.;
  corrAll = f1->Eval(sumpx);
  std::cout << "Overall correction: " 
	    << corrAll << " " << sumpx << " " 
	    << sumpx*corrAll/npixelPerfC << std::endl;

  // 
  // Finalize option=1
  // 
  if (option==1){
    for (unsigned int ibin=0; ibin<charge.size(); ibin++)
      correctedCharge.push_back( charge[ibin]*corrAll ); // or correcting only a certain ranges?
    return correctedCharge;
  }

  //
  // The effective pol1 non-linearity function, for option 2
  //
  double b = (f1->Eval(sumpx) - 1.) / sumpx;
  double bprime   = b * pow(sumpx,2) / sumpx2;
  
  if (option==2){
    for (unsigned int ibin=0; ibin<charge.size(); ibin++){
      if (ibin>=1) npix = npixel[ibin] + fracPreviousTS*npixel[ibin-1];
      else         npix = npixel[ibin];
      corr = 1. + bprime * npix; 
      correctedCharge.push_back( charge[ibin]*corr ); // or correcting only a certain ranges?
    }
    return correctedCharge;    
  }


  //
  // Option 3
  //
  
  //
  // Non-consider non-pol1 for individual TS
  //
  TF1 *f2 = new TF1("func_nonlin_eachTS",pol2,0,25000.,3); // corr function for each TS used for option=2
  f2->SetParameters(1.,2.71238e-05,1.32877e-10);           // later (f2-1) will be scaled 
  //f2->SetParNames("p1","p2");                              // based on the constraint from the overall correction

  //
  // Additional sums
  //
  double sumpx3=0.; // sum of (f(px)-1)*px, where px=charge(TS) or charge(TS)+frac*charge(TS-1)
  for (unsigned int ibin=TMath::Max((unsigned int)0,nTS1); ibin<TMath::Min((unsigned int)npixel.size(),nTS2+1); 
       ibin++){
  //for (unsigned int ibin=nTS1; ibin<TMath::Min(npixel.size(),nTS2+1); ibin++){
    if (ibin>=1) npix = npixel[ibin] + fracPreviousTS*npixel[ibin-1];
    else         npix = npixel[ibin];
    sumpx3 += npixel[ibin]*(f2->Eval(npix)-1.);
  }
  double a   = b * pow(sumpx,2) / sumpx3;

  if (option==3){
    for (unsigned int ibin=0; ibin<charge.size(); ibin++){
      if (ibin>=1) npix = npixel[ibin] + fracPreviousTS*npixel[ibin-1];
      else         npix = npixel[ibin];
      corr = 1. + a *(f2->Eval(npix)-1.); 
      correctedCharge.push_back( charge[ibin]*corr ); // or correcting only a certain ranges?
      // std::cout << charge[ibin]*corr << " " << corr << " " << (corr-1)/npix << std::endl;
      // std::cout << (f2->Eval(npix)-1.)/npix << std::endl;
      // f2->Print();
      // std::cout << f2->GetParameter(0) << std::endl;
      // std::cout << f2->GetParameter(1) << std::endl;
      // std::cout << f2->GetParameter(2) << std::endl;
    }

    return correctedCharge;    
  }

  return correctedCharge;

}

