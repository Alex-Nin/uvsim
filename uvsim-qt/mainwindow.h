#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QToolBar>
#include <QColorDialog>
#include <QLabel>

#include "../uvsim.h"

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
    void setDefaultColors();
    void changeColors();
    void onTextViewerTextChanged();
    void onConsoleFieldInput();

private:
    Ui::MainWindow *ui;

    QTextEdit *console;
    QPushButton *button1, *button2, *button3, *button4;
    QTextEdit *textViewer;
    QLabel *statusLabel;
    QLabel *consoleLabel;
    QLabel *editorLabel;
    QLineEdit *consoleField;
    QToolBar *toolbar;

    QColor defaultPrimaryColor;
    QColor defaultSecondaryColor;
    QColor currentPrimaryColor;
    QColor currentSecondaryColor;

    int fieldOutput;
    void applyColors(const QColor &primary, const QColor &secondary);

    void loadTextFile();
    void saveTextFile();
    void setTextFileTitle(QString title);
    void run();

    bool waitingForInput;
    int inputOperand;
};
#endif // MAINWINDOW_H
