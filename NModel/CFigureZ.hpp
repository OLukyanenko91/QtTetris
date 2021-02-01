#ifndef CFIGUREZ_HPP
#define CFIGUREZ_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureZ : public CFigure
    {
    public:
        CFigureZ()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 3;
            mType = EFigureType::Z;
            mTiles = { 0, 1, 1, 1, 1, 0 };
        }

        virtual ~CFigureZ()
        {}

        virtual void rotate() final override
        {
            if (!mTiles[0])
                mTiles = { 1, 1, 0, 0, 1, 1 };
            else
                mTiles = { 0, 1, 1, 1, 1, 0 };

            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureZ(*this);
        }

        virtual QString getColor() const final override
        {
            return "red";
        }
    };
}

#endif // CFIGUREZ_HPP
