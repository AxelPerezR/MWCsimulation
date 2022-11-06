void graph()
{
	TGraph *gr = new TGraph();
	
	gr->SetMarkerStyle(kFullCircle);
	
	fstream file;
	file.open("dataEvt.txt", ios::in);
	
	while(1)
	{
		double x, y;
		file >> x >> y;
		gr->SetPoint(gr->GetN(), x, y);
		if(file.eof()) break;
	} 
	
	file.close();
	
	Tcanvas *c1 = new TCanvas();
	gr->Draw("ALP");
}
