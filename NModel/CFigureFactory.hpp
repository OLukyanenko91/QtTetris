#ifndef CFIGUREFACTORY_HPP
#define CFIGUREFACTORY_HPP

#include <QRandomGenerator>
#include "CFigure.hpp"
#include "CFigureI.hpp"
#include "CFigureJ.hpp"
#include "CFigureL.hpp"
#include "CFigureO.hpp"
#include "CFigureS.hpp"
#include "CFigureT.hpp"
#include "CFigureZ.hpp"

namespace NModel {
    class CFigureFactory
    {
    public:
        static CFigure* createFigure()
        {
            int type = QRandomGenerator::global()->bounded(0, (int)EFigureType::I + 1);

            switch ((EFigureType)type) {
            case NModel::EFigureType::I:
                return new CFigureI();
                break;
            case NModel::EFigureType::J:
                return new CFigureJ();
                break;
            case NModel::EFigureType::L:
                return new CFigureL();
                break;
            case NModel::EFigureType::O:
                return new CFigureO();
                break;
            case NModel::EFigureType::S:
                return new CFigureS();
                break;
            case NModel::EFigureType::T:
                return new CFigureT();
                break;
            case NModel::EFigureType::Z:
                return new CFigureZ();
                break;
            default:
                break;
            }

            return nullptr;
        }
    };
}

#endif // CFIGUREFACTORY_HPP
