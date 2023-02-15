#include "CentralityEstimator.cxx"

void RunGlauberEstimator(TString flag="AuAu")
{
    //gROOT->LoadMacro("CentralityEstimator.cxx+g");
    
    CentralityEstimator *centEst = new CentralityEstimator();
    
    TString infilename ;
    TString treename ;
    TString outfilename ;    


    if(flag == "AuAu"){
        infilename = "./root/GlauberMC_Au3Au3_ntuple_23.6mb_r6.5541_a0.523_m0.9.root";
        treename = "nt_Au3_Au3";
        outfilename = "./root/GlauberMC_Au3Au3_ntuple_23.6mb_r6.5541_a0.523_m0.9_withEstimator.root";    
        
        centEst->AddEstimator("TOF"                  , -1.64069e-06 , 0.202237 , 6.36083  );
        //f = -1.64069e-06    mu = 0.202237    k = 6.36083    Chi2Min = 50.1303    
        centEst->AddEstimator("RPC"               ,   -1.64069e-06  , 0.503523  , 29.063 ); 
        // f = -1.64069e-06    mu = 0.503523    k = 29.063    Chi2Min = 39.0985
        centEst->AddEstimator("PrimaryParticleCand"  , -1.3825e-07 , 0.185581  , 7.60447 );
        //f = -1.3825e-07    mu = 0.185581    k = 7.60447    Chi2Min = 89.24
        centEst->AddEstimator("SelectedParticleCand" ,  -1.3825e-07  ,0.215636 , 5.18754  );
        //f = -1.3825e-07    mu = 0.215636    k = 5.18754    Chi2Min = 45.4244
    }
    if(flag == "AuAuPU"){
        infilename = "./root/GlauberMC_AuAu_system_run0.root";//GlauberMC_Au3Au3_ntuple_23.6mb_r6.5541_a0.523_m0.9.root";
        treename = "nt_Au_Au";
        outfilename = "./root/GlauberMC_Au3Au3_ntuple_23.6mb_r6.5541_a0.523_m0.9_withEstimatorPileUPSimon.root";    
        
         centEst->AddEstimator("TOFRPCnew"               ,  1.  , 0.742696 , 20.5058 ,"", kTRUE);
        
        centEst->AddEstimator("TOF"                  , -1.64069e-06 , 0.202237 , 6.36083 ,"", kTRUE);
        //f = -1.64069e-06    mu = 0.202237    k = 6.36083    Chi2Min = 50.1303    
        centEst->AddEstimator("RPC"               ,   -1.64069e-06  , 0.503523  , 29.063 ,"", kTRUE);
        // f = -1.64069e-06    mu = 0.503523    k = 29.063    Chi2Min = 39.0985
        centEst->AddEstimator("PrimaryParticleCand"  , -1.3825e-07 , 0.185581  , 7.60447 ,"", kTRUE);
        //f = -1.3825e-07    mu = 0.185581    k = 7.60447    Chi2Min = 89.24
        centEst->AddEstimator("SelectedParticleCand" ,  -1.3825e-07  ,0.215636 , 5.18754  ,"", kTRUE);
        //f = -1.3825e-07    mu = 0.215636    k = 5.18754    Chi2Min = 45.4244

		//new from μ = 0.242, k = 55.828, ε = -0.79 x 10^-6
        centEst->AddEstimator("SelectedParticleCandSimon" ,  -0.79e-06  ,0.242 , 55.828  ,"", kTRUE);

        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.1723045823 , 104. , "FWAu");

        centEst->AddEstimator("TOFRPCnewPileUp"               ,  1.  , 0.742696 , 20.5058 , "PileUp");
        
        centEst->AddEstimator("TOFPileUp"                  , -1.64069e-06 , 0.202237 , 6.36083 , "PileUp");
        //f = -1.64069e-06    mu = 0.202237    k = 6.36083    Chi2Min = 50.1303    
        centEst->AddEstimator("RPCPileUp"               ,   -1.64069e-06  , 0.503523  , 29.063  , "PileUp");
        // f = -1.64069e-06    mu = 0.503523    k = 29.063    Chi2Min = 39.0985
        centEst->AddEstimator("PrimaryParticleCandPileUp"  , -1.3825e-07 , 0.185581  , 7.60447  , "PileUp");
        //f = -1.3825e-07    mu = 0.185581    k = 7.60447    Chi2Min = 89.24
        centEst->AddEstimator("SelectedParticleCandPileUp" ,  -1.3825e-07  ,0.215636 , 5.18754  , "PileUp");
        //f = -1.3825e-07    mu = 0.215636    k = 5.18754    Chi2Min = 45.4244





    }
    else if(flag == "AgAgDec12"){
        infilename = "./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = "./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0_withEstimator.root"; 
        
        centEst->AddEstimator("TOFRPC"               ,  1           ,0.798707 , 120.746  );
        //f = 1    mu = 0.798707    k = 120.746    Chi2Min = 76.0805
        centEst->AddEstimator("TOF"                  , -7.07424e-06 , 0.274859 , 9.55442  );
        //f = -7.07424e-06    mu = 0.274859    k = 9.55442    Chi2Min = 23.0534
        centEst->AddEstimator("RPC"               ,   -1.96366e-06  , 0.604601  , 55.284 ); 
        //f = -1.96366e-06    mu = 0.604601    k = 55.284    Chi2Min = 33.0516
        centEst->AddEstimator("PrimaryParticleCand"  , -1.27035e-06 , 0.168996 , 6.23886 );
        //f = -1.27035e-06    mu = 0.168996    k = 6.23886    Chi2Min = 49.7326
        centEst->AddEstimator("SelectedParticleCand" , -1.78391e-06 , 0.221611 , 8.55049  );
        //f = -1.78391e-06    mu = 0.221611    k = 8.55049    Chi2Min = 108.999

        centEst->AddEstimator("TOFRPCPileUp"               ,  1           ,0.798707 , 120.746  , "PileUp");
        //f = 1    mu = 0.798707    k = 120.746    Chi2Min = 76.0805
        centEst->AddEstimator("TOFPileUp"                  , -7.07424e-06 , 0.274859 , 9.55442  , "PileUp");
        //f = -7.07424e-06    mu = 0.274859    k = 9.55442    Chi2Min = 23.0534
        centEst->AddEstimator("RPCPileUp"               ,   -1.96366e-06  , 0.604601  , 55.284  , "PileUp");
        //f = -1.96366e-06    mu = 0.604601    k = 55.284    Chi2Min = 33.0516
        centEst->AddEstimator("PrimaryParticleCandPileUp"  , -1.27035e-06 , 0.168996 , 6.23886  , "PileUp");
        //f = -1.27035e-06    mu = 0.168996    k = 6.23886    Chi2Min = 49.7326
        centEst->AddEstimator("SelectedParticleCandPileUp" , -1.78391e-06 , 0.221611 , 8.55049   , "PileUp");
        //f = -1.78391e-06    mu = 0.221611    k = 8.55049    Chi2Min = 108.999
    }
    else if(flag == "AgAgGen0"){
        infilename = "./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 
        
        centEst->AddEstimator("TOFRPC"               , -7.60045e-06  ,0.893058 , 2.56612  );
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOF"                  , -7.20045e-06 , 0.252345 , 3.45035  );
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPC"               ,   -5.20045e-06  , 0.590186 , 3.0533 ); 
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCand"  , -1.98545e-06 , 0.226791 , 4.46572 );
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
    }
    else if(flag == "AgAgGen2"){
        infilename = "./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 
        
        centEst->AddEstimator("TOFRPC"               , -7.60045e-06  ,0.893058 , 2.56612  );
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOF"                  , -7.20045e-06 , 0.252345 , 3.45035  );
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPC"               ,   -5.20045e-06  , 0.590186 , 3.0533 ); 
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCand"  , -1.98545e-06 , 0.226791 , 4.46572 );
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259

        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.13231 , 104. , "FWAg");
        
        centEst->AddEstimator("TOFRPCPileUp"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp"                  , -7.20045e-06 , 0.252345 , 3.45035  ,"PileUp");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp"  , -1.98545e-06 , 0.226791 , 4.46572 ,"PileUp");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp" , -1.15545e-06 , 0.254489 , 9.53861  ,"PileUp");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
        centEst->AddEstimator("TOFRPCPileUp2"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp2");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp2"                  , -7.20045e-06 , 0.252345 , 3.45035  ,"PileUp2");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp2"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp2");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp2"  , -1.98545e-06 , 0.226791 , 4.46572 ,"PileUp2");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp2" , -1.15545e-06 , 0.254489 , 9.53861  ,"PileUp2");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259 

    }
    else if(flag == "AgAgGen5"){
        infilename = "./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0fast.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_25.0mb_m0.9AgAg-snn25.0-md0.9-nd0.0-rc1-smax99.0_%s_withEstimatorSimon.root",flag.Data()); 
        
        centEst->AddEstimator("TOFRPC"               , -7.60045e-06  ,0.893058 , 2.56612 ,"", kTRUE);
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOF"                  , -7.20045e-06 , 0.252345 , 3.45035 ,"", kTRUE);
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPC"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"", kTRUE);
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCand"  , -1.91295e-06 , 0.251327 , 7.81392 ,"", kTRUE);
        //f = -1.91295e-06    mu = 0.251327    k = 7.81392    Chi2Min = 217.461
        //f = -1.91295e-06    mu = 0.251142    k = 0.549159    Chi2Min = 1.65913
        centEst->AddEstimator("SelectedParticleCand" , -8.39295e-06 , 0.353451 , 1.2746  ,"", kTRUE);
        //f = -8.39295e-06    mu = 0.353451    k = 1.2746    Chi2Min = 529.477
        //f = -8.39295e-06    mu = 0.351508    k = 0.474222    Chi2Min = 2.48484
        
        //new fits with fixed alpha
        centEst->AddEstimator("TOFNew"                , -1.64069e-06 , 0.213462 , 5.25124 ,"", kTRUE);
        //f = -1.64069e-06    mu = 0.213462    k = 5.25124    Chi2Min = 14.5059
        centEst->AddEstimator("RPCNew"                , -1.64069e-06 , 0.533414 , 22.3768 ,"", kTRUE);
        //f = -1.64069e-06    mu = 0.533414    k = 22.3768    Chi2Min = 6.10273
        
        
        //simon values
        // ToF: α = -2.04e-06, µ = 0.212 und k = 86.265
        // RPC: α = -2.41e-06, µ = 0.540 und k = 6.673
        centEst->AddEstimator("TOFSimon"               , -2.04e-06 , 0.212 , 86.265 ,"", kTRUE);
        centEst->AddEstimator("RPCSimon"               , -2.41e-06 , 0.540 , 6.673  ,"", kTRUE);
        
        
        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.13231 , 104. , "FWAg");
        
        centEst->AddEstimator("TOFRPCPileUp"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp"                  , -7.20045e-06 , 0.252345 , 3.45035  ,"PileUp");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp"   , -1.91295e-06 , 0.251142 , 0.549159 ,"PileUp");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp" , -1.15545e-06 , 0.254489 , 9.53861  ,"PileUp");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
        centEst->AddEstimator("TOFRPCPileUp2"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp2");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp2"                  , -7.20045e-06 , 0.252345 , 3.45035  ,"PileUp2");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp2"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp2");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp2"   , -1.91295e-06 , 0.251142 , 0.549159 ,"PileUp2");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp2" , -8.39295e-06 , 0.351508 , 0.474222  ,"PileUp2");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259 
        
    }
    
    
    else if(flag == "AgAg123Gen0"){
        infilename = "./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 
        
        centEst->AddEstimator("TOFRPC"               , -5.61795e-06  ,0.743202 , 3.9837  );
        //f = -5.61795e-06    mu = 0.743202    k = 3.9837    Chi2Min = 253.426
        centEst->AddEstimator("TOF"                  , -7.20045e-06 , 0.252345 , 3.45035  );
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPC"               ,   -5.20045e-06  , 0.590186 , 3.0533 ); 
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCand"  , -1.98545e-06 , 0.226791 , 4.46572 );
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
    }
    else if(flag == "AgAg123Gen2"){
        infilename = "./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 
        
        centEst->AddEstimator("TOFRPC"               , -5.61795e-06 , 0.748136 , 48.414  );
        //f = -5.61795e-06    mu = 0.748136    k = 48.414    Chi2Min = 228.059
        centEst->AddEstimator("TOF"                  , -7.58295e-06 , 0.227117 , 5.33314  );
        //f = -7.58295e-06    mu = 0.227117    k = 5.33314    Chi2Min = 263.911
        centEst->AddEstimator("RPC"               ,   -5.61795e-06 , 0.534034  , 17.7421 ); 
        //f = -5.61795e-06    mu = 0.534034    k = 17.7421    Chi2Min = 180.22
        centEst->AddEstimator("PrimaryParticleCand"  , -5.15295e-06, 0.274065 ,  6.91603  );
        //f = -5.15295e-06    mu = 0.274065    k = 6.91603    Chi2Min = 500.327
        centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );
        //not jet done
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.13231 , 104. , "FWAg");

    }
    else if(flag == "AgAg123Gen4"){
        infilename = "./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_Ag";
        outfilename = Form("./root/GlauberMC_AgAg_ntuple_23.6mb_m0.9AgAg-snn23.6-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 
        // no new fit - no change here to gen2 and gen0
        centEst->AddEstimator("TOFRPC"               , -5.61795e-06 , 0.748136 , 48.414  );
        // f = -5.61795e-06    mu = 0.748136    k = 48.414    Chi2Min = 228.059
        centEst->AddEstimator("TOF"                  , -7.58295e-06 , 0.228606 ,  6.80823  );
        //f = -7.58295e-06    mu = 0.228606    k = 6.80823    Chi2Min = 84.4556
        centEst->AddEstimator("RPC"               ,   -5.61795e-06 , 0.534034  , 17.7421 ); 
        //f = -5.61795e-06    mu = 0.534034    k = 17.7421    Chi2Min = 177.07
        centEst->AddEstimator("PrimaryParticleCand"  , -5.15295e-06, 0.279686 ,  8.71183   );
        //f = -5.15295e-06    mu = 0.279686    k = 8.71183    Chi2Min = 473.202
        //centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );  //not jet done
        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.13231 , 104. , "FWAg");
        
        // PileUp
        centEst->AddEstimator("TOFRPCPileUp"               , -5.61795e-06 , 0.748136 , 48.414  ,"PileUp");
        // f = -5.61795e-06    mu = 0.748136    k = 48.414    Chi2Min = 228.059
        centEst->AddEstimator("TOFPileUp"                  , -7.58295e-06 , 0.228606 ,  6.80823  ,"PileUp");
        //f = -7.58295e-06    mu = 0.228606    k = 6.80823    Chi2Min = 84.4556
        centEst->AddEstimator("RPCPileUp"               ,   -5.61795e-06 , 0.534034  , 17.7421 ,"PileUp");
        //f = -5.61795e-06    mu = 0.534034    k = 17.7421    Chi2Min = 177.07
        centEst->AddEstimator("PrimaryParticleCandPileUp"  , -5.15295e-06, 0.279686 ,  8.71183   ,"PileUp");
        //f = -5.15295e-06    mu = 0.279686    k = 8.71183    Chi2Min = 473.202
        centEst->AddEstimator("TOFPileUp2"                  , -7.58295e-06 , 0.228606 ,  6.80823  ,"PileUp2");
        //f = -7.58295e-06    mu = 0.228606    k = 6.80823    Chi2Min = 84.4556
        centEst->AddEstimator("RPCPileUp2"               ,   -5.61795e-06 , 0.534034  , 17.7421 ,"PileUp2");
        //f = -5.61795e-06    mu = 0.534034    k = 17.7421    Chi2Min = 177.07
        

    }
    else  if(flag == "AuC"){
        infilename = "./root/GlauberMC_AgC_ntuple_25mb_ntot.root";
        treename = "nt_Au3_C";
        outfilename = "./root/GlauberMC_AgC_ntuple_25mb_withEstimator.root"; 
        
    }
    else  if(flag == "AgC"){
        infilename = "./root/GlauberMC_AgC_ntuple_25.0mb_m0.9AgC-snn25.0-md0.9-nd0.0-rc1-smax99.0.root";
        treename = "nt_Ag_C";
        outfilename = Form("./root/GlauberMC_AgC_ntuple_25.0mb_m0.9AgC-snn25.0-md0.9-nd0.0-rc1-smax99.0_%s_withEstimator.root",flag.Data()); 

        //values from AgAg1580 gen0 and gen2
        centEst->AddEstimator("TOFRPC"               , -7.60045e-06  ,0.893058 , 2.56612  );
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOF"                  , -7.20045e-06 , 0.252345 , 3.45035  );
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPC"               ,   -5.20045e-06  , 0.590186 , 3.0533 ); 
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCand"  , -1.98545e-06 , 0.226791 , 4.46572 );
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCand" , -1.15545e-06 , 0.254489 , 9.53861  );
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259

        //new
        centEst->AddEstimator("FWSumChargeZ"         , 35.2 , 1.13231 , 104. , "FWAg");
        
        //PileUp test
        centEst->AddEstimator("TOFRPCPileUp"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp"                  , -7.20045e-06 , 0.252345 , 3.45035 ,"PileUp");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp"  , -1.98545e-06 , 0.226791 , 4.46572 ,"PileUp");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp" , -1.15545e-06 , 0.254489 , 9.53861 ,"PileUp");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
        centEst->AddEstimator("TOFRPCPileUp2"               , -7.60045e-06  ,0.893058 , 2.56612  ,"PileUp2");
        //f = -7.60045e-06    mu = 0.893058    k = 2.56612    Chi2Min = 185.81
        centEst->AddEstimator("TOFPileUp2"                  , -7.20045e-06 , 0.252345 , 3.45035 ,"PileUp2");
        //f = -7.20045e-06    mu = 0.252345    k = 3.45035    Chi2Min = 57.4873
        centEst->AddEstimator("RPCPileUp2"               ,   -5.20045e-06  , 0.590186 , 3.0533 ,"PileUp2");
        //f = -5.20045e-06    mu = 0.590186    k = 3.05334    Chi2Min = 70.127
        centEst->AddEstimator("PrimaryParticleCandPileUp2"  , -1.98545e-06 , 0.226791 , 4.46572 ,"PileUp2");
        //f = -1.98545e-06    mu = 0.226791    k = 4.46572    Chi2Min = 151.598
        centEst->AddEstimator("SelectedParticleCandPileUp2" , -1.15545e-06 , 0.254489 , 9.53861 ,"PileUp2");
        //f = -1.15545e-06    mu = 0.254489    k = 9.53861    Chi2Min = 133.259
    }
    
    if(!(gSystem->AccessPathName(Form("%s",outfilename.Data()),kFileExists))){
          cout<<endl;
          cout<<"WARNING: the file exist "<<outfilename.Data()<<endl;
          cout<<"         remove it ;) "<<endl;
          cout<<endl;
          return;
    }
    
    //centEst->SetMode("Default");
    centEst->SetInputTree ( infilename, treename);
    centEst->SetOutputTree ( outfilename );
    centEst->LoadInputTree();
    //centEst->SetNpartMax (400);   //not used in Default-Setting
    //centEst->SetNcollMax (1100);
    centEst->Run();

    cout << "Estimator calulaterd " << "\r" << endl;
    return;
}