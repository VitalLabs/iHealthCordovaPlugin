package co.vitallabs.plugin;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import com.jiuan.android.sdk.bp.bluetooth.BPCommManager;
import com.jiuan.android.sdk.bp.bluetooth.BPControl;
import com.jiuan.android.sdk.bp.observer_bp.Interface_Observer_BP;
import com.jiuan.android.sdk.bp.observer_comm.Interface_Observer_CommMsg_BP;
import com.jiuan.android.sdk.device.DeviceManager;

//import android.app.Activity;
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

/**
 * This class echoes a string called from JavaScript.
 */
public class Ihealth extends CordovaPlugin implements Interface_Observer_CommMsg_BP {

  private BPControl bpControl;
	private String TAG = "BPtest_MainActivity";
  private String mAddress;
	private DeviceManager deviceManager;
  
  
  @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

    Log.i(TAG, "calling action:" + action);
        if (action.equals("pluginInitialize")) {
            String message = args.getString(0);
            this.pluginInitialize(message, callbackContext);
            return true;
        }

        if (action.equals("DeviceConnectForBP5")) {
            this.deviceConnectForBP5(callbackContext);
            return true;
        }
        
        return false;
    }

    private void pluginInitialize(String message, CallbackContext callbackContext) {

        Log.i(TAG, "pluginInitialize");
        
        Context context = this.cordova.getActivity().getApplicationContext();
      
        deviceManager = DeviceManager.getInstance();
        Log.i(TAG, "deviceManager"+deviceManager);
        deviceManager.initDeviceManager(context, "robertorobles0@gmail.com");
        Log.i(TAG, "initDeviceManager"+deviceManager);
        deviceManager.initReceiver();
        Log.i(TAG, "initReceiver"+deviceManager);
        deviceManager.initBpStateCallback(this);
        Log.i(TAG, "InitBPStateCB"+deviceManager);
        if (message != null && message.length() > 0) {
            callbackContext.success(message);
        } else {
            callbackContext.error("Expected one non-empty string argument.");
        }
    }

  
  

    private void deviceConnectForBP5(CallbackContext callbackContext) {

      
      //mAddress = getIntent().getStringExtra("mac");

      Context context = this.cordova.getActivity().getApplicationContext();
      mAddress = this.cordova.getActivity().getIntent().getStringExtra("mac");

      Log.i(TAG, "mAddress:" + mAddress);
      deviceManager = DeviceManager.getInstance();

      bpControl = deviceManager.getBpDevice(mAddress);


      String clientID =  "bbcb0a015545402c8c5683b485009045";
      String clientSecret = "278702abdb2041d0bcc0e7b1bbc43b86";
      bpControl.start(context, clientID, clientSecret);

      callbackContext.success("Returning from deviceConnectFroBP5");
    }


      @Override
    public void msgDeviceConnect_Bp(String deviceMac, String deviceType) {
        //deviceMap.put(deviceMac, deviceType);
        //refresh();
        Log.i(TAG, deviceMac + " " + deviceType);
    }

    @Override
    public void msgDeviceDisconnect_Bp(String deviceMac, String deviceType) {
      //deviceMap.remove(deviceMac);
      // refresh();
      Log.i(TAG, deviceMac + " " + deviceType);
    }

  
    // Interface methods
  //   	@Override
	// public void msgInden() {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgBattery(int battery) {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgUserStatus(int status) {
	// 	// TODO Auto-generated method stub
	// 	// Toast.makeText(getApplicationContext(), "user status "+status, Toast.LENGTH_SHORT).show();
	// }

	// @Override
	// public void msgError(int num) {
	// 	// TODO Auto-generated method stub
  //   Log.e("error", ""+num);
  //   // try {
	// 	// 	Message message = new Message();
	// 	// 	message.what = 2;
	// 	// 	Bundle bundle = new Bundle();
	// 	// 	bundle.putInt("error", num);
	// 	// 	message.obj = bundle;
	// 	// 	handler.sendMessage(message);
	// 	// } catch (Exception e) {
	// 	// 	// TODO: handle exception
	// 	// }
	// }

	// @Override
	// public void msgAngle(int angle) {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgZeroIng() {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgZeroOver() {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgPressure(int pressure) {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgMeasure(int pressure, int[] measure, boolean heart) {
	// 	// TODO Auto-generated method stub

	// }

	// @Override
	// public void msgResult(int[] result) {
	// 	// TODO Auto-generated method stub
	// 	Log.e("result", result[0]+" "+result[1]+" "+result[2]+" ");
	// 	// try {
	// 	// 	Message message = new Message();
	// 	// 	message.what = 1;
	// 	// 	Bundle bundle = new Bundle();
	// 	// 	bundle.putIntArray("bp", result);
	// 	// 	message.obj = bundle;
	// 	// 	handler.sendMessage(message);
	// 	// } catch (Exception e) {
	// 	// 	// TODO: handle exception
	// 	// }
	// }

	// @Override
	// public void msgPowerOff() {
	// 	// TODO Auto-generated method stub

	// }


}
