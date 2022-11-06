void graph()
{
	TCanvas *c1 = new TCanvas();
		
	TH1F *hist = new TH1F("hist", "Detectores", 100, 0, 5);
	
	TH1F *histE = (TH1F*)hist->Clone();
	histE->SetName("histE");
	
	fstream fileX;
	fstream fileY;
	
	fileX.open("dataX.txt", ios::in);
	fileY.open("dataY.txt", ios::in);
	
	int value, valueX, valueY;
	
	while(1)
	{
		fileX >> valueX;
		fileY >> valueY;
		if(valueX==50) value=2;
		if(valueX==-50) value=4;
		hist->Fill(value);
		histE->Fill(value);
		if(valueY==50) value=1;
		if(valueY==-50) value=3;
		hist->Fill(value);
		histE->Fill(value);
		if(fileX.eof()) break;
	} 
	
	fileX.close();
	
	hist->SetFillColor(kBlue-9);
	hist->GetXaxis()->SetTitle("Detector");
	hist->GetYaxis()->SetTitle("Fotones detectados");
	
	//Para que nos muestre o no las estadisticas 
	hist->SetStats(0);
	//gStyle->SetOptStat(11);
	
	//histE->SetLineColor(kRed);
	
	hist->Draw();
	//histE->Draw("E1 SAME");
	
	//Leyenda
	//TLegend *leg = new TLegend(0.6,0.7,0.1,0.9);
	//leg->SetBorderSize(0);
	//leg->AddEntry(hist, "Data", "l");
	//leg->AddEntry(histE, "Error", "l");
	//leg->Draw();
}
