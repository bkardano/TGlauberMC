
#ifndef CentralityEstimator_H
#define CentralityEstimator_H 1

#include <vector>
#include "TString.h"
#include "TNamed.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1F.h"


class CentralityEstimator : public TNamed
{

    public:

	/**   Default constructor   **/
	CentralityEstimator() ;
        
    enum eMode { 
        kDefault    = 0,
        kNpartOnly  ,
        kNpart      ,
        kNcoll      ,
        kPileUp     ,
        kPileUp2    ,
        kFWAu       ,
        kFWAg       
    };
    
    UInt_t GetModeFromString(TString s)
    {
             if(s.CompareTo("Default")==0)     return kDefault; 
        else if(s.CompareTo("NpartOnly")==0)   return kNpartOnly; 
        else if(s.CompareTo("Npart")==0)       return kNpart; 
        else if(s.CompareTo("Ncoll")==0)       return kNcoll; 
        else if(s.CompareTo("PileUp2")==0)     return kPileUp2; 
        else if(s.CompareTo("PileUp")==0)      return kPileUp; 
        else if(s.CompareTo("FWAu")==0)        return kFWAu; 
        else if(s.CompareTo("FWAg")==0)        return kFWAg; 
        else return kDefault;
    }
    
        
        
        void      SetInputTree(TString filename, TString treename="nt_Au_Au")
                                         { fInputfilename = filename; fTreeName= treename;}
        void      SetOutputTree(TString filename) { fOutputfilename = filename;}
        void      LoadInputTree(Int_t nEntries = -1);
        Double_t  GetEstimator(Double_t f, UInt_t flag=kDefault);
//        void      AddEstimator(TString name, Double_t f, Double_t mu, Double_t k, UInt_t mode=kDefault);
        void      AddEstimator(TString name, Double_t f, Double_t mu, Double_t k, TString s="Default", Bool_t makeCentrality=kFALSE);
        Int_t     findEdgeBin(TH1F *htemp);
        TH1F*     makePercentiles(TH1F* hist, Float_t fractionXsection=100., Int_t direction=-1);
        void      Run();

        Double_t  NBD(Double_t n, Double_t mu, Double_t k) const;
        void      SetNBDhist(Double_t mu, Double_t k);
        Int_t     GetRandomNBD(Double_t k, Double_t nbar) const;
        /**   Destructor   **/
	virtual ~CentralityEstimator() {};
        
        
        void SetNpartMax(Int_t max)      { fNpartMax =   max; }
        void SetNcollMax(Int_t max)      { fNcollMax =   max; }
        void SetMultMax(Int_t max)       { fMultMax = max; }
        void SetOutDirName(TString name) { fOutDirName = name; }
        TH1F *GetNBDHisto ()             { return hNBD;   }
        TTree*  GetTree() const          {return fSimTree;}
      //  void SetMode(UInt_t mode)        { fMode = mode; }
      //  void SetMode(TString s)          { fMode = GetModeFromString(s); }
        
        
    private:

	/**   Data members  **/
        TH1F  *hNBD;
        TTree *fSimTree;
        TTree *fNewtree;
        
        TFile *fSim;
        TFile *fNewfile;
        
        Float_t fB, fNpart, fNpartA, fNcoll;
        Float_t fTempValue;
    //    Float_t fUsedMu, fUsedK;
        
        vector <TString>  estimatorName;
        vector <UInt_t>   estimatorMode;
        vector <Double_t> estimatorF;
        vector <Double_t> estimatorMu;
        vector <Double_t> estimatorK;
        vector <Bool_t>   estimatorMakeCentrality;
        
        Int_t nEntries;
        Int_t fNpartMax, fNcollMax;
        Int_t fMultMax;
        Int_t fBinSize;
        
        Int_t fFitMultMin;
        Int_t fNormMultMin;

        UInt_t fMode;
        
        TString fOutDirName;
        TString fOutputfilename;
        TString fInputfilename;
        TString fTreeName;
        
        ClassDef(CentralityEstimator, 2);

};


#endif
