#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
//Nuestro sistema de unidades
#include "G4SystemOfUnits.hh"

#include "detector.hh"


//Estoy construyendo el detector
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction(); //Creador
    ~MyDetectorConstruction(); //Destructor

    virtual G4VPhysicalVolume *Construct();
    
private:
	G4VisAttributes* aluminiumVisAtt;
	G4VisAttributes* detectorVisAtt;
	G4LogicalVolume *logicDetector1;
	//G4LogicalVolume *logicDetector2;
	virtual void ConstructSDandField();
};

#endif
