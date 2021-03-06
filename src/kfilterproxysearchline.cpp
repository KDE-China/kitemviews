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

#include "kfilterproxysearchline.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QTimer>
#include <QSortFilterProxyModel>

/**
 * KFilterProxySearchLinePrivate class that helps to provide binary compatibility between releases.
 * @internal
 */
//@cond PRIVATE
class KFilterProxySearchLinePrivate
{
public:
    KFilterProxySearchLinePrivate(KFilterProxySearchLine *parent) :
        q(parent), proxy(nullptr), searchLine(nullptr)
    {
        timer = new QTimer(q);
        timer->setSingleShot(true);
        QObject::connect(timer, SIGNAL(timeout()), q, SLOT(slotSearchLineActivate()));
    }
    QTimer *timer;
    KFilterProxySearchLine *q;
    QSortFilterProxyModel *proxy;
    QLineEdit *searchLine;

    void slotSearchLineChange(const QString &newText);
    void slotSearchLineActivate();
};

void KFilterProxySearchLinePrivate::slotSearchLineChange(const QString &)
{
    timer->start(300);
}

void KFilterProxySearchLinePrivate::slotSearchLineActivate()
{
    if (!proxy) {
        return;
    }

    proxy->setFilterKeyColumn(-1);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterFixedString(searchLine->text());
}
//@endcond

KFilterProxySearchLine::KFilterProxySearchLine(QWidget *parent)
    : QWidget(parent), d(new KFilterProxySearchLinePrivate(this))
{
    d->searchLine = new QLineEdit(this);
    d->searchLine->setClearButtonEnabled(true);
    d->searchLine->setPlaceholderText(tr("Search"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(d->searchLine);

    connect(d->searchLine, SIGNAL(textChanged(QString)),
            SLOT(slotSearchLineChange(QString)));
}

KFilterProxySearchLine::~KFilterProxySearchLine()
{
    delete d;
}

void KFilterProxySearchLine::setText(const QString &text)
{
    d->searchLine->setText(text);
    d->slotSearchLineActivate();
}

void KFilterProxySearchLine::setProxy(QSortFilterProxyModel *proxy)
{
    d->proxy = proxy;
}

QLineEdit *KFilterProxySearchLine::lineEdit() const
{
    return d->searchLine;
}

#include "moc_kfilterproxysearchline.cpp"
