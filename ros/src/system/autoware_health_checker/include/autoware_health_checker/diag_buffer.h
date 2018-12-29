#ifndef DIAG_BUFFER_H_INCLUDED
#define DIAG_BUFFER_H_INCLUDED

//headers in Autoare
#include <autoware_health_checker/constants.h>
#include <autoware_system_msgs/DiagnosticStatus.h>

//headers in STL
#include <vector>
#include <string>
#include <map>
#include <mutex>

//headers in ROS
#include <ros/ros.h>

namespace autoware_health_checker
{
    class DiagBuffer
    {
    public:
        DiagBuffer(std::string key,uint8_t type,std::string description,double buffer_length);
        ~DiagBuffer();
        void addDiag(autoware_system_msgs::DiagnosticStatus status);
        std::vector<autoware_system_msgs::DiagnosticStatus> getAndClearData();
        const uint8_t type;
        const std::string description;
    private:
        std::mutex mtx_;
        uint8_t getErrorLevel();
        void updateBuffer();
        std::string key_;
        ros::Duration buffer_length_;
        std::map<uint8_t,std::vector<autoware_system_msgs::DiagnosticStatus> > buffer_;
        std::vector<autoware_system_msgs::DiagnosticStatus> filterBuffer(ros::Time now, uint8_t level);
        ros::Publisher status_pub_;
    };
}

#endif  //DIAG_BUFFER_H_INCLUDED