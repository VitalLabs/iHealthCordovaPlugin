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

##Before Usage

 - Make sure that you are registered on: https://developer.ihealthlabs.com
 - Register an app on iHealth developer portal and add capability to use the Android/iOS SDK

##Usuage
 - Remember to include the iHealthPlugin.js into your index.html

```html
<script src="http://localhost/plugins/iHealthPlugin.js"></script>

Echoes back a text string sent to the native layer.

```

 - On your app boostrap process you will need to call *once* the initialize function before using other API Cordova functions.

```javascript
window.pluginInitialize(successCallback, errorCallback);

=> Plugin Initialized
```

```
window.ihealth("echome", function(echoValue) {
    alert(echoValue == "echome"); // should alert true.
});
```
