#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_geant4_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
SENSITIVE_DETECTOR="${DET_NAME}_TrackingAction"


# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class ${SENSITIVE_DETECTOR} : public G4UserTrackingAction {
public:
    ${SENSITIVE_DETECTOR}();
    virtual ~${SENSITIVE_DETECTOR}();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}()  {
}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

void ${SENSITIVE_DETECTOR}::PreUserTrackingAction(const G4Track *track){
std::cout <<"RAMAN : Tracking Action begin....." << std::endl;
}

void ${SENSITIVE_DETECTOR}::PostUserTrackingAction(const G4Track *track){
std::cout <<"SEHGAL : Tracking Action ends....." << std::endl;
}

EOF

# Print success message
echo "Tracking Action files created in current directory."

