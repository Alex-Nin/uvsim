#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFormLayout>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create widgets
    textViewer = new QTextBrowser(this);
    button1 = new QPushButton("Load File", this);
    button2 = new QPushButton("Execute File", this);
    button3 = new QPushButton("Enter", this);
    button4 = new QPushButton("Clear output", this);
    console = new QTextEdit(this);

    // Set console to read-only for output part
    console->setReadOnly(true);
    textViewer->setReadOnly(false);

    // Connect buttons to slots
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButton3Clicked);
    connect(button4, &QPushButton::clicked, this, &MainWindow::onButton4Clicked);

    // Connect console input
    connect(console, &QTextEdit::textChanged, this, &MainWindow::onConsoleInput);

    // Layout setup
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);
    layout->addWidget(button3, 0, 2);
    layout->addWidget(button4, 0, 3);
    layout->addWidget(console, 1, 0, 3, 2); // Span 1 row, 4 columns
    layout->addWidget(textViewer, 1, 2, 3, 2); // Span 1 row, 4 columns

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButton1Clicked()
{
    console->append("Load button clicked");
}

void MainWindow::onButton2Clicked()
{
    console->append("Execute button clicked");
}

void MainWindow::onButton3Clicked()
{
    console->append("Enter button clicked");
}

void MainWindow::onButton4Clicked()
{
    console->clear();
    console->append("Console cleared");
}

void MainWindow::onConsoleInput()
{
    QString input = console->toPlainText();
    // Process console input (e.g., clear console)
    if (input.endsWith("\n"))
    {
        // For example, clear the console
        console->clear();
    }
}

void MainWindow::loadTextFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        console->append("Failed to open file");
        return;
    }

    QTextStream in(&file);
    textViewer->setPlainText(in.readAll());
    file.close();
}

