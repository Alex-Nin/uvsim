#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QToolBar>
#include <QColorDialog>
#include <QLabel>

#include "../uvsim.h"
#include "qeventloop.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onTextViewerTextChanged();
    void onConsoleFieldInput();
    void setDefaultColors();
    void changeColors();
    void onTabChanged(int index);

    // Tab-related
    void addNewTab();

private:
    Ui::MainWindow *ui;

    QTextEdit *console, *textViewer;
    QPushButton *button1, *button2, *button3, *button4, *tb;
    QLabel *statusLabel, *consoleLabel, *editorLabel;
    QLineEdit *consoleField;

    // Tabs
    QTabWidget *tabWidget;
    std::vector<UVSim*> uvsimList;

    void createTab();
    // Toolbar for Colors
    QToolBar *colorToolbar, *tabToolbar;
    QColor defaultPrimaryColor, defaultSecondaryColor, currentPrimaryColor, currentSecondaryColor;
    void applyColors(const QColor &primary, const QColor &secondary);

    // Buttons and LineEdit
    void loadTextFile();
    void saveTextFile();
    void setTextFileTitle(QString title);
    void run();
    int getUserInput();

    // De-globalized
    UVSim simulator;
    QEventLoop inputLoop;
    int userInput;

};
#endif // MAINWINDOW_H
