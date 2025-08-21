## Installing on Ubuntu with apt-get[¶](https://catkin-tools.readthedocs.io/en/latest/installing.html#installing-on-ubuntu-with-apt-get "Link to this heading")

First you must have the ROS repositories which contain the `.deb` for `catkin_tools`:
```bash
$ sudo sh \
    -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" \
        > /etc/apt/sources.list.d/ros-latest.list'
$ wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
```
Once you have added that repository, run these commands to install `catkin_tools`:
```bash
$ sudo apt-get update
$ sudo apt-get install python3-catkin-tools
```