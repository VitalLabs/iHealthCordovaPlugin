window.ihealth = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to echo.');
    }, "iHealthPlugin", "ihealth", [str]);
};

window.DeviceConnectForBP7 = function(callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to Connecting. ' + err);
    }, "iHealthPlugin", "DeviceConnectForBP7", []);
};

window.isBP7CuffAvailable = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "isBP7CuffAvailable", []);
};


window.pluginInitialize = function(callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to init. ' + err);
    }, "iHealthPlugin", "pluginInitialize", []);
};

