#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *view = new QWebEngineView(this);
    view->setUrl(QUrl("https://www.google.com"));
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
