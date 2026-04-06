// ============================================================
//  Line Follower Robot — PIC16F887
//  MikroC Pro for PIC
// ============================================================

// --- LCD module pin connections ---
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;

// --- State tracking for LCD updates ---
int current = 1;
int new     = 0;

// --- Forward declaration ---
void lcd();

// ============================================================
void main() {
    // Initialise and clear LCD
    Lcd_init();
    Lcd_cmd(_LCD_CLEAR);
    Lcd_cmd(_LCD_CURSOR_OFF);
    Lcd_out(1, 3, "LINE FOLLOWER");
    delay_ms(1000);
    Lcd_cmd(_LCD_CLEAR);
    Lcd_cmd(_LCD_CURSOR_OFF);

    // Port configuration
    ANSEL  = 0;
    TRISA  = 0xFF;   // IR sensor inputs  (RA0 = left sensor, RA1 = right sensor)
    TRISD  = 0x00;   // All PORTD pins as output

    /*  PORTD pin map
     *  RD1  — Left-turn  LED output
     *  RD2  — Right-turn LED output
     *  RD4  — Motor 1 IN1
     *  RD5  — Motor 1 IN2
     *  RD6  — Motor 2 IN1
     *  RD7  — Motor 2 IN2
     */

    while (1) {

        // Case 4 — Both sensors on white: move forward
        while (PORTA.f0 == 1 && PORTA.f1 == 1) {
            new = 1;
            PORTD.f4 = 1; PORTD.f5 = 0;   // Motor 1 forward
            PORTD.f6 = 1; PORTD.f7 = 0;   // Motor 2 forward
            PORTD.f2 = 0; PORTD.f1 = 0;   // LEDs off
            lcd();
        }

        // Case 2 — Left sensor on black line: turn left
        while (PORTA.f0 == 0 && PORTA.f1 == 1) {
            new = 2;
            PORTD.f4 = 0; PORTD.f5 = 0;   // Motor 1 stop
            PORTD.f6 = 1; PORTD.f7 = 0;   // Motor 2 forward
            PORTD.f2 = 0; PORTD.f1 = 1;   // Left LED on
            lcd();
        }

        // Case 3 — Right sensor on black line: turn right
        while (PORTA.f0 == 1 && PORTA.f1 == 0) {
            new = 3;
            PORTD.f4 = 1; PORTD.f5 = 0;   // Motor 1 forward
            PORTD.f6 = 0; PORTD.f7 = 0;   // Motor 2 stop
            PORTD.f2 = 1; PORTD.f1 = 0;   // Right LED on
            lcd();
        }

        // Case 1 — Both sensors on black line: stop
        while (PORTA.f0 == 0 && PORTA.f1 == 0) {
            new = 4;
            PORTD.f4 = 0; PORTD.f5 = 0;   // Motor 1 stop
            PORTD.f6 = 0; PORTD.f7 = 0;   // Motor 2 stop
            PORTD.f2 = 1; PORTD.f1 = 1;   // Both LEDs on
            lcd();
        }
    }
}

// ============================================================
// lcd() — Updates the LCD only when the motion state changes
// ============================================================
void lcd() {
    if (new != current) {
        Lcd_Cmd(_LCD_CLEAR);
        switch (new) {
            case 1: Lcd_out(1, 3, "MOVING FORWARD"); break;
            case 2: Lcd_out(1, 3, "TURNING LEFT");   break;
            case 3: Lcd_out(1, 3, "TURNING RIGHT");  break;
            case 4: Lcd_out(1, 3, "STOPPED");        break;
        }
        current = new;
    }
}
