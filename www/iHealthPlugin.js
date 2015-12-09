window.ihealth = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "ihealth", [str]);
};

window.DeviceConnectForBP7 = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "DeviceConnectForBP7", []);
};

window.isBP7CuffAvailable = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "isBP7CuffAvailable", []);
};

window.DeviceConnectForBP5 = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "DeviceConnectForBP5", []);
};

window.isBP5CuffAvailable = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "isBP5CuffAvailable", []);
};

window.AnyDeviceConnect = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "AnyDeviceConnect", []);
};

window.isAnyCuffAvailable = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "isAnyCuffAvailable", []);
};

window.pluginInitialize = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "pluginInitialize", []);
};

window.cleanPluginState = function(callback) {
    cordova.exec(callback, function(err) {
        callback(err);
    }, "iHealthPlugin", "cleanPluginState", []);
};

