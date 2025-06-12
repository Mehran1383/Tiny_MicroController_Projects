#include <reg51.h>
#include <absacc.h>

#define SEGMENT_PORT P1
#define DIGIT_PORT P2

sbit START_STOP = P3^0;  // Start/Stop button at P3.0
sbit RESET = P3^1; 			// Reset button at P3.1

unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char running = 0;
unsigned char tick_count = 0;
unsigned char display_digit = 0;
unsigned char display_buffer[4];

// 7-segment codes for common cathode (0-9)
const unsigned char seg_code[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void timer0_isr(void) interrupt 1 
{
    TH0 = 0xD8; // Reload for 10ms (11.0592MHz)
    TL0 = 0xF0;
    
    if(running) {
        tick_count++;
        
        if(tick_count >= 100) { 
            tick_count = 0;
            seconds++;
            
            if(seconds >= 60) {
                seconds = 0;
                minutes++;
                
                if(minutes >= 60) {
                    minutes = 0;
                }
            }
        }
    }
}

void update_display_buffer() 
{
    display_buffer[0] = minutes / 10;    
    display_buffer[1] = minutes % 10;    
    display_buffer[2] = seconds / 10;    
    display_buffer[3] = seconds % 10;    
}

void display() 
{
    // Turn off all digits
    DIGIT_PORT = 0xFF;
    
    SEGMENT_PORT = seg_code[display_buffer[display_digit]];
    
    switch(display_digit) {
        case 0: DIGIT_PORT &= ~0x01; break; 
        case 1: DIGIT_PORT &= ~0x02; break; 
        case 2: DIGIT_PORT &= ~0x04; break; 
        case 3: DIGIT_PORT &= ~0x08; break; 
    }
    
    display_digit = (display_digit + 1) % 4;
}

void init_timer() 
{
    TMOD = 0x01;    // Timer 0, mode 1 
    TH0 = 0xD8;     // High byte for 10ms
    TL0 = 0xF0;     // Low byte
    ET0 = 1;        // Enable Timer 0 interrupt
    EA = 1;         // Enable global interrupts
    TR0 = 1;        // Start timer
}

void main() 
{
    init_timer();
    
    while(1) {
        update_display_buffer();
        display();
        
        if(START_STOP == 0) { 
            while(START_STOP == 0); 
            running = !running;
        }
        
        if(RESET == 0) { 
            while(RESET == 0); 
            seconds = 0;
            minutes = 0;
            tick_count = 0;
            running = 0;
        }
    }
}