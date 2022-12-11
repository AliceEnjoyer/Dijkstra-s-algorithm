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
//    mat.append(QVector<double>{0, 7, 9, 0, 0, 14});
//    mat.append(QVector<double>{7, 0, 10, 15, 0, 0});
//    mat.append(QVector<double>{9, 10, 0, 11, 0, 2});
//    mat.append(QVector<double>{0, 15, 11, 0, 6, 0});
//    mat.append(QVector<double>{0, 0, 0, 6, 0, 9});
//    mat.append(QVector<double>{14, 0, 2, 0, 9, 0});


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
    resLabel->setText("Distance: " + QString::number(d[m]));

//    while (m) {
//        if()
//    }

    for(auto it = path.begin(); it != path.end(); ++it) {
        qDebug() << it.key() << ": " << it.value() << "\n";
    }

//    QString sPath;

//    for(int i = path.value(m); i != -1; i = path.value(i)) { sPath.append(QString::number(i)); }

//    qDebug() << sPath;

}

void winodw::slotSetNewMatrixSizeFromDialog() {
    int buf = bSetV1->text().toInt();
    model1->setRowCount(buf);
    model1->setColumnCount(buf);
}
