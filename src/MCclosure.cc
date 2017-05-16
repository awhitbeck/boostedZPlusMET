#include "CMS_lumi.cc"

void MCclosure(TString tag = "", bool doubleHiggsRegion = true){

    gROOT->ProcessLine(".L ~/tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TFile* f = new TFile("ALPHABEThistos"+tag+".root","READ");
    TH1F* hdata,*hmc;

    const int numSamples = 2;
    const int numMETbins = 2;
    double METbins[numMETbins+2] = {300,500,700,1500};

    const int numRegions = 4;
    TString sampleLabels[numSamples]={"sum","data"};
    //TString METlabels[numMETbins] = {"300","500","700"};
    TString regionLabels[numRegions] = {"doubletagSR","antitagSR","doubletagSB","antitagSB"};
    if( ! doubleHiggsRegion ){
        regionLabels[0] = "tagSR";
        regionLabels[2] = "tagSB";
    }

    TH1F* temp[numRegions];
    TH1F* MC[numRegions];

    for( int r = 0 ; r < numRegions ; r++ ){
        cout << "region: " << regionLabels[r] << endl;
        temp[r] = (TH1F*) f->Get("MET_"+regionLabels[r]+"_sum");
        //temp[r]->Add((TH1F*)f->Get("MET_"+regionLabels[r]+"_TTExtra"));
        temp[r]->Scale(35900.);
        MC[r] = new TH1F("MC_"+regionLabels[r],"MC_"+regionLabels[r],numMETbins+1,METbins);
        MC[r]->Sumw2();
        MC[r]->SetFillStyle(3490);
        MC[r]->SetLineColor(2);
        MC[r]->SetFillColor(2);
        MC[r]->GetXaxis()->SetTitle("MET [GeV]");
        MC[r]->GetYaxis()->SetTitle("Events");
        MC[r]->GetYaxis()->SetLabelFont(43);
        MC[r]->GetYaxis()->SetLabelSize(14);
        MC[r]->GetYaxis()->SetTitleFont(43);
        MC[r]->GetYaxis()->SetTitleSize(20);
        MC[r]->GetYaxis()->SetTitleOffset(1.6);

        MC[r]->GetXaxis()->SetLabelFont(43);
        MC[r]->GetXaxis()->SetLabelSize(14);
        MC[r]->GetXaxis()->SetTitleFont(43);
        MC[r]->GetXaxis()->SetTitleSize(20);
        MC[r]->GetXaxis()->SetTitleOffset(1.6);

        for( int b = 1 ; b <= numMETbins+1 ; b++ ){
            MC[r]->SetBinContent(b,temp[r]->GetBinContent(b));
            MC[r]->SetBinError(b,temp[r]->GetBinError(b));
            cout << "MC yield: " << temp[r]->GetBinContent(b) << " +/- " << temp[r]->GetBinError(b) << endl;
        }
    }

    TH1F* MCprediction = new TH1F(*MC[1]);
    MCprediction->SetNameTitle("MCprediction","MCprediction");
    MCprediction->Multiply(MC[2]);
    MCprediction->Divide(MC[3]);
    MCprediction->SetMarkerColor(1);
    MCprediction->SetMarkerStyle(8);
    MCprediction->SetLineColor(1);
    cout << "MC prediction (B*C/D)" << endl;
    for( int b = 1 ; b <= numMETbins+1 ; b++ ){
        cout << MCprediction->GetBinContent(b) << " +/- " << MCprediction->GetBinError(b) << endl;
    }

    TH1F* Closure = new TH1F(*MC[0]);
    Closure->Divide(MCprediction);
    Closure->GetYaxis()->SetTitle("#kappa");
    Closure->SetNameTitle("Closure","Closure");
    Closure->SetMarkerStyle(8);
    Closure->SetLineColor(1);
    Closure->GetYaxis()->SetRangeUser(0.,2.);
        
    Closure->GetYaxis()->SetLabelFont(43);
    Closure->GetYaxis()->SetLabelSize(14);
    Closure->GetYaxis()->SetTitleFont(43);
    Closure->GetYaxis()->SetTitleSize(20);
    Closure->GetYaxis()->SetTitleOffset(1.6);

    Closure->GetXaxis()->SetLabelFont(43);
    Closure->GetXaxis()->SetLabelSize(14);
    Closure->GetXaxis()->SetTitleFont(43);
    Closure->GetXaxis()->SetTitleSize(20);
    Closure->GetXaxis()->SetTitleOffset(2.);

    cout << "Closure A/(B*C/D)" << endl;
    for( int b = 1 ; b <= numMETbins+1 ; b++ ){
        cout << "bin " << b << ": " << Closure->GetBinContent(b) << " +/- " << Closure->GetBinError(b) << endl;
    }

    TCanvas* can = new TCanvas("can","can",500,500);
    gStyle->SetErrorX(0.5);
    TPad* topPad = new TPad("topPad","topPad",0.,0.4,.99,.99);
    TPad* botPad = new TPad("botPad","botPad",0.,0.01,.99,.39);
    botPad->SetBottomMargin(0.25);
    botPad->SetTopMargin(0.02);
    topPad->SetTopMargin(0.06);
    topPad->SetBottomMargin(0.17);
    topPad->Draw();
    botPad->Draw();
    topPad->cd();

    MC[0]->Draw("e2");
    MCprediction->Draw("p,e1,same");

    writeExtraText = true;
    extraText="Simulation";
    char lumiString[4];
    lumi_13TeV = "35.9 fb^{-1}";
    CMS_lumi( can , 4 , 0 );
    can->Update();
    can->RedrawAxis();
    can->GetFrame()->Draw();

    TLegend* leg = new TLegend(.6,.75,.9,.9);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->AddEntry(MCprediction,"MC (A)","f");
    leg->AddEntry(Closure,"B*C/D pred.","pl");
    leg->Draw();
    
    botPad->cd();
    Closure->Draw("p,e1");

    if( doubleHiggsRegion ){
        can->SaveAs("MCclosure_doubleHiggsRegion.png");
        can->SaveAs("MCclosure_doubleHiggsRegion.pdf");
        can->SaveAs("MCclosure_doubleHiggsRegion.eps");
    }else{
        can->SaveAs("MCclosure_singleHiggsRegion.png");
        can->SaveAs("MCclosure_singleHiggsRegion.pdf");
        can->SaveAs("MCclosure_singleHiggsRegion.eps");        
    }
}