#ifndef OPTICS_USERPHYSICSLIST_V2_HH
#define OPTICS_USERPHYSICSLIST_V2_HH

#include "G4VUserPhysicsList.hh"

class Optics_UserPhysicsList_V2 : public G4VUserPhysicsList {
public:
    Optics_UserPhysicsList_V2();
    virtual ~Optics_UserPhysicsList_V2();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
