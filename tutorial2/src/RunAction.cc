#include "RunAction.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(G4int num)
: G4UserRunAction(), nOfLayers(num)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->CreateH1("Edep in Event", "Edep in Event", //Name & Title
                             nOfLayers, -0.5, nOfLayers-0.5);  //x-axis bins
  analysisManager->SetH1XAxisTitle(0, "copy number");
  analysisManager->SetH1YAxisTitle(0, "Edep [MeV]");
}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run*){
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  auto analysisManager = G4AnalysisManager::Instance();

  G4String fileName = "test";
  analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run* run){
  auto analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->Write();
  analysisManager->CloseFile();
}
