#include "CentralityEstimator.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"

ClassImp(CentralityEstimator)


// -----   Default constructor   -------------------------------------------
CentralityEstimator::CentralityEstimator() 
  : TNamed(),
  fMode(kDefault)
{
        fTempValue=0;
}

void CentralityEstimator::LoadInputTree(Int_t n)
{    
    fSim = new TFile (fInputfilename.Data());
    if (!fSim) {
        std::cout << "LoadInputTree: *** No File: "<< fInputfilename <<"    - Error - " << std::endl;
        exit(EXIT_FAILURE);
    }

    fSimTree = (TTree*) fSim->Get(fTreeName.Data());
    
    if (!fSimTree) {
        std::cout << "LoadInputTree: *** No Tree:"<< fTreeName <<"     - Error - " << std::endl;
        exit(EXIT_FAILURE);
    }
    
    fSimTree->SetBranchAddress("B", &fB);
    fSimTree->SetBranchAddress("Npart", &fNpart);
    fSimTree->SetBranchAddress("NpartA", &fNpartA);
    fSimTree->SetBranchAddress("Ncoll", &fNcoll);
    
    if (n < 0){
        nEntries = fSimTree->GetEntries();
        std::cout << "SetInputTree: *** Warning - Number of Entries < 0 or not set. "
            "total event number "<< nEntries <<" will be used" << std::endl;
    }
    
}


Double_t CentralityEstimator::GetEstimator(Double_t f, UInt_t flag)
{
    Double_t Na    = 0.;    
    Double_t nHits = 0.;

    //if       (f == 1)               Na = fNpart;
    //if     (flag == "")               Na = fNpart;
    //else if(flag == "NpartThreshold") Na = (f + fNpart/fNpartMax) > 1.  ? fNpart : fNpart * (1 - fNpart/fNpartMax );
    //else if(flag == "Default")        Na = fNpart;
    //else if(flag == "Scaling")        Na = fNpart - f * (fNpartMax/fNpart);
    //else if(flag == "NpartOnly")      Na = f*fNpart + (1-f)*fNcoll; 
    //else if(flag == "Npart")          Na = TMath::Power(fNpart, f); 
    //else if(flag == "Ncoll")          Na = TMath::Power(fNcoll, f);
    //else if(flag == "PSD")            Na = f - fNpart;
    //else if(flag == "PileUp")         Na = fNpart;

    //new FW Parametrization
    // "RandomGauss(1.1323160638,0.2)*(47/107.)*(107-NpartA)*(TMath::Erf((NpartA-RandomGauss(0,0.2))/12.2/sqrt(2))):TOF+RPC"
    ///with Double_t RandomGauss(Double_t x1, Double_t x2){  return x1+gRandom->Gaus(0,x2);}
    
    if(flag == kFWAu){
            Na = (79./197.)*(197. - fNpartA);
            //  Zmax = (79./197.) * N_proj_spec = (Z/A)*(A - Npart/2.)
            for (Int_t j=0; j<Na; j++){
                 if(gRandom->Rndm() < (TMath::Erf( fNpartA*sqrt(2.)/f) ) ) nHits += (int)hNBD->GetRandom();
            }
    }
    else if(flag == kFWAg){
            Na = (47./107.)*(107. - fNpartA);
            //  Zmax = (47/107.) * N_proj_spec = (Z/A)*(A - Npart/2.)
            for (Int_t j=0; j<Na; j++){
                 if(gRandom->Rndm() < (TMath::Erf( fNpartA*sqrt(2.)/f) ) ) nHits += (int)hNBD->GetRandom();
            }
    }
    else{
            Na = fNpart;
            //else if     (flag == "NpartThreshold") Na = (f + fNpart/fNpartMax) > 1.  ? fNpart : fNpart * (1 - fNpart/fNpartMax );
            //else if(flag == "Scaling")        Na = fNpart - f * (fNpartMax/fNpart);
            
            if(flag == kNpartOnly)           Na = f*fNpart + (1-f)*fNcoll; 
            else if(flag == kNpart)          Na = TMath::Power(fNpart, f); 
            else if(flag == kNcoll)          Na = TMath::Power(fNcoll, f);

            // // no lininiarity
            // Double_t p0 =     0.740718;//   +/-   0.0264785
            // Double_t p1 =  0.000187403;//   +/-   0.000252608
            // Double_t p2 = -8.92373e-07;//   +/-   5.56444e-07
            // non-liniarity - due reco efficiency 
            //  Double_t p0 =   0.784036;//   +/-   0.0264785
            //  Double_t p1 =  -1.16025e-06;//   +/-   0.000252608
            for (Int_t j=0; j<Na; j++){
                 if(gRandom->Rndm() < 1. + f *fNpart*fNpart ) nHits += (int)hNBD->GetRandom();
            }
            //  std::cout << "fNpartMax  " << fNpartMax << "  nHits  "<< nHits << "  Npart X " << fNpart << " Na  " << Na << " fMode "<< fMode << std::endl;
            if(flag == kPileUp2){   // add hit value of last event
                    Int_t buffer  = fTempValue;
                    fTempValue = nHits;
                    nHits += (int)(buffer * gRandom->Rndm());
            }

            if(flag == kPileUp){   // add hit value of last event
                    Int_t buffer  = fTempValue;
                    fTempValue = nHits;
                    nHits += buffer;
            }
    }
    return nHits;
}

//void CentralityEstimator::AddEstimator(TString name, Double_t f, Double_t mu, Double_t k, UInt_t mode)
//{
//    cout << "Adding Estimator: " << name <<"   f: " << f << "  mu: " << mu << " k: " << k << " mode:" << mode << endl;
//    estimatorName.push_back(name);
//    estimatorMode.push_back(mode);
//    estimatorF.push_back   (f);
//    estimatorMu.push_back  (mu);
//    estimatorK.push_back   (k);
//    
//}

void CentralityEstimator::AddEstimator(TString name, Double_t f, Double_t mu, Double_t k, TString s, Bool_t makeC)
{
    cout << "Adding Estimator: " << name <<"   f: " << f << "  mu: " << mu << " k: " << k << " mode #:" << GetModeFromString(s) << " mode :" << s <<endl;
    estimatorName.push_back(name);
    estimatorMode.push_back(GetModeFromString(s));
    estimatorF.push_back   (f);
    estimatorMu.push_back  (mu);
    estimatorK.push_back   (k);
    estimatorMakeCentrality.push_back(makeC);

    
}

Int_t CentralityEstimator::findEdgeBin(TH1F *htemp)
{
      if(!htemp) return 0;
      Int_t   MeanBin = htemp->FindBin(htemp->GetMean());
      Int_t   nBinsX  = htemp->GetNbinsX();
      Float_t ThresholdBinValue = FLT_MAX;
      Int_t   ThresholdBin = 0;
      for (Int_t i=MeanBin; i<nBinsX; i++) {
             if (htemp->GetBinContent(i)<ThresholdBinValue) {
                 ThresholdBinValue = htemp->GetBinContent(i);
                 ThresholdBin = htemp->GetBinLowEdge(i);
             }
      }
     Float_t QA=0;
     Float_t QA2=0;
     Int_t count=0;
     Int_t MinFitGaus2=0;

     Float_t gaus2Par1=0;
     Float_t gaus2Par2=0;
     Float_t gaus2Par3=0;
     Float_t buffer1=0,buffer2=0;
     TF1 *fgaus = new TF1("fgaus","gaus",0,htemp->GetNbinsX());



     for (Int_t j=MeanBin; j<ThresholdBin; j++) {
            htemp->Fit("fgaus","+QR0","",j,ThresholdBin);
            QA2=QA;
            buffer1 = gaus2Par2;
            buffer2 = gaus2Par3;
            gaus2Par1=fgaus->GetParameter(0);
            gaus2Par2=fgaus->GetParameter(1);
            gaus2Par3=fgaus->GetParameter(2);
            if(fgaus->GetNDF() > 1.) QA  = fgaus->GetChisquare()/fgaus->GetNDF();
                if(0) printf("gausFit QA %f, Par1 %f , Par2  %f, Par3 %f, IBin  %d\n",
                   QA,gaus2Par1,gaus2Par2,gaus2Par3,j);
            if  (  (gaus2Par2<buffer1) || (gaus2Par3>buffer2)) count++;
            if ( (QA<1.5) ) count++;
            if  (count>2) {MinFitGaus2=j-2; break;}
     }
     Double_t ochi2 = 0;
     
     // ======== Threshold Finder
     for (Int_t j=MinFitGaus2; j<nBinsX; j++) {
             if(fgaus->Eval(htemp->GetBinCenter(j)) < 1.){
                     ThresholdBin      = htemp->GetBinCenter(j);
                     break;
             }
     }
      return ThresholdBin;
}


TH1F* CentralityEstimator::makePercentiles(TH1F *htemp, Float_t fractionXsection, Int_t direction)
{
  if(!htemp) return 0;  
  if(fractionXsection<0.1) return 0;
  TH1F *hpercent  = (TH1F*) htemp->Clone("hpercent");
  TString name=htemp->GetName();   
  name.Append("_percentile");
  hpercent->SetNameTitle(name.Data(),name.Data());
  hpercent->Reset();
  Int_t maxBin = htemp->GetNbinsX();
  if(direction<0) maxBin = findEdgeBin(htemp);
  Float_t totIntegral = fractionXsection / htemp->Integral(1,maxBin); 
  if(direction<0){
      for (int ibin=1; ibin<=htemp->GetNbinsX(); ibin++){
          hpercent->SetBinContent(ibin, totIntegral * htemp->Integral(ibin,htemp->GetNbinsX()) );
      } 
  }
  else if(direction>0){
      for (int ibin=1; ibin<=htemp->GetNbinsX(); ibin++){
          hpercent->SetBinContent(ibin, totIntegral * htemp->Integral(1,ibin) );
      } 
  }
  return hpercent;
}

void CentralityEstimator::Run()
{
    fNewfile = new TFile(fOutputfilename ,"recreate");
    fNewtree = fSimTree->CloneTree();
    
    for(UInt_t iArray=0;iArray<estimatorName.size();iArray++){
            TH1F *hist = new TH1F("hist_temp","",500, 0, 500);
            hist->SetCanExtend(TH1::kAllAxes);
            hist->SetDirectory(0);
            
            cout << "Creating Estimator: " << estimatorName[iArray] <<" .... "<< endl;
            Float_t estimator;
            Float_t percentile;
            TBranch *bpt = fNewtree->Branch( estimatorName[iArray].Data() ,&estimator ,Form("%s/F",estimatorName[iArray].Data()) );
            SetNBDhist(estimatorMu[iArray], estimatorK[iArray]);
            for (Int_t i=0; i<nEntries; i++){
                fNewtree->GetEntry(i);
                estimator = GetEstimator(estimatorF[iArray],estimatorMode[iArray]);
                bpt->Fill();
                hist->Fill(estimator);
                if (!(i%100))  cout << "Filling Estimator: " << estimatorName[iArray].Data() <<"  Event # " << i << "\r" << flush;
            }
            cout << endl;
            //hist->Print("all");
            if(estimatorMakeCentrality[iArray]){
                cout << "Making CentralityPercentile: " << estimatorName[iArray] <<endl;
                TH1F *histPercent = (TH1F*) makePercentiles(hist);
                //histPercent->Print("all");
                TBranch *bpt2 = fNewtree->Branch( Form("%s_centrality",estimatorName[iArray].Data()) ,&percentile ,Form("%s_centrality/F",estimatorName[iArray].Data()) );
                for (Int_t i=0; i<nEntries; i++){
                    fNewtree->GetEntry(i);
                    //Int_t bin = histPercent->FindBin(estimator);
                    percentile = histPercent->Interpolate(estimator);
                    bpt2->Fill();
                    cout << "Filling Estimator:  " << estimator << "  Event # " << i << "  Percentile:  "<< percentile << "\r" << flush;
                }
            }
    }
    
    cout << "Making CentralityPercentile for ImpactParameter: "  << endl;
    TH1F *histImp = new TH1F("hist_Imp","",500, 0, 20);
    histImp->SetCanExtend(TH1::kAllAxes);
    histImp->SetDirectory(0);
    
    for (Int_t i=0; i<nEntries; i++){
        fNewtree->GetEntry(i);
        histImp->Fill(fB);
        if (!(i%100))  cout << "Filling ImpactParameter: " << fB <<"  Event # " << i << "\r" << flush;
    }
    cout << endl;
    TH1F *histImpPercent = (TH1F*) makePercentiles(histImp, 100., 1);
    Float_t percentileImp;
    TBranch *bptImp = fNewtree->Branch( "B_centrality" ,&percentileImp ,"B_centrality/F" );
    for (Int_t i=0; i<nEntries; i++){
        fNewtree->GetEntry(i);
        Int_t bin = histImpPercent->FindBin(fB);
        percentileImp = histImpPercent->GetBinContent(bin);
        bptImp->Fill();
        if (!(i%100))  cout << "Filling ImpactParameter Percentile: " << fB <<"  Event # " << i << "\r" << flush;
    }
    /*
    for(UInt_t iArray=0;iArray<estimatorName.size();iArray++){
            cout << "Making CentralityPercentile: " << estimatorName[iArray] <<endl;
            TH1F *histPercent = (TH1F*) makePercentiles(hist);
            Float_t estimator;
            Float_t percentile;
            TBranch *bpt = fNewtree->Branch( estimatorName[iArray].Data() ,&estimator ,Form("%s/F",estimatorName[iArray].Data()) );
            TBranch *bpt = fNewtree->Branch( Form("%s_centrality",estimatorName[iArray].Data()) ,&percentile ,Form("%s_centrality/F",estimatorName[iArray].Data()) );
            SetNBDhist(estimatorMu[iArray], estimatorK[iArray]);
            for (Int_t i=0; i<nEntries; i++)
            {
                fNewtree->GetEntry(i);
                estimator = GetEstimator(estimatorF[iArray],estimatorMode[iArray]);
                bpt->Fill();
                if (!(i%100))  cout << "Filling Estimator: " << estimatorName[iArray].Data() <<"  Event # " << i << "\r" << flush;
            }
            cout << endl;
    }
*/

   //fNewtree->Print();
   fNewtree->Write("", TObject::kOverwrite);
   
   fNewfile->Close();
        

}

void CentralityEstimator::SetNBDhist(Double_t mu, Double_t k)
{
    // Interface for TH1F.
    Int_t nBins = 300;
    
    
    hNBD = new TH1F("hNBD","",nBins, 0, nBins);
    hNBD->SetName(Form("nbd_%f_%f",mu,k));
    hNBD->SetDirectory(0);
    
    for (Int_t i=0; i<nBins; ++i) 
    {
        Double_t val = NBD(i, mu, k);
        if (val>1e-20) hNBD->SetBinContent(i+1, val);
//         std::cout << "val " << val << std::endl;    
    }

}


Double_t CentralityEstimator::NBD(Double_t n, Double_t mu, Double_t k) const
{
    // Compute NBD.
    Double_t F;
    Double_t f;

    if (n+k > 100.0) 
    {
        // log method for handling large numbers
        F  = TMath::LnGamma(n + k)- TMath::LnGamma(n + 1.)- TMath::LnGamma(k);
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        F = F+f;
        F = TMath::Exp(F);
    } 
    else 
    {
        F  = TMath::Gamma(n + k) / ( TMath::Gamma(n + 1.) * TMath::Gamma(k) );
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        f  = TMath::Exp(f);
        F *= f;
    }

    return F;
}

Int_t CentralityEstimator::GetRandomNBD(Double_t k, Double_t nbar) const
{
  // negative binomial distribution generator, S. Voloshin, 09-May-2007
  Double_t sum=0.;
  Int_t i=0;
  Double_t ran=gRandom->Rndm();
  Double_t trm=1./pow(1.+nbar/k,k);
  if (trm==0.)
  {
    cout<<"NBD overflow"<<"  nbar="<<nbar<<"   k="<<k<<endl;
    return -1;
  }
  for(i=0; i<2000 && sum<ran ; i++)
  {
    sum += trm;
    trm *= (k+i)/(i+1.)*(nbar/(nbar+k));
  }
  return i-1;
}