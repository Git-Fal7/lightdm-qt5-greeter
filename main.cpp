/*
* Copyright (c) 2012-2015 Christian Surlykke, Petr Vanek
*
* This file is part of lightdm-qt5-greeter 
* It is distributed under the LGPL 2.1 or later license.
* Please refer to the LICENSE file for a copy of the license.
*/
#include <QtGlobal>
#include <QtDebug>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QIcon>
#include <QLocale>
#include <QSettings>
#include <QTranslator>

#include <iostream>

#include "settings.h"
#include "mainwindow.h"

QFile logfile;
QTextStream ts;

void messageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
    std::cerr << type << ": " << msg.toLatin1().data() << "\n";
}

int main(int argc, char *argv[])
{
    // I have no idea why, but Qt's stock qDebug() output never makes it
    // to /var/log/lightdm/x-0-greeter.log, so we use std::cerr instead..
    qInstallMessageHandler(messageHandler);
    Cache::prepare();

    QApplication a(argc, argv);

    QTranslator* translator = new QTranslator();
    if (translator->load("lightdm-qt5-greeter_" + QLocale::system().name(), "/usr/share/lightdm-qt5-greeter/translations")) {
        QCoreApplication::installTranslator(translator);
    }

    /*if (! Settings().iconThemeName().isEmpty()) {
        QIcon::setThemeName(Settings().iconThemeName());
    }*/

    MainWindow *focusWindow = 0;
    for (int i = 0; i < QGuiApplication::screens().count(); ++i) {
        MainWindow *w = new MainWindow(i);
        w->show();
        if (w->showLoginForm())
            focusWindow = w;
    }

    // Ensure we set the primary screen's widget as active when there
    // are more screens
    if (focusWindow) {
        focusWindow->setFocus(Qt::OtherFocusReason);
        focusWindow->activateWindow();
    }

    return a.exec();
}
