#ifndef BUDGETDATAMODEL_H
#define BUDGETDATAMODEL_H

#include <QAbstractTableModel>

class BudgetDataModel : public QAbstractTableModel
{
    Q_OBJECT

    enum Column: int
    {
        Category,
        Amount,
        numColumns
    };

    enum Row: int
    {
        HourlyPay,
        HoursPerWeek,
        WeeksPerYear,
        GrossSalary,
        Contrib401k,
        AnnualHealthInsurance,
        TaxableIncome,
        AnnualTax,
        AnnualTakeHome,
        MonthlyTakeHome,
        numRows
    };

public:
    explicit BudgetDataModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QMap<Row, float> m_BudgetData;
};

#endif // BUDGETDATAMODEL_H
