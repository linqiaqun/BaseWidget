#include "BaseWidget.h"
#include <QMouseEvent>

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent),
      m_pressed(false),
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
    if (event->button() == Qt::LeftButton)
    {
        m_pressed = true;
        m_delta = event->globalPos() - pos();
    }

    QWidget::mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed)
    {
        move(event->globalPos() - m_delta);
        m_delta = event->globalPos() - pos();
    }

    QWidget::mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    QWidget::mouseReleaseEvent(event);
}
