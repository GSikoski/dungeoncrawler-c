# Dungeon Crawler C (On hold)

## What is it?
A small project that I've used to learn some basic C.
Initially, I planned on only making a single game but it spiralled into more of a mini, text-based RPG game engine.

## How to run it?
The code needs to be compiled on Linux. GCC works fine. If you run `source .env`, the alias `build` will be applied for compiling.
Otherwise, you can run:

`gcc -o a.out *.c`

## How to write for it?
Currently, the only flexible part of the engine is the content of the dungeon. This content is in the `/scripts` directory.
There are a handful of keywords available right now.

### $CHK
The checkpoint tag. Leave it at the end of the script file with the directions to the next file e.g.

`$CHK GORP`

Will end the current script file and load the script contained in `/scripts/GORP.txt`

### $CHOICE & $ GOTO
The choice tag. Another tag for the end of the script file. The structure for 2 choices follows:

```
$CHOICE 2             <- # choices
You do a thing.       <- 1st choice action
$GOTO THING1          <- 1st choice location (/scripts/THING1.txt)
You do another thing
$GOTO THING2
```

### Int
If the parser reads a single integer, it will change the current text speed to print each character after that many milliseconds.
The change is permanent until it is changed again.

```
60                           <- regular text speed
You walk into the building
20                           <- pretty quick
BANG!
60
The door slams behind you
200                          <- really slow
You hear a slow groaning noise in the distance.
```

### Text
The rest is treated as plain text. 
