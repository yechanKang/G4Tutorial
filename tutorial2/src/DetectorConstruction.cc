#include <cstdio>
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"

#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction(G4int num, G4double thickness)
:G4VUserDetectorConstruction(), nOfLayers(num), absorberSizeZ(thickness*cm)
{
  // Geant4 does not allow pure vacuum
  vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"); 

  lead = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
}

DetectorConstruction::~DetectorConstruction(){
}

G4VPhysicalVolume* DetectorConstruction::Construct(){

  G4bool checkOverlaps = true;
  //Set size of Geometry
  G4double worldSizeXY = 50*cm;

  G4double absorberSizeXY = worldSizeXY;

  G4double targetSizeXY = worldSizeXY;
  G4double targetSizeZ = absorberSizeZ*2;
  
  G4double worldSizeZ = targetSizeZ * nOfLayers;
  
  //// Build World
  G4Material* worldMat = vacuum;

  G4Box* solidWorld = 
  	new G4Box("World" , 0.5*worldSizeXY, 0.5*worldSizeXY, 0.5*worldSizeZ);

  G4LogicalVolume* logicWorld =
  	new G4LogicalVolume(solidWorld, worldMat, "World");

  // Set World without mother volume
  G4VPhysicalVolume* physWorld =
  	new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);
 
  // Build Empty Target
  G4Material* targetMat = vacuum;

  G4Box* solidTarget = 
    new G4Box("Target", 0.5*targetSizeXY, 0.5*targetSizeXY, 0.5*targetSizeZ);

  G4LogicalVolume* logicTarget = 
    new G4LogicalVolume(solidTarget, targetMat, "Target");

  G4VisAttributes *vacuumAttributes = new G4VisAttributes ;
  vacuumAttributes->SetVisibility(false) ;

  logicTarget->SetVisAttributes(vacuumAttributes);

  // Make repeated physical volumes
  new G4PVReplica("Target", logicTarget, logicWorld, kZAxis, nOfLayers, targetSizeZ);

  // Build Absorber
  G4Material* absorberMat = lead;

  G4ThreeVector absorberPos = G4ThreeVector(0, 0, 0);

  G4Box* solidAbsorber = 
    new G4Box("Absorber", 0.5*absorberSizeXY, 0.5*absorberSizeXY, 0.5*absorberSizeZ);

  G4LogicalVolume* logicAbsorber =
    new G4LogicalVolume(solidAbsorber, absorberMat, "Absorber");

  // Locate in Logical Target
	new G4PVPlacement(0, absorberPos, logicAbsorber, "Absorber", logicTarget, false, 0, checkOverlaps);

  return physWorld;
}
