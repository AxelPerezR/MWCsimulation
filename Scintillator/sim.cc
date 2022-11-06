//This is for creating main file

#include <iostream> 

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    //Muestra el volumen vacio
    UImanager->ApplyCommand("/vis/open OGL");
    //La posicion incial del detector
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    //Muestra el volumen madre
    UImanager->ApplyCommand("/vis/drawVolume");
    //Se refresca cada vez que lo ejecutamos
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    //Nos dibuja las trayectorias
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    //Nos dibuja trayectorias acumuladas de varios eventos
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    //Añadir ejes
    UImanager->ApplyCommand("/vis/scene/add/axes");
    //Color de las particulas
    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set mu+ cyan");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set mu- magenta");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set opticalphoton green");
    
    
    
    ui->SessionStart();
 
    return 0;
}
