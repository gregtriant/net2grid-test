

# Linked List Implemention

code path:
```
./inc/list.h
```

## Implemented
A `linked list` struct that has void* data inside.
- Can store `any type` of data.

- The user is able to `insert` new data at any position.

- The user is able to `delete` any node of the linked list.

- The user can `retrieve` data at any position.

- The user has to define the `allocation` and `dealocation` functions that the list will use.

TODO:
- In order to make it `thread safe`, we need to add a `mutex` to the `head` node of the list. Then on every function that is called with the head, we will `lock` the mutex, and then `unlock` before any return statement.

- Iteration capabilities can be added by passing in a function to an iterration method, that runs with the data of the current node as arguements.

## Run
In order to run the implementation run the following script in `linux`.
```
./run.sh
```

If you want the Debug out put to show, edit the line of `run.sh` script:
```
...

cmake -DDEBUG_MODE=ON ..

...
```

