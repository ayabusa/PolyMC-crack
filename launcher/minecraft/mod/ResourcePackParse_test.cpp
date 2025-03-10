// SPDX-License-Identifier: GPL-3.0-only
/*
 *  PolyMC - Minecraft Launcher
 *  Copyright (c) 2022 flowln <flowlnlnln@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <QTest>
#include <QTimer>

#include "FileSystem.h"

#include "ResourcePack.h"
#include "tasks/LocalResourcePackParseTask.h"

class ResourcePackParseTest : public QObject {
    Q_OBJECT

    private slots:
    void test_parseZIP()
    {
        QString source = QFINDTESTDATA("testdata");

        QString zip_rp = FS::PathCombine(source, "test_resource_pack_idk.zip");
        ResourcePack pack { QFileInfo(zip_rp) };

        ResourcePackUtils::processZIP(pack);

        QVERIFY(pack.packFormat() == 3);
        QVERIFY(pack.description() == "um dois, feijão com arroz, três quatro, feijão no prato, cinco seis, café inglês, sete oito, comer biscoito, nove dez comer pastéis!!");
    }

    void test_parseFolder()
    {
        QString source = QFINDTESTDATA("testdata");

        QString folder_rp = FS::PathCombine(source, "test_folder");
        ResourcePack pack { QFileInfo(folder_rp) };

        ResourcePackUtils::processFolder(pack);

        QVERIFY(pack.packFormat() == 1);
        QVERIFY(pack.description() == "Some resource pack maybe");
    }

    void test_parseFolder2()
    {
        QString source = QFINDTESTDATA("testdata");

        QString folder_rp = FS::PathCombine(source, "another_test_folder");
        ResourcePack pack { QFileInfo(folder_rp) };

        ResourcePackUtils::process(pack);

        QVERIFY(pack.packFormat() == 6);
        QVERIFY(pack.description() == "o quartel pegou fogo, policia deu sinal, acode acode acode a bandeira nacional");
    }
};

QTEST_GUILESS_MAIN(ResourcePackParseTest)

#include "ResourcePackParse_test.moc"
