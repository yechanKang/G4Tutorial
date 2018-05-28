#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction{
	public :
		RunAction(G4int num);
		virtual ~RunAction();

		virtual void BeginOfRunAction(const G4Run*);
		virtual void EndOfRunAction(const G4Run*);
	private :
    G4int nOfLayers;
};

#endif
