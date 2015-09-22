package co.vitallabs.plugin;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

// import com.jiuan.android.sdk.bp.bluetooth.BPCommManager;
import com.jiuan.android.sdk.bp.bluetooth.BPControl;
// import com.jiuan.android.sdk.bp.observer_bp.Interface_Observer_BP;
// import com.jiuan.android.sdk.bg.observer.Interface_Observer_BG;
// import com.jiuan.android.sdk.bg.observer.Interface_Observer_BGCoomMsg;
// import com.jiuan.android.sdk.bp.observer_comm.Interface_Observer_CommMsg_BP;

// import com.jiuan.android.sdk.device.DeviceManager;

import com.jiuan.android.sdk.abi.bluetooth.ABICommManager;
import com.jiuan.android.sdk.abi.observer_comm.Interface_Observer_CommMsg_ABI;
import com.jiuan.android.sdk.am.observer_comm.Interface_Observer_CommMsg_AM;
import com.jiuan.android.sdk.bg.audio.BG1Control;
import com.jiuan.android.sdk.bg.observer.Interface_Observer_BG;
import com.jiuan.android.sdk.bg.observer.Interface_Observer_BGCoomMsg;
import com.jiuan.android.sdk.bp.observer_comm.Interface_Observer_CommMsg_BP;
import com.jiuan.android.sdk.device.DeviceManager;
import com.jiuan.android.sdk.hs.bluetooth.Hs4sControl;
import com.jiuan.android.sdk.hs.observer_comm.Interface_Observer_CommMsg_HS;
import com.jiuan.android.sdk.po.observer_comm.Interface_Observer_CommMsg_PO;

import org.apache.cordova.CordovaPlugin;

import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

import android.media.AudioManager;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;

public class IhealthDeviceManagerActivity extends Activity implements
                                                             Interface_Observer_BGCoomMsg,
                                                             Interface_Observer_CommMsg_BP,
                                                             Interface_Observer_CommMsg_AM,
                                                             Interface_Observer_CommMsg_HS,
                                                             Interface_Observer_CommMsg_PO,
                                                             Interface_Observer_BG,
                                                             Interface_Observer_CommMsg_ABI {
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

    // Init receiver
    initReceiver();
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
        deviceManager.cancelScanDevice();
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
          if (deviceManager != null) {
            deviceManager.unReceiver();
          }
          
        } catch (Exception e) {
          Log.i(TAG, "Device not registered never");
        }
        //unReceiver();
        deviceManager.cancelScanDevice();
        finish();
      }
        
    } else {
      Log.i(TAG, "First time looking for a device");
      initDeviceManager();
      
      setTimeoutHandler();
    }
    
  }

  private void initReceiver() {
    Log.i(TAG, "initReceiver with IntentFilter");
    IntentFilter intentFilter = new IntentFilter();
    registerReceiver(mReceiver, intentFilter);
  }

  private void initDeviceManager() {
    Log.i(TAG, "initDeviceManager");
    String userId = "devops@vitallabs.co";
    deviceManager.initDeviceManager(this, userId);
    deviceManager.initReceiver();
    deviceManager.initBpStateCallback(this);
    Thread myt = new Thread(new Runnable () {

        @Override
        public void run() {
          try {
            deviceManager.scanDevice();
          } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "EXCEPTION!!!!!!");
          }
          
        }
      });
    myt.start();
  }
  
  private Runnable mRunnable = new Runnable() {

    @Override
    public void run() {
      Log.e(TAG, "Handler is being called by Runnable");
      if (mAddress == null) {
        Intent intentResult = new Intent();
        intentResult.putExtra("result", false);
        intentResult.putExtra("action", action);
        setResult(RESULT_CANCELED, intentResult);
        Log.i(TAG, "TimeOut Activity!!!");
        try {
          Log.i(TAG, "Unregister deviceManager");
          if (deviceManager != null) {
            deviceManager.unReceiver();
          }
          
        } catch (Exception e) {
          Log.i(TAG, "Device not registered never");
        }
        //unReceiver();
        Log.i(TAG, "Aborting");
        deviceManager.cancelScanDevice();
        finish();
      } else {
        Log.i(TAG, "We can't abort the mission now!");
      }
      
    }
  };
  
  public void setTimeoutHandler() {
    Log.i(TAG, "setTimeoutHandler");
    myHandler = new Handler();
    myHandler.postDelayed(mRunnable, 1000);
    
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
    unReceiver();
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
    deviceManager.cancelScanDevice();
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
    deviceManager.cancelScanDevice();
    finish();
      
  }

  // All interface methods
  @Override
  public void msgHeadsetPluIn() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgHeadsetPullOut() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgDeviceConnect_Hs(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceDisconnect_Hs(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceConnect_Am(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceDisconnect_Am(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceConnect_Bg(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceDisconnect_Bg(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceConnect_Po(String deviceMac, String deviceType) {
  }

  @Override
  public void msgDeviceDisconnect_Po(String deviceMac, String deviceType) {
  }

  @Override
  public void msgUserStatus(int status) {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGError(int num) {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGStripIn() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGGetBlood() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGStripOut() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGResult(int result) {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgBGPowerOff() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgDeviceReady_new() {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgDeviceConnect_ABI(String deviceMac, String deviceType, int arg) {
    // TODO Auto-generated method stub
  }

  @Override
  public void msgDeviceDisconnect_ABI(String deviceMac, String deviceType, int arg) {
    // TODO Auto-generated method stub
  }
  
}
