#include <QtTest/QtTest>
#include <QtWidgets>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QTreeView>

#include "MainWindow.h"
#include "DocumentWindow.h"
#include "Syllabizer.hpp"
#include "Document.hpp"

class ProjectTest: public QObject {
    Q_OBJECT

    private:
        MainWindow* pmw;
        DocumentWindow* pdw;
        Document* D;
        QTreeView* ptree;
        QVBoxLayout* pmwlayout;
        QVBoxLayout* pdwlayout;

        QLabel* pcharcount; // pointer to the char couht display widget
        QLabel* ptokcount;
        QLabel* psyllcount;

        QLabel* peasecalc;
        QLabel* pfkcalc;
        QLabel* pgfcalc;

    private slots:
        void initTestCase();
        void testsyllabizer();
        void testdocument();
        void testtoken();
        void testreadinglevel();
        void testguimainwin();
        void testguidocwin();
        void cleanupTestCase();

};