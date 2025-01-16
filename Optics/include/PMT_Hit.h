/*
**	Filename : PMT_Hit.h
**	2025-01-15
**	username : rsehgal
*/
#ifndef PMT_Hit_h
#define PMT_Hit_h

#include <G4VHit.hh>
class PMT_Hit : public G4VHit {
private:
  uint64_t fTime;

public:
  PMT_Hit();
  ~PMT_Hit();
  //std::vector<uint64_t> GetPulse() const;
  uint64_t GetTime() const;
  void FillTime(uint64_t tm);
  void Print();
};
#endif
