#include "Messenger_SensitiveDetector.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

Messenger_SensitiveDetector::Messenger_SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}

Messenger_SensitiveDetector::~Messenger_SensitiveDetector() {}

G4bool Messenger_SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    
    //TODO :  Add Whatall information you want to get from steps
    return true;
}
