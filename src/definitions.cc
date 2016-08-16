#include "heppySkimTree.cc"

// constants
// ==============================================
double bbtagCut = 0.2;
// ==============================================

double fillMET(heppySkimTree* ntuple){
  return ntuple->met_pt;
}

double fillOne(heppySkimTree* ntuple){
  return 1.;
}

double fillLeadingJetMass(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=0) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_mpruned[0];
}


double fillSubLeadingJetMass(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=1) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_mpruned[1];
}

double fillLeadingJetPt(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=0) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_pt[0];
}

double fillSubLeadingJetPt(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=1) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_pt[1];
}

double fillLeadingBBtag(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=0) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_bbtag[0];
}

double fillSubLeadingBBtag(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=1) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_bbtag[1];
}

double fillLeadingTau21(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=0) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_tau2[0]/ntuple->FatjetAK08ungroomed_tau1[0];
}

double fillSubLeadingTau21(heppySkimTree* ntuple){
  if(ntuple->nFatjetAK08ungroomed<=1) 
    return -1.;
  else
    return ntuple->FatjetAK08ungroomed_tau2[1]/ntuple->FatjetAK08ungroomed_tau1[1];
}

double fillHT(heppySkimTree* ntuple){
  double HT = 0.;
  //cout << "nJets: " << ntuple->nJet << endl;
  for(int iJet = 0 ; iJet < ntuple->nJet ; iJet++ ){
    if( ntuple->Jet_pt[iJet]>30. && abs(ntuple->Jet_eta[iJet])<2.4 )
      HT+=ntuple->Jet_pt[iJet];
  }
  
  return HT;
}

double fillSingleJetMass(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 85. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 135. && 
	ntuple->FatjetAK08ungroomed_bbtag[i] > bbtagCut )
      return ntuple->FatjetAK08ungroomed_mpruned[i];
  }
  return -9999.;
}

double fillLooseSingleJetMass(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 50. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 200. )
      return ntuple->FatjetAK08ungroomed_mpruned[i];
  }
  return -9999.;
}

double fillSingleBBtag(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 85. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 135. && 
	ntuple->FatjetAK08ungroomed_bbtag[i] > bbtagCut )
      return ntuple->FatjetAK08ungroomed_bbtag[i];
  }
  return -9999.;
}

double fillSingleTau21(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 85. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 135. && 
	ntuple->FatjetAK08ungroomed_bbtag[i] > bbtagCut )
      return ntuple->FatjetAK08ungroomed_tau2[i]/ntuple->FatjetAK08ungroomed_tau1[i];
  }
  return -9999.;
}

double fillSinglePt(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 85. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 135. && 
	ntuple->FatjetAK08ungroomed_bbtag[i] > bbtagCut )
      return ntuple->FatjetAK08ungroomed_pt[i];
  }
  return -9999.;
}

double fillLooseSinglePt(heppySkimTree* ntuple){

  const int maxJets=2;
  for( int i = 0 ; i < maxJets ; i++){ 
    if( ntuple->nFatjetAK08ungroomed > i && 
	ntuple->FatjetAK08ungroomed_pt[i] > 300. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] > 50. && 
	ntuple->FatjetAK08ungroomed_mpruned[i] < 200. )
      return ntuple->FatjetAK08ungroomed_pt[i];
  }
  return -9999.;
}

double fillAnalysisBins(heppySkimTree* ntuple){
  double MET = ntuple->met_pt;
  double HT = fillHT(ntuple);

  if( MET > 300. && MET < 600. ){
    if( HT > 300. && HT < 1000. ){
      return 1.;
    }else if( HT > 1000. && HT < 2000. ){
      return 2.;
    }else if( HT > 2000. ){
      return 3.;
    }else 
      return -1.;
  }else if( MET > 600. && MET < 1000. ){
    if( HT > 600. && HT < 1000. ){
      return 4.;
    }else if( HT > 1000. && HT < 2000. ){
      return 5.;
    }else if( HT > 2000. ){
      return 6.;
    }else 
      return -1.;
  }else if( MET > 1000. ){
    if( HT > 1000. && HT < 2000. ){
      return 7.;
    }else if( HT > 2000. ){
      return 8.;
    }else 
      return -1.;
  }else 
    return -1.;
}

bool ptBinCut(heppySkimTree* ntuple , int ithBin){
  if( ithBin > 5 ) return false;
  double ptCut[6] = {300.,400.,500.,700.,1000.,999999.};
  double pt = fillLooseSinglePt(ntuple);
  return pt>ptCut[ithBin] && pt<ptCut[ithBin+1];
}
 
bool baselineCut(heppySkimTree* ntuple){
  double HT = fillHT(ntuple);

  return ( ntuple->naLeptons == 0            &&
	   ntuple->met_pt > 300.             &&
	   HT > 600.                         &&
	   ntuple->nFatjetAK08ungroomed >= 2 &&
	   ntuple->FatjetAK08ungroomed_pt[0] > 300. && 
	   ntuple->FatjetAK08ungroomed_mpruned[0] > 50. && 
	   ntuple->FatjetAK08ungroomed_mpruned[0] < 200. && 
	   ntuple->FatjetAK08ungroomed_pt[1] > 300. &&
	   ntuple->FatjetAK08ungroomed_mpruned[1] > 50. && 
	   ntuple->FatjetAK08ungroomed_mpruned[1] < 200. );

}

bool taggingSRCut(heppySkimTree* ntuple ){ 
  return ( baselineCut(ntuple) && 
	   ( ntuple->FatjetAK08ungroomed_bbtag[0] > bbtagCut || 
	     ntuple->FatjetAK08ungroomed_bbtag[1] > bbtagCut ));
}

bool taggingSBCut(heppySkimTree* ntuple ){
  return ( baselineCut(ntuple) && 
	   ntuple->FatjetAK08ungroomed_bbtag[0] < bbtagCut && 
	   ntuple->FatjetAK08ungroomed_bbtag[1] < bbtagCut );
}

bool singleHiggsTagCut(heppySkimTree* ntuple , int nthJet = 0 ){
  double HT = fillHT(ntuple);

  return ( ntuple->naLeptons == 0            &&
	   ntuple->met_pt > 300.             &&
	   HT > 600.                         &&
	   ntuple->nFatjetAK08ungroomed > nthJet &&
	   ntuple->FatjetAK08ungroomed_pt[nthJet] > 300. && 
	   ntuple->FatjetAK08ungroomed_mpruned[nthJet] > 85. && 
	   ntuple->FatjetAK08ungroomed_mpruned[nthJet] < 135. && 
	   ntuple->FatjetAK08ungroomed_bbtag[nthJet] > bbtagCut ); 

}

bool doubleHiggsTagCut(heppySkimTree* ntuple , int nthJet = 0 ){
  double HT = fillHT(ntuple);

  return ( ntuple->naLeptons == 0            &&
	   ntuple->met_pt > 300.             &&
	   HT > 600.                         &&
	   ntuple->nFatjetAK08ungroomed > 2 &&
	   ntuple->FatjetAK08ungroomed_pt[0] > 300. && 
	   ntuple->FatjetAK08ungroomed_mpruned[0] > 85. && 
	   ntuple->FatjetAK08ungroomed_mpruned[0] < 135. && 
	   ntuple->FatjetAK08ungroomed_bbtag[0] > bbtagCut &&
	   ntuple->FatjetAK08ungroomed_pt[1] > 300. && 
	   ntuple->FatjetAK08ungroomed_mpruned[1] > 85. && 
	   ntuple->FatjetAK08ungroomed_mpruned[1] < 135. && 
	   ntuple->FatjetAK08ungroomed_bbtag[1] > bbtagCut ); 

}

