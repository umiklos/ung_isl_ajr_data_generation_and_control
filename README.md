# ung_isl_ajr_data_generation_and_control


ROS 2 C++ package.  [![Static Badge](https://img.shields.io/badge/ROS_2-Humble-34aec5)](https://docs.ros.org/en/humble/)
## Packages and build

It is assumed that the workspace is `~/ros2_ws/`.

### Clone the packages
``` r
cd ~/ros2_ws/src
```
``` r
git clone https://github.com/umiklos/ung_isl_ajr_data_generation_and_control

```

### Build ROS 2 packages
``` r
cd ~/ros2_ws
```
``` r
colcon build --packages-select ung_isl_ajr_data_generation_and_control --symlink-install
```

<details>
<summary> Don't forget to source before ROS commands.</summary>

``` bash
source ~/ros2_ws/install/setup.bash
```
</details>

``` r
ros2 launch ung_isl_ajr_data_generation_and_control data_gen_control.launch.py 
```

``` r
ros2 run ung_isl_ajr_data_generation_and_control generate_range_and_twist 
```

``` r
ros2 run ung_isl_ajr_data_generation_and_control control_node
```
## Graph

``` mermaid
graph LR;

gen([ /gen_range_twist]):::red --> range

range[ /range<br/>sensor_msgs/Range]:::light --> cont([ /control_node]):::red
twist[ /twist<br/>geometry_msgs/Twist]:::light -->cont  
gen --> twist


classDef light fill:#34aec5,stroke:#152742,stroke-width:2px,color:#152742  
classDef dark fill:#152742,stroke:#34aec5,stroke-width:2px,color:#34aec5
classDef white fill:#ffffff,stroke:#152742,stroke-width:2px,color:#152742
classDef red fill:#ef4638,stroke:#152742,stroke-width:2px,color:#fff
```
