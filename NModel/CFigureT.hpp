#ifndef CFIGURET_HPP
#define CFIGURET_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureT : public CFigure
    {
    public:
        CFigureT()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 3;
            mType = EFigureType::T;
            mTiles = { 1, 0, 1, 1, 1, 0 };
        }

        virtual ~CFigureT()
        {}

        virtual void rotate() final override
        {
            if (mTiles[0] && !mTiles[1]) {
                mTiles = { 1, 1, 1, 0, 1, 0 };
            }
            else if (mTiles[0] && mTiles[1]) {
                mTiles = { 0, 1, 1, 1, 0, 1 };
                mX++;
            }
            else if (!mTiles[0] && mTiles[2]) {
                mTiles = { 0, 1, 0, 1, 1, 1 };
                mY++;
                mX--;
            }
            else if (!mTiles[0] && !mTiles[2]) {
                mTiles = { 1, 0, 1, 1, 1, 0 };
                mY--;
            }

            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureT(*this);
        }

        virtual QString getColor() const final override
        {
            return "purple";
        }
    };
}


#endif // CFIGURET_HPP
