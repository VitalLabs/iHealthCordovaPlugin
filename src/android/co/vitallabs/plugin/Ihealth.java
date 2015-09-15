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
  private String mAddress = "8CDE5241FE3A";
  private DeviceManager deviceManager;
  private IhealthActivity iActivity;
  protected Context context;
  private CallbackContext callbackContext;
  
  @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

    this.callbackContext = callbackContext;
    
    Log.i(TAG, "calling action:" + action);
    if (action.equals("pluginInitialize")) {
      this.pluginInitialize(callbackContext);
      return true;
    }

    if (action.equals("DeviceConnectForBP5")) {
      this.deviceConnectForBP5(callbackContext);
      return true;
    }
        
    return false;
  }

    private void pluginInitialize(CallbackContext callbackContext) {

      Log.i(TAG, "Before running the thread");
      //final long duration = args.getLong(0);
      Log.i(TAG, "pluginInitialize");
      Context context = this.cordova.getActivity().getApplicationContext();
      Log.i(TAG, "before Activity");
      Intent intent = new Intent(context, IhealthActivity.class);
      intent.putExtra("mac", mAddress);
      //cordova.getActivity().startActivity(intent);
      this.cordova.startActivityForResult((CordovaPlugin) this, intent, 1);

      Log.i(TAG, "After Activity");
    }

  
  

    private void deviceConnectForBP5(CallbackContext callbackContext) {

      
      //mAddress = getIntent().getStringExtra("mac");

      mAddress = this.cordova.getActivity().getIntent().getStringExtra("mac");

      Log.i(TAG, "mAddress:" + mAddress);
      deviceManager = DeviceManager.getInstance();

      bpControl = deviceManager.getBpDevice(mAddress);
      Log.i(TAG, "bpControl "+bpControl);
      String clientID = "b42e648c6c224f9a890e7d9323dc5b6a";
      String clientSecret = "ce7a64efe52e446990f1c696e864d3a7";
            
      bpControl.start(this.context, clientID, clientSecret);

      callbackContext.success("Returning from deviceConnectFroBP5");
    }



  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent intent) {
    //do something with the result
    Log.i(TAG, "onActivityResult "+requestCode+" "+resultCode+" "+intent);
    if (resultCode == 1) {
      Log.e(TAG, "Getting result from Activity"  + intent.getIntArrayExtra("result"));
    }
    Log.e(TAG, "Getting result from Activity"  + Arrays.toString(intent.getIntArrayExtra("result")));
    super.onActivityResult(requestCode, resultCode, intent);
  }
  
}
