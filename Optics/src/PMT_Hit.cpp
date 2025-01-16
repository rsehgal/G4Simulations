/*
**	Filename : PMT_Hit.cpp
**	2025-01-15
**	username : rsehgal
*/
#include <iostream>
#include "PMT_Hit.h"

PMT_Hit::PMT_Hit() {}

PMT_Hit::~PMT_Hit() {}

/*std::vector<uint64_t> PMT_Hit::GetPulse() const
{
  return fVecOfTime;
}*/

uint64_t PMT_Hit::GetTime() const {
	return fTime;
}

void PMT_Hit::FillTime(uint64_t tm)
{
  fTime =tm;
}

void PMT_Hit::Print()
{

/*  for (unsigned int i = 0; i < fVecOfTime.size(); i++) {
    std::cout << fVecOfTime[i] << " , ";
  }
  std::cout << std::endl;*/
}
