#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
//#include "G4RotationMatrix.hh"
//Nuestro sistema de unidades
#include "G4SystemOfUnits.hh"

//Por el momento no nos interesa
#include "detector.hh"

#include "G4ElectroMagneticField.hh"
#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

#include "G4Navigator.hh"

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;

class G4VisAttributes;

//Estoy construyendo el detector
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction(); //Creador
    ~MyDetectorConstruction(); //Destructor

    virtual G4VPhysicalVolume *Construct();
    //void SetElectricField (const G4String&);
    
private:
	G4VPhysicalVolume *physField;
	G4LogicalVolume *logicChamber;
	G4LogicalVolume *logicDetector;
	G4LogicalVolume *logicWireDetector;
	G4LogicalVolume *logicWire;
	
	G4LogicalVolume *logicWireFieldH[1000];
	G4LogicalVolume *logicWireFieldV[1000];
	
	G4LogicalVolume *logicField;
	G4LogicalVolume *logicFieldXN;
	G4LogicalVolume *logicFieldZP;
	G4LogicalVolume *logicFieldZN;
	G4VisAttributes *wireVisAtt;
	G4VisAttributes *wireFieldVisAtt;
	G4VisAttributes *chamberVisAtt;
	
  	G4double degrees,nParts,V,r,log,Er,ExH,EyH,EzH,ExV,EyV,EzV,rDegrees;
	
	G4ElectricField *fEMfieldH[1000];
	G4EqMagElectricField *fEquationH[1000];
	G4MagIntegratorStepper *fStepperH[1000];
	G4FieldManager *fFieldMgrH[1000];
	G4double fMinStepH[1000];
	G4MagInt_Driver *fIntgrDriverH[1000];
	G4ChordFinder *fChordFinderH[1000];
	
	G4ElectricField *fEMfieldV[1000];
	G4EqMagElectricField *fEquationV[1000];
	G4MagIntegratorStepper *fStepperV[1000];
	G4FieldManager *fFieldMgrV[1000];
	G4double fMinStepV[1000];
	G4MagInt_Driver *fIntgrDriverV[1000];
	G4ChordFinder *fChordFinderV[1000];
	
	//Radial	
	//G4ElectroMagneticField *rField;
	//G4EqMagElectricField *rField;
	//G4MagIntegratorStepper *rField;
	//G4FieldManager *rField;
	//G4double rField;
	//G4ChordFinder *rField;
    //G4LogicalVolume *logicDetector;
    //SD significa Sensitive Detectors, Field es si deseamos agregar un campo electrico o magentico y aqui lo describimosS
    virtual void ConstructSDandField();
};

#endif
