#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtWidgets>

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = nullptr);
    void setMat(QVector<QVector<double>> m);
    void pointFindedNodes(QVector<bool> v);
    void pointAllBlack();
    void clear();
protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QVector<QVector<double>> adjacencyMatrix;
    QGraphicsScene* scene;
    QVector<QGraphicsEllipseItem*> nodes;
    QVector<QGraphicsSimpleTextItem*> nodeLabels;
    QMap<QPair<int, int>, QGraphicsLineItem*> edges;
};

#endif // GRAPHWIDGET_H
