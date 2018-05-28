#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fWorldBox(0)
{
  // You can set more than 1 particle.
  G4int n_particles = 1;
  fParticleGun = new G4ParticleGun(n_particles);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName = "proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleMomentum(10.*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  G4double worldSizeXY = 0;
  G4double worldSizeZ = 0;

  if(!fWorldBox){
    G4LogicalVolume* logicalWorld
      = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

    fWorldBox = dynamic_cast<G4Box*>(logicalWorld->GetSolid()); 
  }
  
  if(fWorldBox){
    worldSizeXY = fWorldBox->GetXHalfLength()*2;
    worldSizeZ = fWorldBox->GetZHalfLength()*2;
  }

  // Set Particle gun position to boundary of the world
  G4double x0 = 0; //size * worldSizeXY * (G4UniformRand()-0.5);
  G4double y0 = 0; //size * worldSizeXY * (G4UniformRand()-0,5);
  G4double z0 = -0.5 * worldSizeZ;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
