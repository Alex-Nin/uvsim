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
    void onButton1Clicked(int tabIndex);
    void onButton2Clicked(int tabIndex);
    void onButton3Clicked(int tabIndex);
    void onButton4Clicked(int tabIndex);
    void onTextViewerTextChanged(int tabIndex);
    void onConsoleFieldInput(int tabIndex);
    void setDefaultColors();
    void changeColors();
    void onTabChanged(int index);
    // Buttons and LineEdit

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
    QMap<int, UVSim*> uvsimMap; // Maps tab index to UVSim instances
    QMap<int, QTextEdit*> textViewerMap, consoleMap;
    QMap<int, QLineEdit*> consoleFieldMap;
    QMap<int, QLabel*> statusLabelMap;

    // Toolbar for Colors
    QToolBar *colorToolbar;
    QColor defaultPrimaryColor, defaultSecondaryColor, currentPrimaryColor, currentSecondaryColor;

    void applyColors(const QColor &primary, const QColor &secondary);

    // Buttons and LineEdit
    void loadTextFile(UVSim *simulator, QTextEdit *textViewer, QTextEdit *consoleMap);
    void saveTextFile(int tabIndex);
    void setTextFileTitle(QString title);
    void run(UVSim *simulator, QTextEdit *console);
    int getUserInput();


    // De-globalized
    QEventLoop inputLoop;
    int userInput;

    void createTab();
};
#endif // MAINWINDOW_H
