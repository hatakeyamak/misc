{

  gStyle->SetOptStat(0);
  
  double Gains_2016last_HEP17_d1[4][13]={
    {
      0.23906,      0.25834,      0.26676,      0.23879,
      0.23177,      0.27161,      0.27187,      0.30716,      0.30163,
      0.33844,      0.32882,      0.35196,      0.44309
    },
    {
      0.18869,      0.21699,      0.24355,      0.23696,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    },
    {
      0.19246,      0.20564,      0.23342,      0.24081,
      0.26542,      0.31676,      0.26166,      0.31911,      0.28481,
      0.38944,      0.30880,      0.40582,      0.57346
    },
    {
      0.21299,      0.24295,      0.23538,      0.28427,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    }
  };

  double Gains_2017start_HEP17_d2[4][13]={
    {
      0.00043,      0.00055,      0.00050,      0.00046,
      0.00044,      0.00049,      0.00054,      0.00059,      0.00044,
      0.00053,      0.00054,      0.00058,      0.00058
    },
    {
      0.00033,      0.00043,      0.00056,      0.00045,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    },
    {
      0.00039,      0.00044,      0.00043,      0.00049,
      0.00049,      0.00045,      0.00047,      0.00047,      0.00044,
      0.00032,      0.00038,      0.00040,      0.00050
    },
    {
      0.00033,      0.00033,      0.00039,      0.00041,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    }
  };

  double RespCorrs_2016last_HEP17_d1[4][13]={
    {
      1.07663,      1.06145,      1.06500,      1.16751,
      1.54390,      1.26847,      1.42250,      1.12990,      1.40579,
      1.19989,      1.70815,      1.17532,      1.08812
    },
    {
      1.31198,      1.22126,      1.09895,      1.22704,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    },
    {
      1.25475,      1.14126,      1.15816,      1.12453,
      1.29752,      1.46189,      1.41133,      1.45275,      1.37953,
      1.69020,      1.63739,      1.90156,      1.65426,
    },
    {
      1.38797,      1.37150,      1.25986,      1.27925,
      0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0      
    }
  };
  
  TH1F *tGains_2016last_HEP17_d1[5];
  tGains_2016last_HEP17_d1[0] = new TH1F("tGains_2016last_HEP17_d1_iphi63","tGains_2016last_HEP17_d1_iphi63",
					13,16.5,29.5);
  tGains_2016last_HEP17_d1[1] = new TH1F("tGains_2016last_HEP17_d1_iphi64","tGains_2016last_HEP17_d1_iphi64",
					13,16.5,29.5);
  tGains_2016last_HEP17_d1[2] = new TH1F("tGains_2016last_HEP17_d1_iphi65","tGains_2016last_HEP17_d1_iphi65",
					13,16.5,29.5);
  tGains_2016last_HEP17_d1[3] = new TH1F("tGains_2016last_HEP17_d1_iphi66","tGains_2016last_HEP17_d1_iphi66",
					13,16.5,29.5);
  tGains_2016last_HEP17_d1[4] = new TH1F("tGains_2016last_HEP17_d1_ave","tGains_2016last_HEP17_d1_ave",
					13,16.5,29.5);

  for (int ibin=0; ibin<13; ibin++) tGains_2016last_HEP17_d1[0]->SetBinContent(ibin+1,Gains_2016last_HEP17_d1[0][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2016last_HEP17_d1[1]->SetBinContent(ibin+1,Gains_2016last_HEP17_d1[1][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2016last_HEP17_d1[2]->SetBinContent(ibin+1,Gains_2016last_HEP17_d1[2][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2016last_HEP17_d1[3]->SetBinContent(ibin+1,Gains_2016last_HEP17_d1[3][ibin]);
  for (int ibin=0; ibin<4;  ibin++) tGains_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(Gains_2016last_HEP17_d1[0][ibin]
										 +Gains_2016last_HEP17_d1[1][ibin]
										 +Gains_2016last_HEP17_d1[2][ibin]
										 +Gains_2016last_HEP17_d1[3][ibin])/4.);
  for (int ibin=4; ibin<13; ibin++) tGains_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(Gains_2016last_HEP17_d1[0][ibin]
										 +Gains_2016last_HEP17_d1[2][ibin])/2.);

  TH1F *tRespCorrs_2016last_HEP17_d1[5];
  tRespCorrs_2016last_HEP17_d1[0] = new TH1F("tRespCorrs_2016last_HEP17_d1_iphi63","tRespCorrs_2016last_HEP17_d1_iphi63",
					13,16.5,29.5);
  tRespCorrs_2016last_HEP17_d1[1] = new TH1F("tRespCorrs_2016last_HEP17_d1_iphi64","tRespCorrs_2016last_HEP17_d1_iphi64",
					13,16.5,29.5);
  tRespCorrs_2016last_HEP17_d1[2] = new TH1F("tRespCorrs_2016last_HEP17_d1_iphi65","tRespCorrs_2016last_HEP17_d1_iphi65",
					13,16.5,29.5);
  tRespCorrs_2016last_HEP17_d1[3] = new TH1F("tRespCorrs_2016last_HEP17_d1_iphi66","tRespCorrs_2016last_HEP17_d1_iphi66",
					13,16.5,29.5);
  tRespCorrs_2016last_HEP17_d1[4] = new TH1F("tRespCorrs_2016last_HEP17_d1_ave","tRespCorrs_2016last_HEP17_d1_ave",
					13,16.5,29.5);

  for (int ibin=0; ibin<13; ibin++) tRespCorrs_2016last_HEP17_d1[0]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[0][ibin]);
  for (int ibin=0; ibin<13; ibin++) tRespCorrs_2016last_HEP17_d1[1]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[1][ibin]);
  for (int ibin=0; ibin<13; ibin++) tRespCorrs_2016last_HEP17_d1[2]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[2][ibin]);
  for (int ibin=0; ibin<13; ibin++) tRespCorrs_2016last_HEP17_d1[3]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[3][ibin]);
  for (int ibin=0; ibin<4;  ibin++) tRespCorrs_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[1][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin]
										 +RespCorrs_2016last_HEP17_d1[3][ibin])/4.);
  for (int ibin=4; ibin<13; ibin++) tRespCorrs_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin])/2.);

  TH1F *tGainsRespCorrs_2016last_HEP17_d1[8];
  tGainsRespCorrs_2016last_HEP17_d1[0] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi63","tGainsRespCorrs_2016last_HEP17_d1_iphi63",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[1] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi64","tGainsRespCorrs_2016last_HEP17_d1_iphi64",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[2] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi65","tGainsRespCorrs_2016last_HEP17_d1_iphi65",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[3] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi66","tGainsRespCorrs_2016last_HEP17_d1_iphi66",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[4] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_ave","tGainsRespCorrs_2016last_HEP17_d1_ave",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[5] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_avenorm","tGainsRespCorrs_2016last_HEP17_d1_avenorm",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[6] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi63_norm","tGainsRespCorrs_2016last_HEP17_d1_iphi63_norm",
					13,16.5,29.5);
  tGainsRespCorrs_2016last_HEP17_d1[7] = new TH1F("tGainsRespCorrs_2016last_HEP17_d1_iphi65_norm","tGainsRespCorrs_2016last_HEP17_d1_iphi65_norm",
					13,16.5,29.5);

  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[0]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2016last_HEP17_d1[0][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[1]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[1][ibin]*Gains_2016last_HEP17_d1[1][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[2]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2016last_HEP17_d1[2][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[3]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[3][ibin]*Gains_2016last_HEP17_d1[3][ibin]);
  for (int ibin=0; ibin<4;  ibin++) tGainsRespCorrs_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2016last_HEP17_d1[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[1][ibin]*Gains_2016last_HEP17_d1[1][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2016last_HEP17_d1[2][ibin]
										 +RespCorrs_2016last_HEP17_d1[3][ibin]*Gains_2016last_HEP17_d1[3][ibin])/4.);
  for (int ibin=4; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2016last_HEP17_d1[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2016last_HEP17_d1[2][ibin])/2.);
  
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[5]->SetBinContent(ibin+1,
											tGainsRespCorrs_2016last_HEP17_d1[4]->GetBinContent(ibin+1)
											/tGainsRespCorrs_2016last_HEP17_d1[4]->GetBinContent(1));
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[6]->SetBinContent(ibin+1,
											tGainsRespCorrs_2016last_HEP17_d1[0]->GetBinContent(ibin+1)
											/tGainsRespCorrs_2016last_HEP17_d1[4]->GetBinContent(1));
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2016last_HEP17_d1[7]->SetBinContent(ibin+1,
											tGainsRespCorrs_2016last_HEP17_d1[2]->GetBinContent(ibin+1)
											/tGainsRespCorrs_2016last_HEP17_d1[4]->GetBinContent(1));
    
  TH1F *tGains_2017start_HEP17_d2[5];
  tGains_2017start_HEP17_d2[0] = new TH1F("tGains_2017start_HEP17_d2_iphi63","tGains_2017start_HEP17_d2_iphi63",
					13,16.5,29.5);
  tGains_2017start_HEP17_d2[1] = new TH1F("tGains_2017start_HEP17_d2_iphi64","tGains_2017start_HEP17_d2_iphi64",
					13,16.5,29.5);
  tGains_2017start_HEP17_d2[2] = new TH1F("tGains_2017start_HEP17_d2_iphi65","tGains_2017start_HEP17_d2_iphi65",
					13,16.5,29.5);
  tGains_2017start_HEP17_d2[3] = new TH1F("tGains_2017start_HEP17_d2_iphi66","tGains_2017start_HEP17_d2_iphi66",
					13,16.5,29.5);
  tGains_2017start_HEP17_d2[4] = new TH1F("tGains_2017start_HEP17_d2_ave","tGains_2017start_HEP17_d2_ave",
					13,16.5,29.5);

  for (int ibin=0; ibin<13; ibin++) tGains_2017start_HEP17_d2[0]->SetBinContent(ibin+1,Gains_2017start_HEP17_d2[0][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2017start_HEP17_d2[1]->SetBinContent(ibin+1,Gains_2017start_HEP17_d2[1][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2017start_HEP17_d2[2]->SetBinContent(ibin+1,Gains_2017start_HEP17_d2[2][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGains_2017start_HEP17_d2[3]->SetBinContent(ibin+1,Gains_2017start_HEP17_d2[3][ibin]);
  for (int ibin=0; ibin<4;  ibin++) tGains_2017start_HEP17_d2[4]->SetBinContent(ibin+1,
										(Gains_2017start_HEP17_d2[0][ibin]
										 +Gains_2017start_HEP17_d2[1][ibin]
										 +Gains_2017start_HEP17_d2[2][ibin]
										 +Gains_2017start_HEP17_d2[3][ibin])/4.);
  for (int ibin=4; ibin<13; ibin++) tGains_2017start_HEP17_d2[4]->SetBinContent(ibin+1,
										(Gains_2017start_HEP17_d2[0][ibin]
										 +Gains_2017start_HEP17_d2[2][ibin])/2.);

  TH1F *tGainsRespCorrs_2017start_HEP17_d2[8];
  tGainsRespCorrs_2017start_HEP17_d2[0] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi63","tGainsRespCorrs_2017start_HEP17_d2_iphi63",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[1] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi64","tGainsRespCorrs_2017start_HEP17_d2_iphi64",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[2] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi65","tGainsRespCorrs_2017start_HEP17_d2_iphi65",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[3] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi66","tGainsRespCorrs_2017start_HEP17_d2_iphi66",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[4] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_ave","tGainsRespCorrs_2017start_HEP17_d2_ave",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[5] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_avenorm","tGainsRespCorrs_2017start_HEP17_d2_avenorm",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[6] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi63_norm","tGainsRespCorrs_2017start_HEP17_d2_iphi63_norm",
					13,16.5,29.5);
  tGainsRespCorrs_2017start_HEP17_d2[7] = new TH1F("tGainsRespCorrs_2017start_HEP17_d2_iphi65_norm","tGainsRespCorrs_2017start_HEP17_d2_iphi65_norm",
					13,16.5,29.5);

  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[0]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2017start_HEP17_d2[0][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[1]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[1][ibin]*Gains_2017start_HEP17_d2[1][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[2]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2017start_HEP17_d2[2][ibin]);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[3]->SetBinContent(ibin+1,RespCorrs_2016last_HEP17_d1[3][ibin]*Gains_2017start_HEP17_d2[3][ibin]);
  for (int ibin=0; ibin<4;  ibin++) tGainsRespCorrs_2017start_HEP17_d2[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2017start_HEP17_d2[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[1][ibin]*Gains_2017start_HEP17_d2[1][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2017start_HEP17_d2[2][ibin]
										 +RespCorrs_2016last_HEP17_d1[3][ibin]*Gains_2017start_HEP17_d2[3][ibin])/4.);
  for (int ibin=4; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[4]->SetBinContent(ibin+1,
										(RespCorrs_2016last_HEP17_d1[0][ibin]*Gains_2017start_HEP17_d2[0][ibin]
										 +RespCorrs_2016last_HEP17_d1[2][ibin]*Gains_2017start_HEP17_d2[2][ibin])/2.);
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[5]->SetBinContent(ibin+1,
											tGainsRespCorrs_2017start_HEP17_d2[4]->GetBinContent(ibin+1)
											 /tGainsRespCorrs_2017start_HEP17_d2[4]->GetBinContent(1));
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[6]->SetBinContent(ibin+1,
											tGainsRespCorrs_2017start_HEP17_d2[0]->GetBinContent(ibin+1)
											 /tGainsRespCorrs_2017start_HEP17_d2[4]->GetBinContent(1));
  for (int ibin=0; ibin<13; ibin++) tGainsRespCorrs_2017start_HEP17_d2[7]->SetBinContent(ibin+1,
											tGainsRespCorrs_2017start_HEP17_d2[2]->GetBinContent(ibin+1)
											 /tGainsRespCorrs_2017start_HEP17_d2[4]->GetBinContent(1));
  
  TCanvas *tc1 = new TCanvas("tc1","tc1",800,600);
  gPad->SetGrid(1);
  tGains_2016last_HEP17_d1[0]->SetMaximum(0.8);
  tGains_2016last_HEP17_d1[0]->SetMinimum(0.0);
  tGains_2016last_HEP17_d1[0]->SetMarkerStyle(20);
  tGains_2016last_HEP17_d1[1]->SetMarkerStyle(20);
  tGains_2016last_HEP17_d1[2]->SetMarkerStyle(20);
  tGains_2016last_HEP17_d1[3]->SetMarkerStyle(20);
  tGains_2016last_HEP17_d1[1]->SetMarkerColor(2);
  tGains_2016last_HEP17_d1[2]->SetMarkerColor(4);
  tGains_2016last_HEP17_d1[3]->SetMarkerColor(6);
  tGains_2016last_HEP17_d1[0]->SetTitleSize(0.05,"XY");
  tGains_2016last_HEP17_d1[0]->GetYaxis()->SetTitle("Gains");
  tGains_2016last_HEP17_d1[0]->GetXaxis()->SetTitle("ieta");
  tGains_2016last_HEP17_d1[0]->Draw("p");
  tGains_2016last_HEP17_d1[1]->Draw("p,same");
  tGains_2016last_HEP17_d1[2]->Draw("p,same");
  tGains_2016last_HEP17_d1[3]->Draw("p,same");
  tGains_2016last_HEP17_d1[4]->Draw("same");
  TLegend *tl1 = new TLegend(0.2,0.55,0.5,0.8);
  tl1->AddEntry(tGains_2016last_HEP17_d1[0],"iphi=63");
  tl1->AddEntry(tGains_2016last_HEP17_d1[1],"iphi=64");
  tl1->AddEntry(tGains_2016last_HEP17_d1[2],"iphi=65");
  tl1->AddEntry(tGains_2016last_HEP17_d1[3],"iphi=66");
  tl1->AddEntry(tGains_2016last_HEP17_d1[4],"Average");
  tl1->Draw();
  tc1->SaveAs("tGains_2016last.pdf");
  
  TCanvas *tc1b = new TCanvas("tc1b","tc1b",800,600);
  gPad->SetGrid(1);
  tRespCorrs_2016last_HEP17_d1[0]->SetMaximum(3.3);
  tRespCorrs_2016last_HEP17_d1[0]->SetMinimum(0.0);
  tRespCorrs_2016last_HEP17_d1[0]->SetMarkerStyle(20);
  tRespCorrs_2016last_HEP17_d1[1]->SetMarkerStyle(20);
  tRespCorrs_2016last_HEP17_d1[2]->SetMarkerStyle(20);
  tRespCorrs_2016last_HEP17_d1[3]->SetMarkerStyle(20);
  tRespCorrs_2016last_HEP17_d1[1]->SetMarkerColor(2);
  tRespCorrs_2016last_HEP17_d1[2]->SetMarkerColor(4);
  tRespCorrs_2016last_HEP17_d1[3]->SetMarkerColor(6);
  tRespCorrs_2016last_HEP17_d1[0]->SetTitleSize(0.05,"XY");
  tRespCorrs_2016last_HEP17_d1[0]->GetYaxis()->SetTitle("RespCorrs");
  tRespCorrs_2016last_HEP17_d1[0]->GetXaxis()->SetTitle("ieta");
  tRespCorrs_2016last_HEP17_d1[0]->Draw("p");
  tRespCorrs_2016last_HEP17_d1[1]->Draw("p,same");
  tRespCorrs_2016last_HEP17_d1[2]->Draw("p,same");
  tRespCorrs_2016last_HEP17_d1[3]->Draw("p,same");
  tRespCorrs_2016last_HEP17_d1[4]->Draw("same");
  tl1->Draw();
  tc1b->SaveAs("tRespCorrs_2016last.pdf");
  
  TCanvas *tc1c = new TCanvas("tc1c","tc1c",800,600);
  gPad->SetGrid(1);
  tGainsRespCorrs_2016last_HEP17_d1[0]->SetMaximum(1.5);
  tGainsRespCorrs_2016last_HEP17_d1[0]->SetMinimum(0.0);
  tGainsRespCorrs_2016last_HEP17_d1[0]->SetMarkerStyle(20);
  tGainsRespCorrs_2016last_HEP17_d1[1]->SetMarkerStyle(20);
  tGainsRespCorrs_2016last_HEP17_d1[2]->SetMarkerStyle(20);
  tGainsRespCorrs_2016last_HEP17_d1[3]->SetMarkerStyle(20);
  tGainsRespCorrs_2016last_HEP17_d1[1]->SetMarkerColor(2);
  tGainsRespCorrs_2016last_HEP17_d1[2]->SetMarkerColor(4);
  tGainsRespCorrs_2016last_HEP17_d1[3]->SetMarkerColor(6);
  tGainsRespCorrs_2016last_HEP17_d1[0]->SetTitleSize(0.05,"XY");
  tGainsRespCorrs_2016last_HEP17_d1[0]->GetYaxis()->SetTitle("Gains #times RespCorrs");
  tGainsRespCorrs_2016last_HEP17_d1[0]->GetXaxis()->SetTitle("ieta");
  tGainsRespCorrs_2016last_HEP17_d1[0]->Draw("p");
  tGainsRespCorrs_2016last_HEP17_d1[1]->Draw("p,same");
  tGainsRespCorrs_2016last_HEP17_d1[2]->Draw("p,same");
  tGainsRespCorrs_2016last_HEP17_d1[3]->Draw("p,same");
  tGainsRespCorrs_2016last_HEP17_d1[4]->Draw("same");
  tl1->Draw();
  tc1c->SaveAs("tGainsRespCorrs_2016last.pdf");
  
  TCanvas *tc2 = new TCanvas("tc2","tc2",800,600);
  gPad->SetGrid(1);
  tGains_2017start_HEP17_d2[0]->SetMaximum(0.0012);
  tGains_2017start_HEP17_d2[0]->SetMinimum(0.0);
  tGains_2017start_HEP17_d2[0]->SetMarkerStyle(20);
  tGains_2017start_HEP17_d2[1]->SetMarkerStyle(20);
  tGains_2017start_HEP17_d2[2]->SetMarkerStyle(20);
  tGains_2017start_HEP17_d2[3]->SetMarkerStyle(20);
  tGains_2017start_HEP17_d2[1]->SetMarkerColor(2);
  tGains_2017start_HEP17_d2[2]->SetMarkerColor(4);
  tGains_2017start_HEP17_d2[3]->SetMarkerColor(6);
  tGains_2017start_HEP17_d2[0]->SetTitleSize(0.05,"XY");
  tGains_2017start_HEP17_d2[0]->GetYaxis()->SetTitle("Gains");
  tGains_2017start_HEP17_d2[0]->GetXaxis()->SetTitle("ieta");
  tGains_2017start_HEP17_d2[0]->Draw("p");
  tGains_2017start_HEP17_d2[1]->Draw("p,same");
  tGains_2017start_HEP17_d2[2]->Draw("p,same");
  tGains_2017start_HEP17_d2[3]->Draw("p,same");
  tGains_2017start_HEP17_d2[4]->Draw("same");
  tl1->Draw();
  tc2->SaveAs("tGains_2017start.pdf");

  TCanvas *tc2c = new TCanvas("tc2c","tc2c",800,600);
  gPad->SetGrid(1);
  tGainsRespCorrs_2017start_HEP17_d2[0]->SetMaximum(0.0021);
  tGainsRespCorrs_2017start_HEP17_d2[0]->SetMinimum(0.0);
  tGainsRespCorrs_2017start_HEP17_d2[0]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[1]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[2]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[3]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[1]->SetMarkerColor(2);
  tGainsRespCorrs_2017start_HEP17_d2[2]->SetMarkerColor(4);
  tGainsRespCorrs_2017start_HEP17_d2[3]->SetMarkerColor(6);
  tGainsRespCorrs_2017start_HEP17_d2[0]->SetTitleSize(0.05,"XY");
  tGainsRespCorrs_2017start_HEP17_d2[0]->GetYaxis()->SetTitle("Gains #times RespCorrs");
  tGainsRespCorrs_2017start_HEP17_d2[0]->GetXaxis()->SetTitle("ieta");
  tGainsRespCorrs_2017start_HEP17_d2[0]->Draw("p");
  tGainsRespCorrs_2017start_HEP17_d2[1]->Draw("p,same");
  tGainsRespCorrs_2017start_HEP17_d2[2]->Draw("p,same");
  tGainsRespCorrs_2017start_HEP17_d2[3]->Draw("p,same");
  tGainsRespCorrs_2017start_HEP17_d2[4]->Draw("same");
  tl1->Draw();
  tc2c->SaveAs("tGainsRespCorrs_2017start.pdf");

  TCanvas *tc3 = new TCanvas("tc3","tc3",800,600);
  gPad->SetGrid(1);
  tGainsRespCorrs_2017start_HEP17_d2[6]->SetMaximum(4.0);
  tGainsRespCorrs_2017start_HEP17_d2[6]->SetMinimum(0.0);
  tGainsRespCorrs_2017start_HEP17_d2[6]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[6]->SetTitleSize(0.05,"XY");
  tGainsRespCorrs_2017start_HEP17_d2[6]->GetYaxis()->SetTitle("Gains #times RespCorrs");
  tGainsRespCorrs_2017start_HEP17_d2[6]->GetXaxis()->SetTitle("ieta");

  tGainsRespCorrs_2017start_HEP17_d2[7]->SetMarkerStyle(20);
  tGainsRespCorrs_2017start_HEP17_d2[7]->SetMarkerColor(2);
  tGainsRespCorrs_2016last_HEP17_d1[6]->SetLineColor(1);
  tGainsRespCorrs_2016last_HEP17_d1[7]->SetLineColor(2);

  tGainsRespCorrs_2017start_HEP17_d2[6]->Draw("p");
  tGainsRespCorrs_2017start_HEP17_d2[7]->Draw("p,same");
  tGainsRespCorrs_2016last_HEP17_d1[6]->Draw("hist,same");
  tGainsRespCorrs_2016last_HEP17_d1[7]->Draw("hist,same");
  TLegend *tl3 = new TLegend(0.2,0.65,0.5,0.8);
  tl3->AddEntry(tGainsRespCorrs_2017start_HEP17_d2[6],"2017 startup, iphi=63","p");
  tl3->AddEntry(tGainsRespCorrs_2017start_HEP17_d2[7],"2017 startup, iphi=65","p");
  tl3->AddEntry(tGainsRespCorrs_2016last_HEP17_d1[6],"2016 last, iphi=63");
  tl3->AddEntry(tGainsRespCorrs_2016last_HEP17_d1[7],"2016 last, iphi=65");
  tl3->Draw();

  tc3->SaveAs("tGainsRespCorrs_2016vs17.pdf");

}
