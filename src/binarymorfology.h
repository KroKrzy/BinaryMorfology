/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef BINARYMORFOLOGY_H
#define BINARYMORFOLOGY_H


#include <Plasma/Applet>

class BinaryMorfology : public Plasma::Applet
{
    Q_OBJECT
    Q_PROPERTY(QString nativeText READ nativeText CONSTANT)

public:
    BinaryMorfology( QObject *parent, const QVariantList &args );
    ~BinaryMorfology();

    QString nativeText() const;

private:
    QString m_nativeText;
};

#endif
