#include "winodw.h"
#define INF 2147483646 // infinite

void winodw::slotDioSetNewMatSizeShow() {
    dioSetNewMatSize->show();
}

void winodw::slotCalculateClicked() {
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

    QVector<QVector<double>> matForGraph2(s, QVector<double>(s, 0));
    for (int i = 0; i < s; ++i) {
        model2->setRes(i, resMat[i].first, QString::fromStdString(resMat[i].second));
        std::string p = resMat[i].second;
        std::istringstream iss(p);
        std::string vert = "";
        std::string lastVert = "";
        while (iss >> vert) {
            if(lastVert != "") {
                int v1 = std::stoi(vert);
                int v2 = std::stoi(lastVert);
                matForGraph2[v1][v2] = 1;

            }
            lastVert = vert;
        }
    }
    graph2->setMat(matForGraph2);

    //QString a = QString().fromStdString(resMat[B].second + ": " + std::to_string(resMat[B].first));
    //resLabel->setText(a);
}

void winodw::slotSetNewMatrixSizeFromDialog() {
    int buf = bSetV1->text().toInt();
    model1->setRowCount(buf);
    model1->setColumnCount(buf);
    model2->setColumnCount(buf);
}


