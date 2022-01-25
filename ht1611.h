#ifndef _HT1611_
#define _HT1611_

#define HT_PORT_DIR      DDRD		// Port to use
#define HT_PORT			 PORTD
#define DI  			 PD0		// Serial data input (CMOS in pull-high)
#define SK	             PD1		// Clock input (CMOS in pull-high)

#define DIGITS_COUNT	  10		// Number of digits		
#define POWER_ON_DELAY_MS 2000		// milliseconds
#define TA_TIME_US        2			// Data setup time ( ?1us )
#define TB_TIME_US        4			// Data hold on time ( ?2us )
#define TC_TIME_US        5			// Inter digit time ( ?5us )

void ht1611_init(void);
void ht1611_display_char(char chr);
void ht1611_display_str(char *s);
void ht1611_display_clear(void);
void on(uint8_t bit);
void off(uint8_t bit);

#endif /* _HT1611_ */