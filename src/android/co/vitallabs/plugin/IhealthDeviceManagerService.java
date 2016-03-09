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

import android.app.Service;
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
import android.os.Binder;
import android.util.Log;

public class IhealthDeviceManagerService extends Service implements
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

  private int availableType;
  
  final int IHEALTH_INITIALIZE_PLUGIN = 0;
  final int IHEALTH_IS_BP5_CUFF_AVAILABLE = 1;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP5 = 2;
  final int IHEALTH_IS_BP7_CUFF_AVAILABLE = 3;
  final int IHEALTH_DEVICE_CONNECT_FOR_BP7 = 4;

  final int IHEALTH_IS_ANY_CUFF_AVAILABLE = 5;
  final int IHEALTH_BP5 = 6;
  final int IHEALTH_BP7 = 7;
  final int UNKNOWN_DEVICE = 8;

  final int IHEALTH_CLEAN_DEVICE_MANAGER = 9;
  
  Handler myHandler;
  private String userId = "devops@vitallabs.co";
  private final IBinder mBinder = new LocalBinder();
  
  @Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
    Log.i(TAG, "onCreate");
    super.onCreate(savedInstanceState);
    mAddress = null;    
  }

  private void initReceiver() {
    Log.i(TAG, "initReceiver with IntentFilter");
    IntentFilter intentFilter = new IntentFilter();
    intentFilter.addAction(Hs4sControl.MSG_HS4S_CONNECTED);
    intentFilter.addAction(Hs4sControl.MSG_HS4S_DISCONNECT);
    intentFilter.setPriority(IntentFilter.SYSTEM_HIGH_PRIORITY);
    registerReceiver(mReceiver, intentFilter);
  }

  private void initDeviceManager() {
    Log.i(TAG, "initDeviceManager");
    
    try {
      //setTimeoutHandler();
      deviceManager.initDeviceManager(this, userId);
      deviceManager.initReceiver();
      deviceManager.initBpStateCallback(this);
    
    } catch (Exception e) {
      Log.e(TAG, "Exception in initDeviceManager??? " + e.toString());
    }

    Thread myt = new Thread(new Runnable () {

        @Override
        public void run() {
          try {
            Thread.sleep(500);
          } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
          }

          try {
            deviceManager.scanDevice();
          } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "Exception in deviceManager.scanDevice");
          }
          
        }
      });
    myt.start();
  }


  // Binder stuff for interacting with the CordovaPlugin
  public class LocalBinder extends Binder {
    IhealthDeviceManagerService getService() {
      // Return this instance of LocalService so clients can call public methods
      return IhealthDeviceManagerService.this;
    }
  }


  @Override
  public IBinder onBind(Intent intent) {
    return mBinder;
  }

  // EOF Binder stuff
  
  private Runnable mRunnable = new Runnable() {

    @Override
    public void run() {
      Log.e(TAG, "Handler is being called by Runnable");
      if (mAddress == null) {
        deviceManager.cancelScanDevice();
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
        Log.i(TAG, "Aborting");
        //finish();
        this.activityResultCallback.onActivityResult(action, RESULT_CANCELED, intentResult);
      } else {
        Log.i(TAG, "We can't abort the mission now!");
      }
      
    }
  };
  
  public void setTimeoutHandler() {
    Log.i(TAG, "setTimeoutHandler");
    myHandler = new Handler();
    myHandler.postDelayed(mRunnable, 3000);
    
  }

  public void removeTimeoutHandler() {
    Log.i(TAG, "removeTimeoutHandler");
    myHandler.removeCallbacks(mRunnable);
  }
  
  @Override
  protected void onStart(Intent intent, int startId) {
    Log.i(TAG, "onStart" + startId);
    super.onStart();
    action = intent.getIntExtra("action", 1);
    this.activityResultCallback = intent.getIntExtra("pluginInstance", 1);
    
    // Init receiver
    initReceiver();


    if (action == IHEALTH_CLEAN_DEVICE_MANAGER) {
      Log.i(TAG, "Unregister deviceManager for cleaning operation");
      try {
        if (deviceManager != null) {
          deviceManager.initDeviceManager(this, userId);
          deviceManager.initReceiver();
          deviceManager.unReceiver();
        }
      } catch (Exception e) {
        Log.i(TAG, "Exception cleaning DM");
      }
      
      Intent intentResult = new Intent();
      intentResult.putExtra("action", action);
      Log.i(TAG, "CLEAN done? " + intentResult);
      setResult(RESULT_OK, intentResult);
      //finish();
      this.activityResultCallback.onActivityResult(action, RESULT_OK, intentResult);
    } else
      if (intent.getBooleanExtra("checkForDevice", false) &&
        intent.getStringExtra("predefinedMac") != null &&
        intent.getIntExtra("predefinedType", UNKNOWN_DEVICE) != UNKNOWN_DEVICE) {
      String predefinedMac = intent.getStringExtra("predefinedMac");
      int predefinedType = intent.getIntExtra("predefinedType", UNKNOWN_DEVICE);
      Log.i(TAG, "Get a predefinedMac address check if is available:" + predefinedMac);

      bpControl = deviceManager.getBpDevice(predefinedMac);
      
      if (bpControl != null) {
        Log.i(TAG, "bpControl show that we already hace a Cuff available!");
        Intent intentResult = new Intent();
        intentResult.putExtra("result", predefinedMac);
        intentResult.putExtra("type", predefinedType);
        intentResult.putExtra("action", action);
        Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
        setResult(RESULT_OK, intentResult);
        deviceManager.cancelScanDevice();
        //finish();
        this.activityResultCallback.onActivityResult(action, RESULT_OK, intentResult);
      } else {
        Log.i(TAG, "bpControl is null so we lost previous paired device...");
        Intent intentResult = new Intent();
        intentResult.putExtra("result", false);
        intentResult.putExtra("action", action);
        Log.i(TAG, "wird state done? " + intentResult);
        setResult(RESULT_CANCELED, intentResult);

        try {
          Log.i(TAG, "Unregister deviceManager");
          if (deviceManager != null) {
            deviceManager.unReceiver();
          }
          
        } catch (Exception e) {
          Log.i(TAG, "Device not registered never");
        }
        deviceManager.cancelScanDevice();
        // finish();
        this.activityResultCallback.onActivityResult(action, RESULT_CANCELED, intentResult);
      }
        
    } else {
      Log.i(TAG, "First time looking for a device");
      initDeviceManager();
    }


    
  }

  @Override
  protected void onDestroy() {
    Log.i(TAG, "onDestroyService");    
    unReceiver();
    super.onDestroy();
    
  }

  private void unReceiver() {
    Log.i(TAG, "Calling unreceiver");
    try {
      unregisterReceiver(mReceiver);
      Log.i(TAG, "unregister success!");
    } catch (Exception e) {
      Log.i(TAG, "Exception in unReceiver " + e.toString());
    }
    
    
  }

  BroadcastReceiver mReceiver = new BroadcastReceiver() {
      public void onReceive(Context context, Intent intent) {
        Log.i(TAG, "onReceive");
        String action = intent.getAction();
        Log.i(TAG, "Action of onReceive" + action);
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

    Intent intentResult = new Intent();
    intentResult.putExtra("result", deviceMac);
    
    if (deviceType.equals("BP5")) {
      intentResult.putExtra("type", this.IHEALTH_BP5);
    } else if (deviceType.equals("BP7")) {
      intentResult.putExtra("type", this.IHEALTH_BP7);
    } else  {
      intentResult.putExtra("type", this.UNKNOWN_DEVICE);
    }
    intentResult.putExtra("action", action);
    Log.i(TAG, "isBPCuffAvailable done? " + intentResult);
    setResult(RESULT_OK, intentResult);
    deviceManager.cancelScanDevice();
    //finish();
    this.activityResultCallback.onActivityResult(action, RESULT_OK, intentResult);
  }
  
  @Override
  public void msgDeviceDisconnect_Bp(String deviceMac, String deviceType) {
    Log.i(TAG, "msgDeviceDisconnect_BP");
    Intent intentResult = new Intent();
    intentResult.putExtra("result", false);
    intentResult.putExtra("action", action);
    Log.i(TAG, "wird state done? " + intentResult);
    setResult(RESULT_CANCELED, intentResult);
    deviceManager.cancelScanDevice();
    //finish();
    this.activityResultCallback.onActivityResult(action, RESULT_CANCELED, intentResult);
      
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
