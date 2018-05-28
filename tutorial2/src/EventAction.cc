#include "EventAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction(RunAction* runAction, G4int num)
: G4UserEventAction(), fRunAction(runAction), nOfLayers(num)
{
  fEdep = new G4double[num];
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*){
  for (G4int i = 0; i < nOfLayers; ++i) fEdep[i] = 0.;
}

void EventAction::EndOfEventAction(const G4Event*){
  for (G4int i = 0; i < nOfLayers; ++i)
    G4AnalysisManager::Instance()->FillH1(0, i, fEdep[i]);
}

void EventAction::addEdep(G4int copyNo, G4double edep){
  fEdep[copyNo] += edep;
}
