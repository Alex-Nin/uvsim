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

// Inside MainWindow constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , defaultPrimaryColor("#4C721D")
    , defaultSecondaryColor("#FFFFFF")
    , currentPrimaryColor(defaultPrimaryColor)
    , currentSecondaryColor(defaultSecondaryColor)
    , userInput(0)
{
    ui->setupUi(this);

    // Create main components
    tabWidget = new QTabWidget(this);
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

    applyColors(defaultPrimaryColor, defaultSecondaryColor);
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

    // QMAPS
    uvsimMap[newTabIndex] = newUVSim;
    textViewerMap[newTabIndex] = textViewer;
    consoleMap[newTabIndex] = console;
    consoleFieldMap[newTabIndex] = consoleField;
    statusLabelMap[newTabIndex] = statusLabel;

    // Connect signals and slots within the tab's context
    connect(button1, &QPushButton::clicked, [this, newTabIndex]() { onButton1Clicked(newTabIndex); });
    connect(button2, &QPushButton::clicked, [this, newTabIndex]() { onButton2Clicked(newTabIndex); });
    connect(button3, &QPushButton::clicked, [this, newTabIndex]() { onButton3Clicked(newTabIndex); });
    connect(button4, &QPushButton::clicked, [this, newTabIndex]() { onButton4Clicked(newTabIndex); });

    // Connect text viewer changes
    connect(textViewer, &QTextEdit::textChanged, [this, newTabIndex]() { onTextViewerTextChanged(newTabIndex); });

    // Connect console field input
    connect(consoleField, &QLineEdit::returnPressed, [this, newTabIndex]() { onConsoleFieldInput(newTabIndex); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButton1Clicked(int tabIndex)
{
    UVSim *currentSim = uvsimMap.value(tabIndex, nullptr);
    QTextEdit *currentTextViewer = textViewerMap.value(tabIndex, nullptr);
    QTextEdit *currentConsole = consoleMap.value(tabIndex, nullptr);

    if (currentSim && currentTextViewer) {
        loadTextFile(currentSim, currentTextViewer, currentConsole);
        consoleMap[tabIndex]->append("Load button clicked");
    }
}

void MainWindow::onButton2Clicked(int tabIndex)
{
    UVSim *currentSim = uvsimMap.value(tabIndex, nullptr);
    QTextEdit *currentConsole = consoleMap.value(tabIndex, nullptr);

    if (currentSim && currentConsole) {
        currentConsole->append("Execute button clicked");
        run(currentSim, currentConsole);
    }
}

void MainWindow::onButton3Clicked(int tabIndex)
{
    saveTextFile(tabIndex);
    consoleMap[tabIndex]->append("Save button clicked");
}

void MainWindow::onButton4Clicked(int tabIndex)
{
    QTextEdit *currentConsole = consoleMap.value(tabIndex, nullptr);

    if (currentConsole) {
        currentConsole->clear();
        currentConsole->append("Console cleared");
    } else {
        qDebug() << "Error: Console widget not found for the current tab.";
    }
}

void MainWindow::onConsoleFieldInput(int tabIndex)
{
    QLineEdit *currentConsoleField = consoleFieldMap.value(tabIndex, nullptr);
    if (currentConsoleField) {
        bool ok;
        int userInput = currentConsoleField->text().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Console Field Input Error", "Please enter a valid integer.");
            currentConsoleField->clear();
            return;
        }

        this->userInput = userInput; // Update the member variable

        currentConsoleField->clear();
        inputLoop.exit();
    }
}

void MainWindow::loadTextFile(UVSim *simulator, QTextEdit *textViewer, QTextEdit *console)
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
                console->append("Warning: Exceeded line limit! Operations beyond line 250 will not be processed."); /* remove line */
            }
            file.close();
        }
    }
    setTextFileTitle(filepath); // If this function depends on the current tab, ensure it handles per-tab titles correctly
}

void MainWindow::saveTextFile(int tabIndex)
{
    QTextEdit *currentTextViewer = textViewerMap.value(tabIndex, nullptr);

    if (!currentTextViewer) return; // Safety check

    QString filepath = QFileDialog::getSaveFileName(this, "Save Text File", "", "Text Files (*.txt)");
    if (!filepath.isEmpty())
    {
        QFile file(filepath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << currentTextViewer->toPlainText();
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Error", "File cannot be saved.");
        }
    }
}

void MainWindow::setTextFileTitle(QString title)
{
    title.append(" - UVSim");
    QMainWindow::setWindowTitle(title);
}

int MainWindow::getUserInput()
{
    while (true) {
        inputLoop.exec();

        QString inputStr = QString::number(userInput);
        QRegularExpression pattern("^[+-]?\\d{1,6}$");
        QRegularExpressionMatch match = pattern.match(inputStr);

        if (!match.hasMatch()) {
            QMessageBox::critical(this, "Error", "User input is invalid: " + inputStr);
            // Clear input field in the current tab
            int currentIndex = tabWidget->currentIndex();
            QLineEdit *currentConsoleField = consoleFieldMap.value(currentIndex, nullptr);
            if (currentConsoleField) {
                currentConsoleField->clear();
            }
        } else {
            break;
        }
    }

    // Append validated input to console
    int currentIndex = tabWidget->currentIndex();
    QTextEdit *currentConsole = consoleMap.value(currentIndex, nullptr);
    if (currentConsole) {
        currentConsole->append(QString::number(userInput));
    }

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
    QColor primaryColor = QColorDialog::getColor(currentPrimaryColor, this, "Select Primary Color");
    if (primaryColor.isValid()) {
        currentPrimaryColor = primaryColor;
    }

    QColor secondaryColor = QColorDialog::getColor(currentSecondaryColor, this, "Select Secondary Color");
    if (secondaryColor.isValid()) {
        currentSecondaryColor = secondaryColor;
    }

    applyColors(currentPrimaryColor, currentSecondaryColor);
}

void MainWindow::applyColors(const QColor &primaryColor, const QColor &secondaryColor)
{
    QPalette palette = qApp->palette();
    palette.setColor(QPalette::Window, primaryColor);
    palette.setColor(QPalette::WindowText, secondaryColor);
    qApp->setPalette(palette);

    currentPrimaryColor = primaryColor;
    currentSecondaryColor = secondaryColor;
}

void MainWindow::onTextViewerTextChanged(int tabIndex)
{
    static bool isUpdating = false;
    if (isUpdating) return;

    isUpdating = true;

    UVSim *simulator = uvsimMap.value(tabIndex, nullptr);
    QTextEdit *textViewer = textViewerMap.value(tabIndex, nullptr);
    QLabel *statusLabel = statusLabelMap.value(tabIndex, nullptr); // Assuming you have a statusLabelMap for each tab

    if (!simulator || !textViewer || !statusLabel) {
        isUpdating = false;
        return; // Safety check
    }

    simulator->clearMemory();

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
        simulator->setMemory(i, value);
    }

    isUpdating = false;
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
