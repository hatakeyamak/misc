
//----------
void dump_XsecLimit(TH2F* h, std::string fname_yaml, std::string model, std::string Mother);
void dump_LimitContour(TGraph* h, std::string fname_yaml, std::string Mother);

//----------
void HEPData_dump(std::string fname, std::string model, std::string mother){

  TFile *_file0 = TFile::Open(fname.c_str());
  _file0->ls();

  if (model!="") model+="_";

  TH2F *obsLimitXsec = (TH2F*) _file0->Get("combined_obsLimit_BR100pct");
  dump_XsecLimit(obsLimitXsec,model+"ObsXsecLimit.yaml",model,mother);

  TGraph *obsLimContour = (TGraph*) _file0->Get("ObsLim");
  dump_LimitContour(obsLimContour,model+"ObservedExclusionContour.yaml",mother);

  TGraph *expLimContour = (TGraph*) _file0->Get("ExpLim");
  dump_LimitContour(expLimContour,model+"ExpectedExclusionContour.yaml",mother);

}

//----------
void dump_LimitContour(TGraph* h, std::string fname_yaml, std::string Mother){

  FILE * pFile;
  pFile = fopen (fname_yaml.c_str(),"w");

  //h->Print();

  std::vector<float> mMother;
  std::vector<float> mLSP;

  double x,y;
  for (int ibin=0; ibin<h->GetN(); ibin++){
    h->GetPoint(ibin,x,y);
    
    if (ibin>=1 && float(x)==mMother.back() && float(y)==mLSP.back()){ // Remove duplicated/repeated points
    } else {
      mMother.push_back(x);
      mLSP.push_back(y);
    }
  }
  
  fprintf(pFile,"independent_variables:\n");
  fprintf(pFile,"- header: {name: '$m_{\\tilde{%s}}$', units: GeV}\n",Mother.c_str());
  fprintf(pFile,"  values:\n");
  for(std::vector<float>::iterator it = mMother.begin(); it != mMother.end(); ++it)
    fprintf(pFile,"  - values: %f\n",*it);

  fprintf(pFile,"dependent_variables:\n");
  fprintf(pFile,"- header: {name: '$m_{\\tilde{\\chi}^0_1}$', units: GeV}\n"); 
  fprintf(pFile," values:\n");
  for(std::vector<float>::iterator it = mLSP.begin(); it != mLSP.end(); ++it)
    fprintf(pFile,"  - values: %f\n",*it);

  fclose (pFile);  
  
}

//----------
void dump_XsecLimit(TH2F* h, std::string fname_yaml, std::string model, std::string Mother){

  FILE * pFile;
  pFile = fopen (fname_yaml.c_str(),"w");

  //h->Print();
  //std::cout << h->GetNbinsX() << std::endl;
  //std::cout << h->GetNbinsY() << std::endl;

  std::vector<float> mMother;
  std::vector<float> mLSP;
  std::vector<float> xsecLimit;
  
  for (int ibinx=1; ibinx<=h->GetNbinsX(); ibinx++){    // 0 is underflow
    for (int ibiny=1; ibiny<=h->GetNbinsY(); ibiny++){  // 0 is underflow
      if (h->GetBinContent(ibinx,ibiny)>0.){

	// printf("%8.1f %8.1f %8f\n",
	//        h->GetXaxis()->GetBinCenter(ibinx),
	//        h->GetYaxis()->GetBinCenter(ibiny),
	//        h->GetBinContent(ibinx,ibiny));

	double MassMother =h->GetXaxis()->GetBinCenter(ibinx);
	double MassLSP=h->GetYaxis()->GetBinCenter(ibiny);
	double Mtop=175.;
	
	if (model=="T2tt" && fabs(MassMother-MassLSP-Mtop)<=25. && MassMother<=275){  // Top corridor points
	    printf("Top corridor points (excluded for now): %8.1f %8.1f %8f\n",
		   h->GetXaxis()->GetBinCenter(ibinx),
		   h->GetYaxis()->GetBinCenter(ibiny),
		   h->GetBinContent(ibinx,ibiny));
	}
	else if (model=="T5ttcc" && MassLSP<50.){                                            // T5tttt low LSP mass points
	    printf("Top corridor points (excluded for now): %8.1f %8.1f %8f\n",
		   h->GetXaxis()->GetBinCenter(ibinx),
		   h->GetYaxis()->GetBinCenter(ibiny),
		   h->GetBinContent(ibinx,ibiny));
	}
	else {	
	mMother.push_back(  h->GetXaxis()->GetBinCenter(ibinx));
	mLSP.push_back(     h->GetYaxis()->GetBinCenter(ibiny));
	xsecLimit.push_back(h->GetBinContent(ibinx,ibiny)     );
	}

      }
    }
  }

  fprintf(pFile,"independent_variables:\n");
  fprintf(pFile,"- header: {name: '$m_{\\tilde{%s}}$', units: GeV}\n",Mother.c_str());
  fprintf(pFile,"  values:\n");
  for(std::vector<float>::iterator it = mMother.begin(); it != mMother.end(); ++it)
    fprintf(pFile,"  - values: %8.1f\n",*it);

  fprintf(pFile,"- header: {name: '$m_{\\tilde{\\chi}^0_1}$', units: GeV}\n"); 
  fprintf(pFile," values:\n");
  for(std::vector<float>::iterator it = mLSP.begin(); it != mLSP.end(); ++it)
    fprintf(pFile,"  - values: %8.1f\n",*it);

  fprintf(pFile,"dependent_variables:\n");
  fprintf(pFile,"- header: {name: UL on cross section, units: pb}\n");
  fprintf(pFile,"  values:\n");
  for(std::vector<float>::iterator it = xsecLimit.begin(); it != xsecLimit.end(); ++it)
    fprintf(pFile,"  - values: %f\n",*it);

  fclose (pFile);  
  
}
