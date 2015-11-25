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
import co.vitallabs.plugin.IhealthBP7Activity;

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

  final int IHEALTH_IS_BP7_CUFF_AVAILABLE = 3;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP7 = 4;

  final int IHEALTH_IS_ANY_CUFF_AVAILABLE = 5;
  final int IHEALTH_BP5 = 6;
  final int IHEALTH_BP7 = 7;
  final int UNKNOWN_DEVICE = 8;

  
  private boolean isCuffAvailable;
  private boolean isTakingMeasure;
  private boolean isChecking;
  private String mac;
  private int deviceType;

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
        isAnyCuffAvailable(callbackContext);
      } else {
        callbackContext.success();
      }
      return true;
    }

    if (action.equals("DeviceConnectForBP7")) {
      isTakingMeasure = true;
      this.deviceConnectForBP7(callbackContext);
      
      return true;
    }

    if (action.equals("isBP7CuffAvailable")) {
       
      Log.i(TAG, "Var isCuffAvailable " + isCuffAvailable+ " - " +isTakingMeasure);
      if (!isTakingMeasure && !isCuffAvailable && !isChecking) {
        isAnyCuffAvailable(callbackContext);
      } else {
        callbackContext.success();
      }
      return true;
    }

    if (action.equals("isAnyCuffAvailable")) {
       
      Log.i(TAG, "Var isCuffAvailable " + isCuffAvailable+ " - " +isTakingMeasure);
      if (!isTakingMeasure && !isCuffAvailable && !isChecking) {
        isAnyCuffAvailable(callbackContext);
      } else {
        callbackContext.success();
      }
      return true;
    }

    if (action.equals("AnyDeviceConnect")) {
      isTakingMeasure = true;
      this.anyDeviceConnect(callbackContext);

      return true;
    }
    
    if (action.equals("cleanPluginState")) {
      Log.i(TAG, "FinishActivity!!");
      try {
        cordova.getActivity().finishActivity(IHEALTH_IS_ANY_CUFF_AVAILABLE);
      } catch (Exception e) {
        Log.e(TAG, "Exception in finishActivity");
      }
      resetPluginState();
      callbackContext.success();
    }
        
    return false;
  }

  private void pluginInitialize(CallbackContext callbackContext) {
    isCuffAvailable = false;
    isTakingMeasure = false;
    isChecking = false;
    deviceType = UNKNOWN_DEVICE;
    callbackContext.success("Plugin Initialized");
  }
  
  // ===================
  // BP5
  // ===================
  
  private void isAnyCuffAvailable(CallbackContext callbackContext) {

    if (!isChecking) {
      isChecking = true;
      final CordovaPlugin plugin = (CordovaPlugin) this;
      cordova.getThreadPool().execute(new Runnable() {
          @Override
          public void run () {
            cordova.setActivityResultCallback(plugin);
            Context context = plugin.cordova.getActivity().getApplicationContext();
            Intent myIntent = new Intent(context, IhealthDeviceManagerActivity.class);
            myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_DOCUMENT);
            myIntent.putExtra("action", IHEALTH_IS_ANY_CUFF_AVAILABLE);
            
            if (mac != null && !mac.equals("") && deviceType != UNKNOWN_DEVICE) {
              Log.i(TAG, "Checking for previous paired device: " + mac);
              myIntent.putExtra("checkForDevice", true);
              myIntent.putExtra("predefinedMac", mac);
              myIntent.putExtra("predefinedType", deviceType);
            } else {
              myIntent.putExtra("checkForDevice", false);
            }
            
            plugin.cordova.startActivityForResult(plugin, myIntent, IHEALTH_IS_ANY_CUFF_AVAILABLE);
            
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
          Context context = plugin.cordova.getActivity().getApplicationContext();
          Log.i(TAG, "before Activity");
          Intent intent = new Intent(context, IhealthBP5Activity.class);
          intent.addFlags(Intent.FLAG_ACTIVITY_MULTIPLE_TASK);
          intent.putExtra("action", IHEALTH_DEVICE_CONNECT_FOR_BP5);
          intent.putExtra("mAddress", mac);
          plugin.cordova.startActivityForResult(plugin, intent, IHEALTH_DEVICE_CONNECT_FOR_BP5);
        }
      });
    
  }

  // ===================
  // BP7
  // ===================
  
  // private void isBP7CuffAvailable(CallbackContext callbackContext) {

  //   if (!isChecking) {
  //     isChecking = true;
  //     final CordovaPlugin plugin = (CordovaPlugin) this;
  //     cordova.getThreadPool().execute(new Runnable() {
  //         @Override
  //         public void run () {
  //           cordova.setActivityResultCallback(plugin);
  //           Context context = plugin.cordova.getActivity().getApplicationContext();
  //           Intent myIntent = new Intent(context, IhealthDeviceManagerActivity.class);
  //           myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_DOCUMENT);
  //           myIntent.putExtra("action", IHEALTH_IS_BP7_CUFF_AVAILABLE);
            
  //           if (mac != null && !mac.equals("")) {
  //             Log.i(TAG, "BP7: Checking for previous paired device: " + mac);
  //             myIntent.putExtra("checkForDevice", true);
  //             myIntent.putExtra("predefinedMac", mac);
  //           } else {
  //             myIntent.putExtra("checkForDevice", false);
  //           }
            
  //           plugin.cordova.startActivityForResult(plugin, myIntent, IHEALTH_IS_BP7_CUFF_AVAILABLE);
            
  //         }
  //       });
  //   } else {
  //     Log.i(TAG, "BP7 is already checking our monitor...");
  //   }
    
  // }

  private void deviceConnectForBP7(CallbackContext callbackContext) {
    final CordovaPlugin plugin = (CordovaPlugin) this;
    
    cordova.getActivity().runOnUiThread(new Runnable() {
        @Override
        public void run () {
          Log.i(TAG, "Var isBP7CuffAvailable " + isCuffAvailable + " - " +isTakingMeasure + " " + mac + " - " + IHEALTH_DEVICE_CONNECT_FOR_BP7);
          cordova.setActivityResultCallback(plugin);
          Context context = plugin.cordova.getActivity().getApplicationContext();
          Log.i(TAG, "BP7 before Activity");
          Intent intent = new Intent(context, IhealthBP7Activity.class);
          intent.addFlags(Intent.FLAG_ACTIVITY_MULTIPLE_TASK);
          intent.putExtra("action", IHEALTH_DEVICE_CONNECT_FOR_BP7);
          intent.putExtra("mAddress", mac);
          plugin.cordova.startActivityForResult(plugin, intent, IHEALTH_DEVICE_CONNECT_FOR_BP7);
        }
      });
    
  }

  private void anyDeviceConnect(CallbackContext callbackContext) {

    if (deviceType == IHEALTH_BP5) {
      Log.i(TAG, "anyDeviceConnect for BP5");
      this.deviceConnectForBP5(callbackContext);
        
    } else if (deviceType == IHEALTH_BP7) {
      Log.i(TAG, "anyDeviceConnect for BP7");
      this.deviceConnectForBP7(callbackContext);
      
    } else {
      resetPluginState();
      callbackContext.error("Unknown Device");
    }
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
    //deviceType = UNKNOWN_DEVICE;
    //mac = null;
  }
  
  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent intent) {

    super.onActivityResult(requestCode, resultCode, intent);
    
    Log.i(TAG, "onActivityResult "+requestCode+" "+resultCode+" "+intent);
    int actionResult = intent.getIntExtra("action", 1);
    switch (actionResult) {
      case IHEALTH_IS_ANY_CUFF_AVAILABLE:
      case IHEALTH_IS_BP7_CUFF_AVAILABLE:
      case IHEALTH_IS_BP5_CUFF_AVAILABLE:
        //Log.i(TAG, "case BP available with mac:" + intent.getStringExtra("result"));
        if (resultCode == Activity.RESULT_OK) {
          Log.i(TAG, "Available? OK");
          isCuffAvailable = true;
          mac =  intent.getStringExtra("result");
          deviceType = intent.getIntExtra("type", UNKNOWN_DEVICE);
          this.callbackContext.success();
        } else {
          Log.i(TAG, "Available? NOTOK");
          isCuffAvailable = false;
          isChecking = false;
          mac = null;
          deviceType = UNKNOWN_DEVICE;
          this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
        }
        break;

    case IHEALTH_DEVICE_CONNECT_FOR_BP5:
    case IHEALTH_DEVICE_CONNECT_FOR_BP7:
        Log.i(TAG, "deviceConnect case result");
        if (resultCode == Activity.RESULT_OK) {
          try {
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
