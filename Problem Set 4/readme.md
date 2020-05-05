## Filter_less

Creates methods that apply the following filter types to photos..
- Grayscale
- Sepia
- Reflect
- Blur

## Filter_more

* not yet implemented

## Recover

Recover files from a memory card. Requires running checks to validate the bytes at the beggining of a jpeg file. The first 4 bytes have a pattern...
- 0xff
- 0xd8
- 0xff
- 0xe0, 0xe1, 0xe2, 0xe3, etc...
