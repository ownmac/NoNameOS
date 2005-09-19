#include <kernel/irq.h>
#include <kernel/kernel.h>
#include <kernel/idt.h>
#include <kernel/isr.h>

ISR irq_stubs[IRQ_ENTRYS] =
{
    irq00, irq01, irq02, irq03, irq04, irq05, irq06, irq07,
	irq08, irq09, irq10, irq11, irq12, irq13, irq14, irq15
};

void irq_remap( void )
{
    outportb( 0x20, 0x11 );
    outportb( 0xA0, 0x11 );

    outportb( 0x21, 0x20 );
    outportb( 0xA1, 0x28 );

    outportb( 0x21, 0x04 );
    outportb( 0xA1, 0x02 );

    outportb( 0x21, 0x01 );
    outportb( 0xA1, 0x01 );

    outportb( 0x21, 0x00 );
    outportb( 0xA1, 0x00 );
}

void irq_init( void )
{
	int i;

    irq_remap();

	for( i=32 ; i<48 ; i++ )
	{
		idt_setEntry(  i, irq_stubs[i-32], 0x08, 0x8E );
		isr_setHandler( i, NULL );
	}
}