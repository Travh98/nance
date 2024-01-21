#include "UserExpensesModel.h"

UserExpensesModel::UserExpensesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_Expenses.append(new Expense("E1", 15.5f));
    m_Expenses.append(new Expense("E2", 16.7f));
}

QVariant UserExpensesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Orientation::Horizontal)
    {
        return QVariant();
    }

    switch(role)
    {
    case Qt::DisplayRole:
    {
        switch(section)
        {
        case ColEnum::ExpenseName:
        {
            return "Expense Name";
        }
        case ColEnum::Amount:
        {
            return "Amount";
        }
        }
    }
    }

    return QVariant();
}

bool UserExpensesModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int UserExpensesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Expenses.length();
}

int UserExpensesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return numCols;
}

QVariant UserExpensesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case ColEnum::ExpenseName:
        {
            return QString(m_Expenses.at(index.row())->name);
        }
        case ColEnum::Amount:
        {
            return QString::number(m_Expenses.at(index.row())->amount, 'f', 2);
        }
        }
    }
    case Qt::BackgroundRole:
    {
        if(flags(index) & Qt::ItemIsEditable)
        {
            return m_tableBackgroundColor.lighter();
        }
        else
        {
            return m_tableBackgroundColor;
        }
    }
    case Qt::TextAlignmentRole:
    {
        switch(index.column())
        {
        case ColEnum::ExpenseName:
        {
            return Qt::AlignmentFlag::AlignLeft;
        }
        case ColEnum::Amount:
        {
            return Qt::AlignmentFlag::AlignRight;
        }
        }
    }
    }

    return QVariant();
}

bool UserExpensesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags UserExpensesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool UserExpensesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool UserExpensesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}
