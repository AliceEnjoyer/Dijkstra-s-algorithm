#ifndef WINODW_H
#define WINODW_H

#include <QtWidgets>
#include "matrixmodel.h"

class winodw : public QWidget {
    Q_OBJECT
private:
    MatrixModel1* model1;
    QPushButton* bCalculate;
    QLineEdit* startPointA;
    QLineEdit* endPointB;
    QLabel* resLabel;
    QPushButton* bSetNewMatrixSize;

    QDialog* dioSetNewMatSize;
    QLineEdit* bSetV1;
    QPushButton *enterMatSize;
public:
    winodw(QWidget *parent = nullptr);
private slots:
    void slotCalculateClicked();
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();
};
#endif // WINODW_H
