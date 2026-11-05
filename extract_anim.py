import zlib

POINTER_OFFSET = 0x101C50

with open("dk64.z64", "rb") as fh:
    fh.seek(POINTER_OFFSET + (13 << 2))
    tbl_13 = POINTER_OFFSET + int.from_bytes(fh.read(4), "big")
    fh.seek(tbl_13)
    file_start = POINTER_OFFSET + int.from_bytes(fh.read(4), "big")
    file_end = POINTER_OFFSET + int.from_bytes(fh.read(4), "big")
    file_size = file_end - file_start
    fh.seek(file_start)
    indic = int.from_bytes(fh.read(2), "big")
    fh.seek(file_start)
    data = fh.read(file_size)
    if indic == 0x1F8B:
        data = zlib.decompress(data, (15 + 32))
    with open("anim.bin", "wb") as fg:
        fg.write(data)