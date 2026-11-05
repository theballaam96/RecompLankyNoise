with open("temp.bin", "rb") as fh:
    with open("src/hajaga.c", "w") as fg:
        fg.write("#include \"modding.h\"\n")
        fg.write("#include \"ultra64.h\"\n")
        fg.write("#include \"recompconfig.h\"\n")
        fg.write("#include \"recompdata.h\"\n")
        fg.write("#include \"recompui.h\"\n")
        fg.write("#include \"recompui_event_structs.h\"\n")
        fg.write("#include \"rt64_extended_gbi.h\"\n")
        fg.write("#include \"enums.h\"\n")
        fg.write("#include \"common_structs.h\"\n")
        fg.write("__attribute__((aligned(8))) u8 hajaga[] = {\n\t")
        size = len(fh.read())
        fh.seek(0)
        for x in range(size):
            fg.write(str(int.from_bytes(fh.read(1), "big")))
            if x == (size - 1):
                fg.write("\n")
            elif (x % 8) == 7:
                fg.write(",\n\t")
            else:
                fg.write(", ")
        fg.write("};\n")
        fg.write(f"u32 hajaga_size = {size};\n")