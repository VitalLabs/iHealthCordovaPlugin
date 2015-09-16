package co.vitallabs.plugin;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;
import java.util.List;


import com.jiuan.android.sdk.bp.bluetooth.BPCommManager;
import com.jiuan.android.sdk.bp.bluetooth.BPControl;
import com.jiuan.android.sdk.bp.observer_bp.Interface_Observer_BP;
import com.jiuan.android.sdk.bp.observer_comm.Interface_Observer_CommMsg_BP;
import com.jiuan.android.sdk.device.DeviceManager;

import android.app.Activity;
import android.content.Intent;
import android.content.Context;
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

import co.vitallabs.plugin.IhealthActivity;

/**
 * This class echoes a string called from JavaScript.
 */
public class Ihealth extends CordovaPlugin {

  private BPControl bpControl;
  private String TAG = "BPtest_Plugin";
  private DeviceManager deviceManager;
  private IhealthActivity iActivity;
  protected Context context;
  private CallbackContext callbackContext;

  final int IHEALTH_INITIALIZE_PLUGIN = 0;
  final int IHEALTH_IS_BP5_CUFF_AVAILABLE = 1;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP5 = 2;
  
  @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

    this.callbackContext = callbackContext;
    
    Log.i(TAG, "calling action:" + action);
    if (action.equals("pluginInitialize")) {
      this.pluginInitialize(callbackContext);
      return true;
    }

    if (action.equals("DeviceConnectForBP5")) {
      cordova.getThreadPool().execute(new Runnable() {
          this.deviceConnectForBP5(callbackContext);
      }
      
      return true;
    }

    if (action.equals("isBP5CuffAvailable")) {
      cordova.getThreadPool().execute(new Runnable() {
          this.isBP5CuffAvailable(callbackContext);
      }
      return true;
    }
        
    return false;
  }

    private void pluginInitialize(CallbackContext callbackContext) {
      callbackContext.success("Plugin Initialized");
    }

  
    private void isBP5CuffAvailable(CallbackContext callbackContext) {
    
        Log.i(TAG, "Before running the thread");
        //final long duration = args.getLong(0);
        Log.i(TAG, "isBP5CuffAvailable");
        Context context = this.cordova.getActivity().getApplicationContext();
        Log.i(TAG, "before Activity");
        Intent intent = new Intent(context, IhealthActivity.class);
        intent.putExtra("action", this.IHEALTH_IS_BP5_CUFF_AVAILABLE);
        this.cordova.startActivityForResult((CordovaPlugin) this, intent, this.IHEALTH_IS_BP5_CUFF_AVAILABLE);
      
        Log.i(TAG, "After Activity");
    
    }

    private void deviceConnectForBP5(CallbackContext callbackContext) {

        Log.i(TAG, "Before running the thread");
        //final long duration = args.getLong(0);
        Log.i(TAG, "pluginInitialize");
        Context context = this.cordova.getActivity().getApplicationContext();
        Log.i(TAG, "before Activity");
        Intent intent = new Intent(context, IhealthActivity.class);
        intent.putExtra("action", this.IHEALTH_DEVICE_CONNECT_FOR_BP5);
        this.cordova.startActivityForResult((CordovaPlugin) this, intent, this.IHEALTH_DEVICE_CONNECT_FOR_BP5);
      
        Log.i(TAG, "After Activity");
    
    }



  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent intent) {

    super.onActivityResult(requestCode, resultCode, intent);
    
    Log.i(TAG, "onActivityResult "+requestCode+" "+resultCode+" "+intent);
    Log.e(TAG, "Getting result from Activity"  + intent);
    
    int actionResult = intent.getIntExtra("action", 1);
    switch (actionResult) {
      case IHEALTH_IS_BP5_CUFF_AVAILABLE:
        Log.i(TAG, "case BP available");
        if (intent.getBooleanExtra("result", false)) {
          callbackContext.success();
        } else {
          callbackContext.error("Device not available");
        }
        break;

      case IHEALTH_DEVICE_CONNECT_FOR_BP5:
        Log.i(TAG, "deviceConnect case");
        try {
          JSONObject json = new JSONObject();
          int[] result = intent.getIntArrayExtra("result");
          json.put("SYS", result[0] + result[1]);
          json.put("DIA", result[1]);
          json.put("heartRate", result[2]);
          callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, json));
        } catch (JSONException e) {
          callbackContext.error("Error" + e.toString());
        }
        break;
    }
    
  }
}
