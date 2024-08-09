#include<QVBoxLayout>
#include <QWidget>
#include <QLabel>
class Sensor : public QWidget {
  Q_OBJECT

 public:
  explicit Sensor(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent* event);
 private:
  QVBoxLayout *mainLayout;
  QWidget* parent;
  QPixmap pixmap1,pixmap2,pixmap3,pixmap4;
  QLabel *labelimg1,*labelimg2,*labelimg3,*labelimg4;
  QLabel *label1,*label2,*label3;
public:
  void setpicture1();
  void setpicture2();
  void setpicture3();
};


