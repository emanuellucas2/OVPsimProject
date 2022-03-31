/*
// Openrisc memory map for RTL
//
//
// ram   - text
// ram   - data, bss, stack
//
*/  


MEMORY
        {
        ram    : ORIGIN = 0x00000000, LENGTH = 0x10000000
        stk    : ORIGIN = 0xfffffffc, LENGTH = 0x00000000        
        }
 
SECTIONS
{    
    .text : 
    {
        *(.text)
        *(.text.*)
        *(.glue_7t)
        *(.glue_7)
        *(.rodata)
    } > ram
            
    .data :
    {
        *(.data)
    } > ram
    
    .bss :
    {
        *(.bss)
    } > ram
    
    .rodata.cst4 :
    {
        *(.rodata.cst4)
        *(.rodata.str1.1)
        _heap = .;
    } > ram
            
    .stack :
    {
        _tos = .;
    } > stk
}
