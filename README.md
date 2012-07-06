My robot is based on [Adventure Bot](https://docs.google.com/file/d/0B__O096vyVYqZWRlMTgxYTEtYjY4MS00NWY5LWE4YmQtZGU5MDI4MWZhYjdi/edit?hl=en_US) with bluetooth module for connect with PC.

## About

![Robot](https://lh5.googleusercontent.com/-3gIiLsbn1LA/T-CnyL-0LXI/AAAAAAAAAWI/wOgKotbTDMQ/s721/bot.png "Robot")

## Features

### Bluethooth module

I have used two spear discrete pins (RX,TX) to connect with bluetooth module. For info
about the module see [here](http://www.pial.net/post/Using-the-HC-05-Bluetooth-RS232-Serial-module-for-cheap-wireless-communication-with-your-uController.aspx).

### ModBus 

The bot supports ModBus-RTU protocol for access to peripheries on level of bluetooth. You can use only
modbus function: 0x3, 0x6, 0x10.

####ModBus map

| Address | Access  | Item        | Description                 |
|--------:|--------:|:------------|:----------------------------|
| 0x0000  | read    |   ir_left   | Raw ADC of left IR          |
| 0x0001  | read    |   ir_right  | Raw ADC of right IR         |
| 0x0002  | read    |   ir_top    | Raw ADC of top IR           |
| 0x0003  | read    |   ir_bottom | Raw ADC of bottom IR        |
| 0x0004  | r\w     |   pan_angle | Angle of pan joint of head  |
| 0x0005  | r\w     |   tilt_angle| Angle of tilt joint of head |


### The Player driver

You can use the bot with the [Player server](http://playerstage.sourceforge.net/) 

Currently the robot provides interface:

  1. *aio* for IRs

## How to use

You must have on your machine:
  1. Arduino IDE
  2. CMake
  3. Player server
  4. [libmodbus](http://www.libmodbus.org/)
  5. Git

Getting start:

  ```sh
    $ git clone https://github.com/flipback/adventure-bot
    $ cd adventure-bot/
    $ mkdir build
    $ cd build/
    $ cmake ..
    $ make
    $ make upload # Load frimware to bot
    $ cd player-driver/
    $ player bot.cfg  # Run the Player server
  ```

Now you can access to bot by player client libraries. For Ruby boys:

  ```ruby
    require 'ruby-player'

    Player::Client "localhost" do |cl|
      aio = cl.aio
      
      c.loop(0.1) do
        puts aio.voltages.inspect
      end
    end
    
