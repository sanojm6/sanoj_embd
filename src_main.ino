#include <Arduino.h>
#include<doors.h>
#include<Blindspot.h>
#include<signals.h>
#include <brake.h>
#include<vehicle.h>
#include<vehicle_sd.h>
#include<ADC.h>
#include <J1939.h>
#include "Ip_op_defs.h"
#include <delay.h>
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN(9);                  //using MCP_CAN class creating object CAN  9 is slave select pin  in arduino

void setup()
{
  // put your setup code here, to run once:
  
      Serial.begin(9600); 
    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 500k
    { 
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    } 

    pinMode(dig_ip_4,INPUT_PULLUP);
    pinMode(DIG_IP_PIN_2,INPUT_PULLUP);
    pinMode(DIG_IP_PIN_3,INPUT_PULLUP);
    pinMode(DIG_IP_PIN_5,INPUT_PULLUP);
     
    pinMode(trig_pin,OUTPUT); //trigger pin
    pinMode(echo_pin,INPUT); // echo pin

    pinMode(DIG_OP_8,OUTPUT);
    pinMode(DIG_OP_10,OUTPUT);
    digitalWrite(DIG_OP_8,LOW);
    digitalWrite(DIG_OP_10,LOW);   
}

void loop() 
{
  
  // put your main code here, to run repeatedly:

  car_door_feature(my_vehicle);
  
  one_second_timer();

  //J1939_send_msg(00,255,0x06,0xFF13,door_msgbuf,4);

  one_second_timer();
   
  ultrasonic_sensor_working(my_vehicle);

  one_second_timer();

  //J1939_send_msg(00,255,0x06,0xFF14,ultrasonic_msg_buf,1);

  right_turn_signals(DIG_IP_PIN_3,DIG_OP_8,my_vehicle);
  
  //J1939_send_msg(00,255,0x06,0xFF15,right_turn_signal_buf,1);

  left_turn_signals(DIG_IP_PIN_2,DIG_OP_10,my_vehicle);
 
 // J1939_send_msg(00,255,0x06,0xFF16,left_turn_signal_buf,1);
  
  park_brake();
  
  one_second_timer();

  vehicle_speed_control();

  J1939_send_msg(03,255,0x06,0xFF18,status_msg_buf,2);

  //adc_speed();  
  
}

