#!/bin/bash

# Check if project name is provided
if [ -z "$1" ]; then
    echo "Usage: ./create_geant4_app.sh <ProjectName>"
    exit 1
fi

# Set project name from the argument
PROJECT_NAME=$1

# Create directories
mkdir -p $PROJECT_NAME/include $PROJECT_NAME/src

# Class names with project name prefix and underscore
DETECTOR_CONSTRUCTION="${PROJECT_NAME}_DetectorConstruction"
PRIMARY_GENERATOR_ACTION="${PROJECT_NAME}_PrimaryGeneratorAction"
STEPPING_ACTION="${PROJECT_NAME}_SteppingAction"
SENSITIVE_DETECTOR="${PROJECT_NAME}_SensitiveDetector"

# Create main application file
cat << EOF > $PROJECT_NAME/$PROJECT_NAME.cc
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "${DETECTOR_CONSTRUCTION}.hh"
#include "${PRIMARY_GENERATOR_ACTION}.hh"
#include "${STEPPING_ACTION}.hh"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new ${DETECTOR_CONSTRUCTION}());
    runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserAction(new ${PRIMARY_GENERATOR_ACTION}());
    runManager->SetUserAction(new ${STEPPING_ACTION}());

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

    delete visManager;
    delete runManager;

    return 0;
}
EOF

# Create DetectorConstruction header file
cat << EOF > $PROJECT_NAME/include/${DETECTOR_CONSTRUCTION}.hh
#ifndef ${DETECTOR_CONSTRUCTION^^}_HH
#define ${DETECTOR_CONSTRUCTION^^}_HH

#include "G4VUserDetectorConstruction.hh"

class ${DETECTOR_CONSTRUCTION} : public G4VUserDetectorConstruction {
public:
    ${DETECTOR_CONSTRUCTION}();
    virtual ~${DETECTOR_CONSTRUCTION}();

    virtual G4VPhysicalVolume* Construct();
};

#endif
EOF

# Create DetectorConstruction source file
cat << EOF > $PROJECT_NAME/src/${DETECTOR_CONSTRUCTION}.cc
#include "${DETECTOR_CONSTRUCTION}.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "${SENSITIVE_DETECTOR}.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
${DETECTOR_CONSTRUCTION}::${DETECTOR_CONSTRUCTION}() {}

${DETECTOR_CONSTRUCTION}::~${DETECTOR_CONSTRUCTION}() {}

G4VPhysicalVolume* ${DETECTOR_CONSTRUCTION}::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    // Attach sensitive detector
    ${SENSITIVE_DETECTOR}* detector = new ${SENSITIVE_DETECTOR}("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    logicWorld->SetSensitiveDetector(detector);

    return physWorld;
}
EOF

# Create PrimaryGeneratorAction header file
cat << EOF > $PROJECT_NAME/include/${PRIMARY_GENERATOR_ACTION}.hh
#ifndef ${PRIMARY_GENERATOR_ACTION^^}_HH
#define ${PRIMARY_GENERATOR_ACTION^^}_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class ${PRIMARY_GENERATOR_ACTION} : public G4VUserPrimaryGeneratorAction {
public:
    ${PRIMARY_GENERATOR_ACTION}();
    virtual ~${PRIMARY_GENERATOR_ACTION}();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
EOF

# Create PrimaryGeneratorAction source file
cat << EOF > $PROJECT_NAME/src/${PRIMARY_GENERATOR_ACTION}.cc
#include "${PRIMARY_GENERATOR_ACTION}.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
${PRIMARY_GENERATOR_ACTION}::${PRIMARY_GENERATOR_ACTION}() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * MeV);
}

${PRIMARY_GENERATOR_ACTION}::~${PRIMARY_GENERATOR_ACTION}() {
    delete fParticleGun;
}

void ${PRIMARY_GENERATOR_ACTION}::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
EOF

# Create SteppingAction header file
cat << EOF > $PROJECT_NAME/include/${STEPPING_ACTION}.hh
#ifndef ${STEPPING_ACTION^^}_HH
#define ${STEPPING_ACTION^^}_HH

#include "G4UserSteppingAction.hh"

class ${STEPPING_ACTION} : public G4UserSteppingAction {
public:
    ${STEPPING_ACTION}();
    virtual ~${STEPPING_ACTION}();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
EOF

# Create SteppingAction source file
cat << EOF > $PROJECT_NAME/src/${STEPPING_ACTION}.cc
#include "${STEPPING_ACTION}.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
${STEPPING_ACTION}::${STEPPING_ACTION}() {}

${STEPPING_ACTION}::~${STEPPING_ACTION}() {}

void ${STEPPING_ACTION}::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;
}
EOF

# Create SensitiveDetector header file
cat << EOF > $PROJECT_NAME/include/${SENSITIVE_DETECTOR}.hh
#ifndef ${SENSITIVE_DETECTOR^^}_HH
#define ${SENSITIVE_DETECTOR^^}_HH

#include "G4VSensitiveDetector.hh"

class ${SENSITIVE_DETECTOR} : public G4VSensitiveDetector {
public:
    ${SENSITIVE_DETECTOR}(const G4String& name);
    virtual ~${SENSITIVE_DETECTOR}();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
EOF

# Create SensitiveDetector source file
cat << EOF > $PROJECT_NAME/src/${SENSITIVE_DETECTOR}.cc
#include "${SENSITIVE_DETECTOR}.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

${SENSITIVE_DETECTOR}::${SENSITIVE_DETECTOR}(const G4String& name) : G4VSensitiveDetector(name) {}

${SENSITIVE_DETECTOR}::~${SENSITIVE_DETECTOR}() {}

G4bool ${SENSITIVE_DETECTOR}::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    return true;
}
EOF

# Create CMakeLists.txt file
cat << EOF > $PROJECT_NAME/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(${PROJECT_NAME})

# Find Geant4 package
find_package(Geant4 REQUIRED)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Include directories
include_directories(\${Geant4_INCLUDE_DIRS} include)

# Add source files
file(GLOB SOURCES src/*.cc)
file(GLOB MAC_FILES *.mac)
file(COPY \${MAC_FILES} DESTINATION \${CMAKE_CURRENT_BINARY_DIR})

# Add executable
add_executable(\${PROJECT_NAME} \${SOURCES} ${PROJECT_NAME}.cc)

# Link with Geant4 libraries
target_link_libraries(\${PROJECT_NAME} \${Geant4_LIBRARIES})

# Set C++ standard
set_target_properties(\${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# Install
install(TARGETS \${PROJECT_NAME} DESTINATION bin)
EOF

# Create mac file for default visualization
cat << EOF > $PROJECT_NAME/vis.mac
/run/initialize
# Macro file for the visualization setting in the initialization phase 
# of the B1 example when running in interactive mode
#

# Use these open statements to open selected visualization
#
# Use this open statement to create an OpenGL view:
/vis/open OGL 600x600-0+0
#
# Use this open statement to create an OpenInventor view:
#/vis/open OI
#
# Use this open statement to create a .prim file suitable for
# viewing in DAWN:
#/vis/open DAWNFILE
#
# Use this open statement to create a .heprep file suitable for
# viewing in HepRApp:
#/vis/open HepRepFile
#
# Use this open statement to create a .wrl file suitable for
# viewing in a VRML viewer:
#/vis/open VRML2FILE
#
# Disable auto refresh and quieten vis messages whilst scene and
# trajectories are established:
/vis/viewer/set/autoRefresh false
/vis/verbose errors
#
# Draw geometry:
/vis/drawVolume
#
# Specify view angle:
/vis/viewer/set/viewpointVector -1 0 0
/vis/viewer/set/lightsVector -1 0 0
#
# Specify style (surface, wireframe, auxiliary edges,...)
/vis/viewer/set/style wireframe
/vis/viewer/set/auxiliaryEdge true
/vis/viewer/set/lineSegmentsPerCircle 100
#
# Draw smooth trajectories at end of event, showing trajectory points
# as markers 2 pixels wide:
/vis/scene/add/trajectories smooth
/vis/modeling/trajectories/create/drawByCharge
/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true
/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2
# To superimpose all of the events from a given run:
/vis/scene/endOfEventAction accumulate

# To get nice view
/vis/geometry/set/visibility World 0 true
/vis/geometry/set/visibility Envelope 0 false
#/vis/viewer/set/style surface

/vis/viewer/set/hiddenMarker true
/vis/viewer/set/viewpointThetaPhi 120 150
#
# Re-establish auto refreshing and verbosity:
/vis/viewer/set/autoRefresh true
/vis/verbose warnings
#
# For file-based drivers, use this to create an empty detector view:
#/vis/viewer/flush

EOF
# Print success message
echo "Geant4 application skeleton created in '$PROJECT_NAME' directory."

