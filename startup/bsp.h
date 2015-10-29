#ifndef _BSP_H_
#define _BSP_H_

/*pcm1795 related gpio*/
#define PCM1795_IIC_SDA_PORT   GPIO_PORTN_BASE
#define PCM_1795_IIC_SDA_PIN   GPIO_PIN_4
#define PCM1795_IIC_SCL_PORT   GPIO_PORTN_BASE
#define PCM_1795_IIC_SCL_PIN   GPIO_PIN_5

#define PCM_1795_RST_PORT      GPIO_PORTP_BASE
#define PCM_1795_RST_PIN       GPIO_PIN_4


/*src4382 related gpio*/
#define SRC4382_IIC_SDA_PORT   GPIO_PORTN_BASE
#define SRC4382_IIC_SDA_PIN    GPIO_PIN_4
#define SRC4382_IIC_SCL_PORT   GPIO_PORTN_BASE
#define SRC4382_IIC_SCL_PIN    GPIO_PIN_5

#define SRC4382_RST_PORT       GPIO_PORTP_BASE
#define SRC4382_RST_PIN        GPIO_PIN_5


/*lcd releated gpio*/
#define LCD_BRIGHT_PORT				 GPIO_PORTF_BASE
#define LCD_BRIGHT_PIN         GPIO_PIN_1 
#define LCD_RS_PORT            GPIO_PORTD_BASE
#define LCD_RS_PIN             GPIO_PIN_1
#define LCD_RW_PORT            GPIO_PORTD_BASE
#define LCD_RW_PIN             GPIO_PIN_0
#define LCD_EN_PORT            GPIO_PORTD_BASE
#define LCD_EN_PIN             GPIO_PIN_7
#define LCD_DB4_PORT           GPIO_PORTD_BASE
#define LCD_DB4_PIN            GPIO_PIN_5
#define LCD_DB5_PORT           GPIO_PORTD_BASE
#define LCD_DB5_PIN            GPIO_PIN_4
#define LCD_DB6_PORT           GPIO_PORTE_BASE
#define LCD_DB6_PIN            GPIO_PIN_5
#define LCD_DB7_PORT           GPIO_PORTE_BASE
#define LCD_DB7_PIN            GPIO_PIN_4

#define LCD_PWM_PORT GPIO_PORTF_BASE
#define LCD_PWM_PIN  GPIO_PIN_1
#define LCD_PWM_CHANNEL  GPIO_PF1_M0PWM1


/*key, encoder, led related gpio*/
#define ENCODE_A_PORT        	 GPIO_PORTD_BASE
#define ENCODE_A_PIN           GPIO_PIN_3
//#define ENCODE_A_INT           INT_GPIOD
#define ENCODE_B_PORT        	 GPIO_PORTQ_BASE
#define ENCODE_B_PIN           GPIO_PIN_0
#define ENCODE_B_INT           INT_GPIOQ0

#define KEY_STB_PORT       		 GPIO_PORTE_BASE
#define KEY_STB_PIN						 GPIO_PIN_1
#define KEY_MISO_PORT          GPIO_PORTE_BASE
#define KEY_MISO_PIN           GPIO_PIN_0
#define KEY_SCK_PORT           GPIO_PORTE_BASE
#define KEY_SCK_PIN            GPIO_PIN_2


/*adc related gpio*/
#define MDC_CARD_DETECT0_PORT  GPIO_PORTB_BASE  
#define MDC_CARD_DETECT0_PIN   GPIO_PIN_5  
#define MDC_CARD_DETECT1_PORT  GPIO_PORTB_BASE  
#define MDC_CARD_DETECT1_PIN   GPIO_PIN_4  


/*njw1194 related gpio*/
#define NJW1194_MOSI_PORT      GPIO_PORTE_BASE
#define NJW1194_MOSI_PIN       GPIO_PIN_3
#define NJW1194_CS_PORT        GPIO_PORTE_BASE
#define NJW1194_CS_PIN         GPIO_PIN_1
#define NJW1194_CLK_PORT       GPIO_PORTE_BASE
#define NJW1194_CLK_PIN        GPIO_PIN_2


/*MDC related gpio*/
#define MDC_MOSI_PORT          GPIO_PORTA_BASE
#define MDC_MOSI_PIN					 GPIO_PIN_4
#define MDC_MISO_PORT          GPIO_PORTA_BASE
#define MDC_MISO_PIN           GPIO_PIN_5
#define MDC_CS_PORT            GPIO_PORTA_BASE
#define MDC_CS_PIN             GPIO_PIN_3
#define MDC_CLK_PORT           GPIO_PORTA_BASE
#define MDC_CLK_PIN            GPIO_PIN_2

#define MDC_INTM0_PORT         GPIO_PORTQ_BASE
#define MDC_INTM0_PIN          GPIO_PIN_5
#define MDC_INTM1_PORT         GPIO_PORTM_BASE
#define MDC_INTM1_PIN          GPIO_PIN_3

#define MDC_PS01_PORT          GPIO_PORTK_BASE
#define MDC_PS01_PIN           GPIO_PIN_6
#define MDC_PS02_PORT          GPIO_PORTM_BASE
#define MDC_PS02_PIN           GPIO_PIN_0

#define MDC_M0PS_ON_PORT       GPIO_PORTK_BASE
#define MDC_M0PS_ON_PIN        GPIO_PIN_5
#define MDC_M1PS_ON_PORT       GPIO_PORTL_BASE
#define MDC_M1PS_ON_PIN        GPIO_PIN_0

#define MDC_PM0EN_PORT         GPIO_PORTK_BASE
#define MDC_PM0EN_PIN					 GPIO_PIN_7
#define MDC_PM1EN_PORT         GPIO_PORTM_BASE
#define MDC_PM1EN_PIN					 GPIO_PIN_1
#define MDC_SPI                SSI0_BASE

#define MDC_IIS_SELECT_PORT    GPIO_PORTM_BASE
#define MDC_IIS_SELECT_PIN     GPIO_PIN_4

#define GPIO1M0_PORT           GPIO_PORTG_BASE
#define GPIO1M0_PIN            GPIO_PIN_2
#define GPIO2M0_PORT           GPIO_PORTG_BASE
#define GPIO2M0_PIN            GPIO_PIN_3
#define GPIO3M0_PORT           GPIO_PORTG_BASE
#define GPIO3M0_PIN            GPIO_PIN_6
#define GPIO4M0_PORT           GPIO_PORTG_BASE
#define GPIO4M0_PIN            GPIO_PIN_7

#define GPIO1M1_PORT           GPIO_PORTK_BASE
#define GPIO1M1_PIN            GPIO_PIN_4
#define GPIO2M1_PORT           GPIO_PORTM_BASE
#define GPIO2M1_PIN            GPIO_PIN_7
#define GPIO3M1_PORT           GPIO_PORTM_BASE
#define GPIO3M1_PIN            GPIO_PIN_6
#define GPIO4M1_PORT           GPIO_PORTM_BASE
#define GPIO4M1_PIN            GPIO_PIN_5

#define MDC_PA0_PORT           GPIO_PORTA_BASE
#define MDC_PA0_PIN            GPIO_PIN_6
#define MDC_PA1_PORT           GPIO_PORTA_BASE
#define MDC_PA1_PIN            GPIO_PIN_7
#define MDC_PA2_PORT           GPIO_PORTF_BASE
#define MDC_PA2_PIN            GPIO_PIN_0

/*power management gpio*/
#define AC_STANDBY_PORT        GPIO_PORTK_BASE
#define AC_STANDBY_PIN				 GPIO_PIN_1
#define AC_DETECT_PORT				 GPIO_PORTK_BASE
#define AC_DETECT_PIN					 GPIO_PIN_2
#define DC5V_EN_PORT					 GPIO_PORTK_BASE
#define DC5V_EN_PIN						 GPIO_PIN_3
#define DC3V_EN_PORT					 GPIO_PORTM_BASE
#define DC3V_EN_PIN						 GPIO_PIN_2
#define POWER_EN01_PORT        GPIO_PORTC_BASE
#define POWER_EN01_PIN         GPIO_PIN_7
#define PS_EN_PORT             GPIO_PORTC_BASE
#define PS_EN_PIN              GPIO_PIN_6

#define AC_STANDBY(x)          GPIO_PIN_SET(AC_STANDBY_PORT, AC_STANDBY_PIN, x)
#define DC5V_EN(x)             GPIO_PIN_SET(DC5V_EN_PORT, DC5V_EN_PIN, x)
#define DC3V_EN(x)             GPIO_PIN_SET(DC3V_EN_PORT, DC3V_EN_PIN, x)
#define POWER_EN01(x)          GPIO_PIN_SET(POWER_EN01_PORT, POWER_EN01_PIN, x)
#define PS_EN(x)							 GPIO_PIN_SET(PS_EN_PORT, PS_EN_PIN, x)

/*audio control gpio*/
#define AMP_MUTE_PORT          GPIO_PORTH_BASE
#define AMP_MUTE_PIN           GPIO_PIN_1

#define AMP_MUTE_ON()						 GPIO_PIN_SET(AMP_MUTE_PORT, AMP_MUTE_PIN, 0)
#define AMP_MUTE_OFF()					 GPIO_PIN_SET(AMP_MUTE_PORT, AMP_MUTE_PIN, 1)

/*IR related gpio*/
#define TIME0_DIVISION 12000
#define FRONT_IR_PORT    GPIO_PORTD_BASE
#define FRONT_IR_PIN     GPIO_PIN_2
#define FRONT_IR_IRQ     INT_GPIOD
#define IR_IN_PORT       GPIO_PORTL_BASE
#define IR_IN_PIN        GPIO_PIN_2

/*Detect related gpio*/
#define AUDIO_SENSE_PORT   GPIO_PORTC_BASE
#define AUDIO_SENSE_PIN    GPIO_PIN_4
#define TRIGGER_IN_PORT    GPIO_PORTL_BASE
#define TRIGGER_IN_PIN     GPIO_PIN_1
#define AC_DETECT_PORT     GPIO_PORTK_BASE
#define AC_DETECT_PIN      GPIO_PIN_2
#define POWER_GOOD_PORT    GPIO_PORTH_BASE
#define POWER_GOOD_PIN     GPIO_PIN_0
#define DC_ERROR_PORT      GPIO_PORTH_BASE
#define DC_ERROR_PIN       GPIO_PIN_2

#define IS_AC_ERROR        (GPIO_ReadSinglePin(AC_DETECT_PORT, AC_DETECT_PIN) == 0? 1:0)
#define IS_POWER_GOOD_ERROR  (GPIO_ReadSinglePin(POWER_GOOD_PORT, POWER_GOOD_PIN) == 0? 1:0)
#define IS_DC_ERROR        (GPIO_ReadSinglePin(DC_ERROR_PORT, DC_ERROR_PIN) == 1? 1:0)

/*EPROM related gpio*/
#define EPROM_SDA_PORT   GPIO_PORTB_BASE
#define EPROM_SDA_PIN    GPIO_PIN_3
#define EPROM_SCL_PORT   GPIO_PORTB_BASE
#define EPROM_SCL_PIN    GPIO_PIN_2

/*74hc595 related gpio*/
#define HC595_DATA_PORT  GPIO_PORTE_BASE
#define HC595_DATA_PIN   GPIO_PIN_3
#define HC595_CLK_PORT   GPIO_PORTE_BASE
#define HC595_CLK_PIN    GPIO_PIN_2
#define HC595_CS_PORT    GPIO_PORTC_BASE
#define HC595_CS_PIN     GPIO_PIN_6

/*LED related gpio*/
#define LEDA_PORT        GPIO_PORTQ_BASE
#define LEDA_PIN         GPIO_PIN_1
#define LEDB_PORT        GPIO_PORTQ_BASE
#define LEDB_PIN         GPIO_PIN_2



#define GPIO_PIN_SET(port,pin,value) do{ \
	if(value){ \
		GPIOPinWrite(port,pin,pin); } \
	else{ \
		GPIOPinWrite(port,pin,0); } \
	}while(0)
	
#define GPIO_PIN_GET(port, pin) (GPIOPinRead(port, pin) == 0? 0:1)
	
#define BSP_ADC0_CHANNLE_MAX  8
	
void bsp_adc_init(void);
	
void bsp_timer0_init(void);
	
uint32 bsp_timer0_get_time(void);
	
void bsp_spi0_init(void);		
void bsp_delay_us(uint32 time);
void bsp_delay_ms(uint32 time);
int bsp_adc0_load(uint16 *buf, uint8 channle, uint8 offset);
void bsp_gpio_init(void);
int bsp_spi_operate(uint32 base, uint32 data);
	
void bsp_pwm1_init(void);
	
void bsp_lcd_bright_control(uint8 duty);

uint8 GPIO_ReadSinglePin(uint32 ulPort, uint8 ucPins);
	
void bsp_timer1_init(void);
	
uint32 bsp_get_elapsedMs(uint32 start);

uint32 bsp_get_curMs(void);

void bsp_spi0_ctl(spi_ctl_t *ctl);
	
#endif



