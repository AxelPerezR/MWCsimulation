#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4UserRunAction.hh"

//No es necesario incluir ninguna dependencia en root
#include "g4root.hh"

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
