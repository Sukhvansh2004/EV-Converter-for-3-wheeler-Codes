#include <ros.h>
#include <sensor_msgs/Imu.h>
#include "SparkFun_ISM330DHCX.h"

SparkFun_ISM330DHCX myISM;

const double factor = 9.80665 * 0.001; // Conversion factor to m/s^2
const double correction_acc_x = -0.0137 + 0.074 - 0.04; // Calibration values (adjust as needed)
const double correction_acc_y = 0.1174 + 0.054 - 0.1080;
const double correction_acc_z = -0.1766;

ros::NodeHandle_<ArduinoHardware, 2, 2, 80, 105> nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("imu_data", &imu_msg);

void setup() {
      Serial.begin(115200);
      delay(2000);
      nh.initNode();
      nh.advertise(imu_pub);
       
      while(!myISM.begin()){
            //Serial.println("Did not begin communication with ISM330DHCX.");
            delay(1);
      }
    
      // Reset the device to default settings for a clean configuration
      myISM.deviceReset();
      
      myISM.setDeviceConfig();
      myISM.setBlockDataUpdate(); // Enable block data update for efficient reading

      // Set accelerometer data rate and full scale
      myISM.setAccelDataRate(ISM_XL_ODR_26Hz); // Set output data rate (e.g., 26 Hz)
      myISM.setAccelFullScale(ISM_2g);        // Set full scale range (e.g., +/- 2 g)

      // Configure accelerometer filter for optimal performance
      myISM.setAccelFilterLP2();                // Apply low-pass filter (LP2)
      myISM.setAccelSlopeFilter(ISM_LP_ODR_DIV_20); // Set slope filter (adjust based on data rate)

      // Configure gyroscope filter (optional, uncomment if needed)
      // myISM.setGyroFilterLP1();
      // myISM.setGyroLP1Bandwidth(ISM_MEDIUM);

      // Wait for the reset to complete
      while (!myISM.getDeviceReset()) {
        //Serial.println("Resetting ISM");
        delay(1);
      }
}

void loop() {

  // Read accelerometer data from your sensor (modify for your sensor)
  sfe_ism_data_t accelData; 
  sfe_ism_data_t gyroData;
  myISM.getAccel(&accelData);
  myISM.getGyro(&gyroData);  

  imu_msg.header.stamp = nh.now();
  imu_msg.header.frame_id = "imu_link";
  imu_msg.linear_acceleration.x = accelData.xData * factor + correction_acc_x;
  imu_msg.linear_acceleration.y = accelData.yData * factor + correction_acc_y;
  imu_msg.linear_acceleration.z = accelData.zData * factor + correction_acc_x;
  imu_msg.angular_velocity.x = gyroData.xData;
  imu_msg.angular_velocity.y = gyroData.yData;
  imu_msg.angular_velocity.z = gyroData.zData;

  // Publish IMU data
  imu_pub.publish(&imu_msg);

  // Handle ROS communication
  nh.spinOnce();// Add a delay between readings (adjust as needed)
 
}