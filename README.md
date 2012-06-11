My robot is based on [Adventure Bot](http://www.youtube.com/watch?v=fDeCK8lloY4) with bluethooth module for connect with PC.

### Bluethooth module

I have used two spear discrete pins (RX,TX) to connect with bluethooth module. For info
about the module see [here](http://www.pial.net/post/Using-the-HC-05-Bluetooth-RS232-Serial-module-for-cheap-wireless-communication-with-your-uController.aspx).

### ModBus 

Bot supports ModBus-RTU protocol for access to peripheries on level of bluethooth. You can use only
modbus function: 0x3, 0x6, 0x10.

####ModBus map

| Address | Access  | Item        | Description                 |
|--------:|--------:|:------------|:----------------------------|
| 0x0000  | read    |   ir_left   | Raw ADC of left IR          |
| 0x0001  | read    |   ir_right  | Raw ADC of right IR         |
| 0x0002  | read    |   ir_top    | Raw ADC of top IR           |
| 0x0003  | read    |   ir_bottom | Raw ADC of bottom IR        |

