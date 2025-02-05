#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_hit_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1
MESSENGER_TYPE=$2

# Class names with project name prefix and underscore
if [ -z "$2" ]; then
MESSENGER="${DET_NAME}_Messenger"
else
MESSENGER="${DET_NAME}_${MESSENGER_TYPE}_Messenger"
fi
DETCLASS="${DET_NAME}_DetectorConstruction"

# Create Hit Class header file
cat << EOF > ${MESSENGER}.h
#ifndef ${MESSENGER^^}_HH
#define ${MESSENGER^^}_HH

#include "G4UImessenger.hh"

class ${DETCLASS};

class ${MESSENGER} : public G4UImessenger {
private:
    ${DETCLASS} *fDetector;
    G4UIdirectory *fDirectory;

    //TODO : Define the desired command by creating their objects
    //G4UIcmdWithAString
    //G4UIcmdWithADouble
    //G4UIcmdWithADoubleAndUnit
    //G4UIcmdWith3Vector
    //G4UIcmdWith3VectorAndUnit
    //G4UIcmdWithABool

public:
    ${MESSENGER}(${DETCLASS} *detector);
    virtual ~${MESSENGER}();
};

#endif
EOF

# Create Hit Class source file
cat << EOF > ${MESSENGER}.cpp
#include "${MESSENGER}.h"

${MESSENGER}::${MESSENGER}(${DETCLASS} *detector) : fDetector(detector)  {
    fDirectory = new G4UIdirectory("/CalicutWorkshop/detector");
    //TODO : Define the desired command by creating their objects
}

${MESSENGER}::~${MESSENGER}() {
    delete fDirectory;
}


EOF

# Print success message
echo "Messenger class skeleton created in current directory."

