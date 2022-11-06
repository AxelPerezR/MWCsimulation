#include "construction.hh"

//Visualizacion
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//Constructor
MyDetectorConstruction::MyDetectorConstruction()
{}

//Destructor
MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	//Material con el que voy a trabajar
	
	G4double temperature = 273.15*kelvin;
	G4double pressure = 1.*atmosphere;
	//PVT
	G4Material *CH2CHC6H4CH3 = new G4Material("CH2CHC6H4CH3", 1.023*g/cm3, 2, kStateSolid, temperature, pressure);
	CH2CHC6H4CH3->AddElement(nist->FindOrBuildElement("C"), 9);
	CH2CHC6H4CH3->AddElement(nist->FindOrBuildElement("H"), 10);
	
	//Benzofenona
	G4Material *C13H10O = new G4Material("C13H10O", 1.1*g/cm3, 3, kStateSolid, temperature, pressure);
	C13H10O->AddElement(nist->FindOrBuildElement("C"), 13);
	C13H10O->AddElement(nist->FindOrBuildElement("H"), 10);
	C13H10O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	//EJ-232Q-0.5% 
	G4Material *EJ232Q = new G4Material("EJ232Q", 1.023*g/cm3, 2, kStateSolid, temperature, pressure);
	EJ232Q->AddMaterial(CH2CHC6H4CH3, 99.5*perCent);
	EJ232Q->AddMaterial(C13H10O, 0.5*perCent);
	
	//Laminas de Aluminio
	G4Material *Aluminio = new G4Material("Aluminio", 2.7*g/cm3, 1, kStateSolid, temperature, pressure);
	Aluminio->AddElement(nist->FindOrBuildElement("Al"), 1);
	
	//El primero es un factor de conversion, el siguiente la longitud de onda del foton en nanometros, supongamos que es luz es azul (0.2) y la ruz roja (0.9)
	/*
	G4int entries = 13;
	G4double hc = 1.239841939;
	G4double energy[entries] = {hc*eV/0.340,hc*eV/0.350,hc*eV/0.360,hc*eV/0.370,hc*eV/0.380,hc*eV/0.390,hc*eV/0.400,hc*eV/0.410,hc*eV/0.420,hc*eV/0.430,hc*eV/0.440,hc*eV/0.450,hc*eV/0.460};
	G4double scintEJ232Q[entries] = {0.1,0.5,0.7,1.0,0.85,0.7,0.55,0.35,0.3,0.15,0.1,0.07,0.05};
	G4double rindexEJ232Q[entries] = {1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58};
	G4double rindexWorld[entries] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
	*/
	
	G4int entries = 25;
	//G4int entries = 2;
	G4double hc = 1.239841939;
	
	G4double energy[entries] = {hc*eV/0.340,hc*eV/0.345,hc*eV/0.350,hc*eV/0.355,hc*eV/0.360,hc*eV/0.365,hc*eV/0.370,hc*eV/0.375,hc*eV/0.380,hc*eV/0.385,hc*eV/0.390,hc*eV/0.395,hc*eV/0.400,hc*eV/0.405,hc*eV/0.410,hc*eV/0.415,hc*eV/0.420,hc*eV/0.425,hc*eV/0.430,hc*eV/0.435,hc*eV/0.440,hc*eV/0.445,hc*eV/0.450,hc*eV/0.455,hc*eV/0.460};
	//G4double energy[entries] = {hc*eV/0.300,hc*eV/0.950};
	
	G4double scintEJ232Q[entries] = {0.15,0.35,0.51,0.49,0.7,0.9,1.0,0.9,0.84,0.86,0.75,0.7,0.55,0.5,0.4,0.35,0.3,0.25,0.2,0.15,0.1,0.07,0.05,0.04,0.03};
	//G4double scintEJ232Q[entries] = {1.0,1.0};
	
	G4double nEJ232Q = 1.58;
	G4double rindexEJ232Q[entries] = {nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q,nEJ232Q};
	//G4double rindexEJ232Q[entries] = {1.58,1.58};
	
	G4double nWorld = 1.0;
	G4double rindexWorld[entries] = {nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld,nWorld};
	//G4double rindexWorld[entries] = {1.0,1.0};
	
	G4MaterialPropertiesTable *mptEJ232Q = new G4MaterialPropertiesTable();
	mptEJ232Q->AddProperty("RINDEX", energy, rindexEJ232Q, entries);
	//Fast
	mptEJ232Q->AddProperty("FASTCOMPONENT", energy, scintEJ232Q, entries);
	mptEJ232Q->AddProperty("SLOWCOMPONENT", energy, scintEJ232Q, entries);
	//Eficiencia
	mptEJ232Q->AddConstProperty("SCINTILLATIONYIELD",2900./MeV);
	//RiseTime
	//mptEJ232Q->AddConstProperty("FASTSCINTILLATIONRISETIME",110.*ps);
	mptEJ232Q->AddConstProperty("FASTTIMECONSTANT",110.*ps);
	//DecayTime
	mptEJ232Q->AddConstProperty("SLOWTIMECONSTANT",700.*ps);
	mptEJ232Q->AddConstProperty("YIELDRATIO",1.0);
	mptEJ232Q->AddConstProperty("RESOLUTIONSCALE",1.0);
	
	
	EJ232Q->SetMaterialPropertiesTable(mptEJ232Q);
	
        //Material del mundo
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	//Definimos nuestro solidWorld en la mitad del tamaño del que queremos, aquì por ejemplo tenemos 1m por lado
	//G4Box *solidWorld = new G4Box("solidWorld", 11.0*cm, 11.0*cm, 20.0*cm);
	G4Box *solidWorld = new G4Box("solidWorld", 6.0*cm, 6.0*cm, 1.0*cm);
	//Nuestro volumen logico
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	
	//Volumen fisico, el primer parametro es la rotacion, el segundo parametro es donde esta centrado, el 0 despues de "physWorld" es el volumen madre, por si estamos haciendo un volumen sobre otro
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	//Definimos el volumen de nuestros plasticos
	G4Box *solidPlastic = new G4Box("solidPlastic", 50.0*mm, 50.0*mm, 3.0*mm);
	
	//Definimos el volumen logico
	G4LogicalVolume *logicPlastic = new G4LogicalVolume(solidPlastic, EJ232Q, "logicPlastic");
	
	//Volumen fisico 1
	//G4VPhysicalVolume *physPlastic = new G4PVPlacement(0, G4ThreeVector(0., 0., 61.0*mm), logicPlastic, "physPlastic", logicWorld, false, 0, true);
	G4VPhysicalVolume *physPlastic = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicPlastic, "physPlastic", logicWorld, false, 0, true);
	
	//Volumen fisico 2
	//G4VPhysicalVolume *physPlastic2 = new G4PVPlacement(0, G4ThreeVector(0., 0., -61.0*mm), logicPlastic, "physPlastic2", logicWorld, false, 0, true);
	
	//Definimos el volumen de nuestras bases de aluminio
	G4Box *solidAluminium = new G4Box("solidAluminium", 50.0*mm, 50.0*mm, 0.00254/2*cm);
	
	//Definimos el volumen de nuestros laterales de aluminio
	G4Box *solidAluminium2 = new G4Box("solidAluminium", 50.0*mm, 0.00254/2*cm, 3.0*mm);
	
	//Definimos el volumen logico de las bases
	G4LogicalVolume *logicAluminium = new G4LogicalVolume(solidAluminium, Aluminio, "logicAluminium");
	
	//Definimos el volumen logico de los laterales
	G4LogicalVolume *logicAluminium2 = new G4LogicalVolume(solidAluminium2, Aluminio, "logicAluminium");
	
	//Superficie Optica
	
	G4OpticalSurface* OpAluminiumSurface = new G4OpticalSurface("AluminiumSurface");
	
	G4LogicalSkinSurface* AluminiumSurface = new G4LogicalSkinSurface("AluminiumSurface",logicAluminium,OpAluminiumSurface);
	
	G4LogicalSkinSurface* AluminiumSurface2 = new G4LogicalSkinSurface("AluminiumSurface2",logicAluminium2,OpAluminiumSurface);
	
	OpAluminiumSurface -> SetFinish(polishedfrontpainted);
	
	/*
	G4double reflectivity[entries] = {0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92,0.92};
	*/
	G4double r = 0.92;
	G4double reflectivity[entries] = {r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r};
	//G4double reflectivity[entries] = {0.92,0.92};
	
	G4MaterialPropertiesTable *mptAluminiumSurface = new G4MaterialPropertiesTable();
	
	mptAluminiumSurface->AddProperty("REFLECTIVITY", energy, reflectivity, entries);
	
	OpAluminiumSurface->SetMaterialPropertiesTable(mptAluminiumSurface);
	
	//Volumen fisico 1 Bases
	G4VPhysicalVolume *physAluminium = new G4PVPlacement(0, G4ThreeVector(0., 0., 3*mm), logicAluminium, "physAluminium", logicPlastic, false, 0, true);
	
	//Volumen fisico 2 bases
	G4VPhysicalVolume *physAluminium2 = new G4PVPlacement(0, G4ThreeVector(0., 0., -3*mm), logicAluminium, "physAluminium2", logicPlastic, false, 0, true);
	
	//Volumen fisico 3 laterales
	G4VPhysicalVolume *physAluminium3 = new G4PVPlacement(0, G4ThreeVector(0., 50.0*mm, 0.), logicAluminium2, "physAluminium3", logicPlastic, false, 0, true);
	
	//Volumen fisico 4 laterales
	G4VPhysicalVolume *physAluminium4 = new G4PVPlacement(0, G4ThreeVector(0., -50.0*mm, 0.), logicAluminium2, "physAluminium3", logicPlastic, false, 0, true);
	
	G4RotationMatrix *Rot = new G4RotationMatrix();
	Rot->rotateZ(90.*deg);
	
	//Volumen fisico 5 laterales
	G4VPhysicalVolume *physAluminium5 = new G4PVPlacement(Rot, G4ThreeVector(50.0*mm, 0., 0.), logicAluminium2, "physAluminium3", logicPlastic, false, 0, true);
	
	//Volumen fisico 6 laterales
	G4VPhysicalVolume *physAluminium6 = new G4PVPlacement(Rot, G4ThreeVector(-50.0*mm, 0., 0.), logicAluminium2, "physAluminium3", logicPlastic, false, 0, true);
	
	//Volumen de nuestro detector
	
	
	//G4Box *solidDetector = new G4Box("solidDetector", 50.0*mm, 0.00254/2*cm, 3.0*mm);
	//Detector chiquito
	//G4Box *solidDetector = new G4Box("solidDetector", 1.5*mm, 0.00254/2*cm, 1.5*mm);
	G4Box *solidDetector = new G4Box("solidDetector", 1.5*mm, 0.65/2*mm, 1.5*mm);
	//G4Box *solidDetector = new G4Box("solidDetector", 5.0*cm, 0.65/2*mm, 5.0*cm);
	
	logicDetector1 = new G4LogicalVolume(solidDetector, worldMat, "logicDetector1");
	
	//G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0, G4ThreeVector(0., -50.0*mm, 0.), logicDetector1, "physDetector", logicPlastic, false, 0, true);
	
	//logicDetector2 = new G4LogicalVolume(solidDetector, worldMat, "logicDetector2");

	//G4VPhysicalVolume *physDetector2 = new G4PVPlacement(0, G4ThreeVector(0., 50.0*mm, 0.), logicDetector1, "physDetector2", logicPlastic, false, 0, true);
	
	G4RotationMatrix *RotD = new G4RotationMatrix();
	RotD->rotateZ(90.*deg);
	//RotD->rotateX(90.*deg);
	
	//Laterales
	G4VPhysicalVolume *physDetector3 = new G4PVPlacement(RotD, G4ThreeVector(50.0*mm+0.65/2*mm-0.0254/2*mm, 0., 0.), logicDetector1, "physDetector2", logicPlastic, false, 0, true);
	//G4VPhysicalVolume *physDetector3 = new G4PVPlacement(RotD, G4ThreeVector(0., 0., 3.0*mm+0.65/2*mm-0.0254/2*mm), logicDetector1, "physDetector2", logicPlastic, false, 0, true);
	
	//G4VPhysicalVolume *physDetector4 = new G4PVPlacement(RotD, G4ThreeVector(-50.0*mm, 0., 0.), logicDetector1, "physDetector2", logicPlastic, false, 0, true);
	
	
	aluminiumVisAtt = new G4VisAttributes(G4Colour(0.72, 0.72, 0.72));
	//detectorVisAtt = new G4VisAttributes(G4Colour(0.3, 0.08, 0.68));
	detectorVisAtt = new G4VisAttributes(G4Colour(0., 0.5, 0.));
	
	aluminiumVisAtt->SetForceSolid(true);
	aluminiumVisAtt->SetVisibility(true);
	detectorVisAtt->SetForceSolid(true);
	detectorVisAtt->SetVisibility(true);
	
	logicAluminium->SetVisAttributes(aluminiumVisAtt);
	logicAluminium2->SetVisAttributes(aluminiumVisAtt);
	logicDetector1->SetVisAttributes(detectorVisAtt);
	//logicDetector2->SetVisAttributes(detectorVisAtt);

	
	return physWorld;
}


void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
    //MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");

    logicDetector1->SetSensitiveDetector(sensDet1);
    //logicDetector2->SetSensitiveDetector(sensDet2);
}


