#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(G4int num)
 : G4VUserActionInitialization(), nOfLayers(num)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const{
  RunAction* runAction = new RunAction(nOfLayers);
  SetUserAction(runAction);
}

void ActionInitialization::Build() const{
  SetUserAction(new PrimaryGeneratorAction);
  
  RunAction* runAction = new RunAction(nOfLayers);
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction(runAction, nOfLayers);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction, nOfLayers));
}
