#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

// ItemModel、ListModel、TableModel、ProxyModel
#include <QAbstractTableModel >

class CurrencyModel : public QAbstractTableModel
{
public:
    CurrencyModel(QObject *parent = nullptr);
    void setCurrencyMap(const QMap<QString, double> &map);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    QString currencyAt(int offset) const;
    QMap<QString, double> currencyMap;
};

#endif // CURRENCYMODEL_H
