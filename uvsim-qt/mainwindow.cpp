#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFormLayout>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

#include "../uvsim.h"
#include "../uvsimIO.h"

UVSim simulator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create widgets
    textViewer = new QTextBrowser(this);
    button1 = new QPushButton("Load File", this);
    button2 = new QPushButton("Execute File", this);
    button3 = new QPushButton("Save As", this);
    button4 = new QPushButton("Clear output", this);
    button5 = new QPushButton("Color Scheme", this);
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
    layout->addWidget(console, 1, 0, 9, 2); // Span 0 rows, 2 columns
    layout->addWidget(textViewer, 1, 2, 10, 2); // Span 0 rows, 2 columns
    layout->addWidget(button5, 10, 1);

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
    loadTextFile();
    console->append("Load button clicked");
}

void MainWindow::onButton2Clicked()
{
    console->append("Execute button clicked");
    QString txtExport = console->toPlainText(); // Loads text-editor's content as program
    run();
}

void MainWindow::onButton3Clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Select File",
        "",
        "Text Files (*.txt);;All Files (*)"
    );

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);
    std::vector<int> memory = simulator.getMemory();

    int lastIndex = -1;
    for (int i = 0; i < memory.size(); ++i) {
        if (memory[i] != 0) {
            lastIndex = i;
        }
    }

    for (int i = 0; i <= lastIndex; ++i) {
        if (memory[i] > 0) {
            out << "+";
        }
        else if (memory[i] == 0) {
            out << "+000";
        }
        out <<memory[i] << '\n';
    }

    file.close();
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

void MainWindow::loadTextFile()
{
    textViewer->clear();
    simulator.clearMemory();
    QString filepath = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");
    if (!filepath.isEmpty())
    {
        QFile file(filepath);
        int i = 0;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString temp = in.readLine();
                textViewer->append(temp);
                simulator.setMemory(i++, temp.toInt());
            }
            file.close();
        }
    }
    this->setTextFileTitle(filepath);
}

void MainWindow::setTextFileTitle(QString title)
{
    title.append(" - UVSim");
    QMainWindow::setWindowTitle(title);
}

int MainWindow::getUserInput() { // Jess TODO
    return 1234;
}

void MainWindow::run() {
    simulator.setAccumulator(0);
    simulator.setInstructionPointer(0);
    simulator.setHalted(false);
    while (!simulator.isHalted()) {
        int instruction = simulator.fetch(simulator.getInstructionPointer());
        simulator.setInstructionPointer(simulator.getInstructionPointer() + 1);

        int opcode = instruction / 100; //YIELDS first two numbers
        int operand = instruction % 100; //YIELDS last two numbers

        switch (opcode) {
            case 10: // READ
                simulator.setMemory(operand, getUserInput());
                break;
            case 11: // WRITE
                console->append(QString::number(simulator.getMemoryAdd(operand)));
                break;
            default:
                simulator.execute(instruction);
        }
    }
}
