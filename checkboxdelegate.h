#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

class QModelIndex;
class QWidget;
class QVariant;

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                 const QModelIndex &index);
private:

};

#endif // CHECKBOXDELEGATE_H
