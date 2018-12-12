#include <inttypes.h>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "wxx_msgs/srv/test.hpp"

#define TestService wxx_msgs::srv::Test

rclcpp::Node::SharedPtr g_node = nullptr;

void handle_service(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<TestService::Request> request,
  const std::shared_ptr<TestService::Response> response)
{
  (void)request_header;
  response->result_data = request->get_data + 10;
  RCLCPP_INFO(g_node->get_logger(), "I get data： %d, I response data: %d", request->get_data, response->result_data)
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  g_node = rclcpp::Node::make_shared("test_service");
  auto server = g_node->create_service<TestService>("test", handle_service);
  rclcpp::spin(g_node);
  rclcpp::shutdown();
  return 0;
}
