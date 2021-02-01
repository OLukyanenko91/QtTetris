#include "QGuiApplication"
#include "GameBoardModel.hpp"
#include "CFigureFactory.hpp"

namespace NModel
{
    CGameBoardModel::CGameBoardModel(const size_t xDimension,
                                     const size_t yDimension,
                                     QObject *parent)
        : QAbstractListModel(parent),
          mFigure(nullptr),
          mShadow(nullptr),
          mXDimension(xDimension),
          mYDimension(yDimension),
          mSpeed(defaultSpeed),
          mScore(defaultScore)
    {
        mFigure = CFigureFactory::createFigure();
        mNextFigure = CFigureFactory::createFigure();
        mShadow = mFigure->copy();
        mBoard.resize(mXDimension * mYDimension);
        std::fill(mBoard.begin(), mBoard.end(), Tile());

        showFigure();
    }

    size_t CGameBoardModel::getXDimension() const
    {
        return mXDimension;
    }

    size_t CGameBoardModel::getYDimension() const
    {
        return mYDimension;
    }

    int CGameBoardModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)

        return mBoard.size();
    }

    QVariant CGameBoardModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid()) {
            return QVariant();
        }

        switch (role) {
        case Qt::DisplayRole:
            return QVariant::fromValue(mBoard[index.row()].mDisplay);
        case FilledRole:
            return QVariant::fromValue(mBoard[index.row()].mFilled);
        case ColorRole:
            return QVariant::fromValue(mBoard[index.row()].mColor);
        default:
            return QVariant();
        }
    }

    QHash<int, QByteArray> CGameBoardModel::roleNames() const
    {
        QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
        roles[FilledRole] = "filled";
        roles[ColorRole] = "figureColor";

        return roles;
    }

    void CGameBoardModel::moveFigure(int direction)
    {
        EMoveDirection moveDirection = EMoveDirection(direction);
        int x = mFigure->getX();
        int y = mFigure->getY();
        hideFigure();

        switch (moveDirection) {
        case NModel::EMoveDirection::DOWN:
            if (canMove(x, y + 1))
                mFigure->move(moveDirection);
            else {
                showFigure();
                removeFullRows();

                // TODO: use smart pointer
                delete mFigure;
                mFigure = mNextFigure;
                mNextFigure = CFigureFactory::createFigure();
                emit nextFigureChanged((int)mNextFigure->getType());

                // TODO: show popup with score
                if (!canMove(mFigure->getX(), mFigure->getY()))
                    QGuiApplication::quit();
            }
            break;
        case NModel::EMoveDirection::LEFT:
            if (canMove(x - 1, y))
                mFigure->move(moveDirection);
            break;
        case NModel::EMoveDirection::RIGHT:
            if (canMove(x + 1, y))
                mFigure->move(moveDirection);
            break;
        default:
            break;
        }

        showFigure();
    }

    void CGameBoardModel::rotateFigure()
    {
        CFigure* copy = mFigure->copy();

        hideFigure();
        mFigure->rotate();

        if (canMove(mFigure->getX(), mFigure->getY()))
            mShadow->rotate();
        else
            *mFigure = *copy;

        showFigure();

        delete copy;
    }

    void CGameBoardModel::throwFigure()
    {
        hideFigure();

        while (canMove(mFigure->getX(), mFigure->getY() + 1))
            mFigure->move(EMoveDirection::DOWN);

        moveFigure((int)EMoveDirection::DOWN);
    }

    int CGameBoardModel::getNextFigureType()
    {
        return (int)mNextFigure->getType();
    }

    // TODO: improve
    void CGameBoardModel::removeFullRows()
    {
        NModel::Tile visibleTile {true, true, ""};
        NModel::Tile invisibleTile {false, false, ""};

        for (auto it = mBoard.end() - mXDimension; it >= mBoard.begin(); it -= mXDimension)
        {
            if (std::find(it, it + mXDimension, invisibleTile) == it + mXDimension)
            {
                mScore += 100;
                emit scoreChanged(mScore);
            }
        }

        for (auto it = mBoard.end() - mXDimension; it >= mBoard.begin(); it -= mXDimension)
        {
            if (std::find(it, it + mXDimension, invisibleTile) == it + mXDimension ||
                std::find(it, it + mXDimension, visibleTile) == it + mXDimension )
            {
                std::replace(it, it + mXDimension, visibleTile, invisibleTile);

                for (auto it2 = it - mXDimension; it2 >= mBoard.begin(); it2 -= mXDimension)
                {
                    if (std::find(it2, it2 + mXDimension, visibleTile) != it2 + mXDimension &&
                        std::find(it2, it2 + mXDimension, invisibleTile) != it2 + mXDimension )
                    {
                        std::swap_ranges(it, it + mXDimension, it2);
                        break;
                    }
                }
            }
        }
    }

    void CGameBoardModel::showFigure()
    {
        auto tiles = mFigure->getTiles();
        int index = 0;
        int x = mFigure->getX();
        int y = mFigure->getY();

        mShadow->setX(x);
        mShadow->setY(y);

        while (canMove(mShadow->getX(), mShadow->getY() + 1))
            mShadow->move(EMoveDirection::DOWN);

        for (int fI = y, sI = mShadow->getY(); fI < y + mFigure->getHeight(); ++fI, ++sI) {
            for (int j = x; j < x + mFigure->getWidth(); ++j) {
                if (tiles[index++]) {
                    mBoard[sI * mXDimension + j] = { true, false };
                    mBoard[fI * mXDimension + j] = { true, true, mFigure->getColor() };
                }
            }
        }

        emit dataChanged(createIndex(0, 0), createIndex(mBoard.size(), 0));
    }

    void CGameBoardModel::hideFigure()
    {
        auto tiles = mFigure->getTiles();
        int index = 0;
        int x = mFigure->getX();
        int y = mFigure->getY();

        for (int fI = y, sI = mShadow->getY(); fI < y + mFigure->getHeight(); ++fI, ++sI) {
            for (int j = x; j < x + mFigure->getWidth(); ++j) {
                if (tiles[index++]) {
                    mBoard[sI * mXDimension + j] = { false, false };
                    mBoard[fI * mXDimension + j] = { false, false };
                }
            }
        }
    }

    bool CGameBoardModel::canMove(int x, int y)
    {
        auto tiles = mFigure->getTiles();
        int index = 0;

        if ( x + mFigure->getWidth() > mXDimension ||
             y + mFigure->getHeight() > mYDimension ||
             x < 0) {
            return false;
        }

        for (int i = y; i < y + mFigure->getHeight(); ++i) {
            for (int j = x; j < x + mFigure->getWidth(); ++j, ++index) {
                if (tiles[index] && mBoard[i * mXDimension + j].mDisplay) {
                    return false;
                }
            }
        }

        return true;
    }
}
