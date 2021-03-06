/******************************************************************************
   OGM Validator - Occupancy Grid Map Validator
   Copyright (C) 2015 OGM Validator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

   Authors :
   * Marios Protopapas, protopapasmarios@gmail.com
   * Manos Tsardoulias, etsardou@gmail.com
******************************************************************************/


#include "ros/ros.h"
/*#include "tf/tf.h"*/
//#include "tf/transform_broadcaster.h"
//#include "nav_msgs/MapMetaData.h"
#include "nav_msgs/OccupancyGrid.h"
#include "ogm_communications/MapPublish.h"
#include "ogm_server/map_loader.h"

/**
@namespace ogm_server
@brief The main namespace for OGM Server
**/ 
namespace ogm_server {

  /**
  @class MapServer
  @brief Implements the OGM map server functionalities
  **/ 
  class MapServer
  {
    public:
      
      /**
      @brief Constructor by filename
      @param fname [const std::string&] The file name
      @return void
      **/
      MapServer(const std::string& fname, bool groundTruth);
     
      /**
      @brief Constructor by filename
      @param fname [const std::string&] The file name
      @return void
      **/
      MapServer(const std::string& fname);

      /**
      @brief Constructor by occupancy grid map
      @param map [const nav_msgs::OccupancyGrid&] The occupancy grid map
      @return void
      **/
      explicit MapServer(const nav_msgs::OccupancyGrid& map);

      nav_msgs::OccupancyGrid getMap();

      std::string getName();
      
    private:
      
      /**
      @brief Publishes the map data and metadata
      @return void
      **/
      void publishData();
      
      /**
      @brief Publishes the map to map_static transform
      @param ev [const ros::TimerEvent&] A ROS timer event
      @return void
      **/
      void publishTransform(const ros::TimerEvent& ev);
    
    private:
    
      //!< The ROS node handle
      ros::NodeHandle n;
      //!< ROS publishers for posting the maps
      ros::Publisher map_pub;
      ros::Publisher viz_pub2;
      ros::Publisher viz_pub1;
      ////!< ROS publisher for posting the map metadata
      //ros::Publisher metadata_pub;
      ////!< ROS timer for tf posting
      //ros::Timer tfTimer;
      ////!< ROS tf broadcaster
      //tf::TransformBroadcaster tfBroadcaster;
      //!< ROS map metadata message
      nav_msgs::MapMetaData meta_data_message_;
      //!< ROS occupancy grid message
      //nav_msgs::OccupancyGrid map_;
      ogm_communications::MapPublish map_;
      //!< the map name
      std::string mapName_;

  };
}
