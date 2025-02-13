#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Messenger_DetectorConstruction.h"
#include "Messenger_PrimaryGeneratorAction.h"
#include "Messenger_SteppingAction.h"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new Messenger_DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserAction(new Messenger_PrimaryGeneratorAction());
    runManager->SetUserAction(new Messenger_SteppingAction());

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
