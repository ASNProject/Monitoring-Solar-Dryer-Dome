package com.example.sistemmonitoring;

import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.text.SimpleDateFormat;
import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.format.TextStyle;
import java.util.Calendar;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    private TextView celcius, day, tanggal, humidity, lux, volt;

    private DatabaseReference database;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        database = FirebaseDatabase.getInstance().getReference();
        FirebaseDatabase mdatabase = FirebaseDatabase.getInstance();

        celcius = (TextView) findViewById(R.id.celcius);
        day = (TextView) findViewById(R.id.day);
        tanggal = (TextView) findViewById(R.id.tanggal);
        humidity = (TextView) findViewById(R.id.humidity);
        lux = (TextView) findViewById(R.id.lux);
        volt = (TextView) findViewById(R.id.volt);

        mdatabase.getReference("Temperature").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Integer temp = dataSnapshot.getValue(Integer.class);
                celcius.setText(String.valueOf(temp));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
        mdatabase.getReference("Humidity").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Integer temp = dataSnapshot.getValue(Integer.class);
                humidity.setText(String.valueOf(temp));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
        mdatabase.getReference("Lux").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Integer temp = dataSnapshot.getValue(Integer.class);
                lux.setText(String.valueOf(temp));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
        mdatabase.getReference("Watt").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Integer temp = dataSnapshot.getValue(Integer.class);
                volt.setText(String.valueOf(temp));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        Calendar calendar = Calendar.getInstance();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("d MMMM yyyy");
        String date = simpleDateFormat.format(calendar.getTime());
        tanggal.setText(date);

        LocalDate date1 = LocalDate.now();
        DayOfWeek dayOfWeek = date1.getDayOfWeek();
        String dayname = dayOfWeek.getDisplayName(TextStyle.FULL, Locale.ENGLISH);
        day.setText(dayname);
    }
}