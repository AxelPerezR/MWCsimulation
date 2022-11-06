#include "OpticalPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

OpticalPhysics::OpticalPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{
}

OpticalPhysics::~OpticalPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4OpticalPhoton.hh"

void OpticalPhysics::ConstructParticle()
{
  G4OpticalPhoton::OpticalPhotonDefinition();
}


#include "G4ProcessManager.hh"

void OpticalPhysics::ConstructProcess()
{
  theScintProcess = new G4Scintillation();  
  theScintProcess->SetScintillationYieldFactor(1.);
  theScintProcess->SetScintillationExcitationRatio(0.0);
  theScintProcess->SetTrackSecondariesFirst(true);
}

void OpticalPhysics::SetScintYieldFactor(G4double yf){
  if(theScintProcess)
    theScintProcess->SetScintillationYieldFactor(yf);
}


