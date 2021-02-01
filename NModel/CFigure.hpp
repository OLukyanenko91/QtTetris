#ifndef CFIGURE_HPP
#define CFIGURE_HPP

#include <QObject>
#include <vector>

namespace NModel
{
    Q_NAMESPACE
    enum class EMoveDirection { DOWN, LEFT, RIGHT };
    Q_ENUM_NS(EMoveDirection)

    Q_NAMESPACE
    enum class EFigureType { L, T, Z, O, J, S, I };
    Q_ENUM_NS(EFigureType)

    class CFigure
    {
    public:
        static constexpr int defaultX {7};
        static constexpr int defaultY {0};

    public:
        CFigure();

        virtual ~CFigure();

        void move(EMoveDirection direction);

    public:
        inline const std::vector<int> getTiles() const
        {
            return mTiles;
        }

        inline void setTiles(const std::vector<int>& tiles)
        {
            mTiles = tiles;
        }

        inline int getX() const
        {
            return mX;
        }

        inline void setX(const int x)
        {
            mX = x;
        }

        inline int getY() const
        {
            return mY;
        }

        inline void setY(const int y)
        {
            mY = y;
        }

        inline int getWidth() const
        {
            return mWidth;
        }

        inline int getHeight() const
        {
            return mHeight;
        }

        inline EFigureType getType() const
        {
            return mType;
        }

    public:
        virtual void rotate() = 0;

        virtual CFigure* copy() const = 0;

        virtual QString getColor() const = 0;

    protected:
        int mX;
        int mY;
        int mWidth;
        int mHeight;
        EFigureType mType;
        std::vector<int> mTiles;
    };
}

#endif // CFIGURE_HPP
