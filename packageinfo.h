#ifndef PACKAGEINFO_H
#define PACKAGEINFO_H

#include <QObject>
#include "transaction.h"

class PackageInfo : public QObject
{
    Q_OBJECT
public:
    explicit PackageInfo(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary, QObject *parent = 0);
    PackageInfo() {;}
signals:
    
public slots:

private:
    PackageKit::Transaction::Info m_info;
    QString m_packageID;
    QString m_summary;
};

#endif // PACKAGEINFO_H
