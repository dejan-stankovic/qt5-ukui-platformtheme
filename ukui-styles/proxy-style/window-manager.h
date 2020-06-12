/*
 * Qt5-UKUI's Library
 *
 * Copyright (C) 2020, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QTimer>
#include <QPoint>

class QMouseEvent;
class AppEventFilter;

/*!
 * \brief The WindowManager class
 * \details
 * This class is use to help window management.
 * There are some qt's windows, such as frameless window, could not
 * move and move resize by it self. Through registering widget to window
 * manager, we can let them movable and can be maximum/half-maximum like
 * other normal window.
 */
class WindowManager : public QObject
{
    friend class AppEventFilter;
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);

    void registerWidget(QWidget *w);
    void unregisterWidget(QWidget *w);

    bool eventFilter(QObject *obj, QEvent *e);

    void buttonPresseEvent(QObject *obj, QMouseEvent *e);
    void mouseMoveEvent(QObject *obj, QMouseEvent *e);
    void mouseReleaseEvent(QObject *obj, QMouseEvent *e);

protected:
    void endDrag();

private:
    QObject *m_current_obj = nullptr;
    bool m_is_dragging = false;
    QTimer m_timer;
    QPoint m_start_point;

    bool m_prepared_to_drag = false;
};

class AppEventFilter : public QObject
{
    friend class WindowManager;
    Q_OBJECT
private:
    explicit AppEventFilter(WindowManager *parent);
    ~AppEventFilter() {}

    bool eventFilter(QObject *obj, QEvent *e);

    WindowManager *m_wm = nullptr;
};

#endif // WINDOWMANAGER_H
