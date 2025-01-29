#include "./runglauber.C" 

void RunGlauberMC(TString flag="AuAu")
{
  //load libraries
  //gROOT->LoadMacro("./runglauber.C+"); // for old ROOT5


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
  Double_t xsectsigma=0;
  
  TString extraText = "";//"_test";

  TString pdir = Form("./root/");
  gSystem->mkdir(pdir.Data(), kTRUE);

  if(flag == "AuAu"){
          sysA="Au3"; 
          sysB="Au3";
          signn=23.6; 
  }
  else if(flag == "AuAu800"){
          sysA="Au3"; 
          sysB="Au3";
          signn=16.64; 
  }
  else if(flag == "AuAu400"){
          sysA="Au3"; 
          sysB="Au3";
          signn=2.0; 
  }
  else if(flag == "AgAg"){
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
          sysA="Au3"; 
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
  else if(flag == "pNb35"){
          sysA="p"; 
          sysB="Nb";
		  //plab = 4.338 GeV/c
		  //totsig_nn 41.83
		  //totsig_pn 42.19
		  //elastic 13
          signn=29.; 
  }
  else if(flag == "piW"){
          sysA="pi"; 
          sysB="W184";
          signn=34.3; 
  }
  else return;

  nevents = 1e5;

  TGlauberMC *mcg = new TGlauberMC(sysA,sysB,signn,xsectsigma);
  mcg->SetMinDistance(mind);
//  mcg->SetRA(r,a);
  if(bmax>0)mcg->SetBmax(bmax);
  mcg->SetDetail(2);

  const char *fname=mcg->Str2(); // name output file
  TString outfilename = Form("%s%s%s.root",pdir.Data(), fname, extraText.Data());    
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

  printf("total cross section: \t%.3f +- %.3f barn \t with a nucleon-nucleon cross section \t%.2f mb \n"
	  ,mcg->GetTotXSect(), mcg->GetTotXSectErr(),signn);
  out.Close();
  
  return;

}
