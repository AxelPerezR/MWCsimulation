#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	//En parentesis va el numero de particulas por evento, cada run en Geant4 contiene varios eventos, y cada evento varias particulas, vamos a colocar una particulo por evento y un run sera la combinacion de varios eventos
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	CLHEP::HepRandom::setTheSeed((unsigned)clock());
	//Aqui definimos el tipo de particulo que deseamos utilizar, y esto es lo ultimo que tenemos que hacer
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//Por ejemplo, deseamos muones negativos
	G4String particleName="mu-";
	//Obtenemos las propiedades de esa particula
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

	//Generamos una particula en una posicion aleatoria
	G4double px = -1.0+2.0*G4UniformRand();
	G4double py = -1.0+2.0*G4UniformRand();

    //Revisar la geometria
	G4ThreeVector pos(10/2*px*cm,10/2*py*cm,1.1/2*cm);
	//G4ThreeVector pos(-3.889*cm,10/2*py*cm,1.1/2*cm);
	//Definimos que tiene una direccion de momento aleatoria
	G4ThreeVector mom(0.,0.,-1);
	//G4double EnergyRest = 105.7*MeV;
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(4.0*GeV);
	//fParticleGun->SetParticleEnergy(4.*GeV);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
