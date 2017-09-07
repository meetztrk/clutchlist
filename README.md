# ClutchList
You can create a new list or manage your list with this tool.<br/><br/>
## Creating a new list
You should define a *clutchList* pointer and call function *newList*.<br/>
`clutchList* list = newList();`


### Add an item
You can call *addItem* or *insertItem* for add an item.<br/>
*addItem* functions need two parameters, *clutchList* pointer and item pointer.<br/>
`addItem(clutchList*, &item);`<br/><br/>
*insertItem* functions need more parameter, it is index, the second function parameter should be index.
`insertItem(clutchList*, int index, &item);`
