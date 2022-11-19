#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QtGui>
#include <QStyledItemDelegate>

/*
 * view 仅仅是用作对 model 数据的展示和对用户输入的处理，而不应该去做其他的工作
 * 为了获得对用户输入控制的灵活性，这种交互工作交给了 delegate
 * 对于一些简单的基于组件的 delegate，可以通过继承 QItemDelegate 或者 QStyledItemDelegate 来实现。这样就可以避免要完全重写 QAbstractItemDelegate 中所需要的所有函数。
 * 它们之间的主要区别在于，QStyledItemDelegate 使用当前的风格(style)去绘制组件。
*/
class TrackDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TrackDelegate(int durationColumn, QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();

private:
    int durationColumn;

};

#endif // TRACKDELEGATE_H
