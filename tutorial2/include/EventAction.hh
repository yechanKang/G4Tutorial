#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class DetectorConstruction;

class EventAction : public G4UserEventAction{
	private :
    RunAction* fRunAction;
    G4int nOfLayers;
    G4double* fEdep;
	public :
		EventAction(RunAction* runAction, G4int num);
		virtual ~EventAction();
		
		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);
		virtual void addEdep(G4int copyNo, G4double edep);
};

#endif
