#ifndef CFIGUREJ_HPP
#define CFIGUREJ_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureJ : public CFigure
    {
    public:
        CFigureJ()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 3;
            mType = EFigureType::J;
            mTiles = { 0, 1, 0, 1, 1, 1 };
        }

        virtual ~CFigureJ()
        {}

        virtual void rotate() final override
        {
            if (!mTiles[0] && mTiles[1]) {
                mTiles = { 1, 0, 0, 1, 1, 1 };
            }
            else if (mTiles[0] && !mTiles[1]) {
                mTiles = { 1, 1, 1, 0, 1, 0 };
                mX++;
            }
            else if (mTiles[4] && !mTiles[5]) {
                mTiles = { 1, 1, 1, 0, 0, 1 };
                mY++;
                mX--;
            }
            else if (!mTiles[4] && mTiles[5]) {
                mTiles = { 0, 1, 0, 1, 1, 1 };
                mY--;
            }

            std::swap(mWidth, mHeight);
        }

        virtual CFigure* copy() const final override
        {
            return new CFigureJ(*this);
        }

        virtual QString getColor() const final override
        {
            return "blue";
        }
    };
}

#endif // CFIGUREJ_HPP
