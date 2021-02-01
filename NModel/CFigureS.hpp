#ifndef CFIGURES_HPP
#define CFIGURES_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureS : public CFigure
    {
    public:
        CFigureS()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 3;
            mType = EFigureType::S;
            mTiles = { 1, 0, 1, 1, 0, 1 };
        }

        virtual ~CFigureS()
        {}

        virtual void rotate() final override
        {
            if (mTiles[0])
                mTiles = { 0, 1, 1, 1, 1, 0 };
            else
                mTiles = { 1, 0, 1, 1, 0, 1 };

            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureS(*this);
        }

        virtual QString getColor() const final override
        {
            return "green";
        }
    };
}

#endif // CFIGURES_HPP
