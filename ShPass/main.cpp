//#include "winodw.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    winodw w;
//    w.show();
//    return a.exec();
//}
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>

class MovableEllipseItem : public QGraphicsEllipseItem {
public:
    MovableEllipseItem(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsEllipseItem(x, y, width, height) {
            setFlag(QGraphicsItem::ItemIsMovable, true); // Устанавливаем флаг на перемещение
        }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && scene()) {
            QPointF newPos = value.toPointF();
            qreal halfWidth = rect().width() / 2;
            qreal halfHeight = rect().height() / 2;

            // Ограничиваем перемещение вершин в пределах сцены
            newPos.setX(qMin(scene()->width() - halfWidth, qMax(halfWidth, newPos.x())));
            newPos.setY(qMin(scene()->height() - halfHeight, qMax(halfHeight, newPos.y())));

            // Обновляем координаты рёбер
            for (QGraphicsLineItem* edge : edges) {
                QPointF source = edge->line().p1();
                QPointF destination = edge->line().p2();
                if (source == pos()) {
                    source = newPos + QPointF(0, halfHeight);
                } else if (destination == pos()) {
                    destination = newPos - QPointF(0, halfHeight);
                }
                edge->setLine(QLineF(source, destination));
            }

            // Обновляем координаты рёбер, принадлежащих этой вершине
            updateEdges();

            return newPos;
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

    void updateEdges() {
        for (QGraphicsLineItem* edge : edges) {
            QPointF source = edge->line().p1();
            QPointF destination = edge->line().p2();
            if (source == pos()) {
                source = scenePos() + QPointF(0, rect().height() / 2);
            } else if (destination == pos()) {
                destination = scenePos() - QPointF(0, rect().height() / 2);
            }
            edge->setLine(QLineF(source, destination));
        }
    }
public:
    QVector<QGraphicsLineItem*> edges;
};

class GraphWidget : public QGraphicsView {
public:
    const qreal nodeRadius = 20;
    const qreal spacing = 100;

    QVector<MovableEllipseItem*> nodes;
    QVector<QGraphicsLineItem*> edges;
    QVector<QVector<double>> mat = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };
    GraphWidget(QWidget *parent = nullptr) : QGraphicsView(parent) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        // Создаем вершины и ребра графа
        createGraph(mat);
    }

protected:
    void createGraph(const QVector<QVector<double>>& mat) {

        for (int i = 0; i < mat.size(); ++i) {
            qreal x = spacing * (i + 1);
            qreal y = spacing * 2;
            MovableEllipseItem *node = new MovableEllipseItem(x - nodeRadius, y - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
            scene->addItem(node);
            nodes.append(node);

            QGraphicsTextItem *label = new QGraphicsTextItem(QString::number(i));
            label->setPos(x - nodeRadius / 2, y - nodeRadius / 2);
            scene->addItem(label);
            label->setParentItem(node);
        }

        for (int i = 0; i < mat.size(); ++i) {
            for (int j = i + 1; j < mat[i].size(); ++j) {
                if (mat[i][j] != 0) {
                    qreal sourceX = nodes[i]->rect().center().x();
                    qreal sourceY = nodes[i]->rect().center().y();
                    qreal destX = nodes[j]->rect().center().x();
                    qreal destY = nodes[j]->rect().center().y();

                    QPointF source = QPointF(sourceX, sourceY + nodeRadius);
                    QPointF destination = QPointF(destX, destY - nodeRadius);

                    QGraphicsLineItem *edge = scene->addLine(source.x(), source.y(), destination.x(), destination.y());
                    edge->setPen(QPen(Qt::black, 2));
                    edges.append(edge);

                    nodes[i]->edges.append(edge); // Добавляем ребро к списку рёбер вершины
                    nodes[j]->edges.append(edge); // Добавляем ребро к списку рёбер вершины
                }
            }
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        QGraphicsView::mousePressEvent(event);
    }

private:
    QGraphicsScene *scene;
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GraphWidget graphWidget;
    graphWidget.setWindowTitle("Graph Widget");
    graphWidget.resize(600, 600);
    graphWidget.show();
    return a.exec();
}



