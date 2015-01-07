/*
 * Copyright 2014 Canonical Ltd.
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
 */

#ifndef UCLISTITEM_H
#define UCLISTITEM_H

#include <QtQuick/QQuickItem>
#include "ucstyleditembase.h"

class UCListItemContent;
class UCListItemDivider;
class UCListItemActions;
class UCAction;
class UCListItemAttached;
class UCListItemPrivate;
class UCListItemAttached;
class UCListItem : public UCStyledItemBase
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *contentItem READ contentItem CONSTANT)
    Q_PROPERTY(UCListItemDivider *divider READ divider CONSTANT)
    Q_PROPERTY(UCListItemActions *leadingActions READ leadingActions WRITE setLeadingActions NOTIFY leadingActionsChanged DESIGNABLE false)
    Q_PROPERTY(UCListItemActions *trailingActions READ trailingActions WRITE setTrailingActions NOTIFY trailingActionsChanged DESIGNABLE false)
    Q_PROPERTY(bool highlighted READ highlighted NOTIFY highlightedChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), qreal swipeOvershoot READ swipeOvershoot WRITE setSwipeOvershoot NOTIFY swipeOvershootChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), bool contentMoving READ contentMoving NOTIFY contentMovingChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), bool selectable READ isSelectable NOTIFY selectableChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), UCAction *action READ action WRITE setAction NOTIFY actionChanged DESIGNABLE false)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), QQmlListProperty<QObject> listItemData READ data DESIGNABLE false)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), QQmlListProperty<QQuickItem> listItemChildren READ children NOTIFY listItemChildrenChanged DESIGNABLE false)
    // FIXME move these to StyledItemBase with subtheming
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), QQmlComponent *style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PRIVATE_PROPERTY(UCListItem::d_func(), QQuickItem *__styleInstance READ styleInstance NOTIFY __styleInstanceChanged)
    Q_CLASSINFO("DefaultProperty", "listItemData")
    Q_ENUMS(PanelStatus)
public:
    enum PanelStatus {
        Disconnected,
        Leading,
        Trailing
    };
    explicit UCListItem(QQuickItem *parent = 0);
    ~UCListItem();

    static UCListItemAttached *qmlAttachedProperties(QObject *owner);

    QQuickItem *contentItem() const;
    UCListItemDivider *divider() const;
    UCListItemActions *leadingActions() const;
    void setLeadingActions(UCListItemActions *options);
    UCListItemActions *trailingActions() const;
    void setTrailingActions(UCListItemActions *options);
    bool highlighted() const;
    QColor color() const;
    void setColor(const QColor &color);
    QColor highlightColor() const;
    void setHighlightColor(const QColor &color);

protected:
    void componentComplete();
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    void itemChange(ItemChange change, const ItemChangeData &data);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool childMouseEventFilter(QQuickItem *child, QEvent *event);
    bool eventFilter(QObject *, QEvent *);
    void timerEvent(QTimerEvent *event);

Q_SIGNALS:
    void leadingActionsChanged();
    void trailingActionsChanged();
    void highlightedChanged();
    void swipeOvershootChanged();
    void contentMovingChanged();
    void colorChanged();
    void highlightColorChanged();
    void selectedChanged();
    void selectableChanged();
    void actionChanged();
    void listItemChildrenChanged();

    void clicked();
    void pressAndHold();

    void styleChanged();
    void __styleInstanceChanged();

    void contentMovementStarted();
    void contentMovementEnded();

public Q_SLOTS:

private:
    Q_DECLARE_PRIVATE(UCListItem)
    Q_PRIVATE_SLOT(d_func(), void _q_updateThemedData())
    Q_PRIVATE_SLOT(d_func(), void _q_rebound())
    Q_PRIVATE_SLOT(d_func(), void _q_updateSize())
    Q_PRIVATE_SLOT(d_func(), void _q_updateIndex())
};
QML_DECLARE_TYPEINFO(UCListItem, QML_HAS_ATTACHED_PROPERTIES)

class UCAction;
class UCListItemActions;
class UCListItemAttachedPrivate;
class UCListItemAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UCListItemActions *actions READ actions NOTIFY actionsChanged)
    Q_PROPERTY(QQmlListProperty<UCAction> visibleActions READ visibleActions NOTIFY visibleActionsChanged)
    Q_PROPERTY(UCListItem *item READ item NOTIFY itemChanged)
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(UCListItem::PanelStatus panelStatus READ panelStatus NOTIFY panelStatusChanged)
    Q_PROPERTY(bool animate READ animate NOTIFY animateChanged)
public:
    explicit UCListItemAttached(QObject *parent = 0);
    ~UCListItemAttached();
    void setList(UCListItem *list, bool leading, bool visualizeActions);
    void connectToAttached(UCListItemAttached *parentAttached);

    UCListItemActions *actions() const;
    QQmlListProperty<UCAction> visibleActions();
    UCListItem *item();
    int index();
    UCListItem::PanelStatus panelStatus();
    bool animate() const;

public Q_SLOTS:
    void snapToPosition(qreal position);

Q_SIGNALS:
    void actionsChanged();
    void visibleActionsChanged();
    void itemChanged();
    void indexChanged();
    void panelStatusChanged();
    void animateChanged();

private:
    Q_DECLARE_PRIVATE(UCListItemAttached)
    friend class UCListItemAction;

private Q_SLOTS:
    void updateVisibleActions();
};


class UCViewItemsAttachedPrivate;
class UCViewItemsAttached : public QObject
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(UCViewItemsAttached::d_func(), bool selectMode READ selectMode WRITE setSelectMode NOTIFY selectModeChanged)
    Q_PRIVATE_PROPERTY(UCViewItemsAttached::d_func(), QList<int> selectedIndexes READ selectedIndexes WRITE setSelectedIndexes NOTIFY selectedIndexesChanged)
public:
    explicit UCViewItemsAttached(QObject *owner);
    ~UCViewItemsAttached();

    static UCViewItemsAttached *qmlAttachedProperties(QObject *owner);

    bool listenToRebind(UCListItem *item, bool listen);
    void disableInteractive(UCListItem *item, bool disable);
    bool isMoving();
    bool isBoundTo(UCListItem *item);

private Q_SLOTS:
    void unbindItem();

Q_SIGNALS:
    void selectModeChanged();
    void selectedIndexesChanged();

private:
    Q_DECLARE_PRIVATE(UCViewItemsAttached)
    QScopedPointer<UCViewItemsAttachedPrivate> d_ptr;
};
QML_DECLARE_TYPEINFO(UCViewItemsAttached, QML_HAS_ATTACHED_PROPERTIES)

#endif // UCLISTITEM_H
