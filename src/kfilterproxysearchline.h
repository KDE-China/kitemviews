/*
 * Copyright (C) 2007-2008 Omat Holding B.V. <info@omat.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KFILTERPROXYSEARCHLINE_H
#define KFILTERPROXYSEARCHLINE_H

#include <kitemviews_export.h>

#ifndef KITEMVIEWS_NO_DEPRECATED

#include <QWidget>
class KFilterProxySearchLinePrivate;

class QLineEdit;
class QSortFilterProxyModel;

/**
 * @class KFilterProxySearchLine kfilterproxysearchline.h KFilterProxySearchLine
 *
 * Responsible for the quick search when you are using a QSortFilterProxyModel.
 * This will give you an widget which you can embed in your application, call
 * the setProxy() function to indicate on which QSortFilterProxyModel this
 * search line should operate.
 *
 * @author Tom Albers <tomalbers@kde.nl>
 * @since 4.2
 * @deprecated since 5.50, use QLineEdit directly. If filtering is expensive,
 * consider a short timer to not act on every keypress, and if results are large,
 * consider not reacting until 3 letters.
 */

class KITEMVIEWS_EXPORT KITEMVIEWS_DEPRECATED KFilterProxySearchLine
    : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructor
     */
    explicit KFilterProxySearchLine(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~KFilterProxySearchLine();

    /**
     * Associate a proxy
     * @param proxy The proxy to operate with.
     */
    void setProxy(QSortFilterProxyModel *proxy);

    /**
     * To set the search to a text.
     */
    void setText(const QString &text);

    /**
     * Returns the pointer of the lineedit..
     */
    QLineEdit *lineEdit() const;

private:
    KFilterProxySearchLinePrivate *const d;
    Q_DISABLE_COPY(KFilterProxySearchLine)
    Q_PRIVATE_SLOT(d, void slotSearchLineChange(const QString &newText))
    Q_PRIVATE_SLOT(d, void slotSearchLineActivate())
};

#endif

#endif
