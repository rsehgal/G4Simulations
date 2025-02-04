#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_eventaction_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
EVENT_ACTION="${DET_NAME}_EventAction"


# Create EventAction header file
cat << EOF > ${EVENT_ACTION}.h
#ifndef ${EVENT_ACTION^^}_HH
#define ${EVENT_ACTION^^}_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class ${EVENT_ACTION} : public G4UserEventAction {
public:
    ${EVENT_ACTION}();
    virtual ~${EVENT_ACTION}();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
EOF

# Create EventAction source file
cat << EOF > ${EVENT_ACTION}.cpp
#include "${EVENT_ACTION}.h"

${EVENT_ACTION}::${EVENT_ACTION}()  {
}

${EVENT_ACTION}::~${EVENT_ACTION}() {}

void ${EVENT_ACTION}::BeginOfEventAction(const G4Event *event){

}

void ${EVENT_ACTION}::EndOfEventAction(const G4Event *event){

}

EOF

# Print success message
echo "EventAction class skeleton created in current directory."

