#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFormLayout>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include <QColorDialog>
#include <QTabBar>

#include "../uvsim.h"
#include "../uvsimIO.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , defaultPrimaryColor("#4C721D")
    , defaultSecondaryColor("#FFFFFF")
    , currentPrimaryColor(defaultPrimaryColor)
    , currentSecondaryColor(defaultSecondaryColor)
{
    ui->setupUi(this);

    // De-globalized
    int userInput;
    QEventLoop inputLoop;
    std::vector<UVSim*> uvsimList;
    QMap<int, UVSim*> uvsimMap;
    QMap<int, QTextEdit*> textViewerMap;
    QMap<int, QTextEdit*> consoleMap;

    // Create widgets
    console = new QTextEdit(this);
    textViewer = new QTextEdit(this);
    button1 = new QPushButton("Load File", this);
    button2 = new QPushButton("Execute File", this);
    button3 = new QPushButton("Save As", this);
    button4 = new QPushButton("Clear console", this);
    consoleField = new QLineEdit(this);
    statusLabel = new QLabel("Lines: 0 / 250", this);
    tabWidget = new QTabWidget(this);

    // Set central widget to tabWidget
    setCentralWidget(tabWidget);

    // Adding the "+" button to the tab bar
    QPushButton *addTabButton = new QPushButton("+", this);
    addTabButton->setFixedSize(20, 20);
    addTabButton->setFlat(true);
    tabWidget->setCornerWidget(addTabButton, Qt::TopRightCorner);

    // Connect "+" button signal to slot to create a new tab
    connect(addTabButton, &QPushButton::clicked, this, &MainWindow::createTab);

    // Connect to handle tab clicks
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Create the first tab
    createTab();

    // Toolbar for Colors
    colorToolbar = addToolBar("Toolbar");
    QAction *viewDefaultColors = new QAction("Set Default Colors", this);
    QAction *changeColorsAction = new QAction("Change Colors", this);
    colorToolbar->addAction(viewDefaultColors);
    colorToolbar->addAction(changeColorsAction);
    connect(viewDefaultColors, &QAction::triggered, this, &MainWindow::setDefaultColors);
    connect(changeColorsAction, &QAction::triggered, this, &MainWindow::changeColors);

    // Connect consoleField returnPressed signal to slot
    connect(consoleField, &QLineEdit::returnPressed, this, &MainWindow::onConsoleFieldInput);

    // Connect user input
    connect(textViewer, &QTextEdit::textChanged, this, &MainWindow::onTextViewerTextChanged);

    // Connect a signal to add new tabs (e.g., from a menu action or button)
    applyColors(defaultPrimaryColor, defaultSecondaryColor);
    // Goes after centralWidget to ensure color layout upon opening
}

MainWindow::~MainWindow()
{
    delete ui;
    // Delete UVSim objects
    for (UVSim* sim : uvsimList) {
        delete sim;
    }
}

void MainWindow::onButton1Clicked()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1) {
        UVSim *currentSim = uvsimMap.value(currentIndex, nullptr);
        QTextEdit *currentTextViewer = textViewerMap.value(currentIndex, nullptr);

        if (currentSim && currentTextViewer) {
            loadTextFile(currentSim, currentTextViewer);
            console->append("Load button clicked");
        }
    }

}

void MainWindow::onButton2Clicked()
{

    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1) {
        UVSim *currentSim = uvsimMap.value(currentIndex, nullptr);
        QTextEdit *currentConsole = consoleMap.value(currentIndex, nullptr); // Assuming consoleMap holds QTextEdit for consoles

        if (currentSim && currentConsole) {
            run(currentSim, currentConsole);
            console->append("Execute button clicked");
        }
    }
}

void MainWindow::onButton3Clicked()
{
    saveTextFile();
    console->append("Save button clicked");
}

void MainWindow::onButton4Clicked()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1) {
        QTextEdit *currentConsole = consoleMap.value(currentIndex, nullptr); // Assuming consoleMap holds QTextEdit for consoles

        if (currentConsole) {
            currentConsole->clear();
            currentConsole->append("Console cleared");
        } else {
            // Handle the case where the console is not found
            qDebug() << "Error: Console widget not found for the current tab.";
        }
    } else {
        qDebug() << "Error: No current tab index.";
    }
}

void MainWindow::onConsoleFieldInput()
{
    userInput = consoleField->text().toInt();
    consoleField->clear();
    inputLoop.exit();
}

void MainWindow::loadTextFile(UVSim *simulator, QTextEdit *textViewer)
{
    if (!simulator || !textViewer) return; // Safety check

    textViewer->clear();
    simulator->clearMemory(); // Ensure you have this method in UVSim

    QString filepath = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");
    if (!filepath.isEmpty())
    {
        QFile file(filepath);
        int i = 0;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            bool isFourDigit = false;
            bool isSixDigit = false;

            while (!in.atEnd()) {
                QString line = in.readLine();

                QRegularExpression regex(R"([+-](\d{4}|\d{6}))");
                if (!regex.match(line).hasMatch()) {
                    QMessageBox::critical(this, "Error", "File contains invalid format.");
                    return;
                }

                if (line.length() == 5) {
                    isFourDigit = true;
                    if (isSixDigit) {
                        QMessageBox::critical(this, "Error", "File contains both 4-digit and 6-digit numbers.");
                        return;
                    }

                    QStringList instructionList = {"10", "11", "20", "21", "30", "31", "32", "33", "40", "41", "42", "43"};
                    if (instructionList.contains(line.mid(1, 2))) {
                        line.insert(1, "0");
                        line.insert(4, "0");
                    }
                    else {
                        line.insert(1, "00");
                    }
                }
                else if (line.length() == 7) {
                    isSixDigit = true;
                    if (isFourDigit) {
                        QMessageBox::critical(this, "Error", "File contains both 4-digit and 6-digit numbers.");
                        return;
                    }
                }

                textViewer->append(line);
                simulator->setMemory(i++, line.toInt());
            }
            QStringList lines = textViewer->toPlainText().split('\n');
            if (lines.size() >= 250) {
                console->append("Warning: Exceeded line limit! Operations beyond line 250 will not be processed.");
            }
            file.close();
        }
    }
    setTextFileTitle(filepath); // If this function depends on the current tab, ensure it handles per-tab titles correctly
}

void MainWindow::saveTextFile()
{
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Select File","","Text Files (*.txt);"
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
        out << QString("%1").arg(memory[i], 6, 10, QChar('0')) << '\n';
    }

    file.close();
}

void MainWindow::setTextFileTitle(QString title)
{
    title.append(" - UVSim");
    QMainWindow::setWindowTitle(title);
}

int MainWindow::getUserInput() {
    while (true) {
        inputLoop.exec();

        QRegularExpression pattern("^[+-]?\\d{1,6}$");
        if (!pattern.match(QString::number(userInput)).hasMatch()) {
            QMessageBox::critical(this, "Error", "User input is invalid: " + QString::number(userInput));
            consoleField->clear();
        }
        else {
            break;
        }
    }
    console->insertPlainText(QString::number(userInput));
    return userInput;
}

void MainWindow::run(UVSim *simulator, QTextEdit *console) {
    if (!simulator || !console) return; // Safety check

    simulator->setAccumulator(0);
    simulator->setInstructionPointer(0);
    simulator->setHalted(false);

    while (!simulator->isHalted()) {
        int instruction = simulator->fetch(simulator->getInstructionPointer());
        simulator->setInstructionPointer(simulator->getInstructionPointer() + 1);

        int opcode = instruction / 1000; //YIELDS first two numbers
        int operand = instruction % 1000; //YIELDS last two numbers

        switch (opcode) {
        case 0:
            // Do nothing.
            break;
        case 10: // READ
            console->append("Enter an integer below: ");
            simulator->setMemory(operand, getUserInput());
            break;
        case 11: // WRITE
            console->append(QString("Output of location %1: %2").arg(operand).arg(simulator->getMemoryAdd(operand)));
            break;
        default:
            simulator->execute(instruction);
        }
    }
    console->append("Simulator halted.");
}

void MainWindow::setDefaultColors()
{
    currentPrimaryColor = defaultPrimaryColor;
    currentSecondaryColor = defaultSecondaryColor;
    applyColors(defaultPrimaryColor, defaultSecondaryColor);
}

void MainWindow::changeColors()
{
    QColor newPrimaryColor = QColorDialog::getColor(currentPrimaryColor, this, "Select Primary Color");
    if (newPrimaryColor.isValid())
    {
        currentPrimaryColor = newPrimaryColor;
    }

    QColor newSecondaryColor = QColorDialog::getColor(currentSecondaryColor, this, "Select Secondary Color");
    if (newSecondaryColor.isValid())
    {
        currentSecondaryColor = newSecondaryColor;
    }

    applyColors(currentPrimaryColor, currentSecondaryColor);
}

void MainWindow::applyColors(const QColor &primary, const QColor &secondary)
{
    QPalette palette = centralWidget()->palette();

    palette.setColor(QPalette::Window, primary);
    palette.setColor(QPalette::Button, secondary);
    QString buttonStyle = QString(
                              "QPushButton {background-color: %1; color: %2}"
                              ).arg(secondary.name(), primary.name());
    button1->setStyleSheet(buttonStyle);
    button2->setStyleSheet(buttonStyle);
    button3->setStyleSheet(buttonStyle);
    button4->setStyleSheet(buttonStyle);
    statusLabel->setStyleSheet(QString("QLabel {color: %2}").arg(secondary.name()));
    centralWidget()->setPalette(palette);
    centralWidget()->setAutoFillBackground(true);
}

void MainWindow::onTextViewerTextChanged()
{
    static bool isUpdating = false;
    if (isUpdating) return;

    isUpdating = true;
    simulator.clearMemory();

    QStringList lines = textViewer->toPlainText().split('\n');
    int lineCount = lines.size();

    // Only keep first 250 lines
    if (lineCount > 250) {
        QString trimmedText = lines.mid(0, 250).join('\n');
        textViewer->setPlainText(trimmedText);
        // Move the cursor to the end of the text
        QTextCursor cursor = textViewer->textCursor();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        textViewer->setTextCursor(cursor);

        lines = trimmedText.split('\n');
        lineCount = lines.size();
    }

    statusLabel->setText(QString("Lines: %1 / 250").arg(lineCount));

    for (int i = 0; i < lineCount; ++i) {
        int value = lines[i].toInt();
        simulator.setMemory(i, value);
    }

    isUpdating = false;
}

void MainWindow::createTab()
{
    // Create a new UVSim object
    UVSim *newUVSim = new UVSim();

    // Create a QWidget to hold the UVSim interface (customize as needed)
    QWidget *tab = new QWidget();
    QVBoxLayout *tabLayout = new QVBoxLayout(tab);

    QTextEdit *console = new QTextEdit(tab);
    QTextEdit *textViewer = new QTextEdit(tab);
    QPushButton *button1 = new QPushButton("Load File", tab);
    QPushButton *button2 = new QPushButton("Execute File", tab);
    QPushButton *button3 = new QPushButton("Save As", tab);
    QPushButton *button4 = new QPushButton("Clear Console", tab);
    QLineEdit *consoleField = new QLineEdit(tab);
    QLabel *statusLabel = new QLabel("Lines: 0 / 250", tab);

    // Button Layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    buttonLayout->addWidget(button4);
    tabLayout->addLayout(buttonLayout);

    // Combo text/console horizontal layout.
    QHBoxLayout *appLayout = new QHBoxLayout();

    // Console Layout
    QVBoxLayout *consoleLayout = new QVBoxLayout();
    consoleLayout->addWidget(console);
    consoleLayout->addWidget(consoleField);
    consoleField->setPlaceholderText("Enter integer here...");
    appLayout->addLayout(consoleLayout);

    // textViewerLayout
    QVBoxLayout *textViewerLayout = new QVBoxLayout();
    textViewerLayout->addWidget(textViewer);
    textViewerLayout->addWidget(statusLabel);
    appLayout->addLayout(textViewerLayout);

    // Combine
    tabLayout->addLayout(appLayout);

    // Set layout to tab
    tab->setLayout(tabLayout);

    // Add the tab to the QTabWidget
    int newTabIndex = tabWidget->addTab(tab, tr("Simulator %1").arg(tabWidget->count() + 1));
    tabWidget->setCurrentIndex(newTabIndex);

    // Set console to read-only for output part
    console->setReadOnly(true);
    textViewer->setReadOnly(false);

    uvsimMap[newTabIndex] = newUVSim;
    textViewerMap[newTabIndex] = textViewer;
    consoleMap[newTabIndex] = console;

    // Connect
    connect(button1, &QPushButton::clicked, this, &MainWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButton3Clicked);
    connect(button4, &QPushButton::clicked, this, &MainWindow::onButton4Clicked);

    // Store the UVSim object
    uvsimList.push_back(newUVSim);
}

void MainWindow::addNewTab()
{
    createTab();
}

void MainWindow::onTabChanged(int index)
{
    if (index == -1) {
        // Handle when there are no tabs or something else specific
        return;
    }
    // Handle the tab change, such as updating UI or state based on the selected tab
}
