#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCalendarWidget>
#include <QComboBox>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QTableWidget>
#include <QToolBar>
#include <QTreeView>
#include <QWidgetAction>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVBoxLayout>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>


#include "DockAreaWidget.h"
#include "DockManager.h"
#include "DockWidget.h"
#include "channel_manager.h"
#include "config/config_manager.h"
#include "display/manager/display_manager.h"
#include "point_type.h"
#include "widgets/dashboard.h"
#include "widgets/sensor.h"
#include "widgets/nav_goal_table_view.h"
#include "widgets/set_pose_widget.h"
#include "widgets/speed_ctrl.h"
#include "widgets/ratio_layouted_frame.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int flag2d=0,flag3d=0,flagbuild=0;
 public slots:
  void signalCursorPose(QPointF pos);
  void SendChannelMsg(const MsgId &id, const std::any &data);
  void RecvChannelMsg(const MsgId &id, const std::any &data);
  void updateOdomInfo(RobotState state);
  void RestoreState();
  void SlotSetBatteryStatus(double percent, double voltage);
  void SlotRecvImage(const std::string &location, std::shared_ptr<cv::Mat> data);
//状态显示
  void begin_mapping();
  void end_mapping();

  void loadAndShowPCD(); //加载点云
 protected:
  virtual void closeEvent(QCloseEvent *event) override;

 private:
  Sensor* sensor;
  QAction *SavePerspectiveAction = nullptr;
  QWidgetAction *PerspectiveListAction = nullptr;
  ChannelManager channel_manager_;
  Ui::MainWindow *ui;
  DashBoard *speed_dash_board_;
  ads::CDockManager *dock_manager_;
  ads::CDockAreaWidget *StatusDockArea;
  ads::CDockWidget *TimelineDockWidget;
  Display::DisplayManager *display_manager_;
  QLabel *label_pos_map_;
  QLabel *label_pos_scene_;
  QThread message_thread_;
  SpeedCtrlWidget *speed_ctrl_widget_;
  NavGoalTableView *nav_goal_table_view_;
  QProgressBar *battery_bar_;
  QLabel *label_power_;
  ads::CDockAreaWidget *center_docker_area_;
  std::map<std::string, RatioLayoutedFrame *> image_frame_map_;
//点云
  QVTKOpenGLNativeWidget *widgetOpenGL;
  vtkSmartPointer<vtkRenderer> renderer;
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
  std::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
  QPushButton *loadButton;
 signals:
  void OnRecvChannelData(const MsgId &id, const std::any &data);

 private:
  void setupUi();
  bool openChannel();
  bool openChannel(const std::string &channel_name);
  void closeChannel();
  void registerChannel();
  void SaveState();
};
#endif  // MAINWINDOW_H
