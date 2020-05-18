package edu.iastate.shoppinglist;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

/**
 * This is a class to handle changing views in the app
 */
public class TODOlistsAdapter extends RecyclerView.Adapter<TODOlistsAdapter.BeanHolder> {

    private List<TODOlist> list;
    private Context context;
    private LayoutInflater layoutInflater;
    private OnTODOlistItemClick onTODOlistItemClick;

    /**
     * This is the public contructor for the class
     * @param list This is the list of TODOlists for the app
     * @param context This is the context for the TODOlists
     */
    public TODOlistsAdapter(List<TODOlist> list, Context context) {
        layoutInflater = LayoutInflater.from(context);
        this.list = list;
        this.context = context;
        this.onTODOlistItemClick = (OnTODOlistItemClick) context;
    }

    /**
     * This is a helper method to return a BeanHolder containing a wanted view
     * @param parent This is the parent of the wanted view
     * @param viewType This is the type of the wanted view
     * @return
     */
    @Override
    public BeanHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = layoutInflater.inflate(R.layout.shoppinglist_list_item, parent, false);
        return new BeanHolder(view);
    }

    /**
     * This is a helper method to log and set the textViews of the wanted view
     * @param holder This is the BeanHolder that contains the view you're editing
     * @param position This is the position in the list of the TODOlist youre editing
     */
    @Override
    public void onBindViewHolder(BeanHolder holder, int position) {
        Log.e("bind", "onBindViewHolder: " + list.get(position));
        holder.textViewName.setText(list.get(position).getName());
        holder.textViewContent.setText(list.get(position).getContent());
    }

    /**
     * This is a helper method to return the number of TODOslists
     * @return an int containing the number of total TODOlists
     */
    @Override
    public int getItemCount() {
        return list.size();
    }

    /**
     * This is the main class for handling the Recycler and setting up the behavior for
     * when a TODOlist is clicked.
     */
    public class BeanHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        TextView textViewContent;
        TextView textViewName;

        /**
         * This is the public contructor for the BeanHolder
         * @param itemView the view of the selected TODOlist
         */
        public BeanHolder(View itemView) {
            super(itemView);
            itemView.setOnClickListener(this);
            textViewContent = itemView.findViewById(R.id.item_text);
            textViewName = itemView.findViewById(R.id.item_name);
        }

        /**
         * This is the method to handle when a TODOlist is clicked
         * @param view the view of the TODOlist that was clicked
         */
        @Override
        public void onClick(View view) {
            onTODOlistItemClick.onTODOlistClick(getAdapterPosition());
        }
    }

    /**
     * This is the interface for when a TODOlist is clicked
     */
    public interface OnTODOlistItemClick {
        void onTODOlistClick(int pos);
    }

}
