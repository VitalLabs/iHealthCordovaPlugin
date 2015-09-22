package co.vitallabs.plugin;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;
import java.util.List;

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

// import co.vitallabs.plugin.IhealthActivity;
import co.vitallabs.plugin.IhealthDeviceManagerActivity;
import co.vitallabs.plugin.IhealthBP5Activity;

/**
 * This class echoes a string called from JavaScript.
 */
public class Ihealth extends CordovaPlugin {

  private String TAG = "BPtest_Plugin";
  protected Context context;
  private CallbackContext callbackContext;
  
  final int IHEALTH_INITIALIZE_PLUGIN = 0;
  final int IHEALTH_IS_BP5_CUFF_AVAILABLE = 1;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP5 = 2;

  private boolean isCuffAvailable;
  private boolean isTakingMeasure;
  private boolean isChecking;
  private String mac;
  
  @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

    this.callbackContext = callbackContext;
    
    Log.i(TAG, "calling action:" + action);
    if (action.equals("pluginInitialize")) {
      Log.i(TAG, "Var isCuffAvailable " + isCuffAvailable + " - " +isTakingMeasure);
      this.pluginInitialize(callbackContext);
      return true;
    }

    if (action.equals("DeviceConnectForBP5")) {
      isTakingMeasure = true;
      this.deviceConnectForBP5(callbackContext);
      
      return true;
    }

    if (action.equals("isBP5CuffAvailable")) {
       
      Log.i(TAG, "Var isCuffAvailable " + isCuffAvailable+ " - " +isTakingMeasure);
      if (!isTakingMeasure && !isCuffAvailable && !isChecking) {
        isBP5CuffAvailable(callbackContext);
      } else {
        callbackContext.success();
      }
      return true;
    }
        
    return false;
  }

    private void pluginInitialize(CallbackContext callbackContext) {
      callbackContext.success("Plugin Initialized");
      isCuffAvailable = false;
      isTakingMeasure = false;
      isChecking = false;
    }

  
    private void isBP5CuffAvailable(CallbackContext callbackContext) {
      
      if (!isChecking) {
        final CordovaPlugin plugin = (CordovaPlugin) this;
        cordova.getThreadPool().execute(new Runnable() {
          @Override
          public void run () {
            isChecking = true;
            Log.i(TAG, "Before running the thread");
            //final long duration = args.getLong(0);
            cordova.setActivityResultCallback(plugin);
            Log.i(TAG, "isBP5CuffAvailable" + " - " +isTakingMeasure);
            Context context = plugin.cordova.getActivity().getApplicationContext();
            Log.i(TAG, "before Activity");
            Intent intent = new Intent(context, IhealthDeviceManagerActivity.class);
            // intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_MULTIPLE_TASK);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            intent.putExtra("action", IHEALTH_IS_BP5_CUFF_AVAILABLE);

            if (mac != null && !mac.equals("")) {
              Log.i(TAG, "We already have a device? " + mac);
              intent.putExtra("checkForDevice", true);
              intent.putExtra("predefinedMac", mac);
            } else {
              intent.putExtra("checkForDevice", false);
            }

            plugin.cordova.startActivityForResult(plugin, intent, IHEALTH_IS_BP5_CUFF_AVAILABLE);
            
            Log.i(TAG, "After Activity");
          }
        });
      } else {
        Log.i(TAG, "is already checking our monitor...");
      }
      
    }

    private void deviceConnectForBP5(CallbackContext callbackContext) {
      final CordovaPlugin plugin = (CordovaPlugin) this;
      
      cordova.getActivity().runOnUiThread(new Runnable() {
          @Override
          public void run () {
            Log.i(TAG, "Var isCuffAvailable " + isCuffAvailable + " - " +isTakingMeasure);
            cordova.setActivityResultCallback(plugin);
            Log.i(TAG, "Before running the thread");
            //final long duration = args.getLong(0);
            Log.i(TAG, "pluginInitialize");
            Context context = plugin.cordova.getActivity().getApplicationContext();
            Log.i(TAG, "before Activity");
            Intent intent = new Intent(context, IhealthBP5Activity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            intent.putExtra("action", IHEALTH_DEVICE_CONNECT_FOR_BP5);
            intent.putExtra("mAddress", mac);
            plugin.cordova.startActivityForResult(plugin, intent, IHEALTH_DEVICE_CONNECT_FOR_BP5);
      
            Log.i(TAG, "After Activity");
            }
        });
      
    }


  private String bpGetErrorMessage (int errorCode) {
    String errorMessage = "Unknown Error";

    switch (errorCode) {
      case 0:
        errorMessage = "Pressure system is unstable before measurement";
        break;
      case 1:
        errorMessage = "Fail to detect systolic pressure";
        break;
      case 2:
        errorMessage = "Fail to detect diastolic pressure";
        break;
      case 3:
        errorMessage = "Pneumatic system blocked or cuff is too tight during inflation";
        break;
      case 4:
        errorMessage = "Pneumatic system leakage or cuff is too loose during inflation";
        break;
      case 5:
        errorMessage = "Cuff pressure above 300mmHg";
        break;
      case 6:
        errorMessage = "More than 160 seconds with cuff pressure above 15 mmHg";
        break;
      case 7:
        errorMessage = "EEPROM accessing error";
        break;
      case 8:
        errorMessage = "Device parameter checking error";
        break;
      case 9:
        errorMessage = "Span Error";
        break;
      case 10:
        errorMessage = "Span Error";
        break;
      case 11:
        errorMessage = "N/A 11";
        break;
      case 12:
        errorMessage = "Communication error";
        break;
      case 13:
        errorMessage = "Low Battery";
        break;
      case 15:
        errorMessage = "Systolic exceeds 260mmHg or diastolic exceeds 199mmHg";
        break;
      case 16:
        errorMessage = "Systolic below 60mmHg or diastolic below 40mmHg";
        break;
      case 17:
        errorMessage = "Arm/wrist movement beyond range";
        break;
      case 18:
        errorMessage = "N/A 18";
        break;
    }

    return errorMessage;
  }

  private void resetPluginState() {
    isTakingMeasure = false;
    isCuffAvailable = false;
    isChecking = false;
    // xsmac = null;
  }
  
  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent intent) {

    super.onActivityResult(requestCode, resultCode, intent);
    
    Log.i(TAG, "onActivityResult "+requestCode+" "+resultCode+" "+intent);
    Log.e(TAG, "Getting result from Activity"  + intent);
    
    int actionResult = intent.getIntExtra("action", 1);
    switch (actionResult) {
      case IHEALTH_IS_BP5_CUFF_AVAILABLE:
        Log.i(TAG, "case BP available with mac:" + intent.getStringExtra("result"));
        if (resultCode == Activity.RESULT_OK) {
          isCuffAvailable = true;
          mac =  intent.getStringExtra("result");
          this.callbackContext.success();
        } else {
          isCuffAvailable = false;
          isChecking = false;
          mac = null;
          this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
        }
        break;

      case IHEALTH_DEVICE_CONNECT_FOR_BP5:
        Log.i(TAG, "deviceConnect case result");
        if (resultCode == Activity.RESULT_OK) {
          try {
            Log.i(TAG, "Success!!!");
            JSONObject json = new JSONObject();
            int[] result = intent.getIntArrayExtra("result");
            json.put("SYS", result[0] + result[1]);
            json.put("DIA", result[1]);
            json.put("heartRate", result[2]);
            resetPluginState();
            this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, json));
          } catch (JSONException e) {
            resetPluginState();
            this.callbackContext.error("Error" + e.toString());
          }
        } else {
          int errorCode = intent.getIntExtra("error", -1);
          resetPluginState();
          Log.e(TAG, "Error: " + bpGetErrorMessage(errorCode));
          this.callbackContext.error("Error: " + bpGetErrorMessage(errorCode));
        }
        
        break;
    }
    
  }
}
