#ifndef CFIGUREL_HPP
#define CFIGUREL_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureL : public CFigure
    {
    public:
        CFigureL()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 3;
            mType = EFigureType::L;
            mTiles = { 1, 0, 1, 0, 1, 1 };
        }

        virtual ~CFigureL()
        {}

        virtual void rotate() final override
        {
            if (mTiles[0] && !mTiles[1]) {
                mTiles = { 1, 1, 1, 1, 0, 0 };
            }
            else if (mTiles[0] && mTiles[1] && mTiles[2]) {
                mTiles = { 1, 1, 0, 1, 0, 1 };
                mX++;
            }
            else if (mTiles[0] && !mTiles[2]) {
                mTiles = { 0, 0, 1, 1, 1, 1 };
                mY++;
                mX--;
            }
            else if (!mTiles[0] && !mTiles[1]) {
                mTiles = { 1, 0, 1, 0, 1, 1 };
                mY--;
            }

            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureL(*this);
        }

        virtual QString getColor() const final override
        {
            return "orange";
        }
    };
}

#endif // CFIGUREL_HPP
