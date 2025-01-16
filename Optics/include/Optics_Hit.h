/*
**	Filename : Optics_Hit.h
**	2025-01-14
**	username : rsehgal
*/
#ifndef Optics_Hit_h
#define Optics_Hit_h

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
class Optics_Hit : public G4VHit {

public:
  Optics_Hit();
  ~Optics_Hit();
  void Fill(double energy);
  double GetEnergy() const;

private:
  double fEDep;
};

//using NaiHitCollection = G4THitsCollection<Optics_Hit>;
//typedef G4THitsCollection<Optics_Hit> NaiHitCollection;
//extern G4Allocator<Optics_Hit> MyHitAllocator;

#endif
