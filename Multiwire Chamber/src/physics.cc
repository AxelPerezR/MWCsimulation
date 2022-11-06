#include "physics.hh" 

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>

#include "A01MuonPhysics.hh"
#include "A01EMPhysics.hh"


MyPhysicsList::MyPhysicsList()
{
	//Mediciones electromagneticas
	RegisterPhysics(  new A01EMPhysics("standard EM")); 
	//RegisterPhysics (new G4EmStandardPhysics());
	//Fenoemenos opticos
	//RegisterPhysics (new G4OpticalPhysics());
	// Muon Physics
	RegisterPhysics(  new A01MuonPhysics("muon"));
}

MyPhysicsList::~MyPhysicsList()
{}



