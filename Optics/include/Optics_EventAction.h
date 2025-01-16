/*
**	Filename : Optics_EventAction.h
**	2025-01-15
**	username : rsehgal
*/
#ifndef Optics_EventAction_h
#define Optics_EventAction_h

#include "G4Event.hh"
#include "G4UserEventAction.hh"

class Optics_EventAction : public G4UserEventAction{

public:
Optics_EventAction();
~Optics_EventAction();

void BeginOfEventAction(const G4Event *event);
void EndOfEventAction(const G4Event *event);

};
#endif
