# VirtualBox Saved State Parser (For Forensics)

## Description:

1) This tool has been used back in 2014 for a CTF Challenge [ASIS-QUALS-2014](http://blog.rentjong.net/2014/05/asis-quals-2014-forensic-300.html)

2) I found this tool to be interesting and decided to save it here in my [GitHub repository](https://github.com/ab2pentest/VirtualBox_SavedState_Parser). I am not sure who the original author of the tool is, but I wanted to preserve it for future reference and potentially contribute to its development..

3) Also you must know that this tool use [liblzf](http://cvs.schmorp.de/liblzf/README) library.

```
LZF is an extremely fast (not that much slower than a pure memcpy)
compression algorithm. It is ideal for applications where you want to
save *some* space but not at the cost of speed. It is ideal for
repetitive data as well. The module is self-contained and very small.
```

# Usage

Before we can use the tool, we need to clone or download it to our local machine.

```
git clone https://github.com/ab2pentest/VirtualBox_SavedState_Parser
```

After that we will need to compile it.

```
gcc parsevbox.c lzf_d.c -o parsevbox
gcc extract_screenshot.c -o extract_screenshot
```

![2022-02-23_01-57-12](https://user-images.githubusercontent.com/84577967/160249355-6a41c043-2ad6-47e8-80d4-9a72fc799ca6.png)

Once we have compiled both files, we can run the tool by following these steps:

```bash
./parsevbox date_savedstateimage.sav
```

The process of running the tool may take several minutes, as it decompresses the `.sav` file and generates additional files that may be useful for forensic analysis.

![2022-03-26_18-14-05](https://user-images.githubusercontent.com/84577967/160250250-768abb89-af80-4540-a1f7-707a174a627f.png)

Great ! Now that the tool has finished running, we can examine the output files to see what they contain.

![2022-03-26_18-15-02](https://user-images.githubusercontent.com/84577967/160250289-6ba2e355-ce88-464d-8a25-f333e86fded9.png)

To extract the screenshot from the output, we can follow these steps:

1) Locate the file `*.sav-DisplayScreenshot.out` in the output directory and rename it to `vbox.img-DisplayScreenshot.out`.
2) Run the `extract_screenshot` tool. This will generate three files: `out.png`, `out.raw`, and `out.ppm`.

These files should contain the screenshot data, which we can view or analyze as needed.

```bash
mv *.sav-DisplayScreenshot.out vbox.img-DisplayScreenshot.out
./extract_screenshot
```

![2022-03-26_18-22-49](https://user-images.githubusercontent.com/84577967/160250508-2995723e-c1da-4696-8537-0371ed5166f8.png)

We can now preview the `out.png` image file to see the screenshot.

![2022-03-26_18-23-55](https://user-images.githubusercontent.com/84577967/160250602-aa618e08-c257-47c2-b076-167dd5e3204b.png)

# Links

Original tool link: https://www.dropbox.com/sh/vtsk0ji7pqhje42/AABY57lRqinlwZpo8t9zzGYka

Original tool writeup (in Turkish): [ASIS-QUALS-2014](http://blog.rentjong.net/2014/05/asis-quals-2014-forensic-300.html)
