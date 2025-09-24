#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(1200, 800);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    QToolBar *toolbar = addToolBar("Navigation");


    QAction *backAction = toolbar->addAction("⟵");
    connect(backAction, &QAction::triggered, this, [this] {
        if (currentView()) currentView()->back();
    });

    QAction *forwardAction = toolbar->addAction("⟶");
    connect(forwardAction, &QAction::triggered, this, [this] {
        if (currentView()) currentView()->forward();
    });

    QAction *reloadAction = toolbar->addAction("⟳");
    connect(reloadAction, &QAction::triggered, this, [this] {
        if (currentView()) currentView()->reload();
    });

    QAction *newTabAction = toolbar->addAction("+");
    connect(newTabAction, &QAction::triggered, this, &MainWindow::newTab);


    urlBar = new QLineEdit(this);
    urlBar->setPlaceholderText("Enter URL and press Enter...");
    toolbar->addWidget(urlBar);

    connect(urlBar, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);


    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget *tab = tabWidget->widget(index);
        tabWidget->removeTab(index);
        delete tab;
    });

    newTab();
}

MainWindow::~MainWindow()
{
}

void MainWindow::newTab()
{
    QWebEngineView *view = new QWebEngineView;
    view->setUrl(QUrl("https://www.google.com"));

    int index = tabWidget->addTab(view, "Tab " + QString::number(tabWidget->count() + 1));

    tabWidget->setCurrentIndex(index);

    connect(view, &QWebEngineView::urlChanged, this, &MainWindow::updateUrlBar);
    connect(view, &QWebEngineView::titleChanged, this, [this, view, index](const QString &title) {
        int idx = tabWidget->indexOf(view);
        if (idx != -1) {
            QString baseTitle = "Tab " + QString::number(idx + 1);
            if (title.contains("Google", Qt::CaseInsensitive)) {
                tabWidget->setTabText(idx, baseTitle);
            } else {
                tabWidget->setTabText(idx, title);
            }
        }
    });

}

void MainWindow::navigateToUrl()
{
    if (!currentView()) return;

    QString urlText = urlBar->text();
    if (!urlText.startsWith("http://") && !urlText.startsWith("https://")) {
        urlText.prepend("https://");
    }

    currentView()->setUrl(QUrl(urlText));
}

void MainWindow::updateUrlBar(const QUrl &url)
{
    urlBar->setText(url.toString());
}

QWebEngineView* MainWindow::currentView() const
{
    return qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
}
