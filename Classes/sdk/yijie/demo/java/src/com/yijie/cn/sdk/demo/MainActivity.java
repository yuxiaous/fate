package com.yijie.cn.sdk.demo;

import android.os.Bundle;
import android.app.ListActivity;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.AdapterView.OnItemClickListener;

import com.yijie.cn.sdk.demo.R;
import com.snowfish.cn.ganga.offline.helper.SFCommonSDKInterface;
import com.snowfish.cn.ganga.offline.helper.SFGameExitListener;
import com.snowfish.cn.ganga.offline.helper.SFIPayResultListener;

public class MainActivity extends ListActivity {
	class PayListener extends SFIPayResultListener {

		@Override
		public void onCanceled(String remain) {
		}
  
		@Override         
		public void onFailed(String remain) {                                                     
		}

		@Override
		public void onSuccess(String remain) {
		}
		;
	}
	
	static final String[] BUTTONS = new String[]{                                 
	    "00.购买计费点：001",
	    "01.购买计费点：002",
	    "02.购买计费点：003",
	  
	  };
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {                
		super.onCreate(savedInstanceState);
	
	    requestWindowFeature(Window.FEATURE_NO_TITLE);

	    getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

	    SFCommonSDKInterface.onInit(this);
	
		boolean b = SFCommonSDKInterface.isMusicEnabled(this);
	
		setListAdapter(new ArrayAdapter<String>(this, R.layout.game_item, BUTTONS));      
	    ListView lv = getListView();
	    lv.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				
			//	String billingIndex = getBillingIndex(position);
				String billingIndex = position + "";
		        SFCommonSDKInterface.pay(MainActivity.this, billingIndex, new PayListener());
			}
	    	
	    });
	   
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	
	 private String getBillingIndex(int i){
		  if(i<9){
			  return "00"+(++i);
		  }else{
			  return "0" + (++i);  
		  }
	  }
	 
	 
	 @Override
	  public void onResume() {
	    super.onResume();
	  }

	 @Override
	  public boolean onKeyDown(int keyCode, KeyEvent event) {
	    if (keyCode == KeyEvent.KEYCODE_BACK) {
	    		
	    	SFCommonSDKInterface.onExit(this, new SFGameExitListener () {

				@Override
				public void onGameExit(boolean flag) {
					if (flag) {
						System.exit(0);
					}
				}
	    	});
	    	//System.exit(0);
	    	return true;
	    }
	    return super.onKeyDown(keyCode, event);
	  }
}
