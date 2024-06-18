

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ung_isl_ajr_data_generation_and_control',
            executable='generate_range_and_twist',
        ),
        Node(
            package='ung_isl_ajr_data_generation_and_control',
            executable='control_node',
        ),
    ])