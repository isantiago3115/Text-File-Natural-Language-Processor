#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QDir::currentPath()+"/text");

    model = new QFileSystemModel(this);
    folderPath = QDir::currentPath()+"/text";
    model->setRootPath(folderPath);

    tree = new QTreeView(this);
    tree->setModel(model);
    tree->setRootIndex(model->index(folderPath));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tree);

    setLayout(layout);

    connect(tree, &QTreeView::clicked, this, &MainWindow::openDoc);
}

void MainWindow::openDoc(const QModelIndex &index){
    QString filePath = model->filePath(index);
    qDebug() << "Clicked file:" << filePath;

    DocumentWindow *window = new DocumentWindow();

    window->load(filePath);
    window->show();
    windows.append(window);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (DocumentWindow* w : windows) {
        if (w) {
            w->close();
            delete w;
        }
    }
    QWidget::closeEvent(event);
}