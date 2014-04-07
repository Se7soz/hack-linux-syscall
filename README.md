hack-linux-syscall
==================

Hijack the linux system calls, for example when the open system call is called, the new hijacked system call is called instead of the original one.


Features

    Hijack linux system call table
    Overriding open system call table with another one
    You can use it to hijack any other system call table

Video demo:
  
    http://se7so.blogspot.com/2012/07/hijacking-linux-system-calls-rootkit.html
    
Compile & Run:

    1. Uncompress the tar file
    2. cd hijack-linux-sys-calls/
    3. Listen to the two music files and diff between them
    4. sudo ./load.sh
    5. Listen now to tamer.mp3, the other file will be opened instead of it
    
