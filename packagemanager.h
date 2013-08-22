/*
 * This file is part of mg-package-manager
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Kyösti Ranto <kyosti.ranto@digia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

//#include "qmlapplicationviewer.h"

#include "packmancontext.h"
#include "packagemodel.h"
#include "packagelist.h"
#include "packagegroup.h"

#include <QObject>
#include <QStringList>

#include <QQmlContext>
#include <QSortFilterProxyModel>

class FilterPackageModel;

class PackageManager : public QObject
{
    Q_OBJECT

public:
    static PackageManager *instance();

    explicit PackageManager(QQuickView *viewer, QObject *parent = 0);

public slots:
    void refreshCache();
    void refreshUpdate();
    void refreshInstalled();
    void refreshAvailable(uint group);
    void refreshAll(uint delay = 0);

    void refreshRepos();

    void uninstallMarkedPackages(bool simulate, bool autoremove);
    void updateMarkedPackages(bool simulate, bool onlyTrusted);
    void installMarkedPackages(bool simulate, bool onlyTrusted);

private slots:
    void onPackage(QSharedPointer<PackageKit::Package> packagePtr);
    void onInstalledPackage(QSharedPointer<PackageKit::Package> packagePtr);
    void onUpdateAvailablePackage(QSharedPointer<PackageKit::Package> packagePtr);
    void onAvailablePackage(QSharedPointer<PackageKit::Package> packagePtr);
    void onFinished(PackageKit::Enum::Exit,uint);

    void onChanged();
    void onCategory(const QString &parent_id, const QString &cat_id, const QString &name, const QString &summary, const QString &icon);
    void onErrorCode(PackageKit::Enum::Error error, const QString& details);
    void onEulaRequired(const PackageKit::Client::EulaInfo &info);
    void onMediaChangeRequired(PackageKit::Enum::MediaType type, const QString& id, const QString& text);
    void onFiles(const QSharedPointer<PackageKit::Package> &package, const QStringList &filenames);
    void onMessage(PackageKit::Enum::Message type, const QString &message);
    void onRepoDetail(const QString& repoId, const QString& description, bool enabled);
    void onRepoSignatureRequired(const PackageKit::Client::SignatureInfo &info);
    void onRequireRestart(PackageKit::Enum::Restart type, const QSharedPointer<PackageKit::Package> &package);

    void onRefreshCacheFinished(PackageKit::Enum::Exit,uint);
    void onRefreshReposFinished(PackageKit::Enum::Exit,uint);

private:
    bool testNetworkConnection(TransactionWrapper *tw);

 private:
    static PackageManager *m_packageManager;

    PackManContext m_packManContext;

    QmlApplicationViewer *m_viewer;
    PackageKit::Client *m_packageKit;

    PackageKit::Transaction *m_refreshCacheTransaction;
    PackageKit::Transaction *m_refreshReposTransaction;
    PackageKit::Transaction *m_getPackagesTransaction;
    PackageKit::Transaction *m_getUpdatesTransaction;
    PackageKit::Transaction *m_searchGroupsTransaction;

    QDeclarativeContext *m_qmlContext;

    PackageModel *m_installedPackagesModel;
    PackageModel *m_availablePackagesModel;
    PackageModel *m_updateAvailablePackagesModel;
    FilterPackageModel *m_installedPackagesFilterModel;
    FilterPackageModel *m_availablePackagesFilterModel;
    FilterPackageModel *m_updateAvailablePackagesFilterModel;

    PackageList m_packagesToBeInstalled;
    PackageList m_packagesToBeRemoved;
    PackageList m_packagesToBeUpdated;

    PackageGroupList m_packageGroups;

    RepositoryList m_repositories;
};

#endif // PACKAGEMANAGER_H
