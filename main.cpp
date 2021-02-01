#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "NModel/GameBoardModel.hpp"
#include "NModel/CFigure.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");

    qmlRegisterUncreatableMetaObject(NModel::staticMetaObject,
                                     "GameAdds",
                                     1, 0,
                                     "NModel",
                                     "Error: only enums");
    qmlRegisterUncreatableMetaObject(NModel::staticMetaObject,
                                     "GameAdds",
                                     1, 0,
                                     "NModel",
                                     "Error: only enums");
    qmlRegisterType<NModel::CGameBoardModel>("Game", 1, 0, "GameBoardModel");

    QQmlApplicationEngine engine;
    NModel::CGameBoardModel model;

    const QUrl url(QStringLiteral("qrc:/resources/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
