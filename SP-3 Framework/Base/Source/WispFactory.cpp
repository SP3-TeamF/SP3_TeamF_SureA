#include "WispFactory.h"

WispFactory::WispFactory()
{

}

WispFactory::~WispFactory()
{

}

Wisp* WispFactory::FetchWisp()
{
    for (auto wispIt : wispList)
    {
        if (wispIt->Get_cActive())
        {
            return wispIt;
        }
    }

    for (unsigned i = 0; i < 10; ++i)
    {
        Wisp* newWisp = new Wisp();
        wispList.push_back(newWisp);
    }

    Wisp* newWisp = wispList.back();
    return newWisp;
}

vector<Wisp*> WispFactory::GetWispList()
{
    return this->wispList;
}

void WispFactory::Update(double dt)
{
    for (auto wispIt : wispList)
    {
        if (wispIt->Get_cActive())
        {
            wispIt->Update(dt);
        }
    }
}

void WispFactory::Reset()
{
    for (auto wispIt : wispList)
    {
        wispIt->Set_cActive(false);
        wispIt->Reset();
    }
}
