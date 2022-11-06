void grMuon()
{
	TCanvas *c1 = new TCanvas();
				
	TH2F *hist = new TH2F("hist", "Posicion de los muones disparados en la superficie del detector de veto", 100, -50, 50, 100, -50, 50);
	
	gStyle->SetPalette(kRainBow);
	
	fstream fileX, fileY;
	fileX.open("dataFx.txt", ios::in);
	fileY.open("dataFy.txt", ios::in);
	
	float valueX;
	float valueY;
	//int valueRound;
	
	while(1)
	{
		fileX >> valueX;
		fileY >> valueY;
		//valueRound = (int)round(value);
		hist->Fill((int)round(valueX),(int)round(valueY));
		if(fileX.eof()) 
			break;
	} 
	
	fileX.close();
	fileY.close();
	
	hist->GetXaxis()->SetTitle("X(cm)");
	hist->GetYaxis()->SetTitle("Y(cm)");
	hist->GetZaxis()->SetTitle("Numero de muones");
	
	//Para que nos muestre o no las estadisticas 
	hist->SetStats(0);
	gStyle->SetOptStat(11);

	hist->Draw("lego2");

	//Leyenda
	//TLegend *leg = new TLegend(0.6,0.7,0.1,0.9);
	//leg->SetBorderSize(0);
	//leg->AddEntry(hist, "Data", "l");
	//leg->AddEntry(histE, "Error", "l");
	//leg->Draw();
}
