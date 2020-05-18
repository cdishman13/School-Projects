package com.example.nightlife2;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;

public class Review extends AppCompatActivity {

    private TextView name;
    private EditText notes;
    private String userNotes;
    private String placeName;
    private Calendar calendar;
    private SimpleDateFormat dateFormat;
    private String date;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_review);
        notes = findViewById(R.id.place_notes);
        name = findViewById(R.id.place_name);

        calendar = Calendar.getInstance();

        Intent intent = getIntent();
        String title = intent.getStringExtra("info");
        for(int i = 0; i < title.length(); i++){
            if(title.charAt(i) == ':'){
                placeName = title.substring(0,i);
            }
        }
        if(placeName == null){
            placeName = title;
        }

        name.setText(placeName);

        loadFromFile(this, placeName);
        if(userNotes != null)
            notes.setText("\n" + userNotes);

        notes.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                userNotes = notes.getText().toString();
            }

            @Override
            public void afterTextChanged(Editable s) {
                saveState(Review.this, placeName);
            }
        });
    }

    public void saveState(Context context, String filename){
        FileOutputStream fos;
        ObjectOutputStream oos;
        dateFormat = new SimpleDateFormat("MM/dd/yyyy");
        date = dateFormat.format(calendar.getTime());

        try{
            fos = context.openFileOutput(filename, Context.MODE_PRIVATE);
            oos = new ObjectOutputStream(fos);
            oos.writeObject(date + ": " + userNotes);
            oos.close();
            fos.close();
        } catch(Exception e){
            Log.d("Review", "Exception on saving", e);
        }
    }

    public void loadFromFile(Context context, String filename){
        FileInputStream fos;
        ObjectInputStream oos;

        try{
            fos = new FileInputStream(context.getFileStreamPath(filename));
            oos = new ObjectInputStream(fos);
            userNotes = (String) oos.readObject();
            oos.close();
            fos.close();
        } catch(Exception e){
            Log.d("Review", "Exception on saving", e);
        }
    }
}
