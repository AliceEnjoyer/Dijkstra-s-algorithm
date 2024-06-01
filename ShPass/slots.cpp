#include "winodw.h"
#include <iostream>
#define INF 2147483646 // infinite

void window::slotDioSetNewMatSizeShow() {
    dioSetNewMatSize->show();
}

void window::slotMenuTriggered(QAction *a)
{
    if(a->text() == "Open...") {
        try {
            bool isOk;
            QVector<QVector<double>> mat = loadAdjacencyMatrix(QFileDialog::getOpenFileName(this, "Pick your save file", "", "*.txt"), isOk);
            if(!isOk) {
                return;
            }
            setMatSize(mat.size());
            model1->setMat(mat);
        } catch (...) {
            resLabel->setText("ERROR");
        }
        QApplication::beep();
        resLabel->setText("File Loaded!");

    } else if(a->text() == "Save"){
        auto matrix = model1->GetVectoredMat();
        std::ofstream fileO;
        fileO.open(filePath.toStdString());
        if (fileO.is_open()) {
            fileO.clear();
            for (const auto& row : matrix) {
                for (int i = 0; i < row.size(); ++i) {
                    fileO << row[i];
                    if (i < row.size() - 1) {
                        fileO << " ";
                    }
                }
                fileO << "\n";
            }
            fileO.close();
        } else {
            resLabel->setText("Unable to open file for writing.");
        }
        QApplication::beep();
        resLabel->setText("File saved!");
    } else if(a->text() =="Save as..."){
        saveAdjacencyMatrix(model1->GetVectoredMat(), QFileDialog::getSaveFileName(0, "Save file", "", "*.txt"));
        QApplication::beep();
        resLabel->setText("File saved!");
    } else if(a->text() == "Help..."){
        QDesktopServices::openUrl(QUrl::fromLocalFile("Help....docx"));
    } else if(a->text() == "About...") {
        QMessageBox::about(0, "About", "<h1>ShPath</h1>\n<h3>This is a program written to solve the problem of searching short distances using Dijkstra`s algorithm with path visualization created by Ilhin Serhii, student of KPI IASA, for coursework.<h3>");
    } else if(a->text() == "Clear") {
        if(QMessageBox::warning(0, "Warning", "Do you really want to clear adjacency matrix?",
                                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes){
            model1->clear();
            model2->clear();
            graph1->clear();
            QApplication::beep();
            resLabel->setText("Adjacency matrix cleared");
        }
    }
}



void window::slotCalculateClicked() {
    bool isAok = true;
    int A = startPointA->text().toInt(&isAok);
    QVector<QVector<double>> mat = model1->GetVectoredMat();
    int s = mat.size();
    if(s == 0){
        QApplication::beep();
        QMessageBox::information(0, "Error message", "Your adjacency matrix is empty");
        return;
    }
    if(!isAok || A < 0){
        QApplication::beep();
        QMessageBox::information(0, "Error message", "You must enter a positive integer as start vertex");
        return;
    }
    if(A>=s){
        QApplication::beep();
        QMessageBox::information(0, "Error message", QString::fromStdString("your graph has "+std::to_string(s)+" vertices, but you enter vertex with number "+std::to_string(A)));
        return;
    }
    if(model1->columnCount() <= 0){
        QApplication::beep();
        QMessageBox::information(0, "Error message", "Unexpected error");
        return;
    }

    graph1->setMat(mat);

    QVector<bool> map(s, 0);
    QVector<std::pair<double, std::string>> resMat(s, std::pair<double,std::string>(INF, ""));
    resMat[A] = std::pair<double,std::string>(0, std::to_string(A)+" ");

    while (true) {
        int min = -1;
        double minValue = INF;
        for (int i = 0; i < s; ++i) {
            if (!map[i] && resMat[i].first < minValue) {
                minValue = resMat[i].first;
                min = i;
            }
        }

        if (min == -1) break;

        map[min] = true;

        for (int i = 0; i < s; ++i) {
            double item = mat[min][i];
            if (item != 0 && !map[i] && resMat[min].first + item < resMat[i].first) {
                resMat[i].first = resMat[min].first + item;
                resMat[i].second = resMat[min].second + std::to_string(i) + " ";
            }
        }
    }

    graph1->pointAllBlack();
    QVector<bool> matForResGraph(s, 0);
    for (const auto& i : resMat) {
        std::istringstream iss(i.second);
        std::string vert = "";
        while (iss >> vert) {
            matForResGraph[std::stoi(vert)] = 1;
        }
    }
    graph1->pointFindedNodes(matForResGraph);
    for (int i = 0; i < s; ++i) {
        model2->setRes(i, resMat[i].first, QString::fromStdString(resMat[i].second));
    }

    QApplication::beep();
    resLabel->setText("Matrix has been calculated!!");
}

void window::slotSetNewMatrixSizeFromDialog() {
    setMatSize(bSetV1->text().toInt());

}

inline void window::setMatSize(const int& size){
    model1->setSize(size);
    model2->setColumnCount(size);
}

void window::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F6) {
        try {
            bool isOk;
            QVector<QVector<double>> mat = loadAdjacencyMatrix(QFileDialog::getOpenFileName(this, "Pick your save file", "", "*.txt"), isOk);
            if(!isOk) {
                return;
            }
            setMatSize(mat.size());
            model1->setMat(mat);
        } catch (...) {
            resLabel->setText("ERROR");
        }
        QApplication::beep();
    } else if (event->key() == Qt::Key_F2) {
        auto matrix = model1->GetVectoredMat();
        std::ofstream fileO(filePath.toStdString());
        if (fileO.is_open()) {
            for (const auto& row : matrix) {
                for (int i = 0; i < row.size(); ++i) {
                    fileO << row[i];
                    if (i < row.size() - 1) {
                        fileO << " ";
                    }
                }
                fileO << "\n";
            }
            fileO.close();
        } else {
            resLabel->setText("Unable to open file for writing.");
        }
        QApplication::beep();
    } else if (event->key() == Qt::Key_F5) {
        saveAdjacencyMatrix(model1->GetVectoredMat(), QFileDialog::getSaveFileName(this, "Save file", "", "*.txt"));
        QApplication::beep();
    }

    QWidget::keyPressEvent(event);
}


