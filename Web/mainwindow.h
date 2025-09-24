#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newTab();
    void navigateToUrl();
    void updateUrlBar(const QUrl &url);

private:
    QLineEdit *urlBar;
    QTabWidget *tabWidget;
    QWebEngineView* currentView() const;
};

#endif
