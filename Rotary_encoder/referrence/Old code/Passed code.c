#define CLK 2
#define DT 3
#define SW 4

volatile byte read_portD = 0;
volatile byte prev_portD = 0;
volatile int motion = 0; //clockwise = +1, a.clockwise = -1, unknown = 0
const byte CW[4] = {11,2,4,13};
const byte ACW[4] = {7,1,8,14};
volatile byte seq = 0;
volatile byte knob_ticks = 0;


void setup() {
  PORTD = PORTD | 0b00001100; //set pin 2(CLK) and 3(DT) as input
  Serial.begin(9600);

  //update the state of DT and CLK and print the state value
  read_portD = (PIND & 0b00001100) >> 2;
  Serial.println(read_portD);
  prev_portD = read_portD;
}

void loop() {
  read_portD = read_portD | (PIND & 0b00001100);

  if(prev_portD != read_portD){
    /*This statemnent to search for start point*/
    if( (read_portD & 0b00000011) == 0b00000011 ){
      /*This statemnent to determine the turning direction of the knob*/
      switch( (read_portD & 0b00001100) >> 2 ){
        case 1: motion = -1; Serial.print("A.CW "); break;
        case 2: motion = 1; Serial.print("CW "); break;
        default: motion = 0; Serial.print("NOT TURNING "); break;
        }
    }

//another possible way
switch(seq){
			case 0: if(read_portD ==  7)  || (read_portD == 11) ) seq++; break;
			case 1: if(read_portD ==  1)  || (read_portD ==  2) ) seq++; break;
			case 2: if(read_portD ==  8)  || (read_portD ==  4) ) seq++; break;
			case 3: if(read_portD == 14)  || (read_portD == 13) ) seq++; break;
			default: break;
		}

    if ( (read_portD == CW[seq]) || (read_portD == ACW[seq]) ){
      seq++;
      Serial.print("sequence:");
      Serial.print(seq);
      Serial.print(" ");

      if(seq == 4){
        seq = 0;
        knob_ticks = knob_ticks + motion;
        Serial.print("knob_ticks:");
        Serial.print(knob_ticks);
        Serial.print(" ");
      }
      
    }
    Serial.print(read_portD);
    Serial.print(" , ");
    Serial.println(prev_portD);
    
  }
  
  prev_portD = read_portD; //save the last read value
  read_portD = read_portD >> 2; //This is to shift the previous state read to the 2 LSB.
  
}