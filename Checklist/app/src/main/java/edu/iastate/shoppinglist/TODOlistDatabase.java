package edu.iastate.shoppinglist;

import android.content.Context;

import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;

/**
 * This is the class that sets up the database for the app
 * Each item in the database has an ID, Name, and a string containing the content
 */
@Database(entities={TODOlist.class}, version = 1, exportSchema = false)
public abstract class TODOlistDatabase extends RoomDatabase {

    public abstract TODOlistDao getTODOlistDao();

    private static TODOlistDatabase TODOlistDB;

    /**
     * Method to create the database if not already created
     * @param context this is the context used to build the database with
     * @return returns a database holding objects of type TODOlist
     */
    public static TODOlistDatabase getInstance(Context context) {
        if(TODOlistDB==null)
            TODOlistDB = buildDatabaseInstance(context);
        return TODOlistDB;
    }

    private static TODOlistDatabase buildDatabaseInstance(Context context) {
        return Room.databaseBuilder(context, TODOlistDatabase.class, Constants.DB_NAME).allowMainThreadQueries().build();
    }

    /**
     * public method to destroy the database
     */
    public void cleanUp(){
        TODOlistDB = null;
    }

}
