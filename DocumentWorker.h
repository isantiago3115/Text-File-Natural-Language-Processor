#ifndef DOCUMENTWORKER_H
#define DOCUMENTWORKER_H

#include <QObject>
#include <QString>
#include "Document.hpp"

class DocumentWorker: public QObject
{
    Q_OBJECT

    public:
        using QObject::sender;
        DocumentWorker(QObject *parent =nullptr);

        int getNumTokens();
        int getNumUnique();
        int getNumSyllables();
        int getNumSentences();

        int getNumHardWords();
        double getReadingEase();
        double getFKGradeLevel();
        double getGFGradeLevel();

        QString getHTML();

    signals:
        void contentsReady(QString contents);
        void statsReady();
        void htmlReady();
        void documentLoadDone();

    public slots:
        void startLoad(QString filename);
    
    private:
        Document D;
        QString html;
        int tokens;
        int uniques;
        int sylls;
        int sents;
        int hard;
        double ease;
        double fk;
        double gf;
};

#endif