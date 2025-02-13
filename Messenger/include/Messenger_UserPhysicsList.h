#ifndef MESSENGER_USERPHYSICSLIST_HH
#define MESSENGER_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class Messenger_UserPhysicsList : public G4VUserPhysicsList {
public:
    Messenger_UserPhysicsList();
    virtual ~Messenger_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
