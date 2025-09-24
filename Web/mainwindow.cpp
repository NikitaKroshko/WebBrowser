#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    view = new QWebEngineView(this);
    view->setUrl(QUrl("https://www.google.com"));
    setCentralWidget(view);


    QToolBar *toolbar = addToolBar("Navigation");


    QAction *backAction = toolbar->addAction("⟵");
    connect(backAction, &QAction::triggered, view, &QWebEngineView::back);


    QAction *forwardAction = toolbar->addAction("⟶");
    connect(forwardAction, &QAction::triggered, view, &QWebEngineView::forward);


    QAction *reloadAction = toolbar->addAction("⟳");
    connect(reloadAction, &QAction::triggered, view, &QWebEngineView::reload);


    urlBar = new QLineEdit(this);
    urlBar->setPlaceholderText("Enter URL and press Enter...");
    toolbar->addWidget(urlBar);

    connect(urlBar, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);


    connect(view, &QWebEngineView::urlChanged, this, &MainWindow::updateUrlBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::navigateToUrl()
{
    QString urlText = urlBar->text();


    if (!urlText.startsWith("http://") && !urlText.startsWith("https://")) {
        urlText.prepend("https://");
    }

    view->setUrl(QUrl(urlText));
}

void MainWindow::updateUrlBar(const QUrl &url)
{
    urlBar->setText(url.toString());
}
