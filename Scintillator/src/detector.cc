#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	quEff = new G4PhysicsOrderedFreeVector();
	
	std::ifstream datafile;
	datafile.open("eff.dat");
	
	while(1)
	{
		G4double wlen, queff;
		
		datafile >> wlen >> queff;
		
		if(datafile.eof())
			break;
		
		G4cout << wlen << " " << queff << G4endl;
		
		quEff->InsertValues(wlen, queff);
	}
	
	datafile.close();
	
	quEff->SetSpline(false);
}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    //Una misma particula no se propague una vez sea detectada en la superficie, lo que no nos sirve.
    track->SetTrackStatus(fStopAndKill);
    
    //Cuando nuestra particula entra esta tiene un punto inicial y un punto final
    //Se supone que es mas complicado 
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4String particleType = aStep->GetTrack()->GetDefinition()->GetParticleName();
    //Imprimimos el nombre de la particula
    G4cout << "Particula: "<< particleType << G4endl;
    //if(particleType == "mu-" || particleType == "mu+") return true;
    //if(particleType == "e-") return true;
    
    //Imprimir el proceso de creación de la partícula
    //G4cout << "Process: " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;

    
    //Imprimimos el resultado
    //G4cout << "Posicion de la particula: "<< posParticle << G4endl;
    //G4cout << "z: "<< posParticle[2] << G4endl;

    //Queremos saber la energia de la particula
    G4double edep = aStep->GetTrack()->GetKineticEnergy();
    //G4double edep = aStep->GetEnergy();
    G4cout << "Energia: "<< edep/eV << G4endl;
    G4cout << "Longitud de onda: "<< 1.239841939/(edep/eV) << G4endl;
    G4double wlen = 1.239841939/(edep/eV)*1000;
    
    //Queremos saber en que celda se detecto.

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy number: "<< copyNo << G4endl;    

    //Posicion del detector
    
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    //G4cout << "Detector position: " << posDetector << G4endl;
    //Siempre que añada otra columna en run.cc debo de ponerla aqui
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    if(particleType == "mu-" || particleType == "mu+" || particleType == "e-") return true;
    
    /*
    static std::ofstream dataFx("dataFx.txt");
    static std::ofstream dataFy("dataFy.txt");
    
    if(particleType == "mu-") 
    {
    	dataFx << posParticle[0] << std::endl;
    	dataFy << posParticle[1] << std::endl;
    
    	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, (int)round(posParticle[0]));
	man->FillNtupleDColumn(2, (int)round(posParticle[1]));
	man->FillNtupleDColumn(3, edep/keV);
	man->FillNtupleDColumn(4, wlen);
    
        man->AddNtupleRow(0);
        return true;
    }
    */
    
    
    /*
    if(posDetector[1] == 0){
    	static std::ofstream dataDetectorX("dataX.txt");
    	dataDetectorX << posDetector[0] << std::endl;
    }    

    if(posDetector[0] == 0){
    	static std::ofstream dataDetectorY("dataY.txt");
    	dataDetectorY << posDetector[1] << std::endl;
    }
    */
    
    //static std::ofstream dataEvt("dataEvt.txt");
    //dataEvt << evt << std::endl;
    
    //if(edep == 0) return true;
    //static std::ofstream dataE("dataE.txt");
    //dataE << edep/keV << std::endl;
    
    static std::ofstream dataLength("dataLength.txt");
    static std::ofstream dataEvt("dataEvt.txt");
    
    if(G4UniformRand() < quEff->Value(wlen))
    {
    	dataLength << wlen << std::endl;
    	dataEvt << evt << std::endl;
    
		G4AnalysisManager *man = G4AnalysisManager::Instance();
		man->FillNtupleIColumn(0, evt);
		man->FillNtupleDColumn(1, posDetector[0]);
		man->FillNtupleDColumn(2, posDetector[1]);
		man->FillNtupleDColumn(3, edep/keV);
		man->FillNtupleDColumn(4, wlen);
		man->AddNtupleRow(0);
    }
    
    /*
	dataLength << wlen << std::endl;
	dataEvt << evt << std::endl;
    
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, posDetector[0]);
	man->FillNtupleDColumn(2, posDetector[1]);
	man->FillNtupleDColumn(3, edep/keV);
	man->FillNtupleDColumn(4, wlen);
	man->AddNtupleRow(0);
    */
	
    return true;
}
