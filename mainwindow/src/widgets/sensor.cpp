#include "widgets/sensor.h"

#include "QDebug"
Sensor::Sensor(QWidget* parent)
    : QWidget(parent),
    labelimg1(new QLabel(this))
{
  this->resize(parent->size());
  this->parent = parent;
    pixmap1.load(":/images/no.jpeg");
    pixmap2.load(":/images/no.jpeg");
    pixmap3.load(":/images/no.jpeg");
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mainLayout->setContentsMargins(0, 0, 0, 0);
        // 创建第一个水平布局
    QHBoxLayout *layout1 = new QHBoxLayout();
    label1 = new QLabel("底盘传感器", this);
    labelimg1->setPixmap(pixmap1);
    label1->setFont(QFont("Arial", 14)); // 设置字体大小为14像素
    layout1->addWidget(label1);
    layout1->setSpacing(50);
    layout1->addWidget(labelimg1);

        // 创建第二个水平布局
        QHBoxLayout *layout2 = new QHBoxLayout();
        label2 = new QLabel("激光雷达", this);
        labelimg2 = new QLabel(this);
        labelimg2->setPixmap(pixmap2);
        label2->setFont(QFont("Arial", 14)); // 设置字体大小为14像素
        layout2->addWidget(label2);
        layout2->setSpacing(50);
        layout2->addWidget(labelimg2);

        // 创建第三个水平布局
        QHBoxLayout *layout3 = new QHBoxLayout();
        label3 = new QLabel("摄像头", this);
        labelimg3 = new QLabel(this);
        labelimg3->setPixmap(pixmap3);
        label3->setFont(QFont("Arial", 12)); // 设置字体大小为14像素
        layout3->addWidget(label3);
        layout3->setSpacing(50);
        layout3->addWidget(labelimg3);

        // 将水平布局添加到主垂直布局中
        mainLayout->addLayout(layout1);
        mainLayout->addLayout(layout2);
        mainLayout->addLayout(layout3);
        // 设置窗口的布局
        setLayout(mainLayout);
}
//动态缩放
void Sensor::paintEvent(QPaintEvent* event) {
  this->resize(parent->size());
  QWidget::paintEvent(event);

  int side = qMin(int(parent->width() / 1.8), parent->height());
  label1->setFixedSize(side/2, side/2);
  label2->setFixedSize(side/2, side/2);
  label3->setFixedSize(side/2, side/2);
  labelimg1->setFixedSize(side/13,side/13);
  labelimg2->setFixedSize(side/13,side/13);
  labelimg3->setFixedSize(side/13,side/13);
  int fontSize = std::max(10, parent->width() / 30); // 设置一个最小字体大小为10
  QFont font = label1->font();
  font.setPointSize(fontSize);
  label1->setFont(font);
  label2->setFont(font);
  label3->setFont(font);
}

void Sensor::setpicture1() {//底盘运行
        pixmap1.load(":/images/yes.jpeg");
        labelimg1->setPixmap(pixmap1);
        labelimg1->repaint();
}

void Sensor::setpicture2() {//激光雷达
    pixmap2.load(":/images/yes.jpeg");
    labelimg2->setPixmap(pixmap2);
    labelimg2->repaint();
}

void Sensor::setpicture3() {//摄像头
    pixmap3.load(":/images/yes.jpeg");
    labelimg3->setPixmap(pixmap3);
    labelimg3->repaint();
}

