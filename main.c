#include "mavlink.h"        // Mavlink interface
#include "mavlink_msg_distance_sensor.h"
#include "SonarEZ0pw.h"
void command_heartbeat();
void command_distance_1();

SonarEZ0pw Sonar(8); // pin D7
float value=0.00;

const int MIN = 30;
const int MAX = 300;

/*
Valid values are (even numbers only):
Pre: 12 to 18 (initialized to 14 by default)
Final: 8 to 14 (initialized to 10 by default)
*/
//const int PreRng = 18;  
//const int PostRng = 14;

//const int Scale = 10;


void setup()
{ 
  Serial.begin(57600);
  
}


void loop() {

  command_heartbeat();
  command_distance_1();
}

void command_heartbeat() {

  //< ID 1 for this system
  int sysid = 100;                   
  //< The component sending the message.
  int compid = MAV_COMP_ID_PATHPLANNER;    
  
  // Define the system type, in this case ground control station
  uint8_t system_type =MAV_TYPE_GCS;
  uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;
  
  uint8_t system_mode = 0; 
  uint32_t custom_mode = 0;                
  uint8_t system_state = 0;
  
  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  
  // Pack the message
  mavlink_msg_heartbeat_pack(sysid,compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);
  
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the message 
  //delay(1);
  Serial.write(buf, len);
}


void command_distance_1() {

  float dist1 = Sonar.Distance(cm);
  dist1 = constrain(dist1, MIN , MAX);


  //MAVLINK DISTANCE MESSAGE
  int sysid = 1;                   
  //< The component sending the message.
  int compid = 158;    

  uint32_t time_boot_ms = 0; /*< Time since system boot*/
  uint16_t min_distance = 1; /*< Minimum distance the sensor can measure in centimeters*/
  uint16_t max_distance = 170; /*< Maximum distance the sensor can measure in centimeters*/
  uint16_t current_distance = dist1; /*< Current distance reading*/
  uint8_t type = 0; /*< Type from MAV_DISTANCE_SENSOR enum.*/
  uint8_t id = 1; /*< Onboard ID of the sensor*/
  uint8_t orientation = 0; /*(0=forward, each increment is 45degrees more in clockwise direction), 24 (upwards) or 25 (downwards)*/
// Consumed within ArduPilot by the proximity class

  uint8_t covariance = 0;


  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
 mavlink_msg_distance_sensor_pack(sysid,compid,&msg,time_boot_ms,min_distance,max_distance,current_distance,type,id,orientation,covariance);

  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  // Send the message (.write sends as bytes) 
  //delay(1);
  Serial.write(buf, len);
}



