#include "matrixmodel.h"

MatrixModel1::MatrixModel1(int rowsCount, int colsCount, QObject* obj)
    : QAbstractTableModel(obj), rows(rowsCount), cols(colsCount)  { }

QVariant MatrixModel1::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() > rows || index.column() > cols) return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? mat.value(index, 0) : QVariant();
}

QVariant MatrixModel1::data(int i, int j) const {
    return mat.value(index(i, j));
}

Qt::ItemFlags MatrixModel1::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool MatrixModel1::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || index.row() > rows || index.column() > cols) return false;

    QString toStr = value.toString();
    if(toStr == "") return false;
    bool isOk;
    double buf = toStr.toDouble(&isOk);
    if(!isOk || buf < 0) {
        QMessageBox::information(0, "Error", "You must write some positive integer (like 3) or positive floating point number using dot(like 3.14)");
        return false;
    }

    VectoredMat[index.row()][index.column()] = buf;

    mat[index] = toStr;
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

void MatrixModel1::setSize(int rowCount) {
    this->rows = rowCount;
    this->cols = rowCount;
    VectoredMat = QVector<QVector<double>>(rowCount, QVector<double>(rowCount, 0));
    emit layoutChanged();
}

void MatrixModel1::clear()
{
    mat.clear();
    VectoredMat.clear();
}

void MatrixModel1::setData(int i, int j, const QVariant& data) {
    QModelIndex ind = index(i, j);
    beginInsertColumns(ind,0, 1);
    mat.insert(ind, data.toString());
    endInsertColumns();
}

void MatrixModel1::clearData() {
    beginResetModel();
    mat.clear();
    endResetModel();
    setSize(0);
}

QVector<QVector<double>> MatrixModel1::GetVectoredMat() {
    return VectoredMat;
}

void MatrixModel1::setMat(const QVector<QVector<double> > &matrix) {
    for (int i = 0; i < VectoredMat.size(); ++i) {
        for (int j = 0; j < VectoredMat.size(); ++j){
            mat[index(i, j)] = QString::fromStdString(std::to_string(matrix[i][j]));
            VectoredMat[i][j] = matrix[i][j];
        }
    }
}
