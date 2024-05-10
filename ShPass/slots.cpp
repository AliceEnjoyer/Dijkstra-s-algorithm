#include "winodw.h"
#define INF 2147483646 // infinite

void winodw::slotDioSetNewMatSizeShow() {
    dioSetNewMatSize->show();
}

void winodw::slotCalculateClicked() {
    bool isAok = true;
 //   bool isBok = true;
    int A = startPointA->text().toInt(&isAok);
//    int B = endPointB->text().toInt(&isBok);
    if (!isAok || A < 0 || /*!isBok || B < 0 ||*/ model1->columnCount() <= 0) return;
    QVector<QVector<double>> mat = model1->GetVectoredMat();

    int s = mat.size();
    QVector<bool> map(s, 0);
    QVector<std::pair<double, std::string>> resMat(s, std::pair<double,std::string>(INF, ""));
    resMat[A] = std::pair<double,std::string>(0, std::to_string(A)+" ");

    int min = A;
    map[min] = 1;
    while(true) {
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


    for (int i = 0; i < s; ++i) {
        model2->setRes(i, resMat[i].first, QString::fromStdString(resMat[i].second));
    }

    //QString a = QString().fromStdString(resMat[B].second + ": " + std::to_string(resMat[B].first));
    //resLabel->setText(a);
}

void winodw::slotSetNewMatrixSizeFromDialog() {
    int buf = bSetV1->text().toInt();
    model1->setRowCount(buf);
    model1->setColumnCount(buf);
    model2->setColumnCount(buf);
}

