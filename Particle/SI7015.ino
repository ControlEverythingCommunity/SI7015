// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SI7015
// This code is designed to work with the SI7015_I²CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=SI7015_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// SI7015 I2C address is 0x40(64)
#define Addr 0x40

double cTemp = 0.0, fTemp = 0.0, humidity = 0.0;
int temp = 0;

void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "SI7015");    
    Particle.variable("humidity", humidity);
    Particle.variable("cTemp", cTemp);
    
    // Initialise I²C communication as Master
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
    Serial.begin(9600);
    delay(300);
}

void loop()
{
    unsigned int data[3];
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select configuration register
    Wire.write(0x03);
    // Command for temperature measurement
    Wire.write(0x11);
    // Stop I²C transmission
    Wire.endTransmission();
    delay(300);
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x00);
    // Stop I²C transmission
    Wire.endTransmission();
    
    Wire.requestFrom(Addr, 1); 
    
    // Read 1 byte of data
    // Status
    if(Wire.available() == 1)
    {
        data[0] = Wire.read();
    }
    
    while((data[0] & 0x01) != 0)
    {
        // Start I²C transmission
        Wire.beginTransmission(Addr);
        // Select data register
        Wire.write(0x00);
        // Stop I²C transmission
        Wire.endTransmission();
        
        Wire.requestFrom(Addr, 1); 
        
        // Read 1 byte of data
        // Status
        data[0] = Wire.read();
    }
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x01);
    // Stop I²C transmission
    Wire.endTransmission();
    
    Wire.requestFrom(Addr, 2); 
    
    
    // Read 2 bytes of data
    // temp msb, temp lsb
    if(Wire.available() == 2)
    {
        data[1] = Wire.read();
        data[2] = Wire.read();
    }
 
    // Convert the data to 14-bits
    temp = ((data[1] * 256) + (data[2] & 0xFC)) / 4;
    cTemp = (temp / 32.0) - 50.0;
    fTemp = cTemp * 1.8 + 32;
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select configuration register
    Wire.write(0x03);
    // Command for humidity measurement
    Wire.write(0x01);
    // Stop I²C transmission
    Wire.endTransmission();
    delay(800);
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x00);
    // Stop I²C transmission
    Wire.endTransmission();
    
    Wire.requestFrom(Addr, 1); 
    
    // Read 1 byte of data
    // Status
    if(Wire.available() == 1)
    {
        data[0] = Wire.read();
    }
        
    while((data[0] & 0x01) != 0)
    {
        // Start I²C transmission
        Wire.beginTransmission(Addr);
        // Select data register
        Wire.write(0x00);
        // Stop I²C transmission
        Wire.endTransmission();
        
        Wire.requestFrom(Addr, 1); 
        
        // Read 1 byte of data
        data[0] = Wire.read();
    }
    
    // Start I²C transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x01);
    // Stop I²C transmission
    Wire.endTransmission();
    
    Wire.requestFrom(Addr, 2); 
    
    // Read 2 bytes of data
    // humidity msb, humidity lsb
    if(Wire.available() == 2)
    {
        data[1] = Wire.read();
        data[2] = Wire.read();
    }
    
    // Convert the data to 12-bits
    humidity = ((data[1] * 256) + (data[2] & 0xF0)) / 16;
    humidity = (humidity / 16) - 24;
    
    // Output data to dashboard 
    Particle.publish("Temperature in Celsius : ", String(cTemp));
    delay(1000);
    Particle.publish("Temperature in Celsius : ", String(fTemp));
    delay(1000);
    Particle.publish("Humidity is : ", String(humidity));
    delay(1000);
}

