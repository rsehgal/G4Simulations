/*
**	Filename : Optics_RunAction.h
**	2025-01-14
**	username : rsehgal
*/
#ifndef Optics_RunAction_h
#define Optics_RunAction_h

//class G4AnalysisManager;
class G4Run;
#include "G4AnalysisManager.hh"
#include "G4UserRunAction.hh"

class Optics_RunAction : public G4UserRunAction{

public:
 Optics_RunAction();
 ~Optics_RunAction();
 void BeginOfRunAction(const G4Run*) ;
 void EndOfRunAction(const G4Run*) ;

public:
 G4AnalysisManager *fAnalManager;
};
#endif
