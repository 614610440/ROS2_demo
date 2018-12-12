#include <iostream>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("wxx_publisher");
    auto publisher = node->create_publisher<std_msgs::msg::String>("wxx_topic");
    auto message = std::make_shared<std_msgs::msg::String>();
    auto publisher_count = 0;
    rclcpp::WallRate loop_rate(500ms);

    while(rclcpp::ok())
    {
        message->data = "Hello WXX！" + std::to_string(publisher_count++); 

        RCLCPP_INFO(node->get_logger(), "Publishing: '%s", message->data.c_str());
        publisher->publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    return 0;
}
