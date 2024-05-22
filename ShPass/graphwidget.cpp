#include "graphwidget.h"
#include <iostream>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);


}

void GraphWidget::setMat(QVector<QVector<double>> m) {
    adjacencyMatrix = m;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < adjacencyMatrix.size(); ++j) {
            if(adjacencyMatrix[i][j] != 0) adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
            else if(adjacencyMatrix[j][i] != 0) adjacencyMatrix[i][j] = adjacencyMatrix[j][i];
        }
    }

    scene->clear();
    int nodeCount = adjacencyMatrix.size();
    nodes.resize(nodeCount);
    nodeLabels.resize(nodeCount);

    for (int i = 0; i < nodeCount; ++i) {
        nodes[i] = scene->addEllipse(-10, -10, 20, 20);
        nodes[i]->setPos(i*34, std::cos(i*M_PI)*100+std::sin(i*M_PI/4)*40);
        nodes[i]->setFlag(QGraphicsItem::ItemIsMovable, true);

        nodeLabels[i] = new QGraphicsSimpleTextItem(QString::number(i));
        nodeLabels[i]->setPos(nodes[i]->pos() - QPointF(5, 5));
        scene->addItem(nodeLabels[i]);
    }

    for (int i = 0; i < nodeCount; ++i) {
        for (int j = i + 1; j < nodeCount; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                QGraphicsLineItem *edge = scene->addLine(nodes[i]->pos().x(), nodes[i]->pos().y(), nodes[j]->pos().x(), nodes[j]->pos().y(), QPen(Qt::black, 1));
                edges[QPair<int, int>(i, j)] = edge;
            }
        }
    }
}

void GraphWidget::pointAllBlack()  {
    for (int i = 0; i < nodes.size(); ++i) {
        nodes[i]->setPen(QPen(Qt::black));
    }
}

void GraphWidget::pointFindedNodes(QVector<bool> v) {
    for (int i = 0; i < v.size(); ++i) {
        if(v[i]) nodes[i]->setPen(QPen(Qt::green));
        else nodes[i]->setPen(QPen(Qt::red));
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);

    for (int i = 0; i < nodes.size(); ++i) {
        nodeLabels[i]->setPos(nodes[i]->pos() - QPointF(5, 5));
        for (int j = i + 1; j < nodes.size(); ++j) {

            QGraphicsLineItem *edge = edges.value(QPair<int, int>(i, j), nullptr);
            if (edge) {
                QPointF p1 = nodes[i]->scenePos();
                QPointF p2 = nodes[j]->scenePos();
                edge->setLine(QLineF(p1, p2));
            }
        }
    }
}
