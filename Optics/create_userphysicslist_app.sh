#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_userphysicslist_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1
VER=$2
# Class names with project name prefix and underscore

if [ -z "$2" ]; then
SENSITIVE_DETECTOR="${DET_NAME}_UserPhysicsList"
else
SENSITIVE_DETECTOR="${DET_NAME}_UserPhysicsList_${VER}"
fi

# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VUserPhysicsList.hh"

class ${SENSITIVE_DETECTOR} : public G4VUserPhysicsList {
public:
    ${SENSITIVE_DETECTOR}();
    virtual ~${SENSITIVE_DETECTOR}();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > ${SENSITIVE_DETECTOR}.cpp
#include "${SENSITIVE_DETECTOR}.h"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}()  {
}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

void ${SENSITIVE_DETECTOR}::ConstructParticle(){
//std::cout <<"RAMAN : Construct Particle....." << std::endl;
}

void ${SENSITIVE_DETECTOR}::ConstructProcess(){
//std::cout <<"SEHGAL : Construct Process....." << std::endl;
}

EOF

# Print success message
echo "UserPhysicsList files created in current directory."

