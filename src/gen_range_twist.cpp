


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <random>

using namespace std::chrono_literals;


class GenRangeTwist : public rclcpp::Node
{
    public:
    GenRangeTwist(): Node("gen_range_twist"), count_(0)
    {
        range_pub_ = this->create_publisher<sensor_msgs::msg::Range>("range", 1);
        twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("twist", 1);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&GenRangeTwist::timer_callback, this));
    }
    private:
        void timer_callback()
        {
            auto range_ = std::make_shared<sensor_msgs::msg::Range>();
            auto twist_ = std::make_shared<geometry_msgs::msg::Twist>();
            range_->header.stamp = this->now();
            range_->header.frame_id = "laser";
            range_->radiation_type = sensor_msgs::msg::Range::INFRARED;
            range_->field_of_view = 3.14;
            range_->min_range = 0.0;
            range_->max_range = 20.0;
            range_->range = cos(count_++ / 75.0) * 20;

            twist_->linear.x = (sin(count_++ / 50.0) * 100)+100;
            twist_->angular.z = sin(count_++ / 20.0) ;

            range_pub_->publish(*range_);
            twist_pub_->publish(*twist_);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr range_pub_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        size_t count_;

};


int main(int argc, char * argv[])

{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GenRangeTwist>());   
    rclcpp::shutdown();
    return 0;
}