package edu.iastate.shoppinglist;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.Ignore;
import androidx.room.PrimaryKey;

import java.io.Serializable;

/**
 * This is the class for the TODOlist object
 * This class implements serializable for tracking in the database
 * The table name for the TODOlist objects database is a constant
 */
@Entity(tableName = Constants.TABLE_NAME_TODOLIST)
public class TODOlist implements Serializable {

    //This is the value that the database will use as it's primary key
    @PrimaryKey(autoGenerate = true)
    private long TODOlist_id;

    //Columns in the database will be named "TODOlist_content"
    @ColumnInfo(name="TODOlist_content")
    private String content;

    private String name;

    /**
     * Public constructor to create a TODOlist object
     * @param content This is the items in the list
     * @param name This is the name of the list
     */
    public TODOlist(String content, String name) {
        this.content = content;
        this.name = name;
    }

    @Ignore
    public TODOlist(){}

    /**
     * Public method to get the ID of a TODOlist
     * @return the serialized id of the TODOlist in the form of a long
     */
    public long getTODOlist_id() {
        return TODOlist_id;
    }

    /**
     * Public method to set the ID of a TODOlist
     * @param TODOlist_id the id that you want the list to have
     */
    public void setTODOlist_id(long TODOlist_id) {
        this.TODOlist_id = TODOlist_id;
    }

    /**
     * Public method for getting the content of a TODOlist
     * @return the content part of the TODOlist in the form of a String
     */
    public String getContent() {
        return content;
    }

    /**
     * Public method for setting the content of a TODOlist
     * @param content a String containing whatever you want as the content of the list
     */
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * Public method for getting the name of a TODOlist
     * @return a String containing the name of the TODOlist
     */
    public String getName() {
        return name;
    }

    /**
     * Public method for setting the name of a TODOlist
     * @param name a String containing what you want the TODOlist to be named
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Public helper method for comparing two TODOlists
     * @param o This is the object you want to compare with the TODOlist
     * @return true if they're the same, false if not
     */
    @Override
    public boolean equals(Object o) {
        if(this==o) return true;
        if(!(o instanceof TODOlist)) return false;
        TODOlist TODOlist = (TODOlist) o;
        if(TODOlist_id != TODOlist.TODOlist_id) return false;
        return name != null ? name.equals(TODOlist.name) : TODOlist.name==null;
    }

    /**
     * Public helper method to convert the TODOlist id into a hashcode
     * @return the hashcode of the TODOlist id
     */
    @Override
    public int hashCode() {
        int result = (int) TODOlist_id;
        result = 31 * result + (name!=null ? name.hashCode() : 0);
        return result;
    }

    /**
     * Public helper method to convert the TODO list as a string
     * @return a String containing all the text from the TODOlist
     */
    @Override
    public String toString() {
        return "TODOlist{"+"TODOlist_id="+TODOlist_id +",content='"+content+'\''+",name='" + name + '\'' + '}';
    }
}
