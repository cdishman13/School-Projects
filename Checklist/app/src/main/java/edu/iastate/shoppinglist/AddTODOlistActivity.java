package edu.iastate.shoppinglist;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;

import java.lang.ref.WeakReference;

/**
 * This is the main activity for adding or editing lists in the app.
 * This class handles the activities for handling the lists
 */
public class AddTODOlistActivity extends AppCompatActivity {

    private TextInputEditText et_name, et_content;
    private boolean update;

    private TODOlist TODOlist;
    private TODOlistDatabase TODOlistDatabase;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_shoppinglist);
        et_name = findViewById(R.id.et_name);
        et_content = findViewById(R.id.et_content);
        TODOlistDatabase = TODOlistDatabase.getInstance(AddTODOlistActivity.this);
        Button button = findViewById(R.id.but_save);
        if ( (TODOlist = (TODOlist) getIntent().getSerializableExtra("TODOlist"))!=null ){
            getSupportActionBar().setTitle("Update TODOlist");
            update = true;
            button.setText("Update");
            et_name.setText(TODOlist.getName());
            et_content.setText(TODOlist.getContent());
        }

        button.setOnClickListener(new View.OnClickListener() {
            /**
             * This method is used to update the list on the update button click
             * @param view this is the view for the button
             */
            @Override
            public void onClick(View view) {
                if (update){
                    TODOlist.setContent(et_content.getText().toString());
                    TODOlist.setName(et_name.getText().toString());
                    TODOlistDatabase.getTODOlistDao().updateTODOlist(TODOlist);
                    setResult(TODOlist,2);
                }
                else {
                    TODOlist = new TODOlist(et_content.getText().toString(), et_name.getText().toString());
                    new InsertTask(AddTODOlistActivity.this,TODOlist).execute();
                }
            }
        });
    }

    private void setResult(TODOlist TODOlist, int flag){
        setResult(flag,new Intent().putExtra("TODOlist",TODOlist));
        finish();
    }

    private static class InsertTask extends AsyncTask<Void,Void,Boolean> {

        private WeakReference<AddTODOlistActivity> activityReference;
        private TODOlist TODOlist;

        InsertTask(AddTODOlistActivity context, TODOlist TODOlist) {
            activityReference = new WeakReference<>(context);
            this.TODOlist = TODOlist;
        }

        @Override
        protected Boolean doInBackground(Void... objs) {
            long j = activityReference.get().TODOlistDatabase.getTODOlistDao().insertTODOlist(TODOlist);
            TODOlist.setTODOlist_id(j);
            Log.e("ID ", "doInBackground: "+j );
            return true;
        }

        @Override
        protected void onPostExecute(Boolean bool) {
            if (bool){
                activityReference.get().setResult(TODOlist,1);
                activityReference.get().finish();
            }
        }
    }

}
