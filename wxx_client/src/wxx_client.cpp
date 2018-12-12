#include <cinttypes>
#include <memory>
#include <chrono>

#include "wxx_msgs/srv/test.hpp"
#include "rclcpp/rclcpp.hpp"

#define TestService wxx_msgs::srv::Test

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_client");
  auto client = node->create_client<TestService>("test");

  auto request = std::make_shared<TestService::Request>();

  for (int i = 0; i <= 10000; i++)
  {
    request->get_data = i;
    auto result_future = client->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node, result_future) != 
        rclcpp::executor::FutureReturnCode::SUCCESS)
    {
       RCLCPP_ERROR(node->get_logger(), "service call failed!");
       continue;
    }

    auto result = result_future.get();

    RCLCPP_INFO(node->get_logger(), "I get result: %d", result->result_data);
    rclcpp::sleep_for(std::chrono::seconds(1));
  }
  
  rclcpp::shutdown();

  return 0;
}
