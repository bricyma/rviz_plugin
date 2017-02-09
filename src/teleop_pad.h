
#ifndef TELEOP_PAD_H
#define TELEOP_PAD_H

#include <ros/ros.h>
#include <ros/console.h>


#include <rviz/panel.h>
#include <sensor_msgs/NavSatFix.h>
#include <dbw_mkz_msgs/SteeringReport.h>
#include <dbw_mkz_msgs/BrakeReport.h>
#include <dbw_mkz_msgs/ThrottleReport.h>
class QLineEdit;

namespace rviz_telop_commander
{

//class DriveWidget;

// BEGIN_TUTORIAL
// Here we declare our new subclass of rviz::Panel.  Every panel which
// can be added via the Panels/Add_New_Panel menu is a subclass of
// rviz::Panel.
//
// TeleopPanel will show a text-entry field to set the output topic
// and a 2D control area.  The 2D control area is implemented by the
// DriveWidget class, and is described there.
class TeleopPanel: public rviz::Panel
{
// This class uses Qt slots and is a subclass of QObject, so it needs
// the Q_OBJECT macro.
Q_OBJECT
public:
  // QWidget subclass constructors usually take a parent widget
  // parameter (which usually defaults to 0).  At the same time,
  // pluginlib::ClassLoader creates instances by calling the default
  // constructor (with no arguments).  Taking the parameter and giving
  // a default of 0 lets the default constructor work and also lets
  // someone using the class for something else to pass in a parent
  // widget as they normally would with Qt.
  TeleopPanel( QWidget* parent = 0 );

  // Now we declare overrides of rviz::Panel functions for saving and
  // loading data from the config file.  Here the data is the
  // topic name.
  virtual void load( const rviz::Config& config );
  virtual void save( rviz::Config config ) const;

  // Next come a couple of public Qt slots.
public Q_SLOTS:
  // The control area, DriveWidget, sends its output to a Qt signal
  // for ease of re-use, so here we declare a Qt slot to receive it.
//  void setVel( float linear_velocity_, float angular_velocity_ );

  // In this example setTopic() does not get connected to any signal
  // (it is called directly), but it is easy to define it as a public
  // slot instead of a private function in case it would be useful to
  // some other user.
  // void setTopic( const QString& topic );
  void setTopic();

  // Here we declare some internal slots.
protected Q_SLOTS:
  // sendvel() publishes the current velocity values to a ROS
  // topic.  Internally this is connected to a timer which calls it 10
  // times per second.
  // void updateTopic();

  // void receiveGPS(const sensor_msgs::NavSatFix &msg);

  // updateTopic() reads the topic name from the QLineEdit and calls
  // setTopic() with the result.

  // Then we finish up with protected member variables.
protected:
  // The control-area widget which turns mouse events into command
  // velocities.
 // DriveWidget* drive_widget_;

  void updateTopic();

  void receiveGPS(const sensor_msgs::NavSatFix &msg);

  void receiveImu(const sensor_msgs::Imu &msg);
  void receiveSpeed(const geometry_msgs::TwistStamped &msg);  
  void receiveBrake(const dbw_mkz_msgs::BrakeReport &msg);
  void receiveThrottle(const dbw_mkz_msgs::ThrottleReport &msg);
  void receiveSteering(const dbw_mkz_msgs::SteeringReport &msg);

  // One-line text editor for entering the outgoing ROS topic name.
  QLineEdit* output_topic_editor_;

  // The current name of the output topic.
  QString output_topic_;

  QLineEdit* output_topic_editor_1;

  // The current name of the output topic.
  QString output_topic_1;

  QLineEdit* output_topic_editor_2;

  // The current name of the output topic.
  QString output_topic_2;

  //gps, heading(from imu), speed, brake, throttle, steering
  QLineEdit* gpsEdit; 
  QLineEdit* headingEdit;
  QLineEdit* speedEdit;
  QLineEdit* brakeEdit;
  QLineEdit* throttleEdit;
  QLineEdit* steeringEdit;




  // The ROS publisher for the command velocity.
  ros::Publisher velocity_publisher_;
  ros::Subscriber gps_subscriber_;
  // The ROS node handle.
  ros::NodeHandle nh_;

  // The latest velocity values from the drive widget.
  float linear_velocity_;
  float angular_velocity_;
  // END_TUTORIAL

  ros::Subscriber gps_sub_;
  ros::Subscriber imu_sub_;
  ros::Subscriber speed_sub_;
  ros::Subscriber brake_sub_;
  ros::Subscriber throttle_sub_;
  ros::Subscriber steering_sub_;

};

} // end namespace rviz_plugin_tutorials

#endif // TELEOP_PANEL_H
