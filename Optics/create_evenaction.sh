#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_eventaction_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
SENSITIVE_DETECTOR="${DET_NAME}_EventAction"


# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class ${SENSITIVE_DETECTOR} : public G4UserEventAction {
public:
    ${SENSITIVE_DETECTOR}();
    virtual ~${SENSITIVE_DETECTOR}();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}()  {
}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

void ${SENSITIVE_DETECTOR}::BeginOfEventAction(const G4Event *event){

}

void ${SENSITIVE_DETECTOR}::EndOfEventAction(const G4Event *event){

}

EOF

# Print success message
echo "EventAction class skeleton created in current directory."

