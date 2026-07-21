#include "DocumentWindow.h"

DocumentWindow::DocumentWindow(QWidget *parent)
    : QWidget(parent)
{
    // D.loadlex();
    // setWindowTitle(filepath);
    // D.load(filepath.toStdString());
    charLabel = new QLabel("chars: ---");
    charLabel->setObjectName("CharCount");
    tokenLabel = new QLabel("words: ---");
    tokenLabel->setObjectName("TokCount");
    uniqueLabel = new QLabel("unique words: ---");

    syllableLabel = new QLabel("syllables: ---");
    syllableLabel->setObjectName("SyllCount");
    sentLabel = new QLabel("sentences: ---");
    QGridLayout *toprow = new QGridLayout;
    toprow->setObjectName("toprow");
    toprow->addWidget(charLabel, 0, 0);
    toprow->addWidget(tokenLabel, 0, 1);
    toprow->addWidget(uniqueLabel, 0, 2);
    toprow->addWidget(syllableLabel, 0, 3);
    toprow->addWidget(sentLabel, 0, 4);

    hardLabel = new QLabel("hard words: ---");
    easeLabel = new QLabel("reading ease: ---");
    easeLabel->setObjectName("EaseCalc");
    fkLabel = new QLabel("F-K grade level: ---");
    fkLabel->setObjectName("FKCalc");
    gfLabel = new QLabel("G-F grade level: ---");
    gfLabel->setObjectName("GFCalc");
    htmlBox = new QCheckBox("HTML output", this);
    htmlBox->setVisible(false);
    secondrow = new QGridLayout;
    secondrow->setObjectName("secondrow");
    secondrow->addWidget(hardLabel, 0, 0);
    secondrow->addWidget(easeLabel, 0, 1);
    secondrow->addWidget(fkLabel, 0, 2);
    secondrow->addWidget(gfLabel, 0, 3);
    secondrow->addWidget(htmlBox, 0, 4);

    content = new QTextEdit("");
    content->setReadOnly(true);
    QFont font("Times New Roman", 11);
    content->setFont(font);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(toprow);
    layout->addLayout(secondrow);
    layout->addWidget(content);

    setFixedSize(800, 600);
    setLayout(layout);

    workerThread = new QThread(this);
    pDW = new DocumentWorker();

    pDW->moveToThread(workerThread);

    connect(this, &DocumentWindow::startLoad, pDW, &DocumentWorker::startLoad);
    connect(pDW, &DocumentWorker::contentsReady, this, &DocumentWindow::updateContents);
    connect(pDW, &DocumentWorker::statsReady, this, &DocumentWindow::updateStats);
    connect(pDW, &DocumentWorker::htmlReady, this, &DocumentWindow::htmlReady);
    connect(pDW, &DocumentWorker::documentLoadDone, this, &DocumentWindow::documentLoadDone);
    connect(workerThread, &QThread::finished, pDW, &QObject::deleteLater);
    connect(htmlBox, &QCheckBox::toggled, this, &DocumentWindow::clickHTML);
}

void DocumentWindow::clickHTML(){
    if(htmlBox->checkState()==Qt::Checked){
        content->setHtml(htmlContent);
    } else if (htmlBox->checkState()==Qt::Unchecked){
        content->setPlainText(plainText);
    }
}

void DocumentWindow::updateContents(QString contents){
    plainText = contents;
    content->setPlainText(contents);
    charLabel->setText("chars: " + QString::number(contents.size()));
}

void DocumentWindow::updateStats() {
    tokenLabel->setText("words: " + QString::number(pDW->getNumTokens()));
    uniqueLabel->setText("unique words: " + QString::number(pDW->getNumUnique()));
    syllableLabel->setText("syllables: " + QString::number(pDW->getNumSyllables()));
    sentLabel->setText("sentences: " + QString::number(pDW->getNumSentences()));

    hardLabel->setText("hard words: " + QString::number(pDW->getNumHardWords()));
    easeLabel->setText("reading ease: " + QString::number(pDW->getReadingEase()));
    fkLabel->setText("F-K grade level: " + QString::number(pDW->getFKGradeLevel()));
    gfLabel->setText("G-F grade level: " + QString::number(pDW->getGFGradeLevel()));
}

void DocumentWindow::htmlReady() {
    htmlContent = pDW->getHTML();
    htmlBox->setVisible(true);
}

void DocumentWindow::documentLoadDone() {
    workerThread->quit();
    workerThread->wait();
}