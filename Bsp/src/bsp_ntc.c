#include "bsp_ntc.h"
#include <stdlib.h>
#include "bsp.h"


#define Zero_Degree           5828    
#define ADC_Sample_Times      60

#define COMPENSATION_VALUE    1

#define OLDER_ARRAY           0



uint16_t *pArray[23];
uint8_t find_out_temperature_value;
uint8_t temp_uint16_t_vlue;
uint8_t length_simple;

uint16_t temp_variable_value_1;

uint8_t  temp_degree;
uint8_t temp_decimal_point;
uint16_t ntc_voltage_value;

typedef struct Msg_NTC
{
  
    uint8_t temp_degree;
    uint8_t temperature_value;
    uint8_t temperature_decimal_point_value;
    uint8_t temperature_rectify_value;
    uint16_t ntc_voltage_value ;  

}MSG_NTC_T;

MSG_NTC_T   g_ntc; /* 定义一个结构体用于消息队列 */



static uint16_t Read_NTC_Temperature_Voltage(void);

static int8_t  Binary_Search(const uint8_t *array ,uint8_t key,uint8_t length);

static uint8_t error_range_calculate_value(uint8_t val);




static void Read_Ntc_Decimal_Point_Numbers(void);

static uint8_t Calculate_Display_Temperature_Value(const uint16_t *pt,uint16_t key,uint8_t length);
static uint8_t Calculate_Display_Temperature_19_21_Value(const uint16_t *pt,uint16_t key,uint8_t length);

uint8_t search_key;


typedef enum{

   degree_zero = 0,
   degree_one = 1,
   degree_two = 2,
   degree_three = 3,
   degree_four = 4,
   degree_five =5,
   degree_six = 6,
   degree_seven = 7,
   degree_eight = 8,
   degree_nine = 9,
   degree_ten = 10,
   degree_eleven = 11,
   degree_twelve = 12,
   degree_thirteen =13,
   degree_fourteen = 14,
   degree_fiveteen =15,
   degree_sixteen =16,
   degree_seventeen =17,
   degree_eighteen = 18,
   degree_nineteen = 19,
   degree_twenty = 20,
   degree_twenty_one = 21,
   degree_twenty_two =22
   
   


}degree_state;


int8_t left_point =0;
int8_t right_point ;
//int8_t length = sizeof(R10K_NTC_81)/(sizeof(R10K_NTC_81[0]));
int8_t mid_value;
//拆分成23个数组，mid =11
static const uint16_t R10K_0_0[2]={2558,2528};   // //array[0]
static const uint16_t R10K_1_4[4]={2497,2466,2434,2402};// //array[1]

/*******************new cal************************/
/***************NTC RES F3950**********************/
static const uint16_t R10K_5_7[3]={2382,2348,2314};  //array[2] =34
static const uint16_t R10K_8_10[3]={2280,2245,2210};  //array[3] = 35
static const uint16_t R10K_11_13[3]={2174,2138,2102};  //array[4] = 37

static const uint16_t R10K_14_15[2]={2065,2028};      //array[5] =37
static const uint16_t R10K_16_18[3]={1991,1954,1917};   //array[6] =37

static const uint16_t R10K_19_21[3]={1880,1843,1806}; //array[7] =37
static const uint16_t R10K_22_23[2]={1769,1731};       //array[8] =36
static const uint16_t R10K_24_26[3]={1694,1658,1622};  //array[9]  = 36

static const uint16_t R10K_27_29[3]={1586,1551,1516}; ////array[10] = 35
static const uint16_t R10K_30_32[3]={1481,1447,1413};//array[11] =34

static const uint16_t R10K_33_35[3]={1379,1346,1313};////array[12] =33
static const uint16_t R10K_36_38[3]={1281,1249,1218}; //array[13]=32

static const uint16_t R10K_39_41[3]={1187,1157,1127};//array[14]=30

static const uint16_t R10K_42_45[4]={1098,1069,1041,1013};//array[15]=28
static const uint16_t R10K_46_49[4]={986,960,934,909};//array[16]=25
static const uint16_t R10K_50_53[4]={884,860,836,813};//array[17]=23


static const uint16_t R10K_54_58[5]={790,768,747,762,706}; //array[18] =20

static const uint16_t R10K_59_63[5]={686,667,648,629,612}; //array[19] =17

static const uint16_t R10K_64_70[7]={594,577,561,545,529,514,500};//array[20] =14

static const uint16_t R10K_71_76[6]={485,472,458,445,432,420};//array[21] =12
/******************end new cal*************************************/



static const uint8_t R10K_Init_0_81_simple[23]={

    25,24,23,22,21,
	20,19,18,17,16,
	15,14,13,12,11,
	10,9,8,7,6,
	5,4,3
};


static uint16_t Read_NTC_Temperature_Voltage_Power_On(void)
{
      uint16_t read_ntc_value;
	 
	  read_ntc_value = Get_Adc_Voltage_Value(ADC_Sample_Times);
	
      

	  return read_ntc_value;
}



static uint16_t Read_NTC_Temperature_Voltage(void)
{
      uint16_t read_ntc_value;
	 
	  read_ntc_value = Get_Adc_Voltage_Value(ADC_Sample_Times);
	
      

	  return read_ntc_value;
}


/*************************************************************************
	*
	*Functin Name: static int8_t  Binary_Search(uint8_t *R10K_NTC_81 ,uint8_t key)
	*Funtion: binary search arithmetic
	*
	*
	*
*************************************************************************/
static int8_t  Binary_Search(const uint8_t *array ,uint8_t key,uint8_t length)
{
     left_point =0 ;
	right_point = length -1;
   while(left_point <= right_point){

        mid_value = (left_point + right_point)/2;

        if(key == array[mid_value]){

		    return   mid_value;

		}
        else if(array[mid_value] >   key ){ //right ->big number

             left_point = mid_value +1;
			

		}
		else if(array[mid_value] < key){ //left -> small number

          right_point = mid_value -1;
		   

       }
	} 
   
	return -1;
} 

/*********************************************************************
    *
*Funtion Name:static void Analysis_Read_Ntc_Votalge(uint8_t readvalue)
    *
    *
*********************************************************************/
static void Read_Ntc_Decimal_Point_Numbers(void)
{
   
   uint8_t temp_decimal_point;
   temp_decimal_point = R10K_Init_0_81_simple[g_ntc.temperature_value] - R10K_Init_0_81_simple[g_ntc.temperature_value +1];

   temp_decimal_point = temp_decimal_point +5;

   g_ntc.temperature_decimal_point_value =  temp_decimal_point/10 ;
   
}
/******************************************************************************
	*
	*Function Name: Read_NTC_Temperature_Value_Handler(void)
	*
	*
	*
******************************************************************************/
void Read_NTC_Temperature_Power_On(void)
{

      
  g_ntc.ntc_voltage_value=Read_NTC_Temperature_Voltage_Power_On(); //Read_NTC_Temperature_Voltage();
  temp_uint16_t_vlue= g_ntc.ntc_voltage_value/100;
  length_simple = sizeof(R10K_Init_0_81_simple)/sizeof(R10K_Init_0_81_simple[0]);
    
  g_ntc.temp_degree = Binary_Search(R10K_Init_0_81_simple,temp_uint16_t_vlue,length_simple);

  Display_Speicial_Temperature_Value(g_ntc.temp_degree);

}

/******************************************************************************
	*
	*Function Name: Read_NTC_Temperature_Value_Handler(void)
	*
	*
	*
******************************************************************************/
void Read_NTC_Temperature_Value_Handler(uint8_t set_temp_flag,uint8_t set_temp_value)
{
    
    
	
	 g_ntc.ntc_voltage_value= Read_NTC_Temperature_Voltage();
     temp_uint16_t_vlue= g_ntc.ntc_voltage_value /100;
	 length_simple = sizeof(R10K_Init_0_81_simple)/sizeof(R10K_Init_0_81_simple[0]);
    
   	 g_ntc.temp_degree = Binary_Search(R10K_Init_0_81_simple,temp_uint16_t_vlue,length_simple);

	 Display_Speicial_Temperature_Value(g_ntc.temp_degree);

     
	 
	 if(set_temp_flag== 1){
         if(set_temp_value >= g_ntc.temperature_value){
//                   g_ntc.relay_keep_temp_flag =1;
//			       KEEP_HEAT_LED_ON();
//	               RELAY_KEEP_TEMP_SetHigh();
//				   KEY_FUN_CONFIRM_LED_ON() ;  
//				   ADD_DEC_LED_OFF();

			  }
              else{
//                  g_ntc.relay_keep_temp_flag =0;
//			      KEEP_HEAT_LED_OFF();
//	              RELAY_KEEP_TEMP_SetLow();
//				  KEY_FUN_CONFIRM_LED_ON() ;
//				   ADD_DEC_LED_OFF();

              }


	 }

	 Smg_Display_Temp_Degree_Handler(g_ntc.temperature_value, g_ntc.temperature_decimal_point_value);
  

}


void Smg_Display_Temp_Degree_Value(void)
{

   Smg_Display_Temp_Degree_Handler(g_ntc.temperature_value, g_ntc.temperature_decimal_point_value);



}

/******************************************************************************
	*
	*Function Name: static void Display_Speicial_Temperature_Value(uint8_t temp)
	*Function :calculate special value
	*Input Ref: speical transmit display temperature value 
	*Return Ref:NO
	*
******************************************************************************/
void Display_Speicial_Temperature_Value(uint8_t temp)
{
   static uint8_t array_subscript;

   switch(temp){

    case degree_zero: //zero degree

         // zero_d =2;
        array_subscript =  Calculate_Display_Temperature_Value(R10K_0_0,g_ntc.ntc_voltage_value,2);
       // HAL_Delay(5);
        g_ntc.temperature_value = g_ntc.temperature_rectify_value ;

    break;

	
   case degree_one :
   	    array_subscript =  Calculate_Display_Temperature_Value(R10K_1_4,g_ntc.ntc_voltage_value,4);
	    //HAL_Delay(5);
        switch(array_subscript){

		 case 0:
		 	g_ntc.temperature_value = 1 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 1:
		 	g_ntc.temperature_value = 2 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 2:
		 	g_ntc.temperature_value = 3 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 3:
		 	g_ntc.temperature_value = 4 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

        }

   break;
   
   case degree_two: //5À~~7 度
   	   array_subscript =  Calculate_Display_Temperature_Value(R10K_5_7,g_ntc.ntc_voltage_value,3);
	   /// HAL_Delay(5);
	   switch(array_subscript){

		 case 0:
		 	g_ntc.temperature_value = 5 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;

		 break;

		 case 1:
		 	g_ntc.temperature_value = 6 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 2:
		 	g_ntc.temperature_value = 7 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;

		 break;

		

        }

   break;

   
   case degree_three :

         array_subscript =  Calculate_Display_Temperature_Value(R10K_8_10,g_ntc.ntc_voltage_value,3);
		 // HAL_Delay(5);
  		
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 8 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 9 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 2:
			  g_ntc.temperature_value = 10 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  
   
		  }

   break;
   
   case degree_four: //11~~13 度

         array_subscript =  Calculate_Display_Temperature_Value(R10K_11_13,g_ntc.ntc_voltage_value,3);
		//	 HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 11 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 12 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 13 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;

   case degree_five : //14~`15 degree
		 array_subscript =  Calculate_Display_Temperature_Value(R10K_14_15,g_ntc.ntc_voltage_value,2);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 14 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 15 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		
   
		  }
   break;
   
   case degree_six://16~18 度
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_16_18,g_ntc.ntc_voltage_value,3);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 16 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 17 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 18 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_seven : //19~21
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_19_21,g_ntc.ntc_voltage_value,3);
		//  HAL_Delay(5);

		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 19 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 20 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 2:
			  g_ntc.temperature_value = 21 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
   
		  }

   break;

  
   case degree_eight : //22``23 degree
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_22_23,g_ntc.ntc_voltage_value,2);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 22 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 23 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		 
   
		  }

   break;

   
case degree_nine ://24`~26 degree
   	    array_subscript =  Calculate_Display_Temperature_Value(R10K_24_26,g_ntc.ntc_voltage_value,3);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 24 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 25 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 26 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_ten :
   	 array_subscript =  Calculate_Display_Temperature_Value(R10K_27_29,g_ntc.ntc_voltage_value,3);
	   //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 27 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 28 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 29 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case  degree_eleven :
   		 array_subscript =  Calculate_Display_Temperature_Value(R10K_30_32,g_ntc.ntc_voltage_value,3);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 30 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 31 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 32 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_twelve :
   	   	 array_subscript =  Calculate_Display_Temperature_Value(R10K_33_35,g_ntc.ntc_voltage_value,3);
	     //  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 33 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 34 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 35 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;

   case degree_thirteen :
   		 array_subscript =  Calculate_Display_Temperature_Value(R10K_36_38,g_ntc.ntc_voltage_value,3);
		//  HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 36 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 37 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 38 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_fourteen : //39~`41 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_39_41,g_ntc.ntc_voltage_value,3);
	    //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 39 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 40 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 41 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;

   case degree_fiveteen : //42~45 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_42_45,g_ntc.ntc_voltage_value,4);
	    //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 42 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 43 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 44 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  g_ntc.temperature_value = 45 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;


   case degree_sixteen : //46~49 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_46_49,g_ntc.ntc_voltage_value,4);
	    //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 46 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 47 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 48 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 3:
			  g_ntc.temperature_value = 49 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		  
   
		  }


   break;

   case degree_seventeen : //50~53 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_50_53,g_ntc.ntc_voltage_value,4);
	    //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 50 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 51 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 52 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  g_ntc.temperature_value = 53 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

   
		  }


   break;

   case degree_eighteen : //54~58 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_54_58,g_ntc.ntc_voltage_value,5);
	    //   HAL_Delay(5);
		 switch(array_subscript){
   
		   case 0:
			  g_ntc.temperature_value = 54 + g_ntc.temperature_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  g_ntc.temperature_value = 55 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  g_ntc.temperature_value = 56 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  g_ntc.temperature_value = 57 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 4:
			  g_ntc.temperature_value = 58 + g_ntc.temperature_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
   
		  }


   break;
   


}
}
/******************************************************************************
	*
	*Function Name: static uint8_t Calculate_Display_Temperature_Value(const uin16_t *pt,uint8_t length)
	*Function :calculate special value
	*Input Ref: speical transmit display temperature value 
	*Return Ref:NO
	*
******************************************************************************/
static uint8_t Calculate_Display_Temperature_Value(const uint16_t *pt,uint16_t key,uint8_t length)
{
      uint8_t i,error_value;
	
	
	  uint16_t temp_temperature_value;
      for(i=0;i<length;i++){

	   if(i==0){
               if(*(pt+0) < key){


			      error_value = error_range_calculate_value(key);


			    if(key- *(pt+0) >=error_value){

				 	g_ntc.temperature_rectify_value = -1;
				 }
				else{
					g_ntc.temperature_rectify_value =0;
				}
				
				    temp_decimal_point = key - *(pt+i);

			        temp_decimal_point = temp_decimal_point  + 5;


                     if(temp_decimal_point > 9 && temp_decimal_point< 100){
                            g_ntc.temperature_decimal_point_value =  temp_decimal_point %10;
                    }
                    else if(temp_decimal_point > 99    && temp_decimal_point< 1000){
                        g_ntc.temperature_decimal_point_value =  (temp_decimal_point %100) %10 ;

                    }
                    else if(temp_decimal_point    < 10){
                        g_ntc.temperature_decimal_point_value =  temp_decimal_point;
                      }

               }
               
			  	
			    temp_temperature_value  = i;
				return temp_temperature_value ;

             }
             else if(*(pt+i) >=  key && (*(pt+i+1) <= key)){ //high temperature degree is number is smaller

           
			
		   temp_decimal_point = *(pt+i) -key;

              temp_decimal_point = temp_decimal_point + 4;
           

		    if(temp_decimal_point > 9 && temp_decimal_point< 100){
                    g_ntc.temperature_decimal_point_value =  temp_decimal_point %10;
            }
            else if(temp_decimal_point > 99    && temp_decimal_point< 1000){
                g_ntc.temperature_decimal_point_value =  (temp_decimal_point %100) %10 ;

            }
            else if(temp_decimal_point    < 10){
                g_ntc.temperature_decimal_point_value =  temp_decimal_point;
              }
                   
            
				temp_temperature_value =  i;
				return temp_temperature_value ;

            

		 }
		 else if(i==(length-1)){

               if(*(pt+i) >  key){


                error_value = error_range_calculate_value(key);
			   if((*(pt+i) - key) >=error_value){
                 g_ntc.temperature_rectify_value =1;
				 
               }
			   else
		      	  g_ntc.temperature_rectify_value =0;

			    temp_decimal_point = *(pt+i)-key; //小数点

                temp_decimal_point = temp_decimal_point + 4;

		        if(temp_decimal_point > 9 && temp_decimal_point< 100){
                    g_ntc.temperature_decimal_point_value =  temp_decimal_point %10;
                    }
                    else if(temp_decimal_point > 99    && temp_decimal_point< 1000){
                        g_ntc.temperature_decimal_point_value =  (temp_decimal_point %100) %10 ;

                    }
                    else if(temp_decimal_point    < 10){
                        g_ntc.temperature_decimal_point_value =  temp_decimal_point;
                      }

                temp_temperature_value  = i;

				return temp_temperature_value ;
			   	

               }

		 }
		
	  }
	  return 0;
}



static uint8_t  error_range_calculate_value(uint8_t val)
{

  uint8_t ret;
  switch(val){


  case 2:

  case 3:

  case 4:

  case 5:

   case 9: //R10K_24_26

    ret = 36;

    return ret;
   break;

   case 13: //R10K_36_38

     ret = 32;

     return ret;

   break;

   case 15:

      ret = 28;

     return ret;

   break;

   case 17: //R10K_46_49

      ret = 23;

     return ret;

   break;


   case 18:
   	  ret = 20;

     return ret;

   break;


   case 19:
   	   ret = 17;

     return ret;

   break;

   case 20:
   	   ret = 14;

     return ret;

   break;

   case 21:
   	   ret = 12;

     return ret;

   break;





  }




}
  
  

