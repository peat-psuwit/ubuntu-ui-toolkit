/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Zsombor Egri <zsombor.egri@canonical.com>
 */

#include <QtTest/QtTest>

#define private public
#include "unitythemeiconprovider.h"
#undef private

class tst_IconProvider : public QObject
{
    Q_OBJECT
public:
    tst_IconProvider() {}

private Q_SLOTS:

    void test_loadIcon_data()
    {
        QTest::addColumn<QString>("icon");
        QTest::addColumn<QSize>("requestSize");
        QTest::addColumn<QSize>("resultSize");

        QTest::newRow("battery0") << "battery-100-charging" << QSize(-1, -1) << QSize(395, 256);
        QTest::newRow("battery1") << "battery-100-charging" << QSize(-1, 16) << QSize(24, 16);
        QTest::newRow("battery2") << "battery-100-charging" << QSize(16, -1) << QSize(16, 10);
        QTest::newRow("battery3") << "battery-100-charging" << QSize(0, 16) << QSize(24, 16);
        QTest::newRow("battery4") << "battery-100-charging" << QSize(16, 0) << QSize(16, 10);
        QTest::newRow("battery5") << "battery-100-charging" << QSize(24, 16) << QSize(24, 16);
        QTest::newRow("battery6") << "battery-100-charging" << QSize(24, 24) << QSize(37, 24);
        QTest::newRow("battery7") << "battery-100-charging" << QSize(37, 24) << QSize(37, 24);

        QTest::newRow("gallery0") << "gallery-app" << QSize(-1, -1) << QSize(512, 512);
        QTest::newRow("gallery1") << "gallery-app" << QSize(-1, 16) << QSize(16, 16);
        QTest::newRow("gallery2") << "gallery-app" << QSize(16, -1) << QSize(16, 16);
        QTest::newRow("gallery3") << "gallery-app" << QSize(0, 16) << QSize(16, 16);
        QTest::newRow("gallery4") << "gallery-app" << QSize(16, 0) << QSize(16, 16);
        QTest::newRow("gallery5") << "gallery-app" << QSize(24, 16) << QSize(24, 24);
        QTest::newRow("gallery6") << "gallery-app" << QSize(24, 24) << QSize(24, 24);
    }

    void test_loadIcon()
    {
        QFETCH(QString, icon);
        QFETCH(QSize, requestSize);
        QFETCH(QSize, resultSize);

        UnityThemeIconProvider provider;
        QSize returnedSize;
        const QPixmap p = provider.requestPixmap(icon, &returnedSize, requestSize);
        QCOMPARE(p.size(), resultSize);
        QCOMPARE(returnedSize, resultSize);
    }

    void test_iconType_data()
    {
        QTest::addColumn<QString>("icon");
        QTest::addColumn<QString>("type");

        QTest::newRow("battery") << "battery-100-charging" << ".svg";
        QTest::newRow("gallery") << "gallery-app" << ".png";
    }

    // This is here because we want to be sure that in test_loadIcon we
    // are testing a svg file and a png file
    void test_iconType()
    {
        QFETCH(QString, icon);
        QFETCH(QString, type);

        UnityThemeIconProvider provider;
        int dummy;
        const QString file = provider.theme->lookupLargestIcon(icon, &dummy);
        QVERIFY(file.endsWith(type));
    }

};

QTEST_MAIN(tst_IconProvider)

#include "tst_iconprovider.moc"
