package co.vitallabs.plugin;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import com.jiuan.android.sdk.bp.bluetooth.BPCommManager;
import com.jiuan.android.sdk.bp.bluetooth.BPControl;
import com.jiuan.android.sdk.bp.observer_bp.Interface_Observer_BP;
import com.jiuan.android.sdk.device.DeviceManager;

//import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This class echoes a string called from JavaScript.
 */
public class IHealth extends CordovaPlugin implements Interface_Observer_BP {

  private BPControl bpControl;
	private String TAG = "BPtest_MainActivity";
  private String mAddress;
	private DeviceManager deviceManager;

  
  @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (action.equals("pluginInitialize")) {
            String message = args.getString(0);
            this.pluginInitialize(message, callbackContext);
            return true;
        }

        if (action.equals("deviceConnectForBP5")) {
            this.deviceConnectForBP5(callbackContext);
            return true;
        }
        
        return false;
    }

    private void pluginInitialize(String message, CallbackContext callbackContext) {
        if (message != null && message.length() > 0) {
            callbackContext.success(message);
        } else {
            callbackContext.error("Expected one non-empty string argument.");
        }
    }

  
  

    private void deviceConnectForBP5(CallbackContext callbackContext) {

      bpControl = deviceManager.getBpDevice(mAddress);

      mAddress = getIntent().getStringExtra("mac");
      Log.i("mAddress", "mAddress:" + mAddress);
      deviceManager = DeviceManager.getInstance();


      String clientID =  "bbcb0a015545402c8c5683b485009045";
      String clientSecret = "278702abdb2041d0bcc0e7b1bbc43b86";
      bpControl.start(this, clientID, clientSecret);

      if (message != null && message.length() > 0) {
        callbackContext.success(message);
      } else {
        callbackContext.error("Expected one non-empty string argument.");
      }
    }
}
