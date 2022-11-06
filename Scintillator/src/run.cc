#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    //Vamos a crear un archivo nuevo siempre que se ejecute
    //Esta funcion se incluye en root
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->OpenFile("output2.root");
    //Que tipo de informacion nos gustaria guardar
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    //man->CreateNtupleDColumn("fZ");
    man->CreateNtupleDColumn("E");
    man->CreateNtupleDColumn("L");
    man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->Write();
    man->CloseFile();
}
