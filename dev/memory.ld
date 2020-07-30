ENTRY(_start)

SECTIONS{
	. = 0x8000;
	
	__start = .;

	.text : {
		obj/arm7.o(.text*);
		*(.text*);
	}

	.rodata : {
		*(.rodata*);
	}

	.data : {		
		*(.data*);
	}

	.bss : {
		*(.bss*);
	}

	.=ALIGN(8);
	__end = .;
}
