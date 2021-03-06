#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

int main(int argc, char** argv){
	G4UIExecutive* ui = 0;
	if(argc == 1){
		ui = new G4UIExecutive(argc, argv);
	}
	
	G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
#else
	G4RunManager* runManager = new G4RunManager;
#endif

  G4int nOfLayers = 100;
  G4double absorberThickness = 0.1;

	DetectorConstruction* fDetectorConstruction = new DetectorConstruction(nOfLayers, absorberThickness);

	runManager->SetUserInitialization(fDetectorConstruction);

	runManager->SetUserInitialization(new FTFP_BERT);

	runManager->SetUserInitialization(new ActionInitialization(nOfLayers));

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if(!ui){
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else{
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	delete visManager;
	delete runManager;
}
