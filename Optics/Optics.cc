#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Optics_DetectorConstruction.hh"
#include "Optics_PrimaryGeneratorAction.hh"
#include "Optics_SteppingAction.hh"
#include "Optics_RunAction.h"
#include "Optics_EventAction.h"
#include "Optics_TrackingAction.h"
#include "G4OpticalPhysics.hh"
#include "Optics_ModularPhysicsList.h"
#include "Optics_UserPhysicsList.h"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new Optics_DetectorConstruction());

    //Pre-packaged physics list
    //G4VModularPhysicsList *physicsList = new QGSP_BERT;//QBBC;//FTFP_BERT; // QBBC;


    //Modular Physics list
    //G4VModularPhysicsList *physicsList = new Optics_ModularPhysicsList;

    //User Physics LIst
    G4VUserPhysicsList *physicsList = new Optics_UserPhysicsList;

#ifdef USE_OPTICAL_PHOTONS
    G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
    physicsList->RegisterPhysics(opticalPhysics);
#endif

    runManager->SetUserInitialization(physicsList);
    
    runManager->SetUserAction(new Optics_PrimaryGeneratorAction());
    //runManager->SetUserAction(new Optics_SteppingAction());
    runManager->SetUserAction(new Optics_RunAction());
    runManager->SetUserAction(new Optics_EventAction());
    runManager->SetUserAction(new Optics_TrackingAction());
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
