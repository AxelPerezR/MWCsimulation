#include "construction.hh"
#include "G4IonisParamMat.hh"
#include "G4MuIonisation.hh"
#include "G4MuBetheBlochModel.hh"

//Visualizacion
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//Para una curva suave
#include "G4UserLimits.hh"

//Campo electrico
//#include "electricField.hh"
#include "G4AutoDelete.hh"

//Coseno y seno
#include <cmath>
#include <iostream>


//Constructor
MyDetectorConstruction::MyDetectorConstruction() : wireVisAtt(0)
  /*,
  fEMfield_1(0),
  fEquation_1(0),
  fStepper_1(0),
  fFieldMgr_1(0),
  fMinStep_1(0),
  fChordFinder_1(0)
  */
{}

//Destructor
MyDetectorConstruction::~MyDetectorConstruction()
{
	delete wireVisAtt;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	//Materiales con los que se va a trabajar
	
	G4double temperature = 273.15*kelvin;
	G4double pressure = 1.*atmosphere;
	
	//Metano
	G4Material *CH4 = new G4Material("CH4", 0.00067898*g/cm3, 2, kStateGas, temperature, pressure);
	CH4->AddElement(nist->FindOrBuildElement("C"), 1);
	CH4->AddElement(nist->FindOrBuildElement("H"), 4);
	
	//Argon
	G4Element *Ar = nist->FindOrBuildElement("Ar");
	
	//Gas
	G4Material *Gas = new G4Material("Gas", 0.0015895*g/cm3, 2, kStateGas, temperature, pressure);
	Gas->AddMaterial(CH4, 10.0*perCent);
	Gas->AddElement(Ar, 90.0*perCent);
	Gas->GetIonisation()->SetMeanExcitationEnergy(182*eV);
	
	//Oro
	G4Element *Au = nist->FindOrBuildElement("Au");
	
	//Tungsteno
	G4Element *W = nist->FindOrBuildElement("W");
	
	//Aleacion oro tungsteno
	G4Material *Alambre = new G4Material("Alambre", 20.2*g/cm3, 2);
	Alambre->AddElement(Au, 5.0*perCent);
	Alambre->AddElement(W, 95.0*perCent);
	
	
    //Material del mundo
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	//Definimos nuestro solidWorld en la mitad del tamaño del que queremos, aquì por ejemplo tenemos 1m por lado
    //11.1
	G4Box *solidWorld = new G4Box("solidWorld", 11.0*cm, 11.0*cm, 1.1*cm);
	
	//Nuestro volumen logico
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	
	//Volumen fisico, el primer parametro es la rotacion, el segundo parametro es donde esta centrado, el 0 despues de "physWorld" es el volumen madre, por si estamos haciendo un volumen sobre otro
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	//Definimos el volumen de nuestra camarita
	G4Box *solidChamber = new G4Box("solidChamber", 5.0*cm, 5.0*cm, 1.1/2*cm);
	
	//Definimos el volumen logico
	logicChamber = new G4LogicalVolume(solidChamber, Gas, "logicChamber");
	
	chamberVisAtt = new G4VisAttributes(G4Colour(0.47,0.96, 0.));
	chamberVisAtt->SetForceWireframe(true);
	chamberVisAtt->SetVisibility(true);
	logicChamber->SetVisAttributes(chamberVisAtt);
	
	//Volumen fisico
	G4VPhysicalVolume *physChamber = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicChamber, "physChamber", logicWorld, false, 0, true);
	
	//Campo	
	//Definimos el volumen de nuestro campo
	//G4Box *solidField = new G4Box("solidField", 5.0*cm/18, 5.0*cm, 1.1/2*cm);
	G4Box *solidField = new G4Box("solidField", 1.0*cm/2, 5.0*cm, 1.1/2*cm);
	
	//Definimos el volumen logico
	logicField = new G4LogicalVolume(solidField, Gas, "logicField");
	
	
	//Volumen fisico
	//X positivo
	//G4VPhysicalVolume *physField = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicField, "physField", logicChamber, false, 0, true);
	
	//physField = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicField, "physField", logicChamber, false, 0, true);
	
	//degrees = 4;
	//nParts = 360/degrees;
	nParts = 4;
	degrees = 360/nParts;
	
	//Campos cilindricos
	
	G4Tubs *wireField = new G4Tubs("wireField", 1.1*cm/4, 1.1*cm/2, 5.0*cm, 0*deg, degrees*deg);
	
	// Hacer invisible la superficie gaussiana
	wireFieldVisAtt = new G4VisAttributes();
	wireFieldVisAtt->SetVisibility(false);
	
	for(G4int i=0; i < nParts; i++)
	{
		G4RotationMatrix *wireFieldRotV = new G4RotationMatrix();
		wireFieldRotV->rotateX(90.*deg);
		wireFieldRotV->rotateZ((i+1)*degrees*deg);
		
		G4RotationMatrix *wireFieldRotH = new G4RotationMatrix();
		wireFieldRotH->rotateY(90.*deg);
		wireFieldRotH->rotateZ((i+1)*degrees*deg);
		
		logicWireFieldV[i] = new G4LogicalVolume(wireField, Gas, "logicWireFieldV[]");
		
		logicWireFieldH[i] = new G4LogicalVolume(wireField, Gas, "logicWireFieldH[]");
		
		//Aquí se puede comentar esto si se quiere visible
		//logicWireFieldV[i]->SetVisAttributes(wireFieldVisAtt); 
		//logicWireFieldH[i]->SetVisAttributes(wireFieldVisAtt);
		
		//G4VPhysicalVolume *physWireField = new G4PVPlacement(wireFieldRotH, G4ThreeVector(5.0*cm/9, 0., 0.), logicWireFieldH[i], "physWireField", logicChamber, false, 0, true); 
		G4VPhysicalVolume *physWireField = new G4PVPlacement(wireFieldRotV, G4ThreeVector(5.0/9*cm,0., 0.), logicWireFieldV[i], "physWireField", logicChamber, false, 0, true);
		
		for(G4int j=0; j < 8; j++)
		{
			//G4VPhysicalVolume *physWireFieldH = new G4PVPlacement(wireFieldRotH, G4ThreeVector(0., -5.0*cm+(j+1)*10.0*cm/9, 0.), logicWireFieldH[i], "physWireFieldH", logicChamber, false, 0, true);
			//G4VPhysicalVolume *physWireFieldV = new G4PVPlacement(wireFieldRotV, G4ThreeVector(-5.0*cm+(j+1)*10.0*cm/9, 0., 0.), logicWireFieldV[i], "physWireFieldV", logicChamber, false, 0, true);
		}
			
	}
	
	
	//Volumen de nuestro detector
	G4Box *detector = new G4Box("detector", 5.0*cm/9, 5.0*cm/9, 0.00254/2*cm);
	
	//Debemos poner el material de los hilos?
	logicDetector = new G4LogicalVolume(detector, Gas, "logicDetector");
	
	/*
	for(G4int i=0; i < 9; i++)
	{
		for(G4int j=0; j < 9; j++)
		{
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-5.0*cm + (2*i+1)*5.0/9*cm, -5.0*cm + (2*j+1)*5.0/9*cm, 0.), logicDetector, "physDetector", logicChamber, false, j+i*9, true);
		}	
	}
	*/
	
	//Volumen del detector de alambre
	G4Tubs *wireDetector = new G4Tubs("wireDetector", 0., 0.00254*cm/2, 5.0*cm, 0*deg, 360*deg);
	
	logicWireDetector = new G4LogicalVolume(wireDetector, Alambre, "logicWireDetector");
	
	G4RotationMatrix *wireDetectorRot = new G4RotationMatrix();
	wireDetectorRot->rotateX(90.*deg);
	
	//G4VPhysicalVolume *physWireDetector = new G4PVPlacement(wireDetectorRot, G4ThreeVector(5.0*cm/9, 0., 0.), logicWireDetector, "physWireDetector", logicChamber, false, 0, true);
	
	
	//Volumen de los alambres 0.00254*cm/2
	G4Tubs *wire = new G4Tubs("wire", 0., 0.00254*cm/2, 5.0*cm, 0*deg, 360*deg);
	
	logicWire = new G4LogicalVolume(wire, Alambre, "logicWire"); 
	
	G4RotationMatrix *wireRotV = new G4RotationMatrix();
	G4RotationMatrix *wireRotH = new G4RotationMatrix();
	wireRotV->rotateX(90.*deg);
	wireRotH->rotateY(90.*deg);
	
	for(G4int i=0; i < 8; i++)
	{
		G4VPhysicalVolume *physWireV = new G4PVPlacement(wireRotV, G4ThreeVector(-5.0*cm+(i+1)*10.0*cm/9, 0., 0.), logicWire, "physWireV", logicChamber, false, 0, true);
		G4VPhysicalVolume *physWireH = new G4PVPlacement(wireRotH, G4ThreeVector(0., -5.0*cm+(i+1)*10.0*cm/9, 0.), logicWire, "physWireH", logicChamber, false, 0, true);
	}
	
	/*
	G4VPhysicalVolume *physWireV = new G4PVPlacement(wireRotV, G4ThreeVector(-5.0*cm+(i+1)*10.0*cm/9, 0., 0.), logicWire, "physWireV", logicChamber, false, 0, true);
	*/
	
	//Atributos de color
	wireVisAtt = new G4VisAttributes(G4Colour(0.8,0.64, 0.32));
	wireVisAtt->SetForceSolid(true);
	wireVisAtt->SetVisibility(true);
	logicWire->SetVisAttributes(wireVisAtt);
	
	
	// set "user limits" for drawing smooth curve
	G4UserLimits* userLimits = new G4UserLimits(20.0*cm);
	logicWire->SetUserLimits(userLimits);		
			
	/*
	//Detector del alambre unico
	G4Box *detector = new G4Box("detector", 10.0*cm, 10.0*cm, 0.00254*cm);
	
	logicDetector = new G4LogicalVolume(detector, Gas, "logicDetector");
	
	G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicDetector, "physDetector", logicChamber, false, 0, true);
	*/
	
	
	return physWorld;
}

//Esta funcion es para los alambres

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicWire->SetSensitiveDetector(sensDet);
	
  //This is the first local electric field(Box_1)
  
  /*
  G4Navigator* aNavigator = new G4Navigator();
  aNavigator->SetWorldVolume(physField);
  
  aNavigator->LocateGlobalPointAndSetup(myPoint);
  G4TouchableHistoryHandle aTouchable =
     aNavigator->CreateTouchableHistoryHandle();

  

   // Do whatever you need with it ...
   // ... convert point in local coordinates (local to the current volume)
   //
   G4ThreeVector localPosition = aTouchable->GetHistory()->
                 GetTopTransform().TransformPoint(myPoint);
                 
   G4cout << "Posicion: "<< localPosition << G4endl;
  
  */
  
  //Campos
  
  rDegrees = degrees*3.1416/180;
  //Er = 100000000.0*volt/cm;
  V = 1000;
  //0.55 es el radio de la superficie gaussiana donde encerramos el campo, dado en cm
  //0.00127 es el radio del alambre dado en cm
  r = 0.55;
  log = std::log(0.55/0.00127);
  Er = V/(r*log)*volt/cm;

  //G4cout << "Intensidad del campo: "<< E << G4endl; 
  
  for(G4int i=0; i < nParts; i++)
  {
	//Vertical----------------------------------------------------------------------------------------------
	
  	ExV = Er*std::cos(rDegrees/2+i*rDegrees);
  	//G4cout << "Angulo " << i << ":" << (rDegrees/2+(i)*rDegrees)*180/3.1416 << G4endl;
	EzV = Er*std::sin(rDegrees/2+i*rDegrees);
  
  	fEMfieldV[i] = new G4UniformElectricField(G4ThreeVector(ExV, 0., EzV));

	fEquationV[i] = new G4EqMagElectricField(fEMfieldV[i]);

	fStepperV[i] = new G4ClassicalRK4(fEquationV[i],12);

	fFieldMgrV[i] = new G4FieldManager(fEMfieldV[i]);
	logicWireFieldV[i]->SetFieldManager(fFieldMgrV[i],true);

	fMinStepV[i] = 0.00010*mm ; // minimal step of 10 microns

	fIntgrDriverV[i] = new G4MagInt_Driver(fMinStepV[i],fStepperV[i],fStepperV[i]->GetNumberOfVariables());

	fChordFinderV[i] = new G4ChordFinder(fIntgrDriverV[i]);
	fFieldMgrV[i]->SetChordFinder(fChordFinderV[i]); 
	
	//Horizontal---------------------------------------------------------------------------------------------
	
	EyH = Er*std::cos(rDegrees/2+i*rDegrees+3.1416/2);
  	//G4cout << "Angulo " << i << ":" << (rDegrees/2+(i)*rDegrees+3.1416/2)*180/3.1416 << G4endl;
	EzH = Er*std::sin(rDegrees/2+i*rDegrees+3.1416/2);
  
  	fEMfieldH[i] = new G4UniformElectricField(G4ThreeVector(0., EyH, EzH));

	fEquationH[i] = new G4EqMagElectricField(fEMfieldH[i]);

	fStepperH[i] = new G4ClassicalRK4(fEquationH[i],12);

	fFieldMgrH[i] = new G4FieldManager(fEMfieldH[i]);
	logicWireFieldH[i]->SetFieldManager(fFieldMgrH[i],true);

	fMinStepH[i] = 0.00010*mm ;

	fIntgrDriverH[i] = new G4MagInt_Driver(fMinStepH[i],fStepperH[i],fStepperH[i]->GetNumberOfVariables());

	fChordFinderH[i] = new G4ChordFinder(fIntgrDriverH[i]);
	fFieldMgrH[i]->SetChordFinder(fChordFinderH[i]); 
  }
  
} 


