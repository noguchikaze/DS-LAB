//delete part
node *p = 0; *c = root; //parent and current
node *left_max = 0; //the key node to take over the node deleted
node *right_min = 0;
node *temp = 0;
//search for the target to delete
while( c != NULL )  //only if current node is not NULL so that we can enter loop
{
  if(c->data == target) //current node is the target
  {//and we need to DELETE in this if statement!!!!!!
    left_max = find_left_max(c);  //return MAX in c->left_ch
    if (left_max == NULL) // if c has no left subtree exists
    {
      if(c == root)
      { root = root->right_ch;  }
      else //if c has parent
      {
        // take the right_min to replace the target
        right_min = find_right_min(c);

      }
      delete c;
      return void;
    }
    // left_max exists
    //replace current target node with the left_max info
    if(p == NULL)
    { //if the target node is root
      if(root->left_ch == left_max)//the case of skewed left subtree
      {
        left_max->right_ch = root->right_ch;
        left_max->parent->left_ch = NULL;  //cut off the original parent
      }
      else  //the left subtree contains left_max exists right subtree
      {
        left_max->right_ch = root->right_ch;
        left_max->parent->right_ch = left_max->left_ch;
        left_max->left_ch = root->left_ch;
      }
      root = left_max;  //change the content of root
      left_max->parent = NULL;  //now the left_max becomes root
      delete c; //delete the current target (root)
    }//end of if(p == NULL)
    else if( c == p->left_ch) //if target < parent
    {

    }
    else if ( c == p->right_ch) // if target > parent
  }
  else if ( target < c->data)//indicate that the target is in c->left
  {
    p = c;  // p will be c's parent while traversing
    c = c->left_ch; //point to the key < current key
  }
  else if( target > c->data)//indicate that the target is in c->right
  {
    p = c;  // p will be c's parent while traversing
    c = c->right_ch;  //point to the key > current key
  }
  else // well there must be something wrong if running to this else statement
  { cout << "DELETE state error!!! CHECK IT!!!" << endl; return void;}
}//end of while
//when c = NULL that we jump out the loop and that means the target doesn't exist
cout << "Nothing can be deleted! The target does not exist"<<endl;
