#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H

#include "DocumentWorker.h"
#include <QLabel>
#include <chrono>
#include <QCheckBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QDebug>
#include <QThread>


class DocumentWindow: public QWidget
{
    Q_OBJECT
    public: 
        using QObject::sender;
        DocumentWindow(QWidget *parent = nullptr);
        ~DocumentWindow() {
            if (workerThread->isRunning()) {
                workerThread->quit();
                workerThread->wait();
            }
        }
        bool load(QString file) {
            // document processing
            this->setWindowTitle(file); 
            workerThread->start();
            emit startLoad(file);
            return true;
        }
        DocumentWorker *pDW;
    signals:
        void startLoad(QString filename);

    public slots:
        void clickHTML();
        void updateContents(QString contents);
        void updateStats();
        void htmlReady();
        void documentLoadDone();

    private:
        QTextEdit *content;
        QCheckBox *htmlBox;

        QLabel *charLabel;
        QLabel *tokenLabel;
        QLabel* uniqueLabel;
        QLabel *syllableLabel;
        QLabel *sentLabel;

        QLabel *hardLabel;
        QLabel *easeLabel;
        QLabel *fkLabel;
        QLabel *gfLabel;
        QGridLayout *secondrow;

        QThread *workerThread;
        QString htmlContent;
        QString plainText;
};

#endif