# ttytie
Concatenate multiple ttyrec sessions into a continuous one, eliminating time gaps

## Building
`make`

Tested under GNU/Linux, and Windows using the [MSYS2][4] environment.

## Usage
`./ttytie [-d <DELAY>] 1.ttyrec [2.ttyrec [...]]`

The program receives a list of one or more names of files recorded by [ttyrec][1],
concatenates them in order of appearance in the argument list, and prints the result 
to `stdout`. Timestamps in each file from the second one onwards are shifted so
that there is but a small fixed delay between each two consecutive `ttyrec` sessions.
This makes the resulting session look smooth and continuous, even if the
original sessions were recorded at arbitrary moments in time.

The optional `-d` argument can be used to set a (fractional) amount of seconds
to delay between consecutive sessions. The default value is 1.0.

### Example

`./ttytie -d 1.5 a.ttyrec b.ttyrec c.ttyrec > result.ttyrec`

This will concatenate three ttyrec sessions with a 1.5 seconds delay between them
and save the output to `result.ttyrec`.

## Motivation

This program was originally written as a means to merge multiple `ttyrec` files
containing one playthrough from a public [NetHack][2] server into a single `ttyrec`
file. The intention was then to render the resulting `ttyrec` into a video recording.
As a game of NetHack may span months or even years of discontinuous playing, and 
since timestamps in `ttyrec` format are absolute, using a simple utility like `cat`
would lead to the resulting session containing huge delays. While the `ttyplay`
utility allows skipping frames by pressing a key, it would be difficult to apply this
to an automated video rendering scenario in the general case.

No logic in this program specifically depends on `ttyrec`s containing NetHack games,
and it can be used to concatenate `ttyrec` sessions of any nature.

## Alternatives

There seems to exist a program called [TTYCONCAT][3] which claims to be specifically
suited for concatenating recordings of NetHack games, along with having numerous
additional features. However, it only seems to be available in the form of a Windows
executable, no source code seems to be available, and the usage/copying terms are 
unclear.


[1]: http://0xcc.net/ttyrec/
[2]: https://www.nethack.org/
[3]: http://www.codehappy.net/nethack/ttyrec.htm#ttyconcat
[4]: https://www.msys2.org/
