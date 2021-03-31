#include <chrono>
#include <string>
#include <iostream>
#include <thread>
#include "deadline_experiment/common_nodes.hpp"
using namespace std;
talker::talker(
    const rclcpp::QoS & qos_profile,
    const std::string & topic_name,
    std::chrono::milliseconds publish_period
	   ):Node("Talker"),
	     qos_profile_(qos_profile),
	     topic_name_(topic_name),
	     publish_period_(publish_period){}

void talker::initialize()
{
    RCLCPP_INFO(get_logger(), "Talker starting up");

    publisher_ = create_publisher<std_msgs::msg::String>(
    topic_name_,
    qos_profile_,
    publisher_options_);
    publish_timer_ = create_wall_timer(
    publish_period_,
    [this]() -> void {
      publish();
    });
}
void talker::publish()
{
  std_msgs::msg::String msg;
  msg.data = "talker says hello!" ;
  RCLCPP_INFO(get_logger(), "Publishing: '%s'", msg.data.c_str());
  publisher_->publish(msg);
}
void talker::pause_publish_for(std::chrono::milliseconds pause_length)
{
   if(pause_timer_){    //already pause
         return;
   }
   publish_timer_->cancel();
   pause_timer_=create_wall_timer(
		   pause_length,
		   [this](){
                   publish();
		   publish_timer_->reset();
		   pause_timer_=nullptr;
		   });
}

listener::listener(
  const rclcpp::QoS & qos_profile,
  const std::string & topic_name
  )
: Node("Listener"),
  qos_profile_(qos_profile),
  topic_name_(topic_name){}

void
listener::initialize()
{
  RCLCPP_INFO(get_logger(), "Listener starting up");
  start_listening();
}
void listener::start_listening()
{
   if(!subscription_){
      subscription_ = create_subscription<std_msgs::msg::String>(
      topic_name_,
      qos_profile_,
      [this](const typename std_msgs::msg::String::SharedPtr msg) -> void
      {
        RCLCPP_INFO(get_logger(), "Listener heard: [%s]", msg->data.c_str());
      },
      subscription_options_);
   }
   std::cout<<"hi";
}
void listener::pause_listening(std::chrono::milliseconds pause_length)
{
   for(int i=0;i<10000;i++)    //do something make the listener busy
   {
      for(int j=0;j<1000;j++)
	  {
              int k=0;
	      k++;
	  }
   }
}
