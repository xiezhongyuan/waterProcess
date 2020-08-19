#ifndef WATERPROCESS_H
#define WATERPROCESS_H

#include <QWidget>
#include <QtWidgets>

class WaterProcess : public QWidget
{
    Q_OBJECT
public:
    explicit WaterProcess(QWidget *parent = nullptr);

    ~WaterProcess(){}

    void setUsedColor (const QColor color);

protected:
    void paintEvent(QPaintEvent *ev);

private:
    //画背景
    void drawBg(QPainter *painter);

    //画水波
    void drawProcess(QPainter *painter);

    //画文字
    void drawValue(QPainter *painter);

public Q_SLOTS:
    void setMinValue(int value);
    void setMaxValue(int value);
    void setValue(int v);

    void setBorderWidth(int width);
    void setWaterHeight(int height);

    void start();
    void stop();

private:
    int     m_minValue;       //最小值
    int     m_maxValue;       //最大值
    int     m_value;          //当前值

    double  m_borderWidth;    //边框宽度
    double  m_waterHeight;    //水波高度
    double  m_offset;         //水波偏移量

    QColor  m_bgColor;        //背景颜色
    QColor  m_borderColor;    //边框颜色
    QColor  m_usedColor;      //进度颜色
    QColor  m_textColor;      //文字颜色

    QTimer  *m_timer;         //水波定时器
};

#endif // WATERPROCESS_H
