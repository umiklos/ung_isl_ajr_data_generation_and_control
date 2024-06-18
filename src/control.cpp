

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "geometry_msgs/msg/twist.hpp"


class control : public rclcpp::Node
{

    public:
        control(): Node("control_node")
        
        {
            range_sub_ = this->create_subscription<sensor_msgs::msg::Range>("range", 1, std::bind(&control::range_callback, this, std::placeholders::_1));
            twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>("twist", 1, std::bind(&control::twist_callback, this, std::placeholders::_1));
            timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&control::timer_callback, this));
        }

    private:
        void timer_callback()
        {
            if(range_<5)
            {
                RCLCPP_INFO(this->get_logger(), "Obstacle detected, stopping robot");
            }
            else if (range_>5 && twist_>10)
            {
                RCLCPP_INFO(this->get_logger(), "Obstacle not detected, moving robot");
            }
            else if (range_<0 && twist_>10)
            {
                RCLCPP_INFO(this->get_logger(), "Obstacle detected, stopping failed :(" );
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "Twist: %f, Angular: %f", twist_, angular_);
            }
        }
        void range_callback(const sensor_msgs::msg::Range::SharedPtr msg) 
        {
            range_=msg->range;
        }

        void twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg) 
        {
            twist_=msg->linear.x;
            angular_=msg->angular.z;
        }
        rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr range_sub_;
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;

        rclcpp::TimerBase::SharedPtr timer_;
        float range_, twist_, angular_;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<control>());
    rclcpp::shutdown();
    return 0;
}



