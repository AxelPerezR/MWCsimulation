void grL()
{
	TCanvas *c1 = new TCanvas();
		
	//340,460		
	TH1F *hist = new TH1F("hist", "Fotones detectados por longitud de onda", 20000, 340, 460);
	
	TH1F *histE = (TH1F*)hist->Clone();
	histE->SetName("histE");
	
	fstream file;
	file.open("dataLength.txt", ios::in);
	
	float value;
	int valueRound;
	
	while(1)
	{
		file >> value;
		valueRound = (int)round(value);
		hist->Fill(valueRound);
		histE->Fill(valueRound);
		if(file.eof()) 
			break;
	} 
	
	file.close();
	
	hist->SetFillColor(kBlue-9);
	hist->SetLineWidth(3);
	hist->GetXaxis()->SetTitle("Longitud de onda (nm)");
	hist->GetYaxis()->SetTitle("Fotones detectados");
	
	//Para que nos muestre o no las estadisticas 
	hist->SetStats(1);
	gStyle->SetOptStat(11);
	
	gStyle->SetEndErrorSize(3);
	histE->SetLineColor(kRed-9);
	
	hist->Draw();
	//histE->Draw("E1 SAME");
	
	//Leyenda
	//TLegend *leg = new TLegend(0.6,0.7,0.1,0.9);
	//leg->SetBorderSize(0);
	//leg->AddEntry(hist, "Data", "l");
	//leg->AddEntry(histE, "Error", "l");
	//leg->Draw();
}
