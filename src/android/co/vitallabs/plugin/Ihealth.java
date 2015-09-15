package co.vitallabs.plugin;

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
public class Ihealth extends CordovaPlugin implements Interface_Observer_BP {

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

        // cordova.getActivity().runOnUiThread(new Runnable() {
        //     @Override
        //     public void run() {
        //       Context context = cordova.getActivity()
        //             .getApplicationContext();
        //       Intent intent = new Intent(context, IhealthActivity.class);
        //       intent.putExtra("mac", mAddress);
        //       cordova.getActivity().startActivity(intent);
        //      }
        //   });

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


    //   @Override
    // public void msgDeviceConnect_Bp(String deviceMac, String deviceType) {
    //     //deviceMap.put(deviceMac, deviceType);
    //     //refresh();
    //     Log.i(TAG, deviceMac + " " + deviceType);
    // }

    // @Override
    // public void msgDeviceDisconnect_Bp(String deviceMac, String deviceType) {
    //   //deviceMap.remove(deviceMac);
    //   // refresh();
    //   Log.i(TAG, deviceMac + " " + deviceType);
    // }

  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent intent) {
    //do something with the result
    Log.i(TAG, "onActivityResult "+requestCode+" "+resultCode+" "+intent);
    if (resultCode == 1) {
      Log.e(TAG, "Getting result from Activity"  + intent.getIntArrayExtra("result"));
    }
    Log.e(TAG, "Getting result from Activity"  + intent.getIntArrayExtra("result"));
    super.onActivityResult(requestCode, resultCode, intent);
  }
  
    // Interface methods
    	@Override
	public void msgInden() {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgBattery(int battery) {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgUserStatus(int status) {
		// TODO Auto-generated method stub
		// Toast.makeText(getApplicationContext(), "user status "+status, Toast.LENGTH_SHORT).show();
	}

	@Override
	public void msgError(int num) {
		// TODO Auto-generated method stub
    Log.e("error", ""+num);
    // try {
		// 	Message message = new Message();
		// 	message.what = 2;
		// 	Bundle bundle = new Bundle();
		// 	bundle.putInt("error", num);
		// 	message.obj = bundle;
		// 	handler.sendMessage(message);
		// } catch (Exception e) {
		// 	// TODO: handle exception
		// }
	}

	@Override
	public void msgAngle(int angle) {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgZeroIng() {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgZeroOver() {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgPressure(int pressure) {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgMeasure(int pressure, int[] measure, boolean heart) {
		// TODO Auto-generated method stub

	}

	@Override
	public void msgResult(int[] result) {
		// TODO Auto-generated method stub
		Log.e("result", result[0]+" "+result[1]+" "+result[2]+" ");
		// try {
		// 	Message message = new Message();
		// 	message.what = 1;
		// 	Bundle bundle = new Bundle();
		// 	bundle.putIntArray("bp", result);
		// 	message.obj = bundle;
		// 	handler.sendMessage(message);
		// } catch (Exception e) {
		// 	// TODO: handle exception
		// }
	}

	@Override
	public void msgPowerOff() {
		// TODO Auto-generated method stub

	}


}
