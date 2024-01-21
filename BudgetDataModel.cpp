#include "BudgetDataModel.h"

BudgetDataModel::BudgetDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // Set default values
    m_BudgetData.insert(BudgetDataModel::RowEnum::HourlyPay, 18.0f);
    m_BudgetData.insert(BudgetDataModel::RowEnum::HoursPerWeek, 40.0f);
    m_BudgetData.insert(BudgetDataModel::RowEnum::WeeksPerYear, 52.0f);
    m_BudgetData.insert(BudgetDataModel::RowEnum::Contrib401kPercent, 3.0f);
    m_BudgetData.insert(BudgetDataModel::RowEnum::AnnualHealthInsurance, 5000.0f);

    // Recalculate on startup
    recalculateValues();

}

QVariant BudgetDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {
        switch(orientation)
        {
        case Qt::Orientation::Horizontal:
        {
            switch(section)
            {
            case ColEnum::Amount:
            {
                return "Amount";
            }
            default:
                return QVariant();
            }
        }
        case Qt::Orientation::Vertical:
        {
            switch(section)
            {
            case RowEnum::HourlyPay:
            {
                return "Hourly Pay";
            }
            case RowEnum::HoursPerWeek:
            {
                return "Hours Per Week";
            }
            case RowEnum::WeeksPerYear:
            {
                return "Weeks Per Year";
            }
            case RowEnum::GrossSalary:
            {
                return "Gross Salary";
            }
            case RowEnum::Contrib401kPercent:
            {
                return "401K Contribution (%)";
            }
            case RowEnum::Contrib401k:
            {
                return "401K Contribution";
            }
            case RowEnum::AnnualHealthInsurance:
            {
                return "Annual Health Insurance";
            }
            case RowEnum::TaxableIncome:
            {
                return "Taxable Income";
            }
            case RowEnum::AnnualTaxPercent:
            {
                return "Annual Tax (%)";
            }
            case RowEnum::AnnualTax:
            {
                return "Annual Tax";
            }
            case RowEnum::AnnualTakeHome:
            {
                return "Annual Take Home";
            }
            case RowEnum::MonthlyTakeHome:
            {
                return "Monthly Take Home";
            }
            default:
                return QVariant();
            }
        }
        }
    }
    case Qt::BackgroundRole:
    {
        return m_tableBackgroundColor;
    }
    default:
        return QVariant();
    }
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

    return RowEnum::numRows;
}

int BudgetDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ColEnum::numColumns;
}

QVariant BudgetDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch(role)
    {
    case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case ColEnum::Amount:
        {
            switch(index.row())
            {
            // Fallthrough to handle displaying percentages
            case RowEnum::Contrib401kPercent:
            case RowEnum::AnnualTaxPercent:
            {
                BudgetDataModel::RowEnum row = static_cast<BudgetDataModel::RowEnum>(index.row());
                return QString::number(m_BudgetData.value(row), 'f', 2) + '%';
            }
            default:
            {
                BudgetDataModel::RowEnum row = static_cast<BudgetDataModel::RowEnum>(index.row());
                return QString::number(m_BudgetData.value(row), 'f', 2);
            }
            }
        }
        }
    }
    case Qt::BackgroundRole:
        if(flags(index) & Qt::ItemIsEditable)
        {
            return m_tableBackgroundColor.lighter();
        }
        else
        {
            return m_tableBackgroundColor;
        }
    case Qt::TextAlignmentRole:
        return Qt::AlignmentFlag::AlignRight;
    }


    return QVariant();
}

bool BudgetDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
    case Qt::EditRole:
    {
        switch(index.column())
        {
        case BudgetDataModel::ColEnum::Amount:
        {
            m_BudgetData.insert(static_cast<BudgetDataModel::RowEnum>(index.row()), value.toFloat());
        }
        }
    }
    }

    if (data(index, role) != value)
    {
        recalculateValues();

        emit dataChanged(index, index, {role});

        return true;
    }
    return false;
}

Qt::ItemFlags BudgetDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    switch(index.row())
    {
    // Fallthrough to the editables
    case RowEnum::HourlyPay:
    case RowEnum::HoursPerWeek:
    case RowEnum::WeeksPerYear:
    case RowEnum::Contrib401kPercent:
    case RowEnum::AnnualHealthInsurance:
    case RowEnum::AnnualTaxPercent:
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    // Fallthrough to the uneditables
    case RowEnum::AnnualTax:
    case RowEnum::GrossSalary:
    case RowEnum::Contrib401k:
    case RowEnum::TaxableIncome:
    case RowEnum::AnnualTakeHome:
    case RowEnum::MonthlyTakeHome:
        return QAbstractItemModel::flags(index);
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void BudgetDataModel::recalculateValues()
{
    float grossSalary = m_BudgetData.value(RowEnum::HourlyPay)
            * m_BudgetData.value(RowEnum::HoursPerWeek)
            * m_BudgetData.value(RowEnum::WeeksPerYear);
    m_BudgetData.insert(RowEnum::GrossSalary, grossSalary);

    float contrib401kPerYear = m_BudgetData.value(RowEnum::GrossSalary)
            * (m_BudgetData.value(RowEnum::Contrib401kPercent) / 100.0f);
    m_BudgetData.insert(RowEnum::Contrib401k, contrib401kPerYear);

    float taxableIncome = m_BudgetData.value(RowEnum::GrossSalary)
            - m_BudgetData.value(RowEnum::Contrib401k)
            - m_BudgetData.value(RowEnum::AnnualHealthInsurance);
    m_BudgetData.insert(RowEnum::TaxableIncome, taxableIncome);

    float annualTax = m_BudgetData.value(RowEnum::TaxableIncome)
            * (m_BudgetData.value(RowEnum::AnnualTaxPercent) / 100.0f);
    m_BudgetData.insert(RowEnum::AnnualTax, annualTax);

    float annualTakeHome = m_BudgetData.value(RowEnum::TaxableIncome)
            - m_BudgetData.value(RowEnum::AnnualTax);
    m_BudgetData.insert(RowEnum::AnnualTakeHome, annualTakeHome);

    float monthlyTakeHome = m_BudgetData.value(RowEnum::AnnualTakeHome) / 12.0f;
    m_BudgetData.insert(RowEnum::MonthlyTakeHome, monthlyTakeHome);

}
