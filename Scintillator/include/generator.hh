#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

//Para usar numeros aleatorios
#include "Randomize.hh"

#include "G4ParticleGun.hh"
//Porque queremos usar GeV u otras cosas
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
	MyPrimaryGenerator();
	~MyPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun *fParticleGun;
};

#endif
