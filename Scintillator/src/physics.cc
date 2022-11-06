#include "physics.hh"
#include "G4MuIonisation.hh" 
#include "OpticalPhysics.hh"

MyPhysicsList::MyPhysicsList()
{
	//Mediciones electromagneticas
	RegisterPhysics (new G4EmStandardPhysics());
	//Fenoemenos opticos
	RegisterPhysics (new G4OpticalPhysics());
	RegisterPhysics(new OpticalPhysics("optical"));
}

MyPhysicsList::~MyPhysicsList()
{}



