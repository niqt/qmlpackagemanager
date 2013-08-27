#include "packageinfo.h"

PackageInfo::PackageInfo(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary, QObject *parent) :
    QObject(parent)
{
    m_info = info;
    m_packageID = packageID;
    m_summary = summary;
}
