#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Analysis.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction(EventAction* eventAction, G4int num)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  nOfLayers(num)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step){
	
  G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume();

  G4int    trackId = step->GetTrack()->GetTrackID();
  G4String volName = volume->GetName();
  G4int    copyNo  = volume->GetCopyNo();

  auto edep = step->GetTotalEnergyDeposit()/MeV;
  fEventAction->addEdep(copyNo, edep);
}
