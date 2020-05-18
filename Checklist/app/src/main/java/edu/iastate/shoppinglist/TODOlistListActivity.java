package edu.iastate.shoppinglist;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;


import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

/**
 * This is the main activity for showing and selecting TODOlists in the app
 */
public class TODOlistListActivity extends AppCompatActivity implements TODOlistsAdapter.OnTODOlistItemClick {

    private TextView textViewMsg;
    private RecyclerView recyclerView;
    private int pos;

    private TODOlistDatabase TODOlistDatabase;
    private TODOlistsAdapter TODOlistsAdapter;
    private List<TODOlist> TODOlists;

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initializeViews();
        displayList();
    }

    private void displayList() {
        TODOlistDatabase = TODOlistDatabase.getInstance(TODOlistListActivity.this);
        new RetrieveTask(this).execute();
    }

    private static class RetrieveTask extends AsyncTask<Void,Void,List<TODOlist>> {
        private WeakReference<TODOlistListActivity> activityReference;

        RetrieveTask(TODOlistListActivity context) {
            activityReference = new WeakReference<>(context);
        }

        @Override
        protected List<TODOlist> doInBackground(Void... voids) {
            if(activityReference.get() != null)
                return activityReference.get().TODOlistDatabase.getTODOlistDao().getTODOlists();
            else
                return null;
        }

        @Override
        protected void onPostExecute(List<TODOlist> TODOlists) {
            if(TODOlists != null && TODOlists.size()>0) {
                activityReference.get().TODOlists.clear();
                activityReference.get().TODOlists.addAll(TODOlists);
                activityReference.get().textViewMsg.setVisibility(View.GONE);
                activityReference.get().TODOlistsAdapter.notifyDataSetChanged();
            }
        }

    }

    /**
     * This is the method to initialize the views of the app and bind them
     */
    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    public void initializeViews() {
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        textViewMsg = findViewById(R.id.name_empty);
        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(listener);
        recyclerView = findViewById(R.id.recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(TODOlistListActivity.this));
        TODOlists = new ArrayList<>();
        TODOlistsAdapter = new TODOlistsAdapter(TODOlists,TODOlistListActivity.this);
        recyclerView.setAdapter(TODOlistsAdapter);
    }

    private View.OnClickListener listener = new View.OnClickListener() {
        /**
         * This is the method to deal with clicking a TODOlist
         * @param view the view of the TODOlist clicked
         */
        @Override
        public void onClick(View view) {
            startActivityForResult(new Intent(TODOlistListActivity.this,AddTODOlistActivity.class),100);
        }
    };

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 100 && resultCode > 0) {
            if (resultCode == 1) {
                TODOlists.add((TODOlist) data.getSerializableExtra("TODOlist"));
            } else if (resultCode == 2) {
                TODOlists.set(pos, (TODOlist) data.getSerializableExtra("TODOlist"));
            }
            listVisibility();
        }
    }

    /**
     * This is the method to handle clicking on a TODOlist item
     * A user can delete, edit, or copy a TODOlist
     * @param pos this is an int to represent what button was pressed. 1=delete, 2=edit, 3=copy
     */
    @Override
    public void onTODOlistClick(final int pos) {
        new AlertDialog.Builder(TODOlistListActivity.this)
                .setTitle("Select Options")
                .setItems(new String[]{"Delete", "Edit", "Copy"}, new DialogInterface.OnClickListener() {
                    /**
                     * This is a method to handle the delete, edit and copy buttons after clicking a TODOlist
                     * @param dialogInterface this is what dialog was selected for the interface
                     * @param i this int represents which button was pressed in the form of a switch
                     */
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        switch (i){
                            case 0: //Delete the TODOlist
                                TODOlistDatabase.getTODOlistDao().deleteTODOlist(TODOlists.get(pos));
                                TODOlists.remove(pos);
                                listVisibility();
                                break;
                            case 1: //Edit the TODOlist
                                TODOlistListActivity.this.pos = pos;
                                startActivityForResult(
                                        new Intent(TODOlistListActivity.this, AddTODOlistActivity.class).putExtra("TODOlist",TODOlists.get(pos)),100);
                                break;
                            case 3: //Copy the TODOlist
                                break;
                        }
                    }
                }).show();

    }

    private void listVisibility(){
        int emptyMsgVisibility = View.GONE;
        if (TODOlists.size() == 0){ // no item to display
            if (textViewMsg.getVisibility() == View.GONE)
                emptyMsgVisibility = View.VISIBLE;
        }
        textViewMsg.setVisibility(emptyMsgVisibility);
        TODOlistsAdapter.notifyDataSetChanged();
    }

    @Override
    protected void onDestroy() {
        TODOlistDatabase.cleanUp();
        super.onDestroy();
    }


}
