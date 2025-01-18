/*
**	Filename : Optics_RunAction.cpp
**	2025-01-14
**	username : rsehgal
*/
#include <iostream>
#include "Optics_RunAction.h"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
Optics_RunAction::Optics_RunAction()
{
  fAnalManager = G4AnalysisManager::Instance();
}

Optics_RunAction::~Optics_RunAction() {}

void Optics_RunAction::BeginOfRunAction(const G4Run *)
{
  std::cout <<"@@@@@@@@ BEGIN OF RUN ACTION @@@@@@@" << std::endl;
  fAnalManager->OpenFile("optics.root");
  fAnalManager->CreateNtuple("ftree","A simple ROOT Tree");
  fAnalManager->CreateNtupleDColumn("eventNo");
  fAnalManager->CreateNtupleDColumn("eDep");
  fAnalManager->CreateNtupleDColumn("eDepSmeared");
  fAnalManager->CreateNtupleDColumn("numDetectedPhotons");
  fAnalManager->CreateNtupleDColumn("numGeneratedPhotons");
  fAnalManager->FinishNtuple();

  fAnalManager->CreateNtuple("photons","A pulse tree");
  fAnalManager->CreateNtupleDColumn("eventNo");
  fAnalManager->CreateNtupleDColumn("tstamp");
  fAnalManager->FinishNtuple();

}

void Optics_RunAction::EndOfRunAction(const G4Run *)
{
  std::cout <<"@@@@@@@@ END OF RUN ACTION @@@@@@@" << std::endl;
  fAnalManager->Write();
  fAnalManager->CloseFile();
}
