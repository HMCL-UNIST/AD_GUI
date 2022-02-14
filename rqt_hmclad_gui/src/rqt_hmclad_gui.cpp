// #include "rqt_hmclad_gui/rqt_hmclad_gui.h"
#include "rqt_hmclad_gui.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <QApplication>
#include <iostream>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include "drive_widget.h"
#include <pthread.h>

// QGLBegin_ = new QGLBegin;
namespace rqt_hmclad_gui {



RqtHmclADPlugin::RqtHmclADPlugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
  , linear_velocity_( 0 )
  , angular_velocity_( 0 )
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("RqtHmclADPlugin");
  drive_widget_ = new DriveWidget;

  
 

}

void RqtHmclADPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);

  
  
  
  connect(ui_.LaunchButton, SIGNAL(clicked()), this, SLOT(push_launch_button()));
  connect(ui_.monitor_button, SIGNAL(clicked()), this, SLOT(push_monitor_button()));
  connect(ui_.debug_button, SIGNAL(clicked()), this, SLOT(push_debug_button()));
  connect(ui_.etc_button, SIGNAL(clicked()), this, SLOT(push_etc_button()));
  connect(ui_.Mdrive_switch, SIGNAL(clicked()), this, SLOT(push_MDrive_button()));
  connect(ui_.widget, SIGNAL( outputVelocity( float, float )), this, SLOT( MDrive_setVel( float, float )));
  
  // QGLBegin_ = new QGLBegin;
  
  
  velSub = nh_.subscribe("/current_velocity",1,&RqtHmclADPlugin::current_velCbk, this);
  mySub = nh_.subscribe("/subs",100,&RqtHmclADPlugin::subcallback, this);
  myPub = nh_.advertise<std_msgs::Float32>("/subs",100);
  manualDrivePub = nh_.advertise<ackermann_msgs::AckermannDrive>("/carla/ego_vehicle/ackermann_cmd",1);
  

  
}

void RqtHmclADPlugin::current_velCbk(const geometry_msgs::TwistStampedConstPtr &msg){  
  int current_speed = (int)msg->twist.linear.x;  
  ui_.speedLCD->setSegmentStyle(QLCDNumber::Outline);
  ui_.speedLCD->display(current_speed);
}

void RqtHmclADPlugin::MDrive_setVel(float linear_vel, float angular_vel){
  std::cout << "linear vel = " << linear_vel << ", angular vel = " << angular_vel << std::endl;
  target_speed = linear_vel;
  target_steering  = angular_vel;
  ackermann_msgs::AckermannDrive manual_drive_msg;
  manual_drive_msg.speed = target_speed;
  manual_drive_msg.steering_angle = fmax(-0.52,fmin(angular_vel,0.52));
  manualDrivePub.publish(manual_drive_msg);
}

void RqtHmclADPlugin::push_MDrive_button(){
  if (ui_.Mdrive_switch->isChecked()){
    ui_.Mdrive_label->setStyleSheet(QStringLiteral("QLabel{font-size:9pt;color: rgb(0, 255, 0);}")); // Green
    ui_.Mdrive_label->setText("Manual Drive Enabled");
    ui_.widget->enableDrive();
    
  }else{
    ui_.Mdrive_label->setStyleSheet(QStringLiteral("QLabel{font-size:9pt;color: rgb(255, 0, 0);}")); // RED
    ui_.Mdrive_label->setText("Manual Drive Disbaled");        
    ui_.widget->disableDrive();
  }
}

void RqtHmclADPlugin::push_monitor_button(){
  ui_.stackedWidget->setCurrentIndex(0);
}

void RqtHmclADPlugin::push_debug_button(){
  ui_.stackedWidget->setCurrentIndex(1);
}

void RqtHmclADPlugin::push_etc_button(){
  ui_.stackedWidget->setCurrentIndex(2);
}

void RqtHmclADPlugin::push_launch_button(){
  std::cout <<"System has been initialized" << std::endl;
  ui_.SystemStatus->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 255, 0);}"));
  ui_.SystemStatus->setText("SYSTEM INITIALIZED");  
  
  // myPub.publish(myMsg);
}

void RqtHmclADPlugin::subcallback(const std_msgs::Float32ConstPtr &msg){
  // ui_.myLabel->setText(QString::number(msg->data));  
  return;
}

void RqtHmclADPlugin::shutdownPlugin()
{
  // TODO unregister all publishers here
}

void RqtHmclADPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void RqtHmclADPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}


/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

} // namespace

PLUGINLIB_EXPORT_CLASS(rqt_hmclad_gui::RqtHmclADPlugin, rqt_gui_cpp::Plugin)