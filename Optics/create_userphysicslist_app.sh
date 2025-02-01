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
USERPHYSICSLIST="${DET_NAME}_UserPhysicsList"
else
USERPHYSICSLIST="${DET_NAME}_UserPhysicsList_${VER}"
fi

# Create User Physics List header file
cat << EOF > ${USERPHYSICSLIST}.h
#ifndef ${USERPHYSICSLIST^^}_HH
#define ${USERPHYSICSLIST^^}_HH

#include "G4VUserPhysicsList.hh"

class ${USERPHYSICSLIST} : public G4VUserPhysicsList {
public:
    ${USERPHYSICSLIST}();
    virtual ~${USERPHYSICSLIST}();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
EOF

# Create User Physics List source file
cat << EOF > ${USERPHYSICSLIST}.cpp
#include "${USERPHYSICSLIST}.h"

${USERPHYSICSLIST}::${USERPHYSICSLIST}()  {
}

${USERPHYSICSLIST}::~${USERPHYSICSLIST}() {}

void ${USERPHYSICSLIST}::ConstructParticle(){
//std::cout <<"RAMAN : Construct Particle....." << std::endl;
}

void ${USERPHYSICSLIST}::ConstructProcess(){
//std::cout <<"SEHGAL : Construct Process....." << std::endl;
}

EOF

# Print success message
echo "UserPhysicsList files created in current directory."

