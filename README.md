iHealth Cordova plugin
====================

This cordova plugin provides a set of Cordova API functions to interact with iHealth Blood Pressure Control.

###Limitations
Supported devices:
 - BP5
 - BP7

Supported Platforms
 - Android 4.0+
 - iOS 8.0+

Tested only on a Appgyver Steroids project.

Device must be paired with the phone before being able to retrive info from it.

##Before Usage

 - Make sure that you are registered on: https://developer.ihealthlabs.com
 - Register an app on iHealth developer portal and add capability to use the Android/iOS SDK

##Usage
 - Remember to include the iHealthPlugin.js into your index.html

```html
<script src="http://localhost/plugins/iHealthPlugin.js"></script>

```

 - On your app boostrap process you will need to call *once* the initialize function before using other API Cordova functions.

```javascript
window.pluginInitialize(successCallback, errorCallback);

=> Plugin Initialized
```

After calling pluginInitalize you can use the rest of the plugin functions.

##API

This plugin exposes two different types of functions:
 - Functions for checking if there are available devices, usually you will only use `isAnyCuffAvailable` to scan for any of the supported devices paired with the phone. 
  - isBP5CuffAvailable (only for BP5 cuffs)
  ```javascript
  window.isBP5CuffAvailable(successCallback, errorCallback);
  => true // if cuff available
  => false // if the scan couldn't find a valid devices paired
  ```
  - isBP7CuffAvailable (only for BP7 cuffs)
  ```javascript
  window.isBP7CuffAvailable(successCallback, errorCallback);
  => true // if cuff available
  => false // if the scan couldn't find a valid devices paired
  ```
  - isAnyCuffAvailable (could detect both BP5 and BP7 devices)
  ```javascript
  window.isAnyCuffAvailable(successCallback, errorCallback);
  => true // if cuff available
  => false // if the scan couldn't find a valid devices paired
  ```
 - If any of above functions return a success callback, the Cordova app can use any of the following functions to retrieve blood pressure measure data. If you don't care about the device type you should only use `window.AnyDeviceConnect`.
  - window.DeviceConnectForBP5 (only for BP5 cuffs)
  ```javascript
  window.DeviceConnectForBP5(successCallback, errrorCallback);
  => {DIA: 120, SYS: 80, heartRate 95} // if success
  => false //if error occurred while taking the measure
  ```
  - window.DeviceConnectForBP7 (only for BP7 cuffs)
  ```javascript
  window.DeviceConnectForBP7(successCallback, errrorCallback);
  => {DIA: 120, SYS: 80, heartRate 95} // if success
  => false //if error occurred while taking the measure
  ```
  - window.AnyDeviceConnect (Both BP5 and BP7, takes more priority a BP5 Cuff)
  ```javascript
  window.DeviceConnectForBP5(successCallback, errrorCallback);
  => {DIA: 120, SYS: 80, heartRate 95} // if success
  => false //if error occurred while taking the measure
  ```

Usually you will first see if there's a BPControl device connected to the device before calling a connect function.

If paired with a BP7 and using either window.AnyDeviceConnect or window.DeviceConnectForBP7 the measure will start if and only if the cuff is between 10 ans 30 degrees from the horizontal table. For more info about taking a valid measure please see the devices manual.
