#ifndef GAMEBOARDMODEL_HPP
#define GAMEBOARDMODEL_HPP

#include <QAbstractListModel>
#include <iostream>
#include <vector>
#include "CFigure.hpp"

namespace NModel
{
    struct Tile
    {
        bool mDisplay;
        bool mFilled;
        QString mColor;

        Tile(const bool display = false,
             const bool filled = false,
             const QString color = "")
            : mDisplay(display)
            , mFilled(filled)
            , mColor(color)
        {}

        bool operator==(const Tile& right) const
        {
            return mDisplay == right.mDisplay && mFilled == right.mFilled;
        }
    };

    class CGameBoardModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int xDimension READ getXDimension CONSTANT)
        Q_PROPERTY(int yDimension READ getYDimension CONSTANT)

        static constexpr size_t defaultXDimension {15};
        static constexpr size_t defaultYDimension {20};
        static constexpr size_t defaultSpeed {5};
        static constexpr size_t defaultScore {100};
        static constexpr size_t delay {1000};

    public:
        enum Roles { FilledRole = Qt::UserRole + 1, ColorRole };

    public:
        CGameBoardModel(const size_t xDimension = defaultXDimension,
                        const size_t yDimension = defaultYDimension,
                        QObject* parent = nullptr);

        size_t getXDimension() const;
        size_t getYDimension() const;
        Q_INVOKABLE void moveFigure(int direction);
        Q_INVOKABLE void rotateFigure();
        Q_INVOKABLE void throwFigure();
        Q_INVOKABLE int getNextFigureType();
        int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    signals:
        void scoreChanged(int value);
        void nextFigureChanged(int value);

    private:
        void removeFullRows();
        void showFigure();
        void hideFigure();
        bool canMove(int x, int y);

    private:
        std::vector<Tile> mBoard;
        CFigure* mFigure;
        CFigure* mNextFigure;
        CFigure* mShadow;
        const int mXDimension;
        const int mYDimension;
        int mSpeed;
        int mScore;
    };
}

#endif // GAMEBOARDMODEL_HPP
