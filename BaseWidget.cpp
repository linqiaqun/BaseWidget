#include "BaseWidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>
#include <QtGlobal>

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent),
      m_isMoving(false),
      m_delta(QPoint(0, 0))
{
    // 设置无边框
    setWindowFlags(Qt::FramelessWindowHint);
}

BaseWidget::~BaseWidget()
{

}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
    // 在最大化状态下无法移动
    if ((!isMaximized()) && (event->button() == Qt::LeftButton))
    {
        m_isMoving = true;
        m_delta = event->globalPos() - pos();
    }

    QWidget::mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMoving)
    {
        move(event->globalPos() - m_delta);
        m_delta = event->globalPos() - pos();
    }

    QWidget::mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isMoving = false;
    QWidget::mouseReleaseEvent(event);
}

void BaseWidget::paintEvent(QPaintEvent *event)
{
#ifdef Q_OS_WIN32
    QPainter painter(this);

    if (isMaximized())
    {
        // 取消背景透明
        setAttribute(Qt::WA_TranslucentBackground, false);

        // 清空背景（绘制阴影时残留）
        painter.fillRect(rect(), Qt::white);
    }
    else
    {
        // 恢复背景透明
        setAttribute(Qt::WA_TranslucentBackground, true);

        // 绘制阴影
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10, 10, width() - 20, height() - 20);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));

        QColor color(0, 0, 0, 50);
        for (int i = 0; i < 10; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(10 - i, 10 - i, width() - (10 - i) * 2, height() - (10 - i) * 2);
            color.setAlpha(150 - qSqrt(i) * 50);
            painter.setPen(color);
            painter.drawPath(path);
        }
    }
#endif

    QWidget::paintEvent(event);
}
