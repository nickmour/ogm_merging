/******************************************************************************
   OGM Validator - Occupancy Grid Map Validator
   Copyright (C) 2016 OGM Validator
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

#include "feature_evaluation/feature_evaluation_descriptors/mean_rays_descriptor.h"

namespace feature_evaluation
{
    /**
    @brief Default Constructor
    @return void
    **/ 
    MeanRaysDescriptor::MeanRaysDescriptor():DescriptorExtractor()
    {
        //ROS_INFO_STREAM("Created MeanRaysDescriptor instance");
    }
    
    /**
    @brief function for description extract computation.
    @param image [const cv::Mat&] the image 
    @param keypoints [std::vector<cv::Keypoint>&] the image detected keypoints
    @param descriptors [cv::Mat&] the descriptors to be extracted
    @return void
    **/
    void MeanRaysDescriptor::compute(const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, cv::Mat* descriptors)
    {
      float previousRadius, initialRadius, radius, nextRadius;
      int r;
      int numRings = 8;
      float x, y;
      cv::Mat img,temp;
      cv::cvtColor(image, img, CV_GRAY2RGB);
      cv::Mat desc = cv::Mat(keypoints.size(), numRings, CV_32FC1);
      std::vector<float> rowFeatures;
      int sumOfRays, thetaIncrement;
      bool outOfBounds;
      std::vector<cv::Point> p;
      std::vector<int> rays;
      float radiusRatio = 1.1;
      float totalLength = std::min(image.rows, image.cols)/5;
      float factor = 0;
      for (int i = 0; i < numRings; i++)
      {
        factor += std::pow(radiusRatio, i);
      }

      initialRadius = totalLength  / factor;


      thetaIncrement = 1;
      int maxRadius;
      cv::RNG rng(12345);
      cv::Scalar color;
      for (int k = 0; k < keypoints.size(); k++)
      {
        //maxRadius = 0;
        sumOfRays = 0;
        previousRadius = 0;
        radius = initialRadius;
        //rays.clear();

        for (int l = 0; l < numRings; l++)
        {
          //maxRadius += 25;
          //p.clear();
          for (int theta = 0; theta < 360; theta = theta + thetaIncrement)
          {
            outOfBounds = false;
            r = 0; //radius;
            nextRadius = radiusRatio *(radius - previousRadius) + radius;
            for(;;)
            {
              r++;
              x = (int) round((r * cos(theta * M_PI / 180)) + keypoints[k].pt.x);
              y = (int) round((r * sin(theta * M_PI / 180)) + keypoints[k].pt.y);
              if(x < 0)
              {
                x = 0;
                outOfBounds = true;
              }

              if(y < 0)
              {
                y = 0;
                outOfBounds = true;
              }

              if(y > image.rows - 1)
              {
                y = image.rows -1;
                outOfBounds = true;
              }

              if(x > image.cols -1)
              {
                x = image.cols - 1;
                outOfBounds = true;
              }

              if(image.at<unsigned char>(y, x) == 0 || image.at<unsigned char>(y, x) == 127 )
              {
                sumOfRays += r;
                //p.push_back(cv::Point(x, y));
                //rays.push_back(r);
                break;
              }
              
              if( outOfBounds || r >= nextRadius)
              {
                  break; 
              }
            }
          }

         desc.at<float>(k, l) = (float)sumOfRays / (360 / thetaIncrement);
         //color = cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
         //std::cout<< "sumOfRays=" << sumOfRays << std::endl;
        //if(k == 12){
/*        for (int i = 0; i < p.size(); i++)*/
        //{

          //cv::line(img, keypoints[k].pt, p[i], color, 1, 8);
        //[>  std::cout << p[i] << " ";<]
          //[>std::cout << rays[i] << " ";<]
        /*}*/
        //std::cout << std::endl;
/*      cv::imshow("MeanRays Descriptors", img);*/
      /*cv::waitKey(0);*/
        previousRadius = radius;
        radius = nextRadius;

      }
    }
     /* ROS_INFO_STREAM("DESC=" << desc.rows << " " << desc.cols);*/
      /*std::cout << "Desc = "<< std::endl << " "  << desc << std::endl << std::endl;*/
      desc.copyTo(*descriptors);
  /*    cv::imshow("MeanRays Descriptors", img);*/
      /*cv::waitKey(1000);*/

    }
} // namespace feature_evaluation
