
#define PRINT_ALL              0xffffffff
#define PRINT_ELF_HEADER       (1 << 1)
#define PRINT_SECTION_HEADER   (1 << 2)
#define PRINT_PROGRAM_HEADER   (1 << 3)
#define PRINT_SYMBOL_TABLE     (1 << 4)
#define PRINT_RELOCATION_TABLE (1 << 5)

void set_on_flag(uint64_t &flags, uint64_t f)
{
    flags |= f; 
}

void set_off_flag(uint64_t &flags, uint64_t f)
{
    flags &= ~f; 
}

bool get_flag(uint64_t &flags, uint64_t f)
{
    return (flags & f);
}