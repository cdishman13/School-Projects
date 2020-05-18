package edu.iastate.shoppinglist;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Update;

import java.util.List;

/**
 * This class is used to query and edit the database
 */
@Dao
public interface TODOlistDao {

    //Retrieve all of the TODOlists from the database
    @Query("SELECT * FROM " + Constants.TABLE_NAME_TODOLIST)
    List<TODOlist> getTODOlists();

    //Insert a new TODOlist into the database
    @Insert
    long insertTODOlist(TODOlist TODOlist);

    //Update a TODOlist in the database
    @Update
    void updateTODOlist(TODOlist repos);

    //Delete a TODOlist from the database
    @Delete
    void deleteTODOlist(TODOlist TODOlist);

    //Delete ALL TODOlists from the database
    @Delete
    void deleteTODOlists(TODOlist... TODOlist);

}
