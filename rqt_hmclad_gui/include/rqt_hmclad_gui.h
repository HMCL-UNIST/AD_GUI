#ifndef RQT_HMCLAD_H
#define RQT_HMCLAD_H

#include <rqt_gui_cpp/plugin.h>
// #include <rqt_hmclad_gui/ui_rqt_hmclad_gui.h>
#include <rqt_hmclad_gui/ui_rqt_hmclad_gui.h>
#include <QWidget>

#include <std_msgs/Float32.h>
#include <iostream>
#include <ros/ros.h>
// #include "qglbegin.h"


namespace rqt_hmclad_gui {
class DriveWidget;

class RqtHmclADPlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  RqtHmclADPlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);
  ros::Publisher myPub;
  std_msgs::Float32 myMsg;
  ros::Subscriber mySub;
  void subcallback(const std_msgs::Float32ConstPtr &msg);
  
// public Q_SLOTS:
  
//   void setVel( float linear_velocity_, float angular_velocity_ );

// protected Q_SLOTS:  
//   void sendVel();

protected slots:
  
  virtual void push_MDrive_button();
  virtual void push_launch_button();
  virtual void push_monitor_button();
  virtual void push_etc_button();
  virtual void push_debug_button();
  virtual void MDrive_setVel(float linear_vel, float angular_vel);
  
protected:

  DriveWidget* drive_widget_;
// protected:
//   QGLBegin* QGLBegin_;
    float linear_velocity_;
  float angular_velocity_;
//signals:
  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();
private:
  Ui::RqtHmclADGuiWidget ui_;
  QWidget* widget_;
  
  ros::NodeHandle nh_;
};
} // namespace

#endif // my_namespace__my_plugin_H
