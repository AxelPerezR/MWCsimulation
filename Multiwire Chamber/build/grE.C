#include <cmath>

void grE()
{
	TCanvas *c2 = new TCanvas();
		
	TH1F *hist = new TH1F("hist", "Energia de los electrones detectados", 1000, 0, 100000);
	
	TH1F *histE = (TH1F*)hist->Clone();
	histE->SetName("histE");
	
	fstream file;
	file.open("dataE.txt", ios::in);
	
	float value;
	
	while(1)
	{
		file >> value;
		hist->Fill(value);
		histE->Fill(value);
		if(file.eof()) break;
	} 
	
	file.close();
	
	hist->SetFillColor(kBlue-9);
	hist->SetLineWidth(2);
	hist->GetXaxis()->SetTitle("Energia (ev)");
	hist->GetYaxis()->SetTitle("Frecuencia");
	
	//Para que nos muestre o no las estadisticas 
	//hist->SetStats(0);
	gStyle->SetOptStat(11);
	
	gStyle->SetEndErrorSize(3);
	histE->SetLineColor(kRed-9);
	
	hist->Draw();
	histE->Draw("E1 SAME");
	
	//Leyenda
	//TLegend *leg = new TLegend(0.6,0.7,0.1,0.9);
	//leg->SetBorderSize(0);
	//leg->AddEntry(hist, "Data", "l");
	//leg->AddEntry(histE, "Error", "l");
	//leg->Draw();
}
