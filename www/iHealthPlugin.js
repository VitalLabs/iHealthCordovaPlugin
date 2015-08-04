window.ihealth = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to echo.');
    }, "iHealthPlugin", "ihealth", [str]);
};

window.DeviceConnectForBP7 = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to echo.');
    }, "iHealthPlugin", "DeviceConnectForBP7", []);
};

window.initplugin = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to echo.');
    }, "iHealthPlugin", "initplugin", []);
};

