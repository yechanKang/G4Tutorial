#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class DetectorConstruction;

class SteppingAction : public G4UserSteppingAction{
	public :
		SteppingAction(EventAction* eventAction, G4int num);
		virtual ~SteppingAction();

		virtual void UserSteppingAction(const G4Step*);

	private :
		EventAction* fEventAction;
    G4int nOfLayers;
};

#endif
