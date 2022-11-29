#include "matrixmodel.h"

MatrixModel1::MatrixModel1(int rowsCount, int colsCount, QObject* obj)
    : QAbstractTableModel(obj), rows(rowsCount), cols(colsCount)  { }

QVariant MatrixModel1::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > rows || index.column() > cols) return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? mat.value(index, 0) : QVariant();
}

int MatrixModel1::data(int i, int j) const {
    return mat.value(index(i, j));
}

Qt::ItemFlags MatrixModel1::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool MatrixModel1::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || index.row() > rows || index.column() > cols) return false;
    int buf = value.toDouble();
    if(buf < 0) buf *= -1;
    mat[index] = buf;
    emit dataChanged(index, index);
    return true;
}

int MatrixModel1::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return rows;
}

int MatrixModel1::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED(parent)
    return cols;
}

QVariant MatrixModel1::headerData (int section, Qt::Orientation orientation, int role) const {
    if( role != Qt::DisplayRole ) return QVariant();
    if( orientation == Qt::Vertical || orientation == Qt::Horizontal) return section;
    return QVariant();
}

void MatrixModel1::setRowCount(int rowCount) {
    this->rows = rowCount;
    emit layoutChanged();
}
void MatrixModel1::setColumnCount(int colCount) {
    this->cols = colCount;
    emit layoutChanged();
}

void MatrixModel1::setData(int i, int j, const double& data) {
    QModelIndex ind = index(i, j);
    beginInsertColumns(ind,0, 1);
    mat.insert(ind, data);
    endInsertColumns();
}

void MatrixModel1::clearData() {
    beginResetModel();
    mat.clear();
    endResetModel();
}

QVector<QVector<double>> MatrixModel1::GetVectoredMat() {
    QVector<QVector<double>> vecMat;
    for (int i = 0 ; i < rows ; ++i) {
        QVector<double> buf;
        for(int j = 0 ; j < cols ; ++j) { buf.push_back(mat.value(index(i, j))); }
        vecMat.push_back(buf);
    }
    return vecMat;
}
