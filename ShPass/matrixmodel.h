#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QAbstractListModel>
#include <QMessageBox>

class MatrixModel1 : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MatrixModel1 (int rows, int cols, QObject* obj = nullptr);

    QVariant data (const QModelIndex& index, int role) const override;
    QVariant data (int i, int j) const;
    bool setData (const QModelIndex& index, const QVariant& data, int role) override;
    void setData (int i, int j, const QVariant& data);
    void clearData();

    int rowCount (const QModelIndex& index = QModelIndex()) const override;
    int columnCount ( const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags (const QModelIndex&) const override;

    QVector<QVector<double>> GetVectoredMat();
    void setMat(const QVector<QVector<double>>& mat);

    void setSize(int rowCount);

    void clear();
private:
    QHash<QModelIndex, QString> mat;
    QVector<QVector<double>> VectoredMat;
    int rows;
    int cols;
    bool isEditable;
};


class MatrixModel2 : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MatrixModel2 (int rows, int cols, QObject* obj = nullptr);

    QVariant data (const QModelIndex& index, int role) const override;
    int data (int i, int j) const;
    bool setData (const QModelIndex& index, const QVariant& data, int role) override;
    void setData (int i, int j, const double& data);
    void clearData();

    int rowCount (const QModelIndex& index = QModelIndex()) const override;
    int columnCount ( const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags (const QModelIndex&) const override;

//    void setRowCount (int);
    void setColumnCount (int);

    QVector<QString> GetVectoredMat();

    void clear();

    void setRes(int Vertice, int pathLenght, QString path);

private:
    QHash<QModelIndex, QString> mat;
    QVector<QString> v;
    int rows;
    int cols;
    bool isEditable;
};


#endif // MATRIXMODEL_H
