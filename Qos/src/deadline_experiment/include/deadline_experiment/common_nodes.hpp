#ifndef QUALITY_OF_SERVICE_DEMO__COMMON_NODES_HPP_
#define QUALITY_OF_SERVICE_DEMO__COMMON_NODES_HPP_
#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class talker : public rclcpp::Node
{
 public:
	 talker(const rclcpp::QoS &qos_profile,
		const std::string &topic_name,
		std::chrono::milliseconds publish_period=std::chrono::milliseconds(500)	 
		);   //constructor

         void initialize();
         void publish();      //publish single message
	 void pause_publish_for(std::chrono::milliseconds pause_duration);
         
	 rclcpp::PublisherOptions & get_options(){return publisher_options_;}
 
 private:
	 rclcpp::QoS qos_profile_;
	 rclcpp::PublisherOptions publisher_options_;
	 rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_=nullptr;

	 const std::string topic_name_;
	 std::chrono::milliseconds publish_period_ = std::chrono::milliseconds(500);
         rclcpp::TimerBase::SharedPtr publish_timer_ = nullptr;
         rclcpp::TimerBase::SharedPtr pause_timer_ = nullptr;
};
class listener : public rclcpp::Node
{
  public:
         listener(
              const rclcpp::QoS & qos_profile,
              const std::string & topic_name
		 );
	 void initialize();
	 void start_listening();
         void pause_listening(std::chrono::milliseconds);

	 rclcpp::SubscriptionOptions & get_options() {return subscription_options_;}


  private:
          rclcpp::QoS qos_profile_;
          rclcpp::SubscriptionOptions subscription_options_;
          rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_ = nullptr;

          const std::string topic_name_;
          rclcpp::TimerBase::SharedPtr pause_timer_ = nullptr;


};
#endif
