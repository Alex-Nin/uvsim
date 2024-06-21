#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onConsoleInput();

    void loadTextFile();

private:
    Ui::MainWindow *ui;
    QTextEdit *console;
    QPushButton *button1, *button2, *button3, *button4;
    QTextBrowser *textViewer;
};
#endif // MAINWINDOW_H
