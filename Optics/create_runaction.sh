#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_RunAction_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
RUN_ACTION="${DET_NAME}_RunAction"


# Create RunAction header file
cat << EOF > ${RUN_ACTION}.h
#ifndef ${RUN_ACTION^^}_HH
#define ${RUN_ACTION^^}_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class ${RUN_ACTION} : public G4UserRunAction {
public:
    ${RUN_ACTION}();
    virtual ~${RUN_ACTION}();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
EOF

# Create RunAction source file
cat << EOF > ${RUN_ACTION}.cpp
#include "${RUN_ACTION}.h"
#include "G4Run.hh"

${RUN_ACTION}::${RUN_ACTION}()  {
}

${RUN_ACTION}::~${RUN_ACTION}() {}

void ${RUN_ACTION}::BeginOfRunAction(const G4Run*){

}

void ${RUN_ACTION}::EndOfRunAction(cconst G4Run*){

}

EOF

# Print success message
echo "RunAction class skeleton created in current directory."

