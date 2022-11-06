#ifndef OpticalPhysics_HH
#define OpticalPhysics_HH

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"

#include "G4Scintillation.hh"

class OpticalPhysics : public G4VPhysicsConstructor
{
public: 
    OpticalPhysics(const G4String& name ="optical");
    virtual ~OpticalPhysics();

public: 
    virtual void ConstructParticle();
 
    virtual void ConstructProcess();

  void SetScintYieldFactor(G4double yf);

protected:
  
  G4Scintillation* theScintProcess;
};


#endif





