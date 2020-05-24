#include <Wire.h>
#include "GY80.h"
//#include "MadgwickAHRS.h"
#include "MahonyAHRS.h"

GY80 sensor = GY80(); //create GY80 instance
//Madgwick filter = Madgwick();
Mahony filter;
float roll , pitch, yaw;
void setup()
{
    // initialize serial communication at 115200 bits per second:
    Serial.begin(115200);
    sensor.begin();       //initialize sensors
    filter.begin(50.0f);
} 


void loop()
{
    GY80_scaled val = sensor.read_scaled();       //get values from all sensors
    
    //MahonyAHRSupdateIMU(val.g_x,val.g_y,val.g_z,val.a_x,val.a_y,val.a_z);
    filter.updateIMU(val.g_x, val.g_y, val.g_z, val.a_x, val.a_y, val.a_z);
    //roll = filter.getRoll();
    //pitch = filter.getPitch();
    //yaw = filter.getYaw();
    //q0, q1, q2, q3;
     //yaw   = atan2(2.0f * (q1 * q2 + q0 *q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3);
     //pitch = -asin(2.0f * (q1 * q3 - q0 *q2));
     //roll = atan2(2.0f * (q0 * q1 +q2 * q3), q0 * q0 - q1 * q1 -q2 *q2 + q3 * q3);
     pitch = filter.getPitch();
     roll  = filter.getRoll();
    Serial.println(roll);
    Serial.println(pitch);
    //Serial.println(yaw);
    delay(1);        // delay in between reads for stability
}
