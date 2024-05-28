#ifndef WINODW_H
#define WINODW_H

#include <QtWidgets>
#include "matrixmodel.h"
#include "graphwidget.h"
#include <fstream>

class window : public QWidget {
    Q_OBJECT
private:
    MatrixModel1* model1;
    MatrixModel2* model2;
    GraphWidget* graph1;
    //GraphWidget* graph2;
    QPushButton* bCalculate;
    QLineEdit* startPointA;
    QLabel* resLabel;
    QPushButton* bSetNewMatrixSize;

    QDialog* dioSetNewMatSize;
    QLineEdit* bSetV1;
    QPushButton *enterMatSize;

    QMenuBar* menu;

    bool ifOpened = false;

//    std::ofstream fileO;
//    std::ifstream fileI;
    QString filePath = "";
public:
    window(QWidget *parent = nullptr);
protected:
    void saveAdjacencyMatrix(const QVector<QVector<double>>& matrix, const QString& filename);
    QVector<QVector<double> > loadAdjacencyMatrix(const QString &filename, bool &isOk);
    inline void setMatSize(const int &size);

    void keyPressEvent(QKeyEvent *event) override;
protected slots:
    //void slotShortcutTriggered(QAction *a);
    void slotCalculateClicked();
    void slotSetNewMatrixSizeFromDialog();
    void slotDioSetNewMatSizeShow();
    void slotMenuTriggered(QAction*);

};
#endif // WINODW_H
