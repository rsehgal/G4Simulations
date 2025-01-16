/*
**	Filename : HitCollections.h
**	2025-01-15
**	username : rsehgal
**
**	Place to create alias for all the Hit collections
*/
#ifndef HitCollections_h
#define HitCollections_h

#include "Optics_Hit.h"
#include "G4THitsCollection.hh"
#include "PMT_Hit.h"

using NaiHitCollection = G4THitsCollection<Optics_Hit>;
using PmtHitCollection = G4THitsCollection<PMT_Hit>;

#endif
