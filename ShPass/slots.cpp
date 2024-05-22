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
            QVector<QVector<double>> mat = loadAdjacencyMatrix(QFileDialog::getOpenFileName(0, "Pick your save file", "", "*.txt"));
            setMatSize(mat.size());
            model1->setMat(mat);
        } catch(...) {
            std::cout << "ERROR\n";
        }


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
            std::cout << "Unable to open file for writing." << std::endl;
        }
    } else if(a->text() =="Save as..."){
        saveAdjacencyMatrix(model1->GetVectoredMat(), QFileDialog::getSaveFileName(0, "Save file", "", "*.txt"));
    } else if(a->text() == "Help..."){

    } else if(a->text() == "About...") {
        QMessageBox::about(0, "About", "<h1>ShPath</h1>\n<h3>This is a program written to solve the problem of searching short distances with path visualization created by Ilhin Serhii, student of KPI IASA, for coursework.<h3>");
    }
}



void window::slotCalculateClicked() {
    bool isAok = true;
    int A = startPointA->text().toInt(&isAok);
    if (!isAok || A < 0 || /*!isBok || B < 0 ||*/ model1->columnCount() <= 0) return;
    QVector<QVector<double>> mat = model1->GetVectoredMat();
    graph1->setMat(mat);

    int s = mat.size();
    QVector<bool> map(s, 0);
    QVector<std::pair<double, std::string>> resMat(s, std::pair<double,std::string>(INF, ""));
    resMat[A] = std::pair<double,std::string>(0, std::to_string(A)+" ");

    int min = A;
    map[min] = 1;
    while(true) {
        if(mat[min].count(0) == s) break;
        for (int i = 0; i < s; ++i) {
            double item = mat[min][i];
            if(item == 0) continue;
            else if(resMat[min].first+item < resMat[i].first){
                resMat[i].first = resMat[min].first+item;
                resMat[i].second = resMat[min].second+std::to_string(i)+" ";
            }
        }

        int minValue = INF;
        int countTrues = 0;
        for (int i = 0; i < s; ++i) {
            if(!map[i]){
                if(resMat[i].first < minValue) {
                    minValue = resMat[i].first;
                    min = i;
                }
            } else {
                ++countTrues;
            }
        }
        if(countTrues == s) {
            break;
        }        

        map[min] = 1;
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
}

void window::slotSetNewMatrixSizeFromDialog() {
    setMatSize(bSetV1->text().toInt());

}

inline void window::setMatSize(const int& size){
    model1->setRowCount(size);
    model1->setColumnCount(size);
    model2->setColumnCount(size);
}

void window::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_F4) {
        try {
            QVector<QVector<double>> mat = loadAdjacencyMatrix(QFileDialog::getOpenFileName(this, "Pick your save file", "", "*.txt"));
            setMatSize(mat.size());
            model1->setMat(mat);
        } catch (...) {
            qDebug() << "ERROR\n";
        }
    } else if (event->key() == Qt::Key_F1) {
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
            qDebug() << "Unable to open file for writing.";
        }
    } else if (event->key() == Qt::Key_F3) {
        saveAdjacencyMatrix(model1->GetVectoredMat(), QFileDialog::getSaveFileName(this, "Save file", "", "*.txt"));
    }

    QWidget::keyPressEvent(event);
}


