#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DocumentWindow.h"
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QList>
#include <QString>

class MainWindow: public QWidget
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);

    private slots:
        void openDoc(const QModelIndex &index);

    protected:
        void closeEvent(QCloseEvent *event) override;

    private:
        QTreeView *tree;
        QFileSystemModel *model;
        QString folderPath;
        QList<DocumentWindow*> windows;
};

#endif