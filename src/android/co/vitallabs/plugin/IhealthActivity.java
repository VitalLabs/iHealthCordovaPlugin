package co.vitallabs.plugin;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import com.jiuan.android.sdk.bp.bluetooth.BPCommManager;
import com.jiuan.android.sdk.bp.bluetooth.BPControl;
import com.jiuan.android.sdk.bp.observer_bp.Interface_Observer_BP;
import com.jiuan.android.sdk.bg.observer.Interface_Observer_BG;
import com.jiuan.android.sdk.bg.observer.Interface_Observer_BGCoomMsg;
import com.jiuan.android.sdk.bp.observer_comm.Interface_Observer_CommMsg_BP;

import com.jiuan.android.sdk.device.DeviceManager;

import org.apache.cordova.CordovaPlugin;

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

public class IhealthActivity extends Activity implements
                                                Interface_Observer_BP,
                                                Interface_Observer_CommMsg_BP {
  private BPControl bpControl;
	private String TAG = "BPIhealthActivity";
	private boolean isOffline = false;
	private String mAddress;
	private DeviceManager deviceManager = DeviceManager.getInstance();
  private CordovaPlugin activityResultCallback;
  private boolean keepRunning;
  private boolean activityResultKeepRunning;
  private String action;
  
  @Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
    action = getIntent().getStringExtra("action");
    super.onCreate(savedInstanceState);
    String userId = "devops@vitallabs.co";
    deviceManager.initDeviceManager(this, userId);
    deviceManager.initReceiver();
    deviceManager.initBpStateCallback(this);
    deviceManager.scanDevice();
    
  }

  // OnActivityResult stuff hopefully it will work
  public void setActivityResultCallback(CordovaPlugin plugin) {
    this.activityResultCallback = plugin;        
  }

  public void startActivityForResult(CordovaPlugin command, Intent intent, int requestCode) {
    this.activityResultCallback = command;
    this.activityResultKeepRunning = this.keepRunning;

    // If multitasking turned on, then disable it for activities that return results
    if (command != null) {
      this.keepRunning = false;
    }

    // Start activity
    super.startActivityForResult(intent, requestCode);
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
    super.onActivityResult(requestCode, resultCode, intent);
    CordovaPlugin callback = this.activityResultCallback;
    if (callback != null) {
      callback.onActivityResult(requestCode, resultCode, intent);
    }
  }
  // EOF OnActivityResult
  
  protected void onStop() {
    super.onStop();
  }


  private Handler handler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch (msg.what) {
			case 1:
				Bundle bundle = (Bundle)msg.obj;
				int[] result = bundle.getIntArray("bp");
				//setText(result);
        Log.e(TAG, "Handler: "+result );
        break;
			case 2:
				Bundle bundle2 = (Bundle)msg.obj;
				int errorNum = bundle2.getInt("error");
				//Toast.makeText(BP5Activity.this, "error:"+errorNum, Toast.LENGTH_LONG).show();
        Log.e(TAG, "HandlerError: "+errorNum );
				break;
			default:
				break;
			}
		}
	};

  private void getbpControl(){
    Log.i(TAG, "inGetBpControl" + mAddress);
    bpControl = deviceManager.getBpDevice(mAddress);
		if(bpControl != null){
			Log.i(TAG, "getbpControl " + bpControl);
			bpControl.controlSubject.attach(this);
      Log.i(TAG, "forceTakeMeasure " + action);
      if (action == "deviceConnectForBP5") {
        startMeasure();
      } else if (action == "isBP5CuffAvailable") {
        Intent intentResult = new Intent();

        intentResult.putExtra("result", true);
        intentResult.putExtra("action", action);
        Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
        setResult(RESULT_OK, intentResult);
        finish();
      }
      
		} else {
			Intent intentResult = new Intent();
      intentResult.putExtra("result", false);
      intentResult.putExtra("action", action);
      Log.i(TAG, "wird state done? " + intentResult);
        
      setResult(RESULT_OK, intentResult);
      finish();
      
		}
	}

	private void getFunctionInfo(){
		// if(bpControl != null){
		// 	bpControl.FunctionInfo(1);
		// 	if(bpControl.offLinedata){
		// 		//showisOffLine.setText("allow offline test");
		// 		isOffline = true;
		// 		isOffLine.setBackgroundResource(R.drawable.iseveryday);
		// 	}else{
		// 		showisOffLine.setText("not allow offline test");
		// 		isOffline = false;
		// 		isOffLine.setBackgroundResource(R.drawable.isnoteveryday);
		// 	}
		// }
	}

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
		Log.e(TAG, "User status " + status);
	}

	@Override
	public void msgError(int num) {
		// TODO Auto-generated method stub
    Log.e(TAG, "error, " + num);
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
		Log.e(TAG, "result:"+ result[0]+" "+result[1]+" "+result[2]+" "+ Arrays.toString(result));
    Intent intentResult = new Intent();
    intentResult.putExtra("result", result);
    intentResult.putExtra("action", action);
    setResult(RESULT_OK, intentResult);
    Log.i(TAG, "Back from succesfull measure");
    //unregisterReceiver();
    finish();
	}

	@Override
	public void msgPowerOff() {
		// TODO Auto-generated method stub

	}

  public void startMeasure () {
    String clientID =  "b42e648c6c224f9a890e7d9323dc5b6a";
    String clientSecret = "ce7a64efe52e446990f1c696e864d3a7";
    Log.i("BeforeStart", clientID+" " + clientSecret + " " +IhealthActivity.this);
    bpControl.start(IhealthActivity.this, clientID, clientSecret);
  }


  // NEW OVERRIDES
  @Override
  public void msgDeviceConnect_Bp(String deviceMac, String deviceType) {
    Log.i(TAG, "msgDeviceConnect_Bp " + deviceMac + " " + deviceType);
    mAddress = deviceMac;
    getbpControl(); 
  }
  
  @Override
  public void msgDeviceDisconnect_Bp(String deviceMac, String deviceType) {
    Log.i(TAG, "msgDeviceDisconnect_Bp" + deviceMac + " " + deviceType);
  }
   
}
