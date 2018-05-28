#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include <vector>

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction{
	public :
		DetectorConstruction(G4int num, G4double thickness);
		virtual ~DetectorConstruction();
		virtual G4VPhysicalVolume* Construct();

	private :
    G4Material* vacuum;
    G4Material* lead;
    G4int nOfLayers;
    G4double absorberSizeZ;
};

#endif
