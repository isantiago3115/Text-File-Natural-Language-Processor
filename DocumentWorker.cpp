#include "DocumentWorker.h"

DocumentWorker::DocumentWorker(QObject *parent)
    : QObject(parent)
{
}

void DocumentWorker::startLoad(QString filename){
    D.loadlex();
    D.load(filename.toStdString());

    emit contentsReady(QString::fromStdString(D.contents));

    tokens = D.numtokens();
    uniques = D.numunique();
    sylls = D.numsyllables();
    sents = D.numsentences();
    hard = D.numhardwords();
    ease = D.getreadingease();
    fk = D.getfkgradelevel();
    gf = D.getgfgradelevel();
    emit statsReady();

    html = QString::fromStdString(D.gethtml());
    emit htmlReady();

    emit documentLoadDone();

}

int DocumentWorker::getNumTokens()
{
    return tokens;
}

int DocumentWorker::getNumUnique()
{
    return uniques;
}

int DocumentWorker::getNumSyllables()
{
    return sylls;
}

int DocumentWorker::getNumSentences()
{
    return sents;
}

int DocumentWorker::getNumHardWords()
{
    return hard;
}

double DocumentWorker::getReadingEase()
{
    return ease;
}

double DocumentWorker::getFKGradeLevel()
{
    return fk;
}

double DocumentWorker::getGFGradeLevel()
{
    return gf;
}

QString DocumentWorker::getHTML()
{
    return html;
}