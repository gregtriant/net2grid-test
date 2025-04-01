

# 24bit Integers
code path:
```
./inc/byteInt.h
```

## Implemented
My solution uses the `linked list` that was created in the other exercise in order to store the integer in more than 3 bytes.
- Store any type of int to the `Number` struct.

- Retrive the correct value from the `Number` struct.

- Use `storeToLinkedListSinged` for `signed` ints and the `storeToLinkedList` for `unsinged`.

TODO:
- In order to save to a Ybyte integer, a macro that defines the correct struct could be used.

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
