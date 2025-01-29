#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_modularphysicslist_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
SENSITIVE_DETECTOR="${DET_NAME}_ModularPhysicsList"


# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VModularPhysicsList.hh"

class ${SENSITIVE_DETECTOR} : public G4VModularPhysicsList {
public:
    ${SENSITIVE_DETECTOR}();
    virtual ~${SENSITIVE_DETECTOR}();
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}()  {
}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}


EOF

# Print success message
echo "Modular physics list skeleton created in current directory."

