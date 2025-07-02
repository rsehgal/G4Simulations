#ifndef NONSEGMENTED_SLAB_HIT_HH
#define NONSEGMENTED_SLAB_HIT_HH

#include "G4VHit.hh"

class NonSegmented_Slab_Hit : public G4VHit {
  double x, z;

public:
  NonSegmented_Slab_Hit();
  virtual ~NonSegmented_Slab_Hit();
  void Print();
  void Set(double X, double Z);
  double GetX() const;
  double GetZ() const;
};

#endif
