#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_class.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
DET_NAME=$1

# Class names with project name prefix and underscore
HIT="${DET_NAME}"


# Create Hit Class header file
cat << EOF > ${HIT}.h
#ifndef ${HIT^^}_HH
#define ${HIT^^}_HH


class ${HIT} {
public:
    ${HIT}();
    virtual ~${HIT}();
};

#endif
EOF

# Create Hit Class source file
cat << EOF > ${HIT}.cpp
#include "${HIT}.h"

${HIT}::${HIT}()  {
}

${HIT}::~${HIT}() {}


EOF

# Print success message
echo "Class skeleton created in current directory."

