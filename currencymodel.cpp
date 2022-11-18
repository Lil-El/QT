#include "currencymodel.h"

CurrencyModel::CurrencyModel(QObject *parent) : QAbstractTableModel (parent)
{

}

int CurrencyModel::rowCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());
        if (currencyMap.value(rowCurrency) == 0.0)
            return "####";
        double amount = currencyMap.value(columnCurrency) / currencyMap.value(rowCurrency);
        return QString("%1").arg(amount, 0, 'f', 4);
    }
    return QVariant();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    return currencyAt(section);
}

bool CurrencyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column() && role == Qt::EditRole) {
        currencyMap["SEK"] = value.toInt();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

// 允许item编辑
Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable; // ItemFlag
    }
    return flags;
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    currencyMap = map;
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}
