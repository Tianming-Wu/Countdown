#include "gradientlabel.h"
#include <QPainter>
#include <QFontMetricsF>

GradientLabel::GradientLabel(QWidget *parent)
    : QLabel(parent)
{
    // 初始化默认渐变（红到蓝）
    m_gradient.setColorAt(0, Qt::red);
    m_gradient.setColorAt(1, Qt::blue);
}

void GradientLabel::setGradientEnabled(bool enabled) {
    if (m_gradientEnabled != enabled) {
        m_gradientEnabled = enabled;
        update();
    }
}

void GradientLabel::setGradientAngle(int angle) {
    if (m_angle != angle) {
        m_angle = angle;
        update();
    }
}

void GradientLabel::setGradientStops(const QGradientStops &stops) {
    m_gradient.setStops(stops);
    update();
}

void GradientLabel::setGradientColors(const QColor &start, const QColor &end) {
    m_gradient.setColorAt(0, start);
    m_gradient.setColorAt(1, end);
    update();
}

void GradientLabel::setText(const QString &text) {
    QLabel::setText(text);
    m_metricsDirty = true;
    update();
}

void GradientLabel::setFont(const QFont &font) {
    QLabel::setFont(font);
    m_metricsDirty = true;
    update();
}

void GradientLabel::resizeEvent(QResizeEvent *event) {
    QLabel::resizeEvent(event);
    m_metricsDirty = true;
}

void GradientLabel::updateTextMetrics() {
    if (!m_metricsDirty) return;

    QFontMetricsF fm(font());
    m_textRect = fm.boundingRect(rect(), alignment(), text());

    // 计算基线位置（考虑对齐方式）
    QPointF baselinePos(0, fm.ascent());

    // 水平对齐修正
    if (alignment() & Qt::AlignLeft) {
        baselinePos.setX(0);
    } else if (alignment() & Qt::AlignRight) {
        baselinePos.setX(width() - m_textRect.width());
    } else { // 默认居中
        baselinePos.setX((width() - m_textRect.width()) / 2.0);
    }

    // 垂直对齐修正
    if (alignment() & Qt::AlignTop) {
        baselinePos.setY(fm.ascent());
    } else if (alignment() & Qt::AlignBottom) {
        baselinePos.setY(height() - fm.descent());
    } else { // 默认垂直居中
        baselinePos.setY((height() + fm.ascent() - fm.descent()) / 2.0);
    }

    // 构建文字路径
    m_textPath = QPainterPath();
    m_textPath.addText(baselinePos, font(), text());

    m_metricsDirty = false;
}

void GradientLabel::paintEvent(QPaintEvent *event) {
    if (!m_gradientEnabled) {
        QLabel::paintEvent(event);
        return;
    }

    updateTextMetrics();

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // 设置渐变（直接使用控件坐标系）
    QLinearGradient gradient;
    gradient.setStops(m_gradient.stops());

    // 计算渐变方向向量（基于控件坐标）
    qreal rad = qDegreesToRadians(m_angle);
    QPointF center = m_textRect.center();
    QPointF offset(qCos(rad) * m_textRect.width()/2,
                   qSin(rad) * m_textRect.height()/2);

    gradient.setStart(center - offset);
    gradient.setFinalStop(center + offset);

    // 绘制渐变文字
    painter.fillPath(m_textPath, gradient);

    // 调试绘制（可选）
    // painter.setPen(Qt::red);
    // painter.drawRect(m_textRect);
    // painter.drawEllipse(center, 2, 2);
}
