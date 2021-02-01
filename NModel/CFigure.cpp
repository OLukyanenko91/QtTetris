#ifndef CFIGURE_CPP
#define CFIGURE_CPP

#include "CFigure.hpp"

namespace NModel
{
    CFigure::CFigure()
    {}

    CFigure::~CFigure()
    {}

    void CFigure::move(EMoveDirection direction)
    {
        switch (direction) {
        case EMoveDirection::DOWN:
            mY++;
            break;
        case EMoveDirection::LEFT:
            mX--;
            break;
        case EMoveDirection::RIGHT:
            mX++;
        default:
            break;
        }
    }
}

#endif // CFIGURE_CPP
