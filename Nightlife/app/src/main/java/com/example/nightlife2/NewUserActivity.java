package com.example.nightlife2;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class NewUserActivity extends AppCompatActivity {

    EditText usr, pass;
    private String new_usr;
    private String new_pass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_user);

        usr = findViewById(R.id.new_user);
        pass = findViewById(R.id.new_pass);
    }

    /**
     * Function that will be called when the user clicks the button "New User"
     * Takes in the text that the user entered for username and password and saves it to the database
     * @param view current view
     */
    public void newUserButtonClicked(View view){
        new_usr = usr.getText().toString();
        new_pass = pass.getText().toString();
        //TODO save the info to database

        if(!new_usr.equals("") && !new_pass.equals("") && validate(new_pass)){
            startActivity(new Intent(this, LoginActivity.class));
        }
    }

    /**
     * Checks to see if the password contains all of the requirements
     * @param password String that is the users password
     * @return True if the password is a valid password. False is the password isn't valid
     */
    public boolean validate(String password){
        if(password.length() < 6){
            Toast toast = Toast.makeText(this, "Must have at least 6 letters", Toast.LENGTH_SHORT);
            toast.show();
            return false;
        }
        if(password.equals(password.toLowerCase())){
            Toast toast = Toast.makeText(this, "Must have an uppercase letter", Toast.LENGTH_SHORT);
            toast.show();
            return false;
        }
        return true;
    }

}
