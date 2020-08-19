#include "waterprocess.h"
#include <QDebug>

WaterProcess::WaterProcess(QWidget *parent)
    : QWidget(parent)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 66;

    m_borderWidth = 10.0;
    m_waterHeight = 0.05;
    m_offset = 0.6;

    m_bgColor = QColor(120, 120, 120);
    m_borderColor = QColor(80, 80, 80);
    m_usedColor = QColor(235, 106, 106);
    m_textColor = QColor(255, 255, 255);

    //波浪
    m_timer = new QTimer(this);
    m_timer->setInterval(100);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_timer->start();

}

void WaterProcess::setUsedColor(const QColor color)
{
    m_usedColor = color;
}

void WaterProcess::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //背景
    drawBg(&painter);

    //进度、水波
    drawProcess(&painter);

    //进度数字
    drawValue(&painter);
}

void WaterProcess::drawBg(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height) - m_borderWidth;

    int startX = (width - side) * 0.5;
    int startY = (height - side) * 0.5;

    painter->save();
    painter->setBrush(QBrush(m_bgColor));
    if (m_borderWidth == 0) {
        painter->setPen(Qt::NoPen);
    } else {
        QBrush brush(m_borderColor);
        painter->setPen(QPen(brush, m_borderWidth, Qt::SolidLine));
    }

    painter->drawEllipse(startX, startY, side, side);
    painter->restore();
}

void WaterProcess::drawProcess(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height) - (2 * m_borderWidth); //直径

    int startX = (width - side) * 0.5;
    int startY = (height - side) *0.5;
    int endX = startX + side;
    int endY = startY + side;

    double percent = (m_value * 1.0) / (m_maxValue - m_minValue);

    double w = 2 * M_PI / endX;
    double A = endY * m_waterHeight;
    double k = endY * (1.0 - percent);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_usedColor);

    QPainterPath totalPath;
    //加入圆形路径
    totalPath.addEllipse(startX, startY, side, side);

    //水波路径
    QPainterPath water1;
    QPainterPath water2;

    water1.moveTo(startX, endY);
    water2.moveTo(startX, endY);

    m_offset += 0.6;
    if (m_offset > (endX / 2)) {
        m_offset = 0;
    }

    for(int i = startX; i < endX; i++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * qSin(w * i + m_offset)) + k;
        //第二条波浪Y轴
        double waterY2;
        waterY2 = (double)(A * qSin(w * i + m_offset + (endX / 2 * w))) + k;

        water1.lineTo(i, waterY1);
        water2.lineTo(i, waterY2);

        if (m_value == m_minValue) {
            waterY1 = endY;
        }

        if (m_value == m_maxValue) {
            waterY1 = startY;
        }
    }
    //封闭
    water1.lineTo(endX, endY);
    water2.lineTo(endX, endY);

    QPainterPath path;
    QColor waterColor1 = m_usedColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_usedColor;
    waterColor2.setAlpha(200);

    //第一条波浪
    path = totalPath.intersected(water1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    //第二条波浪挖去后的路径
    path = totalPath.intersected(water2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);


    painter->restore();
}

void WaterProcess::drawValue(QPainter *painter)
{
    painter->save();
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height) - m_borderWidth;

    int startX = (width - side) * 0.5;
    int startY = (height - side) * 0.5;

    int fontSize = side / 3;


    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(fontSize);
    font.setBold(true);

    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(QRectF(startX, startY, side, side), Qt::AlignCenter, QString("%1%").arg(m_value));

    painter->restore();
}

void WaterProcess::setMinValue(int value)
{
    m_minValue = value;
    update();
}

void WaterProcess::setMaxValue(int value)
{
    m_maxValue = value;
    update();
}

void WaterProcess::setValue(int v)
{
    m_value = v;
    update();
}

void WaterProcess::setBorderWidth(int width)
{
    m_borderWidth = width;
    update();
}

void WaterProcess::setWaterHeight(int height)
{
    m_waterHeight = height;
    update();
}

void WaterProcess::start()
{
    if (m_timer) {
        m_timer->start();
    }
}

void WaterProcess::stop()
{
    if (m_timer) {
        m_timer->stop();
    }
}
