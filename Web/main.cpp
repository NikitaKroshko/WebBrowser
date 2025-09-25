/**
 * @file main.cpp
 * @brief Application setup for mainwindow
 *
 * Sets up QApplication and launches the main window.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

/**
 * @brief Main entry point for the application.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments array.
 * @return int Exit status code from the Qt event loop.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Web_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Show mainwindow
    MainWindow w;
    w.show();

    // Loop
    return a.exec();
}
