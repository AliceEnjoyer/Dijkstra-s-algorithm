#include "winodw.h"

void winodw::slotDioSetNewMatSizeShow() {
    dioSetNewMatSize->show();
}

void winodw::slotCalculateClicked() {
    QVector<QVector<double>> mat = model1->GetVectoredMat();
}

void winodw::slotSetNewMatrixSizeFromDialog() {
    int buf = bSetV1->text().toInt();
    model1->setRowCount(buf);
    model1->setColumnCount(buf);
}

