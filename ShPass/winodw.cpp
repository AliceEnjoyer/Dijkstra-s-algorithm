#include "winodw.h"

winodw::winodw(QWidget *parent) : QWidget(parent) {
    // model init
    QTableView* view = new QTableView;
    model1 = new MatrixModel1(0, 0);
    view->setModel(model1);

    // widgets init
    bCalculate = new QPushButton("Find path");
    bSetNewMatrixSize = new QPushButton("Set matrix size...");
    resLabel = new QLabel("Dijkstra-s-algorithm");
    startPointA = new QLineEdit;
    endPointB = new QLineEdit;


    ///////////////////////////////////// dialog init
    dioSetNewMatSize = new QDialog(this);
    enterMatSize = new QPushButton("Enter matrix size");
    bSetV1 = new QLineEdit;
    bSetV1->setValidator(new QIntValidator());
    QHBoxLayout *hbl1d = new QHBoxLayout;
    hbl1d->addWidget(new QLabel("Verticies number: "));
    hbl1d->addWidget(bSetV1);
    QVBoxLayout *vbld = new QVBoxLayout;
    vbld->addLayout(hbl1d);
    vbld->addWidget(enterMatSize);
    dioSetNewMatSize->setLayout(vbld);
    //////////////////////////////////

    // connection
    connect(bSetNewMatrixSize, &QPushButton::clicked, this,
            &winodw::slotDioSetNewMatSizeShow);
    connect(enterMatSize, &QPushButton::clicked, this,
            &winodw::slotSetNewMatrixSizeFromDialog);
    connect(bCalculate, &QPushButton::clicked, this,
            &winodw::slotCalculateClicked);

    // layout setup
    QHBoxLayout* hbl = new QHBoxLayout;
    hbl->addWidget(new QLabel("Start point: "));
    hbl->addWidget(startPointA);
    hbl->addSpacing(15);
    hbl->addWidget(new QLabel("End point: "));
    hbl->addWidget(endPointB);
    hbl->addSpacing(40);
    hbl->addWidget(bSetNewMatrixSize);
    hbl->addWidget(bCalculate);
    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(view);
    vbl->addLayout(hbl);
    vbl->addWidget(resLabel);

    setLayout(vbl);
}


