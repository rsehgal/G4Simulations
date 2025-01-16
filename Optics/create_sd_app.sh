#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_geant4_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
SENSITIVE_DETECTOR="${DET_NAME}_SD"


# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"

class ${SENSITIVE_DETECTOR} : public G4VSensitiveDetector {
public:
    ${SENSITIVE_DETECTOR}(const G4String& name, const G4String &collName);
    virtual ~${SENSITIVE_DETECTOR}();
    virtual void Initialize(G4HCofThisEvent *hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}(const G4String& name, const G4String &collName) : G4VSensitiveDetector(name) {
collectionName.insert(collName);
}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

void ${SENSITIVE_DETECTOR}::Initialize(G4HCofThisEvent *hce){}

G4bool ${SENSITIVE_DETECTOR}::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    return true;
}

void ${SENSITIVE_DETECTOR}::EndOfEvent(G4HCofThisEvent *hce){}
EOF

# Print success message
echo "Sensitive Detector files created in current directory."

