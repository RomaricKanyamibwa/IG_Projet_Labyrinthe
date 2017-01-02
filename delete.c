nodeT *ListDelete(nodeT *currP, elementT value)
{
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;

  /*
   * Check to see if current node is one
   * to be deleted.
   */
  if (currP->element == value) {
    nodeT *tempNextP;

    /* Save the next pointer in the node. */
    tempNextP = currP->next;

    /* Deallocate the node. */
    free(currP);

    /*
     * Return the NEW pointer to where we
     * were called from.  I.e., the pointer
     * the previous call will use to "skip
     * over" the removed node.
     */
    return tempNextP;
  }

  /*
   * Check the rest of the list, fixing the next
   * pointer in case the next node is the one
   * removed.
   */
  currP->next = ListDelete(currP->next, value);


  /*
   * Return the pointer to where we were called
   * from.  Since we did not remove this node it
   * will be the same.
   */
  return currP;
}
