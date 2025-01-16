/*
**	Filename : Optics_Hit.cpp
**	2025-01-14
**	username : rsehgal
*/

#include "Optics_Hit.h"

//G4Allocator<Optics_Hit> MyHitAllocator;

Optics_Hit::Optics_Hit() {}

Optics_Hit::~Optics_Hit() {}

double Optics_Hit::GetEnergy() const
{
  return fEDep;
}

void Optics_Hit::Fill(double energy)
{
  fEDep = energy;
}
