#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_geant4_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
TRACKING_ACTION="${DET_NAME}_TrackingAction"


# Create TrackingAction header file
cat << EOF > ${TRACKING_ACTION}.h
#ifndef ${TRACKING_ACTION^^}_HH
#define ${TRACKING_ACTION^^}_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class ${TRACKING_ACTION} : public G4UserTrackingAction {
public:
    ${TRACKING_ACTION}();
    virtual ~${TRACKING_ACTION}();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
EOF

# Create TrackingAction source file
cat << EOF > ${TRACKING_ACTION}.cpp
#include "${TRACKING_ACTION}.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${TRACKING_ACTION}::${TRACKING_ACTION}()  {
}

${TRACKING_ACTION}::~${TRACKING_ACTION}() {}

void ${TRACKING_ACTION}::PreUserTrackingAction(const G4Track *track){
std::cout <<"RAMAN : Tracking Action begin....." << std::endl;
}

void ${TRACKING_ACTION}::PostUserTrackingAction(const G4Track *track){
std::cout <<"SEHGAL : Tracking Action ends....." << std::endl;
}

EOF

# Print success message
echo "Tracking Action files created in current directory."

