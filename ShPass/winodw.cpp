#include "winodw.h"
#include <iostream>

window::window(QWidget *parent) : QWidget(parent) {

    // model init
    QTableView* view = new QTableView;
    model1 = new MatrixModel1(0, 0);
    view->setModel(model1);
    view->setToolTip("It is an adjacency matrix");

    QTableView* view2 = new QTableView;
    model2 = new MatrixModel2(1, 0);
    view2->setModel(model2);
    view2->setToolTip("It is a result row matrix");

    // widgets init
    bCalculate = new QPushButton("Find path");
    bCalculate->setToolTip("Press this button to calculate set adjacency matrix");
    bSetNewMatrixSize = new QPushButton("Set adjacency matrix size...");
    bSetNewMatrixSize->setToolTip("Press this button to set adjacency matrix size");
    resLabel = new QLabel("Dijkstra-s-algorithm");
    resLabel->setToolTip("This label is for showing program status");
    startPointA = new QLineEdit;
    startPointA->setToolTip("Enter there a start vertex from wich algorithm will calculate a path to other vertices");


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
            &window::slotDioSetNewMatSizeShow);
    connect(enterMatSize, &QPushButton::clicked, this,
            &window::slotSetNewMatrixSizeFromDialog);
    connect(bCalculate, &QPushButton::clicked, this,
            &window::slotCalculateClicked);

    QMenu* mFile = new QMenu("File");
    mFile->addAction("Open...", Qt::Key_F6);
    mFile->addAction("Save", Qt::Key_F2);
    mFile->addAction("Save as...", Qt::Key_F5);
    mFile->addSeparator();
    mFile->addAction("Clear");


    menu = new QMenuBar;
    menu->addMenu(mFile);
    menu->addAction("Help...",Qt::Key_F8);
    menu->addAction("About...");

    connect(menu, &QMenuBar::triggered, this, &window::slotMenuTriggered);

    bSetNewMatrixSize->setMinimumWidth(350);
    bCalculate->setMinimumWidth(350);

    graph1 = new GraphWidget();
    graph1->setToolTip("It is a graph of your adjacency matrix");

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
    QHBoxLayout* graphHbl = new QHBoxLayout;
    graphHbl->addWidget(graph1);
    //graphHbl->addWidget(graph2);
    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(menu);
    vbl->addLayout(matHbl);
    vbl->addLayout(graphHbl);
    vbl->addLayout(hbl);
    vbl->addWidget(resLabel);

    setLayout(vbl);

    setFocusPolicy(Qt::StrongFocus);
}

void window::saveAdjacencyMatrix(const QVector<QVector<double> > &matrix, const QString &filename){
    std::ofstream fileO;
    fileO.open(filename.toStdString());
    filePath = "";
    if (fileO.is_open()) {
        for (const auto& row : matrix) {
            for (int i = 0; i < row.size(); ++i) {
                fileO << row[i];
                if (i < row.size() - 1) {
                    fileO << " ";
                }
            }
            fileO << "\n";
        }
        filePath = filename;
        fileO.close();

        resLabel->setText("File saved.");
    } else {
        resLabel->setText("Unable to open file for writing.");
    }
}

QVector<QVector<double>> window::loadAdjacencyMatrix(const QString& filename, bool& isOk) {
    QVector<QVector<double>> matrix;
    std::ifstream fileI;
    fileI.open(filename.toStdString());
    std::string line;

    int lineCount = 0;
    if (fileI.is_open()) {
        try {
            while (std::getline(fileI, line)) {
                ++lineCount;
                std::istringstream stream(line);
                QVector<double> row;
                std::string value;
                while (stream >> value) {
                    row.push_back(std::stod(value));
                }
                if(row.length() != 0) matrix.push_back(row);
            }
            ifOpened = true;
//            if(fileO.is_open()) fileO.close();
//            fileO.open(filename.toStdString());
            filePath = filename;
            resLabel->setText("File loaded.");
        } catch (...) {
            QApplication::beep();
            QMessageBox::information(0, "Error file reading", QString::fromStdString("File has reading error on " + std::to_string(lineCount) + " line"));
            resLabel->setText("Try fix your previous file or open another file");
            isOk = false;
            matrix.clear();
        }

        fileI.close();

    } else {
        resLabel->setText("Unable to open file for reading.");
    }

    isOk = true;
    return matrix;
}

