#pragma once

#include "engine/MVP/Interfaces.h"
//#include "engine/MVP/Observable.h"
#include <string>


// struct DataModel
// {
//     DataModel() : ageDuCapitaine(42), nomDuCapitaine(std::string("Jack Sparrow"))
//     {
//     }
//     Observable<int> ageDuCapitaine;
//     Observable<std::string> nomDuCapitaine;
// };

// class Player : public IModel
// {
// public:
//     Player(int x, int y) : m_x(x), m_y(y) {}
//
//     Observable<int> m_x;
//     Observable<int> m_y;
//
// };

struct DataModel : public IModel
{
    DataModel() : ageDuCapitaine(42), nomDuCapitaine(std::string("Jack Sparrow"))
    {
    }
    Observable<int> ageDuCapitaine;
    Observable<std::string> nomDuCapitaine;
};
