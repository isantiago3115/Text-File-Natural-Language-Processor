#include "ProjectTest.h"

QTEST_MAIN(ProjectTest)

using std::vector;
using std::string;

void ProjectTest::initTestCase(){
    pmw = new MainWindow();
    pmw->show();
    D = new Document();
    QString fileToLoad = "thehobbit.txt";
    QString fullFilePath;
    QDirIterator it(QDir::currentPath() + "/text", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        if (it.fileName() == fileToLoad) {
            fullFilePath = it.filePath();
            break;
        }
    }
    QVERIFY2(!fullFilePath.isEmpty(), "File not found in 'text' folder");
    D->load(fullFilePath.toStdString());
    pdw = new DocumentWindow();
    pdw->load(fullFilePath);
    pdw->show();

    ptree = pmw->findChild<QTreeView*>();
    QVERIFY2(this->ptree, "Could not find a QTreeView in the MainWindow");
    pmwlayout = pmw->findChild<QVBoxLayout*>();
    pdwlayout = pdw->findChild<QVBoxLayout*>();
    pcharcount = pdw->findChild<QLabel*>("CharCount");
    QVERIFY2(pcharcount, "CharCount QLabel not found");
    ptokcount = pdw->findChild<QLabel*>("TokCount");
    QVERIFY2(ptokcount, "TokCount QLabel not found");
    psyllcount = pdw->findChild<QLabel*>("SyllCount");
    QVERIFY2(psyllcount, "SyllCount QLabel not found");
    peasecalc = pdw->findChild<QLabel*>("EaseCalc");
    QVERIFY2(peasecalc, "EaseCalc QLabel not found");
    pfkcalc = pdw->findChild<QLabel*>("FKCalc");
    QVERIFY2(pfkcalc, "FKCalc QLabel not found");
    pgfcalc = pdw->findChild<QLabel*>("GFCalc");
    QVERIFY2(pgfcalc, "GFCalc QLabel not found");
}

string syllabizedstring(string input, vector<int> breaks) {
    string result = input;
    for (vector<int>::reverse_iterator it = breaks.rbegin(); it != breaks.rend(); ++it) {
    if (*it > 0) { // don't insert a dash for the start of the word
    result.insert(*it, "-");
    }
}
return result;
}

void ProjectTest::testsyllabizer(){
    vector<string> words = {"emit", "poke", "mango", "opening", "napkin", "ope", "computer", "nation", "undeniable", "recalling"};
    vector<string> syllabized = {"e-mit", "poke", "man-go", "o-pen-ing", "nap-kin", "ope", "com-put-er", "na-tion", "un-de-ni-able", "re-call-ing"};
    for(int i = 0; i<10; i++){
        string result = syllabizedstring(words[i], Syllabizer::syllabize(words[i]));
        QVERIFY(result==syllabized[i]);
    }
}

void ProjectTest::testdocument(){
    Document D1;
    Document D2("mango test. Two opening.");
    Document D3 = D2;
    QVERIFY(!(D3==D1));
    QVERIFY(D3==D2);
    D1 = D3;
    QVERIFY(D1==D3);
    QVERIFY(D2.numsentences()==2);
    QVERIFY(D2.numhardwords()==1);
    QVERIFY(D2.numtokens()==4);
    QVERIFY(D2.numsyllables()==7);
}

void ProjectTest::testtoken(){
    Token T1("opening");
    Token T2("Sentence");
    Token T3 = T2;
    QVERIFY(T3!=T1);
    QVERIFY(T3==T2);
    T3 = T1;
    QVERIFY(T3==T1);
    QVERIFY(T3!=T2);
    QVERIFY(T3.get()=="opening");
    QVERIFY(T1.get()=="opening");
}

void ProjectTest::testreadinglevel(){
    Document D4("Would you needlessly ignore me... without proof of a disreputable action? For what reason am I thus disregarded? It will not stand! I will plead my case before a jury of my peers, and will see justice done.");
    QVERIFY(D4.numtokens()==38);
    QVERIFY(D4.numsyllables()==54);
    QVERIFY(D4.numsentences()==4);
    QVERIFY(D4.numhardwords()==4);
    QVERIFY(D4.getreadingease()>76);
    QVERIFY(D4.getreadingease()<78);
    QVERIFY(D4.getfkgradelevel()>4);
    QVERIFY(D4.getfkgradelevel()<5);
    QVERIFY(D4.getgfgradelevel()>4);
    QVERIFY(D4.getgfgradelevel()<5);

    QVERIFY(D->numtokens() == 8846);
    QVERIFY(D->numsyllables() == 11623);
    QVERIFY(D->numsentences() == 534);
    QVERIFY(D->numhardwords() == 439);
    QVERIFY(qAbs(D->getreadingease() - 78.8627) < .1);
    QVERIFY(qAbs(D->getfkgradelevel() - 6.3749) < .1);
    QVERIFY(qAbs(D->getgfgradelevel() - 7.12249) < .1);
}

void ProjectTest::testguimainwin(){
    QString fileToLoad = "thehobbit.txt";
    QString fullFilePath;
    QDirIterator it(QDir::currentPath() + "/text", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        if (it.fileName() == fileToLoad) {
            fullFilePath = it.filePath();
            break;
        }
    }
    QVERIFY2(!fullFilePath.isEmpty(), "File not found in 'text' folder");
    QFileSystemModel* fsmodel = qobject_cast<QFileSystemModel*>(this->ptree->model());
    QModelIndex fidx = fsmodel->index(fullFilePath);
    QVERIFY2(fidx.isValid(), "file not found");
    QRect rect = this->ptree->visualRect(fidx);
    QPoint nameloc = rect.center();
    QTest::mouseClick(this->ptree->viewport(), Qt::LeftButton, Qt::NoModifier, nameloc);
    DocumentWindow* docWin = pmw->findChild<DocumentWindow*>();
    QVERIFY2(docWin, "DocumentWindow did not open after clicking file");
}

void ProjectTest::testguidocwin(){
    QCOMPARE(pcharcount->text(), QString("char count: "+QString::number(D->numchar())));
    QCOMPARE(ptokcount->text(), QString("token count: "+QString::number(D->numtokens())));
    QCOMPARE(psyllcount->text(), QString("syllable count: "+QString::number(D->numsyllables())));
    QCOMPARE(peasecalc->text(), QString("reading ease: "+QString::number(D->getreadingease())));
    QCOMPARE(pfkcalc->text(), QString("F-K grade level: "+QString::number(D->getfkgradelevel())));
    QCOMPARE(pgfcalc->text(), QString("G-F grade level: "+QString::number(D->getgfgradelevel())));
}

void ProjectTest::cleanupTestCase(){
    if(pdw){
        pdw->close();
        delete pdw;
        pdw = nullptr;
    }
    if(pmw){
        pmw->close();
        delete pmw;
        pmw = nullptr;
    }
    if(D){
        delete D;
        D = nullptr;
    }
}