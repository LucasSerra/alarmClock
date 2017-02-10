package com.example.felipe.aslap;

import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TimePicker;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.util.Calendar;
import javax.net.ssl.HttpsURLConnection;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MyActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        final TimePicker timePicker=(TimePicker)findViewById(R.id.timePicker);
        timePicker.setIs24HourView(true);
        timePicker.setHour(Calendar.getInstance().get(Calendar.HOUR_OF_DAY));


        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);

        if (fab != null) {
            fab.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Toast.makeText(MainActivity.this, "Sending data to Spark Cloud!", Toast.LENGTH_SHORT).show();
                    if(timePicker.getHour() < 10 && timePicker.getMinute() > 10){
                        new PostClient().execute("0"+(String.valueOf(timePicker.getHour()))+":"+String.valueOf(timePicker.getMinute()));

                    }else if(timePicker.getMinute() < 10 && timePicker.getHour()>10){
                        new PostClient().execute((String.valueOf(timePicker.getHour()))+":0"+String.valueOf(timePicker.getMinute()));
                    }else if(timePicker.getHour() < 10 && timePicker.getMinute() < 10){
                        new PostClient().execute("0"+(String.valueOf(timePicker.getHour()))+":0"+String.valueOf(timePicker.getMinute()));
                    }else {
                        new PostClient().execute((String.valueOf(timePicker.getHour())) + ":" + String.valueOf(timePicker.getMinute()));
                    }
                }
            });
        }
    }

    /*
         * POST EXAMPLE
         */
    // We must do this as a background task, elsewhere our app crashes
    class PostClient extends AsyncTask<String, Void, String> {
        public String doInBackground(String... IO) {

            // Predefine variables
            String io = new String(IO[0]);
            URL url;

            try {
                // Stuff variables
                url = new URL("https://api.particle.io/v1/devices/55ff6d066678505556411367/alarm");
                String param = "access_token=c0ed181d6b0d4884303399e8934f92c6362012af&params="+io;
                Log.d(TAG, "param:" + param);

                // Open a connection using HttpURLConnection
                HttpsURLConnection con = (HttpsURLConnection) url.openConnection();

                con.setReadTimeout(7000);
                con.setConnectTimeout(7000);
                con.setDoOutput(true);
                con.setDoInput(true);
                con.setInstanceFollowRedirects(false);
                con.setRequestMethod("POST");
                con.setFixedLengthStreamingMode(param.getBytes().length);
                con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

                // Send
                PrintWriter out = new PrintWriter(con.getOutputStream());
                out.print(param);
                out.close();

                con.connect();

                BufferedReader in = null;
                if (con.getResponseCode() != 200) {
                    in = new BufferedReader(new InputStreamReader(con.getErrorStream()));
                    Log.d(TAG, "!=200: " + in);
                } else {
                    in = new BufferedReader(new InputStreamReader(con.getInputStream()));
                    Log.d(TAG, "POST request send successful: " + in);
                };


            } catch (Exception e) {
                Log.d(TAG, "Exception");
                e.printStackTrace();
                return null;
            }
            // Set null and we´e good to go
            return null;
        }
    }
}
