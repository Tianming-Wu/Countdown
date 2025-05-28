#pragma once
#include <QLabel>
#include <QLinearGradient>
#include <QPainterPath>

class GradientLabel : public QLabel {
    Q_OBJECT
    Q_PROPERTY(bool gradientEnabled READ isGradientEnabled WRITE setGradientEnabled)
    Q_PROPERTY(int gradientAngle READ gradientAngle WRITE setGradientAngle)
public:
    explicit GradientLabel(QWidget *parent = nullptr);

    // 渐变控制
    bool isGradientEnabled() const { return m_gradientEnabled; }
    void setGradientEnabled(bool enabled);

    int gradientAngle() const { return m_angle; }
    void setGradientAngle(int angle);

    // 渐变颜色设置
    void setGradientStops(const QGradientStops &stops);
    void setGradientColors(const QColor &start, const QColor &end);

public slots:
    void setText(const QString &text);
    void setFont(const QFont &font);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateTextMetrics();

    bool m_gradientEnabled = false;
    int m_angle = 30; // 默认30度角
    QLinearGradient m_gradient;
    QPainterPath m_textPath;
    QRectF m_textRect;
    bool m_metricsDirty = true;
};
