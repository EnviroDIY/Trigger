# Hardware for Trigger
This Trigger library can switch an Arduino output pin from high to low, from low to high, or to send a pulse of a fixed time length (i.e. low-high-low). This is often enough to operate an external device.

In many cases, additional external switching hardware may be required. Examples include:
* A latching switch, if the switch state needs to be maintained during sleep mode for the Arduino data logger, which is a common requirement.
* A contact closure switch, if the external device requires a "floating" line to be grounded, such as with an ISCO portable sampler.
* A high amperage relay switch.

Here we provide designs and documentation for the following:
* **[ISCO-Mayfly-Trigger](https://github.com/EnviroDIY/Trigger/tree/master/hardware/ISCO-Mayfly-Trigger)**
  * This latching contact closure was specifically designed to *Inhibit* and *un-Inhibit* (i.e. run) a sampling program for a [ISCO 3700 Portable Sampler](http://www.teledyneisco.com/en-us/waterandwastewater/Pages/3700-Sampler.aspx) or other [ISCO Water and Wastewater Sampler](http://www.teledyneisco.com/en-us/water-and-wastewater/samplers).
  * See https://github.com/EnviroDIY/Trigger/tree/master/hardware/ISCO-Mayfly-Trigger
