/* Canonical definition of device addresses on the RocketNet
 * This file should be synched across all projects that want
 * to connect to the RocketNet
 */
#ifndef NET_ADDRS_H_
#define NET_ADDRS_H_
#include <netinet/in.h>

#ifdef FCF_FC_NETWORK
#define RNH_IP    IPv4(10,10,10,5)
#define FC_IP     IPv4(10,10,10,10)
#define SENSOR_IP IPv4(10,10,10,20)
#define ROLL_IP   IPv4(10,10,10,30)
#define GPS_IP    IPv4(10,10,10,40)
#define WIFI_IP   IPv4(172,17,0,2)

#else
#define RNH_IP    IPv4(127,0,0,1)
#define FC_IP     IPv4(127,0,0,1)
#define SENSOR_IP IPv4(127,0,0,1)
#define ROLL_IP   IPv4(127,0,0,1)
#define GPS_IP    IPv4(127,0,0,1)
#define WIFI_IP   IPv4(127,0,0,1)
#endif


/* RCI */
#define RCI_PORT 23
extern const struct sockaddr * RCI_ADDR;
extern const struct sockaddr * RNH_RCI_ADDR;
extern const struct sockaddr * SENSOR_RCI_ADDR;
extern const struct sockaddr * GPS_RCI_ADDR;
extern const struct sockaddr * ROLL_RCI_ADDR;

/* Rocket Net Hub */
#define RNH_BATTERY 36101 // Battery data
#define RNH_PORT 36102    // Port data
#define RNH_ALARM 36103   // Battery alarm
#define RNH_UMBDET 36104  // Umbilical detect
extern const struct sockaddr * RNH_BATTERY_ADDR;
extern const struct sockaddr * RNH_PORT_ADDR;
extern const struct sockaddr * RNH_ALARM_ADDR;
extern const struct sockaddr * RNH_UMBDET_ADDR;

/* Flight Computer */
#define FC_LISTEN_PORT 36000 // FC device listener
#define FCF_HEALTH_PORT 36201 // FC health monitor
extern const struct sockaddr * FC_ADDR;

/* Sensor Node */
#define ADIS_PORT 35020 // ADIS16405
#define MPU_PORT 35002  // MPU1950
#define MPL_PORT 35010  // MPL3115A2
#define BMP_PORT 35011  // BMP180
extern const struct sockaddr * ADIS_ADDR;
extern const struct sockaddr * MPU_ADDR;
extern const struct sockaddr * MPL_ADDR;
extern const struct sockaddr * BMP_ADDR;

/* Roll Control */
#define ROLL_PORT 35003    // Servo control
extern const struct sockaddr * ROLL_ADDR;

/* WiFi */
#define WIFI_PORT 35001
extern const struct sockaddr * WIFI_ADDR;

/* ARM Signal */
#define ARM_IP IPv4(127,0,0,1)
#define ARM_PORT 35666
#define RC_SERVO_ENABLE_PORT 35667
extern const struct sockaddr * ARM_ADDR;
extern const struct sockaddr * RC_SERVO_ENABLE_ADDR;

#define JGPS_PORT 35050

#define GPS_COTS 35051
extern const struct sockaddr * GPS_COTS_ADDR;

#endif /* NET_ADDRS_H_ */
