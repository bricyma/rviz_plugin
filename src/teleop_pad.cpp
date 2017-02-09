
#include <stdio.h>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTimer>

#include <geometry_msgs/Twist.h>
#include <QDebug>

#include "teleop_pad.h"

namespace rviz_telop_commander
{

//TODO
TeleopPanel::TeleopPanel( QWidget* parent )
  : rviz::Panel( parent )
  , linear_velocity_( 0 )
  , angular_velocity_( 0 )
{
  QFormLayout* form_layout = new QFormLayout;

  //gps, heading(from imu), speed, brake, throttle, steering
  form_layout->addRow(tr("&GPS:"), gpsEdit);
  form_layout->addRow(tr("&Heading:"), headingEdit);
  form_layout->addRow(tr("&Speed:"), speedEdit);
  form_layout->addRow(tr("&Brake:"), brakeEdit);
  form_layout->addRow(tr("&Throttle:"), throttleEdit);
  form_layout->addRow(tr("&steering:"), steeringEdit);

  setLayout(form_layout);




  // QVBoxLayout* topic_layout = new QVBoxLayout;
  // topic_layout->addWidget( new QLabel( "Teleop Topic:" ));
  // output_topic_editor_ = new QLineEdit;
  // topic_layout->addWidget( output_topic_editor_ );


  // topic_layout->addWidget( new QLabel( "Linear Velocity:" ));
  // output_topic_editor_1 = new QLineEdit;
  // topic_layout->addWidget( output_topic_editor_1 );


  // topic_layout->addWidget( new QLabel( "Angular Velocity:" ));
  // output_topic_editor_2 = new QLineEdit;
  // topic_layout->addWidget( output_topic_editor_2 );

  // QHBoxLayout* layout = new QHBoxLayout;
  // layout->addLayout( topic_layout );
  // setLayout( layout );
 // output_topic_editor_->setText(QString::fromStdString("GPS"));


  updateTopic();

 
}


//TODO
void TeleopPanel::receiveGPS(const sensor_msgs::NavSatFix &msg){
  if( ros::ok() && gps_subscriber_)
  {
    // QString lng = QString::number(msg.longitude);
    // QString lat = QString::number(msg.latitude);
    QString lng = QString("%7").arg(msg.longitude);
    QString lat = QString("%7").arg(msg.latitude);
    output_topic_editor_1->setText(lng);
    output_topic_editor_2->setText(lat);
    output_topic_editor_->setText(QString::number(msg.header.seq));
    std::cout<<lng.toStdString()<<std::endl; 
  }
}


void TeleopPanel::receiveImu(const sensor_msgs::Imu &msg){
  //TODO quat->eular
  if (ros::ok() && imu_sub_){
  }
}

void TeleopPanel::receiveSpeed(const geometry_msgs::TwistStamped &msg){
  if (ros::ok() && speed_sub_){
    QString speed = QString::number(msg.twist.linear.x);
    speedEdit->setText(speed);
  }
}


void TeleopPanel::receiveBrake(const dbw_mkz_msgs::BrakeReport &msg){
  if (ros::ok() && brake_sub_){
    QString brake_flag; 
    if (msg.pedal_input > 0.14)
      brake_flag = QString::fromStdString("True");
    else
      brake_flag = QString::fromStdString("False");
    brakeEdit->setText(brake_flag);
  }
}


void TeleopPanel::receiveThrottle(const dbw_mkz_msgs::ThrottleReport &msg){
  if (ros::ok() && throttle_sub_){
    QString throttle = QString::number(msg.pedal_input);
    throttleEdit->setText(throttle);
  }
}

void TeleopPanel::receiveSteering(const dbw_mkz_msgs::SteeringReport &msg){
  if (ros::ok && steering_sub_){
    QString steering;
    //TODO, need to check
    if (msg.steering_wheel_angle > 0)
      steering_report = QString::fromStdString("Left");
    else
      steering_report = QString::fromStdString("Right");
    steeringEdit->setText(steering);
  }
}




void TeleopPanel::updateTopic()
{
  gps_sub_ = nh_.subscribe("/navsat/fix", 1, &TeleopPanel::receiveGPS, this);
  imu_sub_ = nh_.subscribe("/imu/data", 1, &TeleopPanel::receiveImu, this);
  speed_sub_ = nh_.subscribe("/vehicle/twist", 1, &TeleopPanel::receiveSpeed, this);
  brake_sub_ = nh_.subscribe("/vehicle/brake_report", 1, &TeleopPanel::receiveBrake, this);
  throttle_sub_ = nh_.subscribe("/vehicle/throttle_report", 1, &TeleopPanel::receiveThrottle, this);
  steering_sub_ = nh_.subscribe("/vehicle/steering_report", 1, &TeleopPanel::receiveSteering, this);

  std::cout<<"update topic"<<std::endl;
}


void TeleopPanel::save( rviz::Config config ) const
{
  rviz::Panel::save( config );
  config.mapSetValue( "Topic", output_topic_ );
}

// Load all configuration data for this panel from the given Config object.
void TeleopPanel::load( const rviz::Config& config )
{
  rviz::Panel::load( config );
  QString topic;
  if( config.mapGetString( "Topic", &topic ))
  {
    output_topic_editor_->setText( topic );
    updateTopic();
  }
}

} // end namespace rviz_plugin_tutorials

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_telop_commander::TeleopPanel,rviz::Panel )
// END_TUTORIAL
