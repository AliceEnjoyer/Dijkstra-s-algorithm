#include "winodw.h"
#define INF 2147483646 // infinite

void winodw::slotDioSetNewMatSizeShow() {
    dioSetNewMatSize->show();
}

void winodw::slotCalculateClicked() {
    bool isAok = true;
    bool isBok = true;
    int A = startPointA->text().toInt(&isAok);
    int B = endPointB->text().toInt(&isBok);
    if (!isAok || A < 0 || !isBok || B < 0 || model1->columnCount() <= 0) return;
    QVector<QVector<double>> mat = model1->GetVectoredMat();


    int m = A;
    int s = mat.size();
    QHash<int, int> path;
    QVector<double> d(s, INF);
    QSet<int> set;
    d[A] = 0;
    set.insert(A);
    path.insert(A, -1);

    do {
        for(int i = 0 ; i < s; ++i){
            if(d[i] > mat[m][i] + d[m] && mat[m][i] != 0 && set.find(i) == set.end()) d[i] = mat[m][i] + d[m];
        }

        int min = INF;
        int buf{};
        for(int i = 0; i < s; ++i) {
            if(min >= d[i] && set.find(i) == set.end()){
                min = d[i];
                buf = i;
            }
        }

        path.insert(buf, m);

        m = buf;
        set.insert(m);

    } while (m != B);

    QString res;
    for(int i = B; i != A; i = path.value(i)) {
        QMap<int, double> buf;
        for(int j = 0; j < s; ++j){
            if(mat[i][j] != 0){
                buf.insert(j, d[j] + mat[i][j]);
            }
        }
        int min = INF;
        int resPos = -1;
        for(int j : buf.keys()){
            if(min > buf[j]){
                min = buf[j];
                resPos = j;
            }
        }
        path[i] = resPos;
        res.append(QString::number(i)+ ' ');
    }
    std::reverse(res.begin(), res.end());
    resLabel->setText("Distance: " + QString::number(d[m]) + "\tPath: " + QString::number(A) + ' ' + res);
}

void winodw::slotSetNewMatrixSizeFromDialog() {
    int buf = bSetV1->text().toInt();
    model1->setRowCount(buf);
    model1->setColumnCount(buf);
}

