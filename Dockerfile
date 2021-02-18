FROM ros:noetic-perception

ENV CATKIN_WS=/root/catkin_ws

RUN   if [ "x$(nproc)" = "x1" ] ; then export USE_PROC=1 ; \
      else export USE_PROC=$(($(nproc)/2)) ; fi && \
      apt-get update && apt-get install -y \
      apt-utils \
      ros-${ROS_DISTRO}-rosserial &&\
      rm -rf /var/lib/apt/lists/*

# Copy Project
COPY . $CATKIN_WS/src/ultrabot_stm
RUN chmod -R +x $CATKIN_WS/src/ultrabot_stm

# Build Project
WORKDIR $CATKIN_WS
RUN /bin/bash -c 	"source /opt/ros/$ROS_DISTRO/setup.bash && \
			cd $CATKIN_WS && catkin_make && source devel/setup.bash"

# Source ros package from entrypoint
RUN sed --in-place --expression \
      '$isource "$CATKIN_WS/devel/setup.bash"' \
      /ros_entrypoint.sh