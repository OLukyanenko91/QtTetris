#ifndef CFIGUREI_HPP
#define CFIGUREI_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureI : public CFigure
    {
    public:
        CFigureI()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 1;
            mHeight = 4;
            mType = EFigureType::I;
            mTiles = { 1, 1, 1, 1, 1, 1 };
        }

        virtual ~CFigureI()
        {}

        virtual void rotate() final override
        {
            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureI(*this);
        }

        virtual QString getColor() const final override
        {
            return "cyan";
        }
    };
}

#endif // CFIGUREI_HPP
