#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "NonSegmented_DetectorConstruction.h"
#include "NonSegmented_PrimaryGeneratorAction.h"
#include "NonSegmented_SteppingAction.h"

#include "FTFP_BERT_HP.hh"
#include "G4VModularPhysicsList.hh"
#include "G4OpticalPhysics.hh"

#include "NonSegmented_EventAction.h"
#include "NonSegmented_RunAction.h"
int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;

    G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics;
    G4VModularPhysicsList *physicsList = new FTFP_BERT_HP();
    physicsList->RegisterPhysics(opticalPhysics);

    runManager->SetUserInitialization(new NonSegmented_DetectorConstruction());
    //runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserAction(new NonSegmented_PrimaryGeneratorAction());
    runManager->SetUserAction(new NonSegmented_RunAction());
    runManager->SetUserAction(new NonSegmented_EventAction());
    //runManager->SetUserAction(new NonSegmented_SteppingAction());

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
