# What is this?

This project aims to simplify renaming SNES music files from a standardized name format, into their actual song titles.

You can actually download old-school SNES music via http://www.snesmusic.org. After this you'll receive a folder full of ".rsn" files with cryptic filenames. These filenames can be renamed to the actual game title names using the instructions on the [website](http://www.snesmusic.org/v2/players.php#renset), though this project aims to eventually make that painless.

Once the ".rsn" files are renamed, they can be extracted as RAR files. The only trouble is, the files within conform to a standardized filename structure. They are *not* named by the title of the original song.

*This project will unrar the ".rsn" files passed in as arguments and rename all extracted song files to their original song titles automatically, and to a desginated output directory.*