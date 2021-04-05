# runbot_stm: STM32 Controller ROS Wrapper

## Requirements

- ROS Noetic
- rosserial
- roscpp  

## Description

 This package consists of necessary datatype descriptions, sync node, and several test examples.  

 The main launchfile is *stm.launch*. It starts the communication between a controller and the PC and run a syncing node, that ping a controller when ROS is connected.

 *imu_integration.launch* additionally runs tf2 broadcaster and rviz for showing the IMU orientation.

### Publishers

 > Battery state: charge (%), voltage (V), current (mA), power consumption (W)  

- /stm/power

> Emergency button state (bool)

- /stm/emergency

> IMU data (sensor_msgs/Imu)

- /stm/imu  

> Ultrasound rangefinders data (MultiArray of Int16 = range in millimeters)

- /stm/rangefinders

### Subscribers  

> Calibrate IMU listener. Call it "--once". ~ 5 second calibration time.

- /stm/imu/calibrate

> Syncronization topic listener. If no sync data, then STM is waiting for connection.

- /stm/sync

### Services  

> Led service allow to control RGB strip: color + brightness (0.0 till 1.0)

- /stm/led

> Relay service allow to control relays :) It request bool type variables (Relay1,...,Relay7) and response with two array: status of a single relay (bool) and switching timeout (int, currently set to 3 seconds)

- /stm/relay

### STM32 Node rates

- Power state and emergency button state: 10 Hz
- Rangefinders: 20 Hz
- IMU: 100 Hz
- Sync: 20 Hz (1 Hz embedded timer period)

## Docker

 **Notice**: Do not forget to forward USB interface into a container.  

 You could use *docker-compose* configuration to run this node explicitly with ROS master or as a reference for a global setup.
 docker-compose in terminal usage:

 ```bash
    docker-compose up
 ```

 Daemon:

```bash
    docker-compose up -d
 ```

 Stop daemon:
  
 ```bash
    docker-compose down
 ```
