#ifndef WISPFACTORY_H_
#define WISPFACTORY_H_

#include "Wisp.h"
#include <vector>
using std::vector;

class WispFactory
{
public:
    WispFactory();
    virtual ~WispFactory();
    
    Wisp* FetchWisp();

    void Update(double dt);
    void Reset();

    vector<Wisp*> GetWispList();

private:
    vector<Wisp*> wispList;
};

#endif WISPFACTORY_H_