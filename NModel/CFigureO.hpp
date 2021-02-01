#ifndef CFIGUREO_HPP
#define CFIGUREO_HPP

#include "CFigure.hpp"

namespace NModel
{
    class CFigureO : public CFigure
    {
    public:
        CFigureO()
        {
            mX = defaultX;
            mY = defaultY;
            mWidth = 2;
            mHeight = 2;
            mType = EFigureType::O;
            mTiles = { 1, 1, 1, 1 };
        }

        virtual ~CFigureO()
        {}

        virtual void rotate() final override
        {}

        virtual CFigure* copy() const final override
        {
            return new CFigureO(*this);
        }

        virtual QString getColor() const final override
        {
            return "yellow";
        }
    };
}

#endif // CFIGUREO_HPP
