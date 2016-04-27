[![SI7015](SI7015_I2CS.png)](https://www.controleverything.com/content/Temperature?sku=SI7015_I2CS)
# SI7015
SI7015 Humidity and Temperature Sensor

The SI7015 is a Humidity and Temperature Sensor.

This Device is available from ControlEverything.com [SKU: SI7015_I2CS]

https://www.controleverything.com/content/Temperature?sku=SI7015_I2CS

This Sample code can be used with Raspberry pi.

## Java
Download and install pi4j library on Raspberry pi. Steps to install pi4j are provided at:

http://pi4j.com/install.html

Download (or git pull) the code in pi.

Compile the java program.
```cpp
$> pi4j SI7015.java
```

Run the java program.
```cpp
$> pi4j SI7015
```

## Python
Download and install smbus library on Raspberry pi. Steps to install smbus are provided at:

https://pypi.python.org/pypi/smbus-cffi/0.5.1

Download (or git pull) the code in pi. Run the program.

```cpp
$> python SI7015.py
```

#####The code output is the relative humidity and temperature reading in degree celsius and fahrenheit.
