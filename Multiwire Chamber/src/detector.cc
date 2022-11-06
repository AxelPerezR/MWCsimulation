#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

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
    G4cout << "Posición de la partícula en x: "<<  posParticle[0] << G4endl;
    //if(particleType == "mu-" || particleType == "mu+") return true;
    //if(particleType == "e-") return true;
    
    /*
    if(posParticle[0] == 5.0*cm/9 && posParticle[1] == 0.)
    {
    	track->SetTrackStatus(fStopAndKill);
    }  
	*/
    
    //Imprimimos el resultado
    //G4cout << "Posicion de la particula: "<< posParticle << G4endl;
    //G4cout << "z: "<< posParticle[2] << G4endl;

    //Queremos saber la energia de la particula
    G4double edep = aStep->GetTotalEnergyDeposit();
    //G4double edep = aStep->GetEnergy();
    G4cout << "Energia: "<< edep/MeV << G4endl;
    
    //Queremos saber en que celda se detecto.

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy number: "<< copyNo << G4endl;    

    //Posicion del detector
    
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << "Detector position: " << posDetector << G4endl;
    //Siempre que añada otra columna en run.cc debo de ponerla aqui
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    if(particleType == "mu-" || particleType == "mu+") return true;
    
    static std::ofstream dataEvt("dataEvt.txt");
    dataEvt << evt << std::endl;
    
    //if(edep == 0) return true;
    static std::ofstream dataE("dataE.txt");
    dataE << edep/eV << std::endl;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->FillNtupleDColumn(4, edep/keV);
    man->AddNtupleRow(0);
 
    return true;
}
