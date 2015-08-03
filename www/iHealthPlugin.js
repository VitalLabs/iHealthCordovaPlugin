window.ihealth = function(str, callback) {
    cordova.exec(callback, function(err) {
        callback('Nothing to echo.');
    }, "iHealthPlugin", "ihealth", [str]);
};
