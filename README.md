# VirtualBox Saved State Parser (For Forensics)

## Important:

1) This tool has been used back in 2014 for a CTF Challenge [ASIS-QUALS-2014](http://blog.rentjong.net/2014/05/asis-quals-2014-forensic-300.html)

2) I don't know who's the original tool writer but I found it really helpfull so I thought about saving it here in github.

3) Also you must know that this tool use [liblzf](http://cvs.schmorp.de/liblzf/README) library.

```
LZF is an extremely fast (not that much slower than a pure memcpy)
compression algorithm. It is ideal for applications where you want to
save *some* space but not at the cost of speed. It is ideal for
repetitive data as well. The module is self-contained and very small.
```

## Usage:

We first need to compile the files:

```
gcc parsevbox.c lzf_d.c -o parsevbox
gcc extract_screenshot.c -o extract_screenshot
```

![2022-02-23_01-57-12](https://user-images.githubusercontent.com/84577967/160249355-6a41c043-2ad6-47e8-80d4-9a72fc799ca6.png)

After we compile both of files we can run the tool easily in this way:

```bash
./parsevbox date_savedstateimage.sav
```

The process may take several minutes while it decompress the `.sav` file and will drop out some files that we can use later in forensics ...

![2022-03-26_18-14-05](https://user-images.githubusercontent.com/84577967/160250250-768abb89-af80-4540-a1f7-707a174a627f.png)

Great ! We can list out the dropped out files

![2022-03-26_18-15-02](https://user-images.githubusercontent.com/84577967/160250289-6ba2e355-ce88-464d-8a25-f333e86fded9.png)

To extract the screenshot from the output we have a file `*.sav-DisplayScreenshot.out` that we should rename to `vbox.img-DisplayScreenshot.out`
and then we can run `extract_screenshot` tool, this will drop 3 files `out.png`, `out.raw` and `out.ppm`

```bash
mv *.sav-DisplayScreenshot.out vbox.img-DisplayScreenshot.out
./extract_screenshot
```

![2022-03-26_18-22-49](https://user-images.githubusercontent.com/84577967/160250508-2995723e-c1da-4696-8537-0371ed5166f8.png)

Now we can preview the `out.png` image file

![2022-03-26_18-23-55](https://user-images.githubusercontent.com/84577967/160250602-aa618e08-c257-47c2-b076-167dd5e3204b.png)

# Links

Original tool link: https://www.dropbox.com/sh/vtsk0ji7pqhje42/AABY57lRqinlwZpo8t9zzGYka

Original tool writeup (in Turkish): [ASIS-QUALS-2014](http://blog.rentjong.net/2014/05/asis-quals-2014-forensic-300.html)
