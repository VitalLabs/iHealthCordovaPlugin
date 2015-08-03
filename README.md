iHealth Cordova plugin
====================

First attempt to have an iHealth Native API wrapper to use in a Steroids projetc
##Usage

Echoes back a text string sent to the native layer.

```
window.ihealth("echome", function(echoValue) {
    alert(echoValue == "echome"); // should alert true.
});
```
