/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "binarymorfology.h"
#include <KLocalizedString>

BinaryMorfology::BinaryMorfology(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_nativeText(i18n("Text coming from C++ plugin"))
{
}

BinaryMorfology::~BinaryMorfology()
{
}

QString BinaryMorfology::nativeText() const
{
    return m_nativeText;
}

K_EXPORT_PLASMA_APPLET_WITH_JSON(binarymorfology, BinaryMorfology, "metadata.json")

#include "binarymorfology.moc"
