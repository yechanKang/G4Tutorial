#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization(G4int num)
 : G4VUserActionInitialization(), nOfLayers(num)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const{
}

void ActionInitialization::Build() const{
  SetUserAction(new PrimaryGeneratorAction);
}
