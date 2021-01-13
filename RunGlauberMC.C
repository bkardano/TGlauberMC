void RunGlauberMC(TString flag="AuAu")
{
  //load libraries
  gROOT->LoadMacro("./runglauber.C+");


  //---------------------------------------------------//
  // SETTINGS
  //---------------------------------------------------//
  // general
  Bool_t bPrint    = kTRUE;
  
  Int_t nevents = 1e6;// 3e6; //1e5; // number of events to simulate 
  // supported systems are e.g. "p", "d", "Si", "Au", "Pb", "U" 
  Option_t *sysA="Au3"; 
  Option_t *sysB="Au3";
  Double_t signn=23.6; //43.6;// 25; // inelastic nucleon nucleon cross section
  Double_t mind=0.9;
  Double_t bmax=0.;

  TString pdir = Form("./root/");
  gSystem->mkdir(pdir.Data(), kTRUE);

  if(flag == "AgAg"){
          sysA="Ag"; 
          sysB="Ag";
          signn=25.; 
  }
  else if(flag == "AgAg123"){
          sysA="Ag"; 
          sysB="Ag";
          signn=23.6; 
  }
  else  if(flag == "AuC"){
          sysA="Au"; 
          sysB="C";
          signn=23.6; 
  }
  else  if(flag == "AgC"){
          sysA="Ag"; 
          sysB="C";
          signn=25.;
          bmax=14.; 
  }
  else  if(flag == "AgC1230"){
          sysA="Ag"; 
          sysB="C";
          signn=23.6;
          bmax=14.; 
  }
  else  if(flag == "CC1"){
          sysA="C"; 
          sysB="C";
          signn=22.; 
  }
  else  if(flag == "CC2"){
          sysA="C"; 
          sysB="C";
          signn=26.; 
  }

  else return;

  //  TGlauberMC(const char* NA = "Pb", const char* NB = "Pb", Double_t xsect = 42, Double_t xsectpn = 0, Double_t xsectsigma=0);

  //TGlauberMC *mcg = reinterpret_cast<TGlauberMC *>(gInterpreter->ProcessLine(".L ./runglauber.C"));

  TGlauberMC *mcg = new TGlauberMC(sysA,sysB,signn);
  mcg->SetMinDistance(mind);
//  mcg->SetRA(r,a);
  mcg->SetCalcArea(kTRUE);
  mcg->SetCalcLength(kTRUE);
  if(bmax>0)mcg->SetBmax(bmax);

  const char *fname=mcg->Str2(); // name output file
  TString outfilename = Form("%sGlauberMC_%s%s_ntuple_%2.1fmb_m%2.1f%s.root",pdir.Data(), sysA, sysB, signn, mind , fname );    
  printf("filename: \t%s\n",outfilename.Data());
  TFile *outputFile = NULL;
  if((gSystem->AccessPathName(Form("%s",outfilename.Data()),kFileExists))){
        outputFile = TFile::Open(outfilename.Data(),"RECREATE",outfilename.Data(),9);
  }
  else{
        cout<<endl;
        cout<<"WARNING: the file exist "<<outfilename.Data()<<endl;
        cout<<"         remove it ;) "<<endl;
        cout<<endl;
        return;
  }

  mcg->Run(nevents);

  TNtuple  *nt=mcg->GetNtuple();
  TNtuple  *ntInfo=mcg->GetNtupleInfo();
  TFile out(outfilename.Data(),"recreate",outfilename.Data(),9);
  if(nt) nt->Write();
  if(ntInfo) ntInfo->Write();

  printf("total cross section with a nucleon-nucleon cross section \t%f is \t%f  \n",signn,mcg->GetTotXSect());
  out.Close();

}
