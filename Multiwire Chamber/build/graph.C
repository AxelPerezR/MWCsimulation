void graph()
{
	TCanvas *c1 = new TCanvas();
		
	TH1F *hist = new TH1F("hist", "Frecuencia de eventos", 1000, 0, 1000);
	
	TH1F *histE = (TH1F*)hist->Clone();
	histE->SetName("histE");
	
	fstream file;
	file.open("stuff.txt", ios::in);
	
	int value;
	
	while(1)
	{
		file >> value;
		hist->Fill(value);
		histE->Fill(value);
		if(file.eof()) break;
	} 
	
	file.close();
	
	hist->SetFillColor(kBlue-9);
	hist->GetXaxis()->SetTitle("Muon disparado");
	hist->GetYaxis()->SetTitle("Electrones detectados");
	
	//Para que nos muestre o no las estadisticas 
	hist->SetStats(0);
	//gStyle->SetOptStat(11);
	
	histE->SetLineColor(kRed);
	
	hist->Draw();
	histE->Draw("E1 SAME");
	
	//Leyenda
	//TLegend *leg = new TLegend(0.6,0.7,0.1,0.9);
	//leg->SetBorderSize(0);
	//leg->AddEntry(hist, "Data", "l");
	//leg->AddEntry(histE, "Error", "l");
	//leg->Draw();
}
