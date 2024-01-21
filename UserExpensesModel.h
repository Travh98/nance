#ifndef USEREXPENSESMODEL_H
#define USEREXPENSESMODEL_H

#include <QAbstractTableModel>
#include <QColor>

struct Expense
{
    QString name;
    float amount;

    Expense(const QString& n, const float& a): name(n), amount(a)
    {

    }
};

class UserExpensesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum ColEnum: int
    {
        ExpenseName,
        Amount,
        numCols
    };

    explicit UserExpensesModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<Expense*> m_Expenses;

    QColor m_tableBackgroundColor = QColor(25, 25, 25);
};

#endif // USEREXPENSESMODEL_H
