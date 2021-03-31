//In this experiment I will pause the listener for 1 s with 5s time interval and set the deadline for 600ms  for simulating the situation that the listener is busy 

#include<string>
#include<chrono>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/executors/single_threaded_executor.hpp"

#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include "deadline_experiment/common_nodes.hpp"
int main(int argc,char * argv[])
{
   std::chrono::milliseconds deadline_duration(600);
   std::chrono::milliseconds period_pause_listener(5000);
   std::chrono::milliseconds duration_pause_listener(2000);
   std::string topic("chatter");


   rclcpp::init(argc,argv);
   rclcpp::executors::SingleThreadedExecutor executor;



   rclcpp::QoS qos_profile(10);
   qos_profile.deadline(deadline_duration);

   auto Talker=std::make_shared<talker>(qos_profile,topic);
   Talker->get_options().event_callbacks.deadline_callback =
    [node = Talker.get()](rclcpp::QOSDeadlineOfferedInfo & event) -> void
    {
      RCLCPP_INFO(
        node->get_logger(), "Offered deadline missed");
    };

 // auto Listener = std::make_shared<listener>(qos_profile, topic);
  
 // Listener->get_options().event_callbacks.deadline_callback =
  //  [node = Listener.get()](rclcpp::QOSDeadlineRequestedInfo & event) -> void
   // {
   //   RCLCPP_INFO(
   //     node->get_logger(), "Requested deadline missed");
   // };

  Talker->initialize();
 // Listener->initialize();

  //auto pause_timer = Listener->create_wall_timer(
//		  period_pause_listener,
//		  [Listener,duration_pause_listener]()->void{
  //                  Listener->pause_listening(duration_pause_listener);
//		  });
  // Execution
  executor.add_node(Talker);
//  executor.add_node(Listener);
  executor.spin();

  // Cleanup
  rclcpp::shutdown();
  return 0;

}
















