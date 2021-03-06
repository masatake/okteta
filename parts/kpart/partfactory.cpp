/*
    This file is part of the Okteta KPart module, made within the KDE community.

    Copyright 2003,2007,2009 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "partfactory.h"

// part
#include "part.h"
// Okteta Kasten
#include <kasten/okteta/bytearrayviewprofilemanager.h>
#include <kasten/okteta/bytearraystreamencoderconfigeditorfactoryfactory.h>
#include <kasten/okteta/bytearraydatageneratorconfigeditorfactoryfactory.h>
#include <kasten/okteta/bytearraystreamencoderfactory.h>
#include <kasten/okteta/bytearraydatageneratorfactory.h>
// KF5
#include <KLocalizedString>


OktetaPartFactory::OktetaPartFactory()
  : mAboutData( QStringLiteral("oktetapart"), i18n("OktetaPart"), QStringLiteral("0.13.60"),
                i18n("Embedded hex editor"), KAboutLicense::GPL_V2, i18n("2003-2014 Friedrich W. H. Kossebau") )
{
// TODO: also load encoder and other plugins here
    mAboutData.addAuthor( i18n("Friedrich W. H. Kossebau"), i18n("Author"), QStringLiteral("kossebau@kde.org") );

    mByteArrayViewProfileManager = new Kasten::ByteArrayViewProfileManager();

//     const QList<AbstractModelStreamEncoder*> encoderList =
//         ByteArrayStreamEncoderFactory::createStreamEncoders();

//     const QList<AbstractModelDataGenerator*> generatorList =
//         ByteArrayDataGeneratorFactory::createDataGenerators();

//     const QList<AbstractModelStreamEncoderConfigEditorFactory*> encoderConfigEditorFactoryList =
//         ByteArrayStreamEncoderConfigEditorFactoryFactory::createFactorys();

//     const QList<AbstractModelDataGeneratorConfigEditorFactory*> generatorConfigEditorFactoryList =
//         ByteArrayDataGeneratorConfigEditorFactoryFactory::createFactorys();

//     mDocumentManager->codecManager()->setEncoders( encoderList );
//     mDocumentManager->codecManager()->setGenerators( generatorList );
//     mDocumentManager->syncManager()->setDocumentSynchronizerFactory( new ByteArrayRawFileSynchronizerFactory() );

//     mViewManager->codecViewManager()->setEncoderConfigEditorFactories( encoderConfigEditorFactoryList );
//     mViewManager->codecViewManager()->setGeneratorConfigEditorFactories( generatorConfigEditorFactoryList );
}


QObject* OktetaPartFactory::create( const char* iface,
                                    QWidget* parentWidget,
                                    QObject* parent,
                                    const QVariantList& args,
                                    const QString& keyword )
{
Q_UNUSED( parentWidget )
Q_UNUSED( args )
Q_UNUSED( keyword );

    const QByteArray className( iface );
    const OktetaPart::Modus modus =
        ( className == "KParts::ReadOnlyPart" ) ? OktetaPart::ReadOnlyModus :
        ( className == "Browser/View" ) ?         OktetaPart::BrowserViewModus :
        /* else */                                OktetaPart::ReadWriteModus;

    OktetaPart* part = new OktetaPart( parent, mAboutData, modus, mByteArrayViewProfileManager );

    return part;
}


OktetaPartFactory::~OktetaPartFactory()
{
    delete mByteArrayViewProfileManager;
}
