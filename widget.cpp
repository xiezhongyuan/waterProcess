#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->waterProcess2->setUsedColor(QColor(79, 175, 243));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_borderWidthSlider_valueChanged(int value)
{
    ui->waterProcess1->setBorderWidth(value);
    ui->waterProcess2->setBorderWidth(value);
}

void Widget::on_processSlider_valueChanged(int value)
{
    ui->waterProcess1->setValue(value);
    ui->waterProcess2->setValue(value);
}
