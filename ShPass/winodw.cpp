#include "winodw.h"

winodw::winodw(QWidget *parent) : QWidget(parent) {
    // model init
    QTableView* view = new QTableView;
    model1 = new MatrixModel1(0, 0);
    view->setModel(model1);

    QTableView* view2 = new QTableView;
    model2 = new MatrixModel2(1, 0);
    view2->setModel(model2);

    // widgets init
    bCalculate = new QPushButton("Find path");
    bSetNewMatrixSize = new QPushButton("Set matrix size...");
    resLabel = new QLabel("Dijkstra-s-algorithm");
    startPointA = new QLineEdit;


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

    QMenu* mFile = new QMenu("File...");
    mFile->addAction("Open... (ctrl+o)");
    mFile->addAction("Save (ctrl+s)");
    mFile->addAction("Save as... (shift+ctrl+o)");

    menu = new QMenuBar;
    menu->addMenu(mFile);
    menu->addAction("Help...");
    menu->addAction("About...");

    bSetNewMatrixSize->setMinimumWidth(400);
    bCalculate->setMinimumWidth(400);

    // layout setup
    QHBoxLayout* hbl = new QHBoxLayout;
    hbl->addWidget(new QLabel("Start point: "));
    hbl->addWidget(startPointA);
    hbl->addSpacing(15);
    hbl->addWidget(bSetNewMatrixSize);
    hbl->addWidget(bCalculate);
    QHBoxLayout* matHbl = new QHBoxLayout;
    matHbl->addWidget(view);
    matHbl->addWidget(view2);
    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(menu);
    vbl->addLayout(matHbl);
    vbl->addLayout(hbl);
    vbl->addWidget(resLabel);

    setLayout(vbl);
}


