/*------------------------------------------------------------------------------
ZCConfig.cpp

 Created : 2015-09-15  godshalk
 Modified: 2015-10-28  godshalk

------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <TString.h>
#include "../interface/NtupleProcConfig.h"

using std::cout;     using std::endl;   using std::stringstream;
using std::string;   using std::pair;   using std::vector;

NtupleProcConfig::NtupleProcConfig(TString fnc)
: ConfigReader(fnc)
{
  // TEST output
    cout << "    ZCConfig: Created.\n"
            "      Config Input File: " << fn_config << "\n"
         << endl;

  // Open and read in config file
    cout << "\t\t" << pt.get<string>("FILE LOCATIONS.muon") << endl;
    cout << "\t\t" << pt.get<float> ("MUON.muon_pt_min"   ) << endl;
    cout << endl;

    fn_ntuple["muon"   ] = pt.get<string>("FILE LOCATIONS.muon"   );
    fn_ntuple["elec"   ] = pt.get<string>("FILE LOCATIONS.elec"   );
    fn_ntuple["dy"     ] = pt.get<string>("FILE LOCATIONS.dy"     );
    fn_ntuple["dy1j"   ] = pt.get<string>("FILE LOCATIONS.dy1j"   );
    fn_ntuple["ww"     ] = pt.get<string>("FILE LOCATIONS.ww"     );
    fn_ntuple["wz"     ] = pt.get<string>("FILE LOCATIONS.wz"     );
    fn_ntuple["zz"     ] = pt.get<string>("FILE LOCATIONS.zz"     );
    fn_ntuple["ttlep"  ] = pt.get<string>("FILE LOCATIONS.ttlep"  );
    fn_ntuple["ttsemi" ] = pt.get<string>("FILE LOCATIONS.ttsemi" );
    fn_ntuple["tthad"  ] = pt.get<string>("FILE LOCATIONS.tthad"  );
    fn_ntuple["t_s"    ] = pt.get<string>("FILE LOCATIONS.t_s"    );
    fn_ntuple["t_t"    ] = pt.get<string>("FILE LOCATIONS.t_t"    );
    fn_ntuple["t_tw"   ] = pt.get<string>("FILE LOCATIONS.t_tw"   );
    fn_ntuple["tbar_s" ] = pt.get<string>("FILE LOCATIONS.tbar_s" );
    fn_ntuple["tbar_t" ] = pt.get<string>("FILE LOCATIONS.tbar_t" );
    fn_ntuple["tbar_tw"] = pt.get<string>("FILE LOCATIONS.tbar_tw");

    fn_output = pt.get<string>("FILE LOCATIONS.output");

    setWeight["dy"     ] = pt.get<float>("DATASET WEIGHTS.dy"     );
    setWeight["ww"     ] = pt.get<float>("DATASET WEIGHTS.ww"     );
    setWeight["wz"     ] = pt.get<float>("DATASET WEIGHTS.wz"     );
    setWeight["zz"     ] = pt.get<float>("DATASET WEIGHTS.zz"     );
    setWeight["tthad"  ] = pt.get<float>("DATASET WEIGHTS.tthad"  );
    setWeight["ttlep"  ] = pt.get<float>("DATASET WEIGHTS.ttlep"  );
    setWeight["ttsemi" ] = pt.get<float>("DATASET WEIGHTS.ttsemi" );
    setWeight["t_s"    ] = pt.get<float>("DATASET WEIGHTS.t_s"    );
    setWeight["t_t"    ] = pt.get<float>("DATASET WEIGHTS.t_t"    );
    setWeight["t_tw"   ] = pt.get<float>("DATASET WEIGHTS.t_tw"   );
    setWeight["tbar_s" ] = pt.get<float>("DATASET WEIGHTS.tbar_s" );
    setWeight["tbar_t" ] = pt.get<float>("DATASET WEIGHTS.tbar_t" );
    setWeight["tbar_tw"] = pt.get<float>("DATASET WEIGHTS.tbar_tw");

    minSVT = pt.get<float>("SVT OPERATING POINTS.minSVT");
    noSVT  = pt.get<float>("SVT OPERATING POINTS.noSVT" );

    stdCSVOpPts["NoHF"] = pt.get<float>("HF TAGGING OPERATING POINTS.NoHF");
    stdCSVOpPts["CSVL"] = pt.get<float>("HF TAGGING OPERATING POINTS.CSVL");
    stdCSVOpPts["CSVM"] = pt.get<float>("HF TAGGING OPERATING POINTS.CSVM");
    stdCSVOpPts["CSVT"] = pt.get<float>("HF TAGGING OPERATING POINTS.CSVT");
    stdCSVOpPts["CSVS"] = pt.get<float>("HF TAGGING OPERATING POINTS.CSVS");

    flatHFTagSF["NoHF"      ] = pt.get<float>("CSV SCALE FACTORS.NoHF"      );
    flatHFTagSF["CSVL"      ] = pt.get<float>("CSV SCALE FACTORS.CSVL"      );
    flatHFTagSF["CSVM"      ] = pt.get<float>("CSV SCALE FACTORS.CSVM"      );
    flatHFTagSF["CSVT"      ] = pt.get<float>("CSV SCALE FACTORS.CSVT"      );
    flatHFTagSF["CSVS"      ] = pt.get<float>("CSV SCALE FACTORS.CSVS"      );
    flatHFTagSF["CSVS_ljmis"] = pt.get<float>("CSV SCALE FACTORS.CSVS_ljmis");

    maxNumJets  = pt.get<int>("RUNNING VARIABLES.max_ntuple_jets" );
    maxNumMuons = pt.get<int>("RUNNING VARIABLES.max_ntuple_muons");
    maxNumElecs = pt.get<int>("RUNNING VARIABLES.max_ntuple_elecs");

    muonPtMin  = pt.get<float>("MUON.muon_pt_min" );
    muonEtaMax = pt.get<float>("MUON.muon_eta_max");
    //muon_iso
    //muon_id

    elecPtMin       = pt.get<float>("ELECTRON.elec_pt_min"        );
    elecEtaInnerMax = pt.get<float>("ELECTRON.elec_eta_inner_max" );
    elecEtaOuterMin = pt.get<float>("ELECTRON.elec_eta_outer_min" );
    elecEtaOuterMax = pt.get<float>("ELECTRON.elec_eta_outer_max" );
    //elec_iso
    //elec_id

    dilepInvMassMin = pt.get<float> ("DILEPTON.dimuon_invmass_min");
    dilepInvMassMax = pt.get<float> ("DILEPTON.dimuon_invmass_max");
    dilepMuonCharge = pt.get<string>("DILEPTON.dimuon_charge");
    dilepElecCharge = pt.get<string>("DILEPTON.dielec_charge");

    metMax          = pt.get<float>("MET.met_max");

    nJetsAnalyzed   = pt.get<float>("JET.num_jets_to_analyze");
    jetPtMin        = pt.get<float>("JET.jet_pt_min"         );
    jetEtaMax       = pt.get<float>("JET.jet_eta_max"        );

    jsonSelect      = pt.get<bool>("JSON.use_JSON");

    string triggerStr_muon    = pt.get<string>("TRIGGERS.muon_triggers"                );
    string triggerStr_elec    = pt.get<string>("TRIGGERS.elec_triggers"                );
    string binStr_jet_pt      = pt.get<string>("DIFFERENTIAL ANALYSIS.jet_pt_bins"     );
    string binStr_jet_eta     = pt.get<string>("DIFFERENTIAL ANALYSIS.jet_eta_bins"    );
    string binStr_dilepton_pt = pt.get<string>("DIFFERENTIAL ANALYSIS.dilepton_pt_bins");

  // Close config file.


  // Complete processing on config file variables.
    processTriggerString( muonTriggers  , triggerStr_muon    );
    processTriggerString( elecTriggers  , triggerStr_elec    );

    processBinString(     jetPtBins     , binStr_jet_pt      );
    processBinString(     jetEtaBins    , binStr_jet_eta     );
    processBinString(     dileptonPtBins, binStr_dilepton_pt );

    cout << "  TEST CONFIG FILE READ COMPLETE!! \n" << endl;

}


void NtupleProcConfig::processBinString(vector<pair<float,float> >& binSet, string& inputString)
{
    cout << "processBinString: INPUT STRING " << inputString << endl; 
    vector<float> binBounds = getListFromString<float>(inputString);
    int numBins = binBounds.size();
    binSet.push_back({binBounds[0], binBounds[numBins-1]});
    cout << "processBinString: PUSHING BACK " << binBounds[0] << "," << binBounds[numBins-1] << endl;
    for(int i=1; i<numBins; i++)
    {   // Remember, fencepost problem...
        binSet.push_back({binBounds[i-1], binBounds[i]});
        cout << "processBinString: PUSHING BACK " << binBounds[i-1] << "," << binBounds[i] << endl;
    }

    cout << "processBinString: FINAL PAIR LIST: ";
    for(auto& bin : binSet) cout << "(" << bin.first << "," << bin.second << "), ";
    cout << endl;
}


void NtupleProcConfig::processTriggerString(vector<int>& trigSet, string& inputString)
{
    trigSet = getListFromString<int>(inputString);
}
