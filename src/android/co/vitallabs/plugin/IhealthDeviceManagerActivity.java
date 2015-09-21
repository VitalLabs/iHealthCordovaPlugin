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
import android.content.BroadcastReceiver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;

public class IhealthDeviceManagerActivity extends Activity implements
                                                             Interface_Observer_CommMsg_BP {
  private BPControl bpControl;
	private String TAG = "IhealthDevicemanagerActivity";
	private boolean isOffline = false;
	private String mAddress;
	private DeviceManager deviceManager = DeviceManager.getInstance();
  private CordovaPlugin activityResultCallback;
  private boolean keepRunning;
  private boolean activityResultKeepRunning;
  private int action;

  final int IHEALTH_INITIALIZE_PLUGIN = 0;
  final int IHEALTH_IS_BP5_CUFF_AVAILABLE = 1;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP5 = 2;
  Handler myHandler;

  
  @Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
    Log.i(TAG, "onCreate");
    mAddress = null;
    action = getIntent().getIntExtra("action", 1);
    super.onCreate(savedInstanceState);

    if (getIntent().getBooleanExtra("checkForDevice", false) &&
        getIntent().getStringExtra("predefinedMac") != null) {
      String predefinedMac = getIntent().getStringExtra("predefinedMac");
      Log.i(TAG, "Get a predefinedMac address check if is available:" + predefinedMac);

      bpControl = deviceManager.getBpDevice(predefinedMac);
      
      if (bpControl != null) {
        Log.i(TAG, "bpControl show that we already hace a Cuff available!");
        Intent intentResult = new Intent();
        intentResult.putExtra("result", predefinedMac);
        intentResult.putExtra("action", action);
        Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
        setResult(RESULT_OK, intentResult);
        finish();
      } else {
        Log.i(TAG, "bpControl is null so we lost previous paired device...");
        Intent intentResult = new Intent();
        intentResult.putExtra("result", false);
        intentResult.putExtra("action", action);
        Log.i(TAG, "wird state done? " + intentResult);
        setResult(RESULT_CANCELED, intentResult);
        //deviceManager.unReceiver();
        try {
          Log.i(TAG, "Unregister deviceManager");
          deviceManager.unReceiver();
        } catch (Exception e) {
          Log.i(TAG, "Device not registered never");
        }
        unReceiver();
        finish();
      }
        
    } else {
      Log.i(TAG, "First time looking for a device");
      initDeviceManager();
    }
    
  }


  private void initDeviceManager() {
    Log.i(TAG, "initDeviceManager");
    String userId = "devops@vitallabs.co";
    deviceManager.initDeviceManager(this, userId);
    deviceManager.initReceiver();
    deviceManager.initBpStateCallback(this);
    deviceManager.scanDevice();
  }
  
  private Runnable mRunnable = new Runnable() {

    @Override
    public void run() {
      Log.e(TAG, "Handler is being called by Runnable");
      Intent intentResult = new Intent();
      intentResult.putExtra("error", -1);
      intentResult.putExtra("action", action);
      setResult(RESULT_CANCELED, intentResult);
      Log.i(TAG, "TimeOut Activity!!!");
      finish();
    }
  };
  
  public void setTimeoutHandler() {
    Log.i(TAG, "setTimeoutHandler");
    myHandler = new Handler();
    myHandler.postDelayed(mRunnable, 2000);
    
  }

  public void removeTimeoutHandler() {
    Log.i(TAG, "removeTimeoutHandler");
    myHandler.removeCallbacks(mRunnable);
  }
  
  // OnActivityResult stuff hopefully it will work
  public void setActivityResultCallback(CordovaPlugin plugin) {
    Log.i(TAG, "setActivityResultCallback");
    this.activityResultCallback = plugin;        
  }

  public void startActivityForResult(CordovaPlugin command, Intent intent, int requestCode) {
    Log.i(TAG, "startActivityForResult first");
    this.activityResultCallback = command;
    this.activityResultKeepRunning = this.keepRunning;
    intent.putExtra("action", requestCode);
    // If multitasking turned on, then disable it for activities that return results
    if (command != null) {
      this.keepRunning = false;
    }

    // Start activity
    Log.i(TAG, "startActivityForResult"+requestCode);
    super.startActivityForResult(intent, requestCode);
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
    Log.i(TAG, "onActivityResult");
    super.onActivityResult(requestCode, resultCode, intent);
    CordovaPlugin callback = this.activityResultCallback;
    if (callback != null) {
      callback.onActivityResult(requestCode, resultCode, intent);
    }
  }
  // EOF OnActivityResult

  @Override
  protected void onStart() {
    Log.i(TAG, "onStart");
    super.onStart();
  }

  @Override
  protected void onRestart() {
    Log.i(TAG, "onRestart");
    super.onRestart();
  }

  @Override
  protected void onResume() {
    Log.i(TAG, "onResume");
    super.onResume();
  }

  @Override
  protected void onPause() {
    Log.i(TAG, "onPause");
    super.onPause();
  }
  
  @Override
  protected void onStop() {
    Log.i(TAG, "onStopActivity");
    if (deviceManager != null) {
      Log.i(TAG, "before unReceiver");
      
      // try {
      //   deviceManager.unReceiver();
      // } catch (Exception e) {
      //   Log.i(TAG, "Device not registered never");
      // }
      
      Log.i(TAG, "after unReceiver");
    }
    
    super.onStop();
    //unReceiver();
  }


  
  @Override
  protected void onDestroy() {
    Log.i(TAG, "onDestroy");
    super.onDestroy();
    
  }

  private void unReceiver() {
    try {
      unregisterReceiver(mReceiver);
    } catch (Exception e) {
      Log.i(TAG, "Exception in unReceiver " + e.toString());
    }
    
    
  }

  BroadcastReceiver mReceiver = new BroadcastReceiver() {
      public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
        Log.i(TAG, "onReceive"+action);
      }
    };

  
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

  // private void getbpControl(){
  //   Log.i(TAG, "inGetBpControl" + mAddress);
  //   bpControl = deviceManager.getBpDevice(mAddress);
  //   removeTimeoutHandler();
  //   if(bpControl != null){
	// 		Log.i(TAG, "getbpControl " + bpControl);
	// 		bpControl.controlSubject.attach(this);
  //     Log.i(TAG, "forceTakeMeasure " + action);
  //     if (action == this.IHEALTH_DEVICE_CONNECT_FOR_BP5) {
  //       startMeasure();
  //     } else if (action == this.IHEALTH_IS_BP5_CUFF_AVAILABLE) {
  //       Intent intentResult = new Intent();
  //       intentResult.putExtra("result", true);
  //       intentResult.putExtra("action", action);
  //       Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
  //       setResult(RESULT_OK, intentResult);
  //       finish();
  //     }
      
	// 	} else {
	// 		Intent intentResult = new Intent();
  //     intentResult.putExtra("result", false);
  //     intentResult.putExtra("action", action);
  //     Log.i(TAG, "wird state done? " + intentResult);
  //     setResult(RESULT_OK, intentResult);
  //     finish();
      
	// 	}
	// }

	private void getFunctionInfo(){
		
	}

	// @Override
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
	// 	Log.e(TAG, "User status " + status);
	// }

	// @Override
	// public void msgError(int num) {
	// 	// TODO Auto-generated method stub
  //   removeTimeoutHandler();  
  //   Log.e(TAG, "error, " + num);
  //   Intent intentResult = new Intent();
  //   intentResult.putExtra("error", num);
  //   intentResult.putExtra("action", action);
  //   setResult(RESULT_CANCELED, intentResult);
  //   Log.i(TAG, "Back from unsuccesfull measure " + num);
  //   finish();
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
  //   removeTimeoutHandler();
  //   Log.e(TAG, "result:"+ result[0]+" "+result[1]+" "+result[2]+" "+ Arrays.toString(result));
  //   Intent intentResult = new Intent();
  //   intentResult.putExtra("result", result);
  //   intentResult.putExtra("action", action);
  //   setResult(RESULT_OK, intentResult);
  //   Log.i(TAG, "Back from succesfull measure");
  //   //unregisterReceiver();
  //   finish();
	// }

	// @Override
	// public void msgPowerOff() {
	// 	// TODO Auto-generated method stub

	// }

  // public void startMeasure () {
  //   String clientID =  "b42e648c6c224f9a890e7d9323dc5b6a";
  //   String clientSecret = "ce7a64efe52e446990f1c696e864d3a7";
  //   Log.i("BeforeStart", clientID+" " + clientSecret + " " +IhealthActivity.this);
  //   bpControl.start(IhealthActivity.this, clientID, clientSecret);
  // }


  // NEW OVERRIDES
  @Override
  public void msgDeviceConnect_Bp(String deviceMac, String deviceType) {
    Log.i(TAG, "msgDeviceConnect_Bp " + deviceMac + " " + deviceType);
    mAddress = deviceMac;

    //getbpControl();
    Intent intentResult = new Intent();
    intentResult.putExtra("result", deviceMac);
    intentResult.putExtra("action", action);
    Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
    setResult(RESULT_OK, intentResult);
    finish();
  }
  
  @Override
  public void msgDeviceDisconnect_Bp(String deviceMac, String deviceType) {
    //removeTimeoutHandler();
    Log.i(TAG, "msgDeviceDisconnect_BP");
    Intent intentResult = new Intent();
    intentResult.putExtra("result", false);
    intentResult.putExtra("action", action);
    Log.i(TAG, "wird state done? " + intentResult);
    setResult(RESULT_CANCELED, intentResult);
    finish();
      
  }
   
}
