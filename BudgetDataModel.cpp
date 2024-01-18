#include "BudgetDataModel.h"

BudgetDataModel::BudgetDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant BudgetDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::ItemDataRole::DisplayRole)
    {
        return QVariant();
    }

    switch(orientation)
    {
    case Qt::Orientation::Horizontal:
    {
        switch(section)
        {
        case Column::Category:
        {
            return "Category";
        }
        case Column::Amount:
        {
            return "Amount";
        }
        }
    }
    case Qt::Orientation::Vertical:
    {
        switch(section)
        {
        case Row::HourlyPay:
        {
            return "Hourly Pay";
        }
        case Row::HoursPerWeek:
        {
            return "Hours Per Week";
        }
        case Row::WeeksPerYear:
        {
            return "Weeks Per Year";
        }
        case Row::GrossSalary:
        {
            return "Gross Salary";
        }
        case Row::Contrib401k:
        {
            return "401K Contribution";
        }
        case Row::AnnualHealthInsurance:
        {
            return "Annual Health Insurance";
        }
        case Row::TaxableIncome:
        {
            return "Taxable Income";
        }
        case Row::AnnualTax:
        {
            return "Annual Tax";
        }
        case Row::AnnualTakeHome:
        {
            return "Annual Take Home";
        }
        case Row::MonthlyTakeHome:
        {
            return "Monthly Take Home";
        }
        }
    }
    }
    return QVariant();
}

bool BudgetDataModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int BudgetDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return Row::numRows;
}

int BudgetDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return Column::numColumns;
}

QVariant BudgetDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch(index.column())
    {
    case Column::Category:
        return QVariant();
    case Column::Amount:
    {
        BudgetDataModel::Row row = index.row();

        return m_BudgetData.value(index.row());
    }
    }

    return QVariant();
}

bool BudgetDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags BudgetDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
