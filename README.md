# What is this?

This project aims to simplify renaming SNES music files from a standardized name format, into their actual song titles.

You can actually download old-school SNES music via http://www.snesmusic.org. After this you'll receive a folder full of ".rsn" files with cryptic filenames. These rsn files can be renamed to the actual game title names using the [instructions for renset](http://www.snesmusic.org/v2/players.php#renset) on the SNESmusic.org website, until this project can do that job too.

Once the ".rsn" files are renamed, they can be extracted as RAR files. The only trouble is, the files within conform to a standardized 8.3 filename structure. They are *not* named by the title of the original song.

**This project will unrar the ".rsn" files passed in as arguments into folders inside a designated output directory (`processed/` by default) and rename all extracted ".spc" song files to their original song titles automatically.**

# Usage

```
spcrenamer [-o outputDir] RSN_FILE...
```

## Example

Possible folder structure (but do it however you like):

```
----- rsn/
   |   \--- abc.rsn
   |    --- xyz.rsn
   |
   -- renamed/
   |
   -- spcrenamer/
       \-- spcrenamer
        -- libunrar.so
```

Typing this command from the root:

```
./spcrenamer/spcrenamer -o renamed rsn/*.rsn
```

Will produce:

```
renamed/
 \-- abc/
 |    \-- 01-Title.spc
 |    |-- 02-Intro.spc
 |    |   ...
 |    |-- etc.
 \-- xyz/
      \-- 01-Title.spc
      |-- 02-Intro.spc
      |   ...
      |-- etc.
```

If you were just to extract the rsn files manually with an archiver, the spc filenames would resemble `abc-01.spc`. This application will dig into the header of each spc file for its song title, and rename it as above. The filename of the rsn is used to extract the spc files to a directory of the same name. Until this project can rename the rsn files to their game titles, using [renset](http://www.snesmusic.org/v2/players.php#renset) is recommended before you begin.
