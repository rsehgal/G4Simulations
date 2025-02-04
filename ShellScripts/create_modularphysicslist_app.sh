#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_modularphysicslist_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
MODULARPHYSICSLIST="${DET_NAME}_ModularPhysicsList"


# Create Modular Physics  List header file
cat << EOF > ${MODULARPHYSICSLIST}.h
#ifndef ${MODULARPHYSICSLIST^^}_HH
#define ${MODULARPHYSICSLIST^^}_HH

#include "G4VModularPhysicsList.hh"

class ${MODULARPHYSICSLIST} : public G4VModularPhysicsList {
public:
    ${MODULARPHYSICSLIST}();
    virtual ~${MODULARPHYSICSLIST}();
};

#endif
EOF

# Create Modular Physics  List source file
cat << EOF > ${MODULARPHYSICSLIST}.cpp
#include "${MODULARPHYSICSLIST}.h"

${MODULARPHYSICSLIST}::${MODULARPHYSICSLIST}()  {
}

${MODULARPHYSICSLIST}::~${MODULARPHYSICSLIST}() {}


EOF

# Print success message
echo "Modular physics list skeleton created in current directory."

