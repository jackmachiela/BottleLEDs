# BottleLEDs



This is a custom LED driver that I created(\*) for my brother's antique bottle collection.



What you'll need:

* A single 5V WS2812B addressable RGB LED strip (5m)
* 2 small trimpots - Pot 1 (A0) sets color, sweeping through the color wheel, while Pot 2 (A1) sets overall brightness (dimmer)
* a 30x70mm perfboard
* assorted male and female pin header strips
* 2-screw terminal block



Make sure the FastLED library is install via Library Manager in the Arduino IDE.





![01 - Bottle Display](https://github.com/jackmachiela/BottleLEDs/blob/main/images/01%20-%20Bottle%20Display.jpg)



I've copied and modified the 3D printfile by @hmaki for a Pefboard 70x30 case. All I did was fill in the ventilation holes, and later cut and drilled a few extra holes in it.



https://www.printables.com/model/659390-perfboard-70x30-case/files



![02 - Finished product](https://github.com/jackmachiela/BottleLEDs/blob/main/images/02%20-%20Finished%20product.JPG)



It runs on a standard Arduino Nano clone. Input is a standard USB charger, but try to aim for a high amp one, say 2.4a or higher. The code is currently set for a 3a model. The variables MAX\_BRIGHTNESS\_COLOR and MAX\_BRIGHTNESS\_WHITE should be adjusted up or down depending on your amp rating (max is 255). Use your friendly AI to adjust the code if in doubt.



A quick fritzing layout:



![03 - Perfboard 70x30](https://github.com/jackmachiela/BottleLEDs/blob/main/images/03%20-%20Perfboard%2070x30.jpg)


My soldering skills aren't great, but it all works, so "good enough":



![04 - circuit (bottom)](https://github.com/jackmachiela/BottleLEDs/blob/main/images/04%20-%20circuit%20(bottom).JPG)



This is the open case:



![05a - Open, with Nano](https://github.com/jackmachiela/BottleLEDs/blob/main/images/05a%20-%20Open%2C%20with%20Nano.JPG)



![05b - Open, without Nano](https://github.com/jackmachiela/BottleLEDs/blob/main/images/05b%20-%20Open%2C%20without%20Nano.JPG)





The tricky bit is the connector to the LED strip. I'm using standard pin headers, but I didn't want to have them accidentally disconnect, so I faced the female pin strip inwards, and bent the cable 180 degrees. This way a gently tug will actually make the connection more secure rather than less. Best solution: don't pull at the cable.



The other end of that cable is basically the end-cable from the LED strip, which is the opposite gender of the start of the strip. You'll only need one, so cut off the end one and use it for this bit.





![06a - LED connector (without brace)](https://github.com/jackmachiela/BottleLEDs/blob/main/images/06a%20-%20LED%20connector%20(without%20brace).JPG)



![06b - LED connector (with brace)](https://github.com/jackmachiela/BottleLEDs/blob/main/images/06b%20-%20LED%20connector%20(with%20brace).JPG)




Placeholder : I will add a photo of the finished design when I've installed it (after next week). 


(\*) Full disclosure: I vibe-coded this from start to finish. I've been a programmer since the mid 1980s, and have better things to do with my time. Claude is perfectly capable of a simple project like this without setting your house on fire or destroying the world. If you don't like that, go find a different project to copy.



