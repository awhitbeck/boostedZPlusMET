#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>

#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"

using namespace std;

int main(int argc, char** argv){

    int MAX_EVENTS(99999999);
    if( argc >= 2 )
        MAX_EVENTS = atoi(argv[1]);

    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
  
    skimSamples skims(skimSamples::kLowDphi);
    typedef plot<RA2bTree> plot;

    plot METplot(*fillMET<RA2bTree>,"MET_lowDPhi_baseline","MET [GeV]",15,300.,800.);
    plot HTplot(*fillHT<RA2bTree>,"HT_lowDPhi_baseline","H_{T} [GeV]",17,300,2000.);
    plot NJetsplot(*fillNJets<RA2bTree>,"NJets_lowDPhi_baseline","n_{j}",14,1.5,15.5);
    plot BTagsplot(*fillBTags<RA2bTree>,"BTags_lowDPhi_baseline","n_{b}",6,-0.5,5.5);

    plot J2NbhadronPlot(*fillLeadingNbHadrons<RA2bTree>,"J1pt_numBhadrons_baseline","n_{b-had}",5,-0.5,4.5);
    plot J1NbhadronPlot(*fillSubLeadingNbHadrons<RA2bTree>,"J2pt_numBhadrons_baseline","n_{b-had}",5,-0.5,4.5);

    vector<plot> LeadingBBdiscVersusNbHad;
    TString binLabel;
    for( int i=0; i<5 ; i++){    
        binLabel="";
        binLabel+=i;
        LeadingBBdiscVersusNbHad.push_back(plot(*fillLeadingBBtag<RA2bTree>,"J1pt_BBtag_lowDPhi_NbHad"+binLabel,"bb-disc",20,-1,1));
    }
    vector<plot> SubLeadingBBdiscVersusNbHad;
    for( int i=0; i<5 ; i++){    
        binLabel="";
        binLabel+=i;
        SubLeadingBBdiscVersusNbHad.push_back(plot(*fillSubLeadingBBtag<RA2bTree>,"J2pt_BBtag_lowDPhi_NbHad"+binLabel,"bb-disc",20,-1,1));
    }

    plot DeltaPhi1plot(*fillDeltaPhi1<RA2bTree>,"DeltaPhi1_lowDPhi_baseline","#Delta#Phi_{1}",20,0,3.1415);
    plot DeltaPhi2plot(*fillDeltaPhi2<RA2bTree>,"DeltaPhi2_lowDPhi_baseline","#Delta#Phi_{2}",20,0,3.1415);
    plot DeltaPhi3plot(*fillDeltaPhi3<RA2bTree>,"DeltaPhi3_lowDPhi_baseline","#Delta#Phi_{3}",20,0,3.1415);
    plot DeltaPhi4plot(*fillDeltaPhi4<RA2bTree>,"DeltaPhi4_lowDPhi_baseline","#Delta#Phi_{4}",20,0,3.1415);

    plot J1pt_Massplot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass_lowDPhi_baseline","m_{J} [GeV]",20,50.,200.);
    plot J2pt_Massplot(*fillSubLeadingJetMass<RA2bTree>,"J2pt_Mass_lowDPhi_baseline","m_{J} [GeV]",20,50.,200.);
    plot J1bbtag_Massplot(*fillLeadingBBtagJetMass<RA2bTree>,"J1bbtag_Mass_lowDPhi_baseline","m_{J} [GeV]",20,50.,200.);
    plot J2bbtag_Massplot(*fillSubLeadingBBtagJetMass<RA2bTree>,"J2bbtag_Mass_lowDPhi_baseline","m_{J} [GeV]",20,50.,200.);

    plot J1pt_BBplot(*fillLeadingBBtag<RA2bTree>,"J1pt_BBtag_lowDPhi_baseline","bb-tag",20,-1.,1.);
    plot J2pt_BBplot(*fillSubLeadingBBtag<RA2bTree>,"J2pt_BBtag_lowDPhi_baseline","bb-tag",20,-1.,1.);
    plot J1bbtag_BBplot(*fillLeadingBBtagJetBBtag<RA2bTree>,"J1bbtag_BBtag_lowDPhi_baseline","bb-tag",20,-1.,1.);
    plot J2bbtag_BBplot(*fillSubLeadingBBtagJetBBtag<RA2bTree>,"J2bbtag_BBtag_lowDPhi_baseline","bb-tag",20,-1.,1.);

    plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_lowDPhi_baseline","#tau_{21}",20,0.,1.);
    plot J2pt_Tau21plot(*fillSubLeadingTau21<RA2bTree>,"J2pt_Tau21_lowDPhi_baseline","#tau_{21}",20,0.,1.);
    plot J1bbtag_Tau21plot(*fillLeadingBBtagJetTau21<RA2bTree>,"J1bbtag_Tau21_lowDPhi_baseline","#tau_{21}",20,0.,1.);
    plot J2bbtag_Tau21plot(*fillSubLeadingBBtagJetTau21<RA2bTree>,"J2bbtag_Tau21_lowDPhi_baseline","#tau_{21}",20,0.,1.);

    plot J1pt_Ptplot(*fillLeadingJetPt<RA2bTree>,"J1pt_Pt_lowDPhi_baseline","p_{T,J} [GeV]",40,300.,2300.);
    plot J2pt_Ptplot(*fillSubLeadingJetPt<RA2bTree>,"J2pt_Pt_lowDPhi_baseline","p_{T,J} [GeV]",40,300.,2300.);
    plot J1bbtag_Ptplot(*fillLeadingBBtagJetPt<RA2bTree>,"J1bbtag_Pt_lowDPhi_baseline","p_{T,J} [GeV]",40,300.,2300.);
    plot J2bbtag_Ptplot(*fillSubLeadingBBtagJetPt<RA2bTree>,"J2bbtag_Pt_lowDPhi_baseline","p_{T,J} [GeV]",40,300.,2300.);

    plot J1pt_JetFlavorPlot(*fillLeadingJetFlavor<RA2bTree>,"J1pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);
    plot J2pt_JetFlavorPlot(*fillSubLeadingJetFlavor<RA2bTree>,"J2pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);

    vector<plot> plots;
    plots.push_back(J1NbhadronPlot);
    plots.push_back(J2NbhadronPlot);
    plots.push_back(METplot);
    plots.push_back(HTplot);
    plots.push_back(NJetsplot);
    plots.push_back(BTagsplot);

    plots.push_back(DeltaPhi1plot);
    plots.push_back(DeltaPhi2plot);
    plots.push_back(DeltaPhi3plot);
    plots.push_back(DeltaPhi4plot);

    plots.push_back(J1pt_Massplot);
    plots.push_back(J2pt_Massplot);
    plots.push_back(J1bbtag_Massplot);
    plots.push_back(J2bbtag_Massplot);
    plots.push_back(J1pt_BBplot);
    plots.push_back(J2pt_BBplot);
    plots.push_back(J1bbtag_BBplot);
    plots.push_back(J2bbtag_BBplot);
    plots.push_back(J1pt_Tau21plot);
    plots.push_back(J2pt_Tau21plot);
    plots.push_back(J1bbtag_Tau21plot);
    plots.push_back(J2bbtag_Tau21plot);
    plots.push_back(J1pt_Ptplot);
    plots.push_back(J2pt_Ptplot);
    plots.push_back(J1bbtag_Ptplot);
    plots.push_back(J2bbtag_Ptplot);
    plots.push_back(J1pt_JetFlavorPlot);
    plots.push_back(J2pt_JetFlavorPlot);

    // background MC samples
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){

        RA2bTree* ntuple = skims.ntuples[iSample];

        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            plots[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }
        for( int iPlot = 0 ; iPlot < LeadingBBdiscVersusNbHad.size() ; iPlot++){
            LeadingBBdiscVersusNbHad[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            LeadingBBdiscVersusNbHad[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }
        for( int iPlot = 0 ; iPlot < SubLeadingBBdiscVersusNbHad.size() ; iPlot++){
            SubLeadingBBdiscVersusNbHad[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            SubLeadingBBdiscVersusNbHad[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }

        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        int iBin=0; 
        double weight,trigWeight;
        TString filename;

        for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 1000000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;

            filename = ntuple->fChain->GetFile()->GetName();
            if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;

            if(! lowDphiBaselineCut(ntuple) ) continue;

            //if( iEvt > 100000 ) break;
            //std::vector<double> EfficiencyCenterUpDown = Eff_MetMhtSextetReal_CenterUpDown(ntuple->HT, ntuple->MHT, ntuple->NJets);
            //EfficiencyCenterUpDown[0];
            trigWeight = lowDphiTrigWeights(ntuple);
            weight = ntuple->Weight*lumi*customPUweights(ntuple)*trigWeight;
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
                iBin = plots[iPlot].fill(ntuple,weight);
                if( plots[iPlot].label == "J1pt_numBhadrons_baseline" && iBin > 0 && iBin <= 5 ){
                    LeadingBBdiscVersusNbHad[iBin-1].fill(ntuple,weight);
                }
                if( plots[iPlot].label == "J2pt_numBhadrons_baseline" && iBin > 0 && iBin <= 5 )
                    SubLeadingBBdiscVersusNbHad[iBin-1].fill(ntuple,weight);
            }
        }
    }

    // Data samples
    RA2bTree* ntuple = skims.dataNtuple;
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,"data_HTMHT");
    }
    for( int iPlot = 0 ; iPlot < LeadingBBdiscVersusNbHad.size() ; iPlot++){
        LeadingBBdiscVersusNbHad[iPlot].addDataNtuple(ntuple,"data");
    }
    for( int iPlot = 0 ; iPlot < SubLeadingBBdiscVersusNbHad.size() ; iPlot++){
        SubLeadingBBdiscVersusNbHad[iPlot].addDataNtuple(ntuple,"data");
    }
  
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    int iBin=0;
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 1000000 == 0 ) cout << "data_HTMHT: " << iEvt << "/" << numEvents << endl;
        if( !lowDphiBaselineCut(ntuple) ) continue;
        if( !lowDphiTriggerCut(ntuple) ) continue;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            iBin = plots[iPlot].fillData(ntuple);
            if( plots[iPlot].label == "J1pt_numBhadrons_baseline" && iBin > 0 && iBin <= 5 )
                LeadingBBdiscVersusNbHad[iBin-1].fillData(ntuple);
            if( plots[iPlot].label == "J2pt_numBhadrons_baseline" && iBin > 0 && iBin <= 5 )
                SubLeadingBBdiscVersusNbHad[iBin-1].fillData(ntuple);
        }
    }
    TFile* outputFile = new TFile("plotObs_lowDPhi_baseline.root","RECREATE");

    for( int iPlot = 0 ; iPlot < LeadingBBdiscVersusNbHad.size() ; iPlot++){
        LeadingBBdiscVersusNbHad[iPlot].buildSum();
        LeadingBBdiscVersusNbHad[iPlot].Write();
        LeadingBBdiscVersusNbHad[iPlot].sum->Write();
        TCanvas* can = new TCanvas("can","can",500,500);
        can->SetTopMargin(0.05);
        LeadingBBdiscVersusNbHad[iPlot].Draw(can,skims.ntuples,skims.signalNtuples,"../plots/plotObs_lowDPhi_baseline_plots",0.1,2.0,true);
    }
    for( int iPlot = 0 ; iPlot < SubLeadingBBdiscVersusNbHad.size() ; iPlot++){
        SubLeadingBBdiscVersusNbHad[iPlot].buildSum();
        SubLeadingBBdiscVersusNbHad[iPlot].Write();
        SubLeadingBBdiscVersusNbHad[iPlot].sum->Write();
        TCanvas* can = new TCanvas("can","can",500,500);
        can->SetTopMargin(0.05);
        SubLeadingBBdiscVersusNbHad[iPlot].Draw(can,skims.ntuples,skims.signalNtuples,"../plots/plotObs_lowDPhi_baseline_plots",0.1,2.0,true);
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write();
        TCanvas* can = new TCanvas("can","can",500,500);
        can->SetTopMargin(0.05);
        plots[iPlot].Draw(can,skims.ntuples,skims.signalNtuples,"../plots/plotObs_lowDPhi_baseline_plots",0.1,2.0,true);
    }
}
