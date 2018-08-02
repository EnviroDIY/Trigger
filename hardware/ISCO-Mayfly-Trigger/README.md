# Hardware for ISCO-Mayfly-Trigger
This latching contact closure switch was specifically designed to *Inhibit* and *un-Inhibit* (i.e. run) a sampling program for a [ISCO 3700 Portable Sampler](http://www.teledyneisco.com/en-us/waterandwastewater/Pages/3700-Sampler.aspx) or other [ISCO Water and Wastewater Sampler](http://www.teledyneisco.com/en-us/water-and-wastewater/samplers).

This design utilizes two connected [Pololu Mini Pushbutton Power Switch LV](https://www.pololu.com/product/2808) boards ($3.95 each), wired in a clever way modified from an [original design by Bobby Schulz](https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/BobbbyOriginalDesign_ISCO_Trigger_5-4-2018.pdf).

### Description of latching contact closure setup

**Figure 1** shows the complete setup, with the Mayfly connected to the grove ports on the left and the ISCO connected on the right via the ISCO's white (pin B) common/ground wire and the ISCO's red (pin F) inhibit wire.

<img src="https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/IMG_6770_ISCO-Mayfly-Trigger.JPG"  width="600">

Figure 1 Notes:
- The Grove connectors on the Mayfly are split in order to access Mayfly pin D7, which sends the trigger pulse signal, and also to access constant 3.3V power from the D4-5 Grove port. NOTE that this setup requires constant power, not switching power.
- An ISCO sampler program will be "Inhibited" as long as pin F, which floats at ~5V, is grounded to pin B, according to the the [ISCO Sampler/Flowmeter Connector Pigtail product sheet](https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/ISCO-PigtailPinWiring.pdf) and the [ISCO 3700 Portable Sampler User Manual](https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/3700%20Portable%20Sampler%20User%20Manual.pdf) (pages 3-106 to 3-107).


**Figure 2** shows the details for connects on Switch 1 (Fig. 2A), Switch 2 (Fig. 2B) and the pinouts for the [Pololu Mini Pushbutton Power Switch LV] (Fig. 2C).

| <img src="https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/IMG_6773_ISCO-Mayfly-Trigger-Switch1.JPG"  height="200"> | <img src="https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/IMG_6772_ISCO-Mayfly-Trigger-Switch2.JPG"  height="200"> | <img src="https://a.pololu-files.com/picture/0J6761.1200.jpg?a49cd139840f29608e58b4b0a77dd58f"  height="200"> |

Figure 2 Notes, with description of hardware behavior:
- Switch 1 is manually set to ON using the pushbutton and indicated by the red LED light glowing. The Mayfly turns Switch 1 OFF by sending a 3.3V pulse to the OFF pin (shown here via the white wire).
- Switch 2 is turned OFF when Switch 1 is turned ON, via a connection from Switch 1 Vout to Switch 2 OFF pins (shown here via the yellow wire). 
  - When Switch 2 is OFF, its CTRL pin is grounded, which when wired to ISCO Pin F (red wire in pigtail connector) will ***Inhibit*** the ISCO program from running.
  - When Switch 2 is ON, its CTRL pin floats, which when wired to ISCO Pin F with an ***inline 5.1k ohm resistor*** (faintly visible here within the shown red crimp connector), will *un-inhibit* the ISCO program, letting it run. 
  - NOTE: Switch 2 will only automatically turn ON (when Switch 1 turns OFF) if there is a positive float voltage (>1V) applied to CTRL, such as when wired to a powered ISCO (which floats at 5V).
  

  ### Instructions for use with ISCO
  
Configure ISCO
- Configuration is all “defaults” (i.e. “NO” for all Enable Pin settings)
  - Except: set Start Time Delay = 0 min

Program ISCO
- Follow “Example: Time-Paced Sequential Sampling” on pages 3-26 to 3-27 in [ISCO 3700 Portable Sampler User Manual](https://github.com/EnviroDIY/Trigger/blob/master/hardware/ISCO-Mayfly-Trigger/3700%20Portable%20Sampler%20User%20Manual.pdf)
  - Enter Start Time? select NO

Inhibit ISCO
- Manually toggle Switch 1 pushbutton to ON, so red LED glows
  - Switch 2 will turn OFF, ISCO Pin F will be grounded, which will Inhibit any ISCO program

Start ISCO time-based program, while it is “disabled” (Pin F is grounded)
- Set ISCO to “Start Sampling” using a program
- The ISCO will immediately display: “Sampler Inhibited!”, if Start Time Delay = 0 min (in Configuration)

Un-Inhibit ISCO, to let program run
- Turn Switch 1 OFF, which will turn Switch 2 ON and allow ISCO Pin F to float
  - Preferably done automatically using Trigger software on Mayfly
  - Can also be done manually using the Switch 1 pushbutton
- NOTE: Switch 1 must remain OFF for the entire Sampling Program to complete filling all bottles
  - A user can manually PAUSE a program by toggling Switch 1 ON in the middle of a program run, however, the ISCO will only display "Sampler Inhibited" when it is time to fill the next bottle.

 
### Developer Notes

I discovered through trial and error that the floating voltage of ISCO Pin F:
- dropped from 4.95V to 1.96V when connected to the CTRL pin of Switch 2 (while Switch 2 is ON)
- must drop to below ~2.0V to "Inhibit"
- must rise to above ~2.6V to let ISCO run

I found that I had to insert a 5.1k ohm resistor inline with ISCO Pin F (red wire) to properly Inhibit and un-Inhibit the ISCO. Here are results from my trial and error tests.

| Pin F inline resistor (kOhm) | Pin F Volts when OFF | Re-Inhibit ISCO? | Pin F Volts when ON | Trigger ISCO? |
| --- | --- | --- | --- | --- |
| none | 0.018 | YES | 1.96 | NO |
| 3.3 | 1.260 | YES | 2.535 | NO |
| 4.7 | 1.536 | YES | 2.678 | YES |
| 5.1 | 1.706 |  YES |2.766 | YES |
| 6.8 | 2.042 | NO | 2.945 | YES |
| 10 | 2.525 | NO | 3.25 | YES |

I also found that if I inserted my own 5V pullup to this circuit, to get a clean jump from 0V to 5V, that it didn't trigger the ISCO. In other words, I really needed it to passively "float".
