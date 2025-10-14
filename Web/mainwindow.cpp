/**
 * @file mainwindow.cpp
 * @brief A tabbed web browser using Qt.
 *
 * Provides navigation toolbar, URL bar, and tabbed browsing with QWebEngineView.
 */
#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QUrl>
/**
 * @brief Construct the MainWindow with toolbar, URL bar, and tab widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1200, 800);

    // Central widget
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    // Navigation toolbar
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

    // Tab close handling
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget *tab = tabWidget->widget(index);
        tabWidget->removeTab(index);
        delete tab;
    });

    // Initial open
    newTab();
}

MainWindow::~MainWindow() {}

/**
 * @brief Open a new tab, the default is google.com.
 */
void MainWindow::newTab()
{
    QWebEngineView *view = new QWebEngineView;
    view->setUrl(QUrl("https://www.google.com"));

    int index = tabWidget->addTab(view, "Tab " + QString::number(tabWidget->count() + 1));
    tabWidget->setCurrentIndex(index);

    // Sync URL with page
    connect(view, &QWebEngineView::urlChanged, this, &MainWindow::updateUrlBar);

    // continuously update title
    connect(view, &QWebEngineView::titleChanged, this, [this, view](const QString &title) {
        int idx = tabWidget->indexOf(view);
        if (idx != -1) {
            if (title.contains("Google", Qt::CaseInsensitive))
                tabWidget->setTabText(idx, "New Tab " + QString::number(idx + 1));
            else
                tabWidget->setTabText(idx, title);
        }
    });
}

/**
 * @brief Navigate to URL typed in the URL bar, uses http as default.
 */
void MainWindow::navigateToUrl()
{
    if (!currentView()) return;

    // Handle users inputting without http
    QString urlText = urlBar->text();
    if (!urlText.startsWith("http://") && !urlText.startsWith("https://"))
        urlText.prepend("https://");

    currentView()->setUrl(QUrl(urlText));
}

/**
 * @brief Keep URL in sync with page.
 */
void MainWindow::updateUrlBar(const QUrl &url)
{
    urlBar->setText(url.toString());
}

/**
 * @brief Returns the active browser tab.
 */
QWebEngineView* MainWindow::currentView() const
{
    return qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
}
