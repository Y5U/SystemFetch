# SystemFetch
Another neofetch-like utility but this time it's fast.

# Example
  ![example](https://raw.githubusercontent.com/Y5U/SystemFetch/main/example.png)

# Speed
Here is a table of the time it took to execute all of these programs, measured in ms and using an average of 10 runs.
SystemFetch | neofetch | screenfetch | pfetch
----------- | ---------|-------------|---------|
1.002 ms    | 165.59 ms| 412.153 ms  |14.392 ms|

As you can see SystemFetch is about 14x faster than the fastest program (pfetch).

  
# Compile
```
$ git clone https://github.com/Y5U/SystemFetch.git
$ cd SystemFetch
$ make
# make install
$ sf
```

# Compatibility
This is probably not very portable, though I am trying to make it. If you want to help, test it on your BSD or Linux distrobution and report any errors or issues.
* Tested OSes
  + Arch Linux
  + FreeBSD (no memory support)

# TODO
* Add ascii art (maybe)
* Add memory compatibility with freeBSD
