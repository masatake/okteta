/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2009, 2010, 2011  Alex Richardson <alex.richardson@gmx.de>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) version 3, or any
 *   later version accepted by the membership of KDE e.V. (or its
 *   successor approved by the membership of KDE e.V.), which shall
 *   act as a proxy defined in Section 6 of version 3 of the license.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
#include "chardatainformation.h"

// KF5
#include <KLineEdit>
#include <KLocalizedString>
// Qt
#include <QLocale>
#include <QScriptValue>


#include "structviewpreferences.h"

namespace {
    QString charString(quint8 value)
    {
        switch (value)
        {
            case '\0': return QStringLiteral("'\\0'");
            case '\a': return QStringLiteral("'\\a'");
            case '\b': return QStringLiteral("'\\b'");
            case '\f': return QStringLiteral("'\\f'");
            case '\n': return QStringLiteral("'\\n'");
            case '\r': return QStringLiteral("'\\r'");
            case '\t': return QStringLiteral("'\\t'");
            case '\v': return QStringLiteral("'\\v'");
            default: break;
        }
        QChar qchar = QChar(quint32(value));
        if (!qchar.isPrint())
            qchar = QChar::ReplacementCharacter;
        return QString(QLatin1Char('\'') + qchar + QLatin1Char('\''));
    }
}

QString CharDataInformationMethods::staticValueString(quint8 value)
{
    QString charStr = charString(value);
    if (Kasten::StructViewPreferences::showCharNumericalValue())
    {
        int base = Kasten::StructViewPreferences::charDisplayBase();
        const QString num = (base == 10 && Kasten::StructViewPreferences::localeAwareDecimalFormatting())
            ? QLocale().toString(value)
            : QString::number(value, base);
        charStr += QStringLiteral(" (") + PrimitiveDataInformation::basePrefix(base)
                + num + QLatin1Char(')');
    }
    return charStr;
}

QWidget* CharDataInformationMethods::staticCreateEditWidget(QWidget* parent)
{
    return new KLineEdit(parent);
}

QVariant CharDataInformationMethods::staticDataFromWidget(const QWidget* w)
{
    //TODO fix this code!!
    const KLineEdit* edit = qobject_cast<const KLineEdit*> (w);
    if (edit)
    {
        QString text = edit->text();
        if (text.length() == 0)
        {
            return QVariant();
        }
        if (text.length() == 1)
        {
            //TODO char codec
            return (unsigned char) text.at(0).toLatin1();
        }
        if (text.at(0) == QLatin1Char('\\'))
        {
            //escape sequence
            if (text.at(1) == QLatin1Char('x'))
            {
                //hex escape:
                bool okay;
                QString valStr = text.mid(2, 2); //only 2 chars
                quint8 val = valStr.toInt(&okay, 16);
                if (okay)
                    return val;
                else
                    return QVariant();
            }
            else if (text.at(1) == QLatin1Char('n'))
            {
                return (quint8) '\n'; //newline
            }
            else if (text.at(1) == QLatin1Char('t'))
            {
                return (quint8) '\t'; //tab
            }
            else if (text.at(1) == QLatin1Char('r'))
            {
                return (quint8) '\r'; //cr
            }
            else
            {
                //octal escape:
                bool okay;
                QString valStr = text.mid(1, 3); //only 2 chars
                quint8 val = valStr.toInt(&okay, 8);
                if (okay)
                    return val;
                else
                    return QVariant();
            }
        }
    }
    return QVariant();
}

void CharDataInformationMethods::staticSetWidgetData(quint8 value, QWidget* w)
{
    KLineEdit* edit = qobject_cast<KLineEdit*> (w);
    if (edit)
    {
        QChar qchar(value, 0);
        if (! qchar.isPrint())
            qchar = QChar(QChar::ReplacementCharacter);
        edit->setText( qchar );
    }
}

QScriptValue CharDataInformationMethods::asScriptValue(quint8 value, QScriptEngine* engine, ScriptHandlerInfo* handler)
{
    Q_UNUSED(engine);
    Q_UNUSED(handler);
    return QScriptValue(QString(value > 127 ? QChar::ReplacementCharacter : QChar(value, 0)));
}
