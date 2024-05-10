#include "matrixmodel.h"

MatrixModel2::MatrixModel2(int rowsCount, int colsCount, QObject* obj)
    : QAbstractTableModel(obj), rows(rowsCount), cols(colsCount)  { }

QVariant MatrixModel2::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > rows || index.column() > cols) return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? mat.value(index, 0) : QVariant();
}

//double MatrixModel2::data(int i, int j) const {
//    return mat.value(index(i, j)).first;
//}

Qt::ItemFlags MatrixModel2::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool MatrixModel2::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || index.row() > rows || index.column() > cols) return false;
    mat[index] = value.toString();
    v[index.column()] = value.toString();
    emit dataChanged(index, index);
    return true;
}

int MatrixModel2::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return rows;
}

int MatrixModel2::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return cols;
}

QVariant MatrixModel2::headerData (int section, Qt::Orientation orientation, int role) const {
    if( role != Qt::DisplayRole ) return QVariant();
    if( orientation == Qt::Vertical || orientation == Qt::Horizontal) return section;
    return QVariant();
}

//void MatrixModel2::setRowCount(int rowCount) {
//    this->rows = rowCount;
//    emit layoutChanged();
//}
void MatrixModel2::setColumnCount(int colCount) {
    v = QVector<QString>(colCount);
    this->cols = colCount;
    emit layoutChanged();
}

QVector<QString> MatrixModel2::GetVectoredMat() {
    return v;
}

void MatrixModel2::setRes(int Vertice, int pathLenght, QString path) {
    QModelIndex ind = index(0, Vertice);
    beginInsertColumns(ind,0, 1);
    v[Vertice] = QString::number(pathLenght) + " (" + path + ")";
    mat.insert(ind, v[Vertice]);
    endInsertColumns();
    emit layoutChanged();
}



//void MatrixModel2::setData(int i, int j, const double& data) {
//    QModelIndex ind = index(i, j);
//    beginInsertColumns(ind,0, 1);
//    mat.insert(ind, data);
//    endInsertColumns();
//}

//void MatrixModel2::clearData() {
//    beginResetModel();
//    mat.clear();
//    endResetModel();
//}
