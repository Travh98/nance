#ifndef BUDGETDATAMODEL_H
#define BUDGETDATAMODEL_H

#include <QAbstractTableModel>
#include <QColor>

class BudgetDataModel : public QAbstractTableModel
{
    Q_OBJECT

    enum ColEnum: int
    {
        Amount,
        numColumns
    };

    enum RowEnum: int
    {
        HourlyPay,
        HoursPerWeek,
        WeeksPerYear,
        GrossSalary,
        Contrib401kPercent,
        Contrib401k,
        AnnualHealthInsurance,
        TaxableIncome,
        AnnualTaxPercent,
        AnnualTax,
        AnnualTakeHome,
        MonthlyTakeHome,
        numRows
    };

public:
    explicit BudgetDataModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QMap<RowEnum, float> m_BudgetData;

    QColor m_tableBackgroundColor = QColor(25, 25, 25);

    void recalculateValues();
};

#endif // BUDGETDATAMODEL_H
