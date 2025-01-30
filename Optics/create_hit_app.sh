#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_hit_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
SENSITIVE_DETECTOR="${DET_NAME}_Hit"


# Create SensitiveDetector header file
cat << EOF > ${SENSITIVE_DETECTOR}.h
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VHit.hh"

class ${SENSITIVE_DETECTOR} : public G4VHit {
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
echo "Hit class skeleton created in current directory."

