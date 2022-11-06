#ifndef A01MuonPhysics_h
#define A01MuonPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"
//Lo encontre aqui: https://gitlab.cern.ch/geant4/geant4/blob/36c080dca608e34725b7089dbe1cb775a1de8e22/source/processes/electromagnetic/utils/include/G4MultipleScattering.hh
#include "G4VMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuIonisation.hh"
#include "G4hIonisation.hh"

class A01MuonPhysics : public G4VPhysicsConstructor
{
  public:
    A01MuonPhysics(const G4String& name="muon");
    virtual ~A01MuonPhysics();

  public:
    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    virtual void ConstructParticle();

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    virtual void ConstructProcess();

  protected:

};


#endif

