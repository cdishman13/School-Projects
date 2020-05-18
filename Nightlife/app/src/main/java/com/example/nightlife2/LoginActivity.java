package com.example.nightlife2;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;


public class LoginActivity extends AppCompatActivity {

    private String username;
    private String password;
    EditText usr, pass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        usr = findViewById(R.id.username);
        pass = findViewById(R.id.password);
    }

    /**
     * Function that is called when the "Login" button is clicked
     * Checks if the account the user enters is valid
     * If it is valid then it sends them to the map - MapsActivity
     * @param view the current view
     */
    public void loginButtonClicked(View view){
        username = usr.getText().toString();
        password = pass.getText().toString();

        //validate(username, password);
        if(!username.equals("") && !password.equals("")){
            Intent intent = new Intent(this, MapsActivity.class);
            startActivity(intent);
        }
    }

    /**
     * Checks to see if the password the user enters matches the username in the database
     * @param user String that is the username
     * @param pass String that is the password
     * @return
     */
    public boolean validate(String user, String pass){
        //TODO
        //Check if username is in database
        //Check if password that user entered corresponds to the correct password
        return true;
    }

    /**
     * Function that is called when the "New User" button is clicked
     * Send the user to create a user page - NewUserActivity
     * @param view the current view
     */
    public void newUserButtonClicked(View view){
        Intent intent = new Intent(this, NewUserActivity.class);
        startActivity(intent);
    }
}
