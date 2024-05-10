#ifndef WINODW_H
#define WINODW_H

#include <QtWidgets>
#include "matrixmodel.h"

class winodw : public QWidget {
    Q_OBJECT
private:
    MatrixModel1* model1;
    MatrixModel2* model2;
    QPushButton* bCalculate;
    QLineEdit* startPointA;
    QLabel* resLabel;
    QPushButton* bSetNewMatrixSize;

    QDialog* dioSetNewMatSize;
    QLineEdit* bSetV1;
    QPushButton *enterMatSize;

    QMenuBar* menu;
public:
    winodw(QWidget *parent = nullptr);
private slots:
    void slotCalculateClicked();
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();
};
#endif // WINODW_H
